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

#ifndef  DLLX64
#pragma  CODE_SECTION(adcA1ISR, ".TI.ramfunc");
#pragma  DATA_SECTION(g_stAnaPhyRaw, 		".CtrlVariableSector");
#pragma  DATA_SECTION(gs_stSogi, 					".CtrlVariableSector");
#pragma  DATA_SECTION(gs_stVpfcNotchFilt, ".CtrlVariableSector");
#pragma  DATA_SECTION(gs_stOrthPll, 			".CtrlVariableSector");
#endif


#define        ADC_INT1                  						 (1 << 0)


#if(ISR_CPU_LOAD_TEST == 1)
ISR_EXE_VAR_ENTITY(ADCA1_ISR)
#endif

/*********variable declaration region *************************************/


/************ Variable definition region *********************************/
volatile ANA_PHY_VALUE_T 		g_stAnaPhyRaw;
volatile SOGI_OBJ_T   					gs_stSogi;
volatile NOTCH_OBJ_2TH_T	    gs_stVpfcNotchFilt;
volatile ORTH_PLL_OBJ_T  		    gs_stOrthPll;

volatile float                  		g_f32VpfcIsrLpf = 0.0f;
unsigned short				         g_u16PllFirstStart  = 1;
volatile unsigned short         g_u16FaultDetetFlag = 0;
unsigned short						g_u16LoopWorkMode =  LOOP_INVALID_MODE;
float										g_f32OpenDuty = 0.0f;
void adc_isr_init(void)
{
	gs_stSogi.stCoff.f32Kp = 1.414f;
	gs_stSogi.stCoff.u8Ena2nd = 0;   //���׽�ֹ
	gs_stSogi.stCoff.f32Ts = CTR_PERIOD;
	gs_stSogi.stInter.f32IntegOut = 0.0f;
	gs_stSogi.stInter.f32IntegOutQ = 0.0f;
	gs_stSogi.stInter.f32IntegOut2nd = 0.0f;
	gs_stSogi.stInter.f32IntegOut2ndQ = 0.0f;
	sogi_set_freq_1p(&gs_stSogi, 50.0f);

	gs_stOrthPll.stCoff.f32CosOmegT = 0.99998832001792715673006690787073f;
	gs_stOrthPll.stCoff.f32SinOmegT = 0.00483320056729547671334289638923f;
	gs_stOrthPll.stCoff.f32OutMax = 425.0f;
	gs_stOrthPll.stCoff.f32Kp = 0.001f;


	gs_stVpfcNotchFilt.stOut.f32Out = 0;
	gs_stVpfcNotchFilt.stCoff.f32Sin1OmegT = 0.00483320056729547671334289638923f;   		//Sin(2*pi*50/fs)
	gs_stVpfcNotchFilt.stCoff.f32Cos1OmegT = 0.99998832001792715673006690787073f;   		//Cos(2*pi*50/fs)
	gs_stVpfcNotchFilt.stCoff.f32Sin2OmegT = 0.00966628823119899249250527769323f;   		//Sin(2*pi*100/fs)
	gs_stVpfcNotchFilt.stCoff.f32Cos2OmegT = 0.99995328034455258936414796865385f;   		//Cos(2*pi*100/fs)
	gs_stVpfcNotchFilt.stCoff.f32Width0 = 0.001;
	gs_stVpfcNotchFilt.stCoff.f32Width1 = 0.0083;
	//gs_stVpfcNotchFilt.stCoff.f32Width1 = 0.00f;
	gs_stVpfcNotchFilt.stCoff.f32Width2 = 0.0167;

	gs_stVpfcNotchFilt.stInner.f32Out0thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Out0thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Out1thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Out1thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Out2thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Out2thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict0thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict0thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict1thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict1thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict2thX = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32OutPredict2thY = 0.0f;
	gs_stVpfcNotchFilt.stInner.f32Err = 0.0f;

	g_stAnaPhyRaw.f32Iin					= 0.0f;
	g_stAnaPhyRaw.f32IinH					= 0.0f;
	g_stAnaPhyRaw.f32IinL					= 0.0f;
	g_stAnaPhyRaw.f32IlAve					= 0.0f;
	g_stAnaPhyRaw.f32IlAveH					= 0.0f;
	g_stAnaPhyRaw.f32IlAveL					= 0.0f;
	g_stAnaPhyRaw.f32Vin					= 0.0f;
	g_stAnaPhyRaw.f32VinL					= 0.0f;
	g_stAnaPhyRaw.f32VinN					= 0.0f;
}

