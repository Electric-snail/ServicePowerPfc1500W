                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   /*********************************************************************
File name:       BSW_ISR_ADC.c 
Purpose :         Read the value from ADC registers  respectively

Copyright Notice:
 *  Created on:
 *      Author:
**********************************************************************/
#include "PUBLIC_INC/DF_MATH.H"
#include "SOFTWARE_ENV_CFG.h"

#ifndef  DLLX64
#include "CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL_INC/BSW_MCAL_PWM.h"
#include "MCAL_INC/BSW_MCAL_GPIO.h"
#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE.H"
#include "DEBUG_PLATFORM/SFRA/SFRA.H"
#include "DEBUG_PLATFORM/PERFORMACE_TEST/PERFORMACE_TEST.H"
#endif

#include "HAL_INC/BSW_HAL_PWM.h"
#include "HAL_INC/BSW_HAL_ADC.h"
#include "HAL_INC/BSW_HAL_GPIO.h"
#include "HAL_INC/BSW_HAL_TIMER.h"
#include "ISR_INC/BSW_ISR_ADC.h"
#include "DIAGNOSTIC/DIAGNOSTIC.h"
#include "MEASURE/MEASURE.H"
#include "PFC_CTR/PFC_CTR.H"
#include "POWER_FSM/POWER_FSM.h"

#if(ISR_CPU_LOAD_TEST == 1)
ISR_EXE_VAR_ENTITY(adcA1ISR)
#endif

#ifndef  DLLX64
#pragma  CODE_SECTION(adcA1ISR, 				".TI.ramfunc");
#pragma  DATA_SECTION(g_stAnaPhyRaw, 		".CtrlVariableSector");
//#pragma  DATA_SECTION(gs_stSogi, 					".CtrlVariableSector");
#pragma  DATA_SECTION(gs_stVpfcNotchFilt, ".CtrlVariableSector");
#pragma  DATA_SECTION(gs_stOrthPll, 			".CtrlVariableSector");
#endif


#define        ADC_INT1                  						 (1 << 0)
/*********variable declaration region *************************************/


/************ Variable definition region *********************************/
volatile ANA_PHY_VALUE_T 		g_stAnaPhyRaw;
//volatile SOGI_OBJ_T   					gs_stSogi;
//volatile NOTCH_OBJ_2TH_T	    gs_stVpfcNotchFilt;
volatile NOTCH_OBJ_T	    		gs_stVpfcNotchFilt;

volatile ORTH_PLL_OBJ_T  		    gs_stOrthPll;

volatile float                  		g_f32VpfcIsrLpf = 0.0f;
unsigned short				         g_u16PllFirstStart;
volatile unsigned short         g_u16FaultDetetFlag = 0;
unsigned short						g_u16LoopWorkMode =  LOOP_INVALID_MODE;
float										g_f32OpenDuty = 0.0f;

void adc_isr_init(void)
{
/*	gs_stSogi.stCoff.f32Kp = 1.414f;
	gs_stSogi.stCoff.u8Ena2nd = 0;   //二阶禁止
	gs_stSogi.stCoff.f32Ts = CTR_PERIOD;
	gs_stSogi.stInter.f32IntegOut = 0.0f;
	gs_stSogi.stInter.f32IntegOutQ = 0.0f;
	gs_stSogi.stInter.f32IntegOut2nd = 0.0f;
	gs_stSogi.stInter.f32IntegOut2ndQ = 0.0f;
	sogi_set_freq_1p(&gs_stSogi, 50.0f);*/

	gs_stOrthPll.stCoff.f32CosOmegT = 0.99998832001792715673006690787073f;
	gs_stOrthPll.stCoff.f32SinOmegT = 0.00483320056729547671334289638923f;
	gs_stOrthPll.stCoff.f32OutMax 	  = 425.0f;
	gs_stOrthPll.stCoff.f32Kp             = 0.01f;


	gs_stVpfcNotchFilt.stOut.f32Out = 0;
	gs_stVpfcNotchFilt.stCoff.f32Sin1OmegT = 0.00966628823119899249250527769323f;   		//Sin(2*pi*100/fs)
	gs_stVpfcNotchFilt.stCoff.f32Cos1OmegT = 0.99995328034455258936414796865385f;   		//Cos(2*pi*100/fs)
	gs_stVpfcNotchFilt.stCoff.f32Width0 = 0.001;
	gs_stVpfcNotchFilt.stCoff.f32Width1 = 0.0083f;

	gs_stVpfcNotchFilt.stInner.f32Out0thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Out0thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Out1thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Out1thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict0thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict0thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict1thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict1thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Err 					  = 0.0f;

	g_stAnaPhyRaw.f32Iin									 = 0.0f;
	g_stAnaPhyRaw.f32IinH									 = 0.0f;
	g_stAnaPhyRaw.f32IinL									 = 0.0f;
	g_stAnaPhyRaw.f32IlAve								 = 0.0f;
	g_stAnaPhyRaw.f32IlAveH								 = 0.0f;
	g_stAnaPhyRaw.f32IlAveL								= 0.0f;
	g_stAnaPhyRaw.f32Vin									= 0.0f;
	g_stAnaPhyRaw.f32VinL									= 0.0f;
	g_stAnaPhyRaw.f32VinN								= 0.0f;
	g_u16PllFirstStart                                           = 1;
}