INTERRUPT void adcA1ISR(void)
{
            float 		f32VinL,		f32VinN,		f32Vpfc,			f32CurInductorAveH, 			f32CurInductorAveL,		f32IinL,		f32IinH;

            float       f32Duty;

            UINT16 		u16PwmSwitch,    u16PwmCounter;

			//����CPU load ������ִ��ʱ��ʱʹ��
			#if(TASK_CPU_LOAD_TEST == 1)
			 UINT16 u16TaskTestTimerStatus = GetTaskTestTimerStatus();
			 StopTaskTestTimer();
			#elif(ISR_CPU_LOAD_TEST == 1)
			 ResetTaskTestTimer();
			#endif

			 //�����������ֵ.
			f32VinL 						= bsw_hal_calc_vin_l();
			f32VinN 						= bsw_hal_calc_vin_n();
			f32Vpfc 						=	 bsw_hal_calc_vpfc();
			f32CurInductorAveH				= bsw_hal_calc_cur_inductor_ave_h();
			f32CurInductorAveL				= bsw_hal_calc_cur_inductor_ave_l();
			f32IinL 						= bsw_hal_calc_iin_l();
			f32IinH 						= bsw_hal_calc_iin_h();

			//У׼��������ֵ
			#if(PARAM_CALIB_ENABLE == TRUE)
			//0~10�� low;  10-40 high
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

			//��L,N������ֵ��׼����Vin, ���ݲ����źŵĴ�С��ѡ���ź�ͨ��
			g_stAnaPhyRaw.f32Vin = 	   g_stAnaPhyRaw.f32VinL -  g_stAnaPhyRaw.f32VinN;

			if(g_stAnaPhyRaw.f32IlAveL  > 30.0f)
				g_stAnaPhyRaw.f32IlAve  =g_stAnaPhyRaw.f32IlAveH;
			else
				g_stAnaPhyRaw.f32IlAve  =g_stAnaPhyRaw.f32IlAveL;

			if(g_stAnaPhyRaw.f32IinL  > 30.0f)
				g_stAnaPhyRaw.f32Iin  = g_stAnaPhyRaw.f32IinH;
			else
				g_stAnaPhyRaw.f32Iin  = g_stAnaPhyRaw.f32IinL;

			//��VPFC��ѹ�����˲�����
			#if(NOTICH_FILT_ENABLE == TRUE)
						gs_stVpfcNotchFilt.stIn.f32In = g_stAnaPhyRaw.f32Vpfc;
						notch_filter_2th(&gs_stVpfcNotchFilt);
			#else

			#endif
			LPF(g_f32VpfcIsrLpf, g_stAnaPhyRaw.f32Vpfc, 1.0f, (float)CTR_PERIOD);
			//�������ѹ�������໷
			gs_stOrthPll.stIn.f32SigIn = g_stAnaPhyRaw.f32Vin;
			if (g_u16PllFirstStart == 1)
			{
				gs_stOrthPll.stOut.f32SigAlpha = g_stAnaPhyRaw.f32Vin;
				gs_stOrthPll.stOut.f32SigBeta = 0.0f;
				g_u16PllFirstStart = 0;
			}
			orth_pll_proc_1p(&gs_stOrthPll);

			//ִ����Ҫ���ж�ִ�е�MEASURE������
			measure_fast_task();

			//ִ�п��ٱ�������
			diagnostic_fast_task();

			//�ж��Ƿ��й��Ϸ�����ͳһ�������ж�
		 if ((u16_get_auto_recv_diag() != 0x0000)|| (u16_get_no_recv_diag() != 0x0000)){
				g_u16FaultDetetFlag = 1;
			}

			//����ģʽ�����п�����
			if((g_u16LoopWorkMode  == LOOP_OPEN_MODE)&& (g_u16FaultDetetFlag == 0)&&(u16_get_controller_cmd() == 1)){
					 f32Duty        			=  g_f32OpenDuty;
					 u16PwmSwitch 	= 1;
			}else if(g_u16LoopWorkMode 	>  LOOP_OPEN_MODE) {
					 if ((g_u16FaultDetetFlag == 0)&&(u16_get_controller_cmd() == 1)) {
					     pfc_controller();
					     f32Duty 		= f32_get_pwm_duty();
						 u16PwmSwitch 	= 1;
					}else{
						pfc_controller_init();
						f32Duty 					= 0;
						 u16PwmSwitch 	= 0;
					}
			}else{
				 u16PwmSwitch 	= 0;
			}

			//���ݻ�·���н��,����PWMģ��
			if(u16PwmSwitch == 1){
				   set_pfc_pwm_duty(f32Duty,   u16PwmCounter);
				   pfc_drv_turn_on();
			}else{
				   pfc_drv_turn_off();
			}

			 #ifndef DLLX64
				//�������ʾ��������
				#define GEN_SW_SCOPE_ISR_CALL
				#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
				#undef GEN_SW_SCOPE_ISR_CALL

				//����CPUload ������ִ��ʱ����Ժ���.
				#if(TASK_CPU_LOAD_TEST == 1)
					ReloadTaskTestTimerStatus(u16TaskTestTimerStatus);
				#elif(ISR_CPU_LOAD_TEST == 1)
					ISR_EXE_VAR_CALL(ADCA1_ISR);
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