//The run time is 8.5us
INTERRUPT void adcA1ISR(void)
{
            float 		f32VinL,		f32VinN,		f32Vpfc,			f32CurInductorAveH, 			f32CurInductorAveL,		f32IinL,		f32IinH;

            float       f32Duty;

            UINT16 	u16PwmCounter;

			//测试CPU load 和任务执行时间时使用
			#if(TASK_CPU_LOAD_TEST == 1)
			 UINT16 u16TaskTestTimerStatus = get_performace_test_timer_status();
			 stop_performace_test_timer();
			#elif(ISR_CPU_LOAD_TEST == 1)
			 reset_performace_test_timer();
			#endif

			 //计算各个采样值.
			f32VinL 							= bsw_hal_calc_vin_l();
			f32VinN 							= bsw_hal_calc_vin_n();
			f32Vpfc 							=	 bsw_hal_calc_vpfc();
			f32CurInductorAveH		= bsw_hal_calc_cur_inductor_ave_h();
			f32CurInductorAveL		= bsw_hal_calc_cur_inductor_ave_l();
			f32IinL 							= bsw_hal_calc_iin_l();
			f32IinH 							= bsw_hal_calc_iin_h();

			//校准各个采样值
			#if(PARAM_CALIB_ENABLE == TRUE)
			//0~10： low;  10-40 high
				   f32CalibK 		= (float)i16_get_param_calib_k(IL_CALIB_L)*0.00390625f;
				   f32CalibOffset	= (float)i16_get_param_calib_offset(IL_CALIB_L)*0.00390625f;
				   g_stAnaPhyRaw.f32IlAveL = f32CurInductorAveTempL * f32CalibK + f32CalibOffset;

				   f32CalibK 		= (float)i16_get_param_calib_k(IL_CALIB_H)*0.00390625f;
				   f32CalibOffset	= (float)i16_get_param_calib_offset(IL_CALIB_H)*0.00390625f;
				   g_stAnaPhyRaw.f32IlAveH = f32CurInductorAveTempH * f32CalibK + f32CalibOffset;

				   f32CalibK 		= (float)i16_get_param_calib_k(VIN_L_CALI)*0.00390625f;
				   f32CalibOffset	= (float)i16_get_param_calib_offset(VIN_L_CALI)*0.00390625f;
				   g_stAnaPhyRaw.f32VinL = f32VinL * f32CalibK + f32CalibOffset;

				   f32CalibK 		= (float)i16_get_param_calib_k(VIN_N_CALI)*0.00390625f;
				   f32CalibOffset	= (float)i16_get_param_calib_offset(VIN_N_CALI)*0.00390625f;
				   g_stAnaPhyRaw.f32VinN= f32VinN * f32CalibK + f32CalibOffset;

				   f32CalibK 		= (float)i16_get_param_calib_k(VPFC_CALI)*0.00390625f;
				   f32CalibOffset	= (float)i16_get_param_calib_offset(VPFC_CALI)*0.00390625f;
				   g_stAnaPhyRaw.f32Vpfc= f32Vpfc * f32CalibK + f32CalibOffset;

				   f32CalibK 			= (float)i16_get_param_calib_k(IIN_L_CALI)*0.00390625f;
				   f32CalibOffset	= (float)i16_get_param_calib_offset(IIN_L_CALI)*0.00390625f;
				   g_stAnaPhyRaw.f32IinL		= f32IinL * f32CalibK + f32CalibOffset;

				   f32CalibK 			= (float)i16_get_param_calib_k(IIN_H_CALI)*0.00390625f;
				   f32CalibOffset	= (float)i16_get_param_calib_offset(IIN_H_CALI)*0.00390625f;
				   g_stAnaPhyRaw.f32IinH		= f32IinH * f32CalibK + f32CalibOffset;
			#else
				   g_stAnaPhyRaw.f32IlAveL  	= f32CurInductorAveL;
				   g_stAnaPhyRaw.f32IlAveH 	    = f32CurInductorAveH;
				   g_stAnaPhyRaw.f32VinL 		= f32VinL;
				   g_stAnaPhyRaw.f32VinN 		= f32VinN;
				   g_stAnaPhyRaw.f32Vpfc		= f32Vpfc;
				   g_stAnaPhyRaw.f32IinL        = f32IinL;
				   g_stAnaPhyRaw.f32IinH        = f32IinH;
			#endif

			//将L,N各采样值，准换成Vin, 根据采样信号的大小，选择信号通道
			g_stAnaPhyRaw.f32Vin = 	   g_stAnaPhyRaw.f32VinL -  g_stAnaPhyRaw.f32VinN;

			if(g_stAnaPhyRaw.f32IlAveL  > 30.0f)
				g_stAnaPhyRaw.f32IlAve  =g_stAnaPhyRaw.f32IlAveH;
			else
				g_stAnaPhyRaw.f32IlAve  =g_stAnaPhyRaw.f32IlAveL;

			if(g_stAnaPhyRaw.f32IinL  > 30.0f)
				g_stAnaPhyRaw.f32Iin  = g_stAnaPhyRaw.f32IinH;
			else
				g_stAnaPhyRaw.f32Iin  = g_stAnaPhyRaw.f32IinL;

			LPF(g_f32VpfcIsrLpf, g_stAnaPhyRaw.f32Vpfc, 5000.0f, (float)CTR_PERIOD);
			//执行需要在中断执行的MEASURE的任务
			measure_fast_task();

			//对VPFC电压进行滤波处理
			if( u16_get_vin_type() == AC_TYPE){
					#if(NOTICH_FILT_ENABLE == TRUE)
					//	gs_stVpfcNotchFilt.stCoff.f32Cos1OmegT = 0.99995328034455258936414796865385f;   		//Cos(2*pi*100/fs)
					//	gs_stVpfcNotchFilt.stCoff.f32Sin1OmegT = 0.00966628823119899249250527769323f;   		//Sin(2*pi*100/fs)
						gs_stVpfcNotchFilt.stCoff.f32Cos1OmegT =   f32_get_vin_cos_2omgt();
						gs_stVpfcNotchFilt.stCoff.f32Sin1OmegT  =   f32_get_vin_sin_2omgt();
						gs_stVpfcNotchFilt.stIn.f32In 					    =    g_stAnaPhyRaw.f32Vpfc;
						notch_filter(&gs_stVpfcNotchFilt);
					#endif
					//对输入电压进行锁相环
					gs_stOrthPll.stIn.f32SigIn = g_stAnaPhyRaw.f32Vin;
					if (g_u16PllFirstStart == 1)
					{
						gs_stOrthPll.stOut.f32SigAlpha = g_stAnaPhyRaw.f32Vin;
						if(g_stAnaPhyRaw.f32Vin > 0){
							gs_stOrthPll.stOut.f32SigBeta   = -1.414f * f32_get_vin_rms();
						}else{
							gs_stOrthPll.stOut.f32SigBeta   = 1.414f * f32_get_vin_rms();
						}
						g_u16PllFirstStart = 0;
					}
					gs_stOrthPll.stCoff.f32CosOmegT =  f32_get_vin_cos_omgt();
					gs_stOrthPll.stCoff.f32SinOmegT =   f32_get_vin_sin_omgt();
				//	gs_stOrthPll.stCoff.f32CosOmegT =  0.999990539f;
				//	gs_stOrthPll.stCoff.f32SinOmegT =   0.004488344f;
					orth_pll_proc_1p(&gs_stOrthPll);
			}
			//执行快速保护任务
			diagnostic_fast_task();
			//根据模式，运行控制器
#if defined OPEN_LOOP_CTR
			if((g_u16FaultDetetFlag == 0)&&(u16_get_controller_cmd() == 1)){
					 f32Duty        			=  0.2;
					 u16PwmSwitch 	= 1;
			}

#elif (defined CLOSE_LOOP_CTR)||(defined IL_CLOSE_LOOP_MODE)
			 if ((g_u16FaultDetetFlag == 0)&&(u16_get_controller_cmd() == 1)) {
				 pfc_controller();
				 f32Duty 		        = f32_get_pwm_duty();
				 set_pfc_pwm_duty(f32Duty,   u16PwmCounter);
				 pfc_drv_turn_on();
			}else{
				BSW_HAL_ALERT_SET();
				pfc_controller_init();
				f32Duty 				= 0;
				 pfc_drv_turn_off();
			}
#endif
		 #ifndef DLLX64
			//调用软件示波器功能
			#define GEN_SW_SCOPE_ISR_CALL
			#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
			#undef GEN_SW_SCOPE_ISR_CALL

			//调用CPUload 和任务执行时间测试函数.
			#if(TASK_CPU_LOAD_TEST == 1)
				reload_performace_test_timer_status(u16TaskTestTimerStatus);
			#elif(ISR_CPU_LOAD_TEST == 1)
				ISR_EXE_VAR_CALL(adcA1ISR);
			#endif
				//Clear the interrupt flag
				AdcaRegs.ADCINTFLGCLR.all |= ADC_INT1;
				// Check if overflow has occurred
				 if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)       //ADCINT overflow occurred
				 {
					 AdcaRegs.ADCINTOVFCLR.all |= ADC_INT1 ;     //Clear overflow flag
					 AdcaRegs.ADCINTFLGCLR.all |= ADC_INT1 ;     //Re-clear ADCINT flag
				 }
				 PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
		 #endif
}



