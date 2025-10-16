                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   /*********************************************************************
File name:       BSW_ISR_ADC.c 
Purpose :         Read the value from ADC registers  respectively

Copyright Notice:
 *  Created on:
 *      Author:
**********************************************************************/
#include "DF_MATH.H"
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#ifndef  DLLX64
#include "CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL_INC/BSW_MCAL_PWM.h"
#include "MCAL_INC/BSW_MCAL_GPIO.h"
#endif

#if(DB_TOOL_ENABLE == TRUE)
#include "DEBUG_PLATFORM/PARAMETER_CTRL/PARAMETER.H"
#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE.H"
#include "DEBUG_PLATFORM/SFRA/SFRA.H"
#endif

#include "HAL_INC/BSW_HAL_PWM.h"
#include "HAL_INC/BSW_HAL_ADC.h"
#include "HAL_INC/BSW_HAL_GPIO.h"
#include "HAL_INC/BSW_HAL_TIMER.h"
#include "ISR_INC/BSW_ISR_ADC.h"
//#include "ASW_BASIC.h"
#include "SYS_FSM/SYS_FSM_INF.h"
#include "DIAGNOSTIC/DIAGNOSTIC_INF.h"
#include "SVC/TASK/BSW_TASK_SERVICE.h"
#include "PFC_CTR/PFC_CTR.H"
#include "POWER_FSM/POWER_FSM.H"

#ifndef  DLLX64
#pragma  CODE_SECTION(adcA1ISR, ".TI.ramfunc");
#endif


#define        ADC_INT1                  					(1 << 0)
#define       LOOP_INVALID_MODE              0
#define     	LOOP_OPEN_MODE                   1
#define       LOOP_CLOSE_MODE 				  2


#if(ISR_CPU_LOAD_TEST == 1)
ISR_EXE_VAR_ENTITY(ADCA1_ISR)
#endif

/*********variable declaration region *************************************/


/************ Variable definition region *********************************/
volatile ANA_PHY_VALUE_T 	g_stAnaPhyRaw = { 0 };
volatile ANA_PHY_VALUE_T 	g_stAnaPhyLpf = { 0 };
unsigned short   g_u16LoopWorkMode =  LOOP_INVALID_MODE;
float                    g_f32OpenDuty = 0.0f;

__interrupt void adcA1ISR(void)
{
            float 		f32VinL,		f32VinN,		f32Vpfc,			f32CurInductorAveH, 			f32CurInductorAveL,		f32IinL,		f32IinH;

            float       f32Duty;

            UINT16 		u16PwmSwitch = 0,    u16PwmCounter  = 0;

			#if(TASK_CPU_LOAD_TEST == 1)
			 UINT16 u16TaskTestTimerStatus = GetTaskTestTimerStatus();
			 StopTaskTestTimer();
			#elif(ISR_CPU_LOAD_TEST == 1)
			 ResetTaskTestTimer();
			#endif

			f32VinL 						= bsw_hal_calc_vin_l();

			f32VinN 						= bsw_hal_calc_vin_n();

			f32Vpfc 						=	 bsw_hal_calc_vpfc();

			f32CurInductorAveH = bsw_hal_calc_cur_inductor_ave_h();

			f32CurInductorAveL = bsw_hal_calc_cur_inductor_ave_l();

			f32IinL 						= bsw_hal_calc_iin_l();

			f32IinH 						= bsw_hal_calc_iin_h();

			#if(PARAM_CALIB_ENABLE == 1)
			//0~10£º low;  10-40 high
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
				   g_stAnaPhyRaw.f32IlAveH 	= f32CurInductorAveH;
				   g_stAnaPhyRaw.f32VinL 		= f32VinL;
				   g_stAnaPhyRaw.f32VinN 		= f32VinN;
				   g_stAnaPhyRaw.f32Vpfc		= f32Vpfc;
				   g_stAnaPhyRaw.f32IinL        = f32IinL;
				   g_stAnaPhyRaw.f32IinH        = f32IinH;
			#endif

			g_stAnaPhyRaw.f32Vin = 	   g_stAnaPhyRaw.f32VinL -  g_stAnaPhyRaw.f32VinN;

			if(g_stAnaPhyRaw.f32IlAveL  > 2.0f)
				g_stAnaPhyRaw.f32IlAve  =g_stAnaPhyRaw.f32IlAveH;
			else
				g_stAnaPhyRaw.f32IlAve  =g_stAnaPhyRaw.f32IlAveL;

			if(g_stAnaPhyRaw.f32IinL  > 2.0f)
				g_stAnaPhyRaw.f32Iin  =g_stAnaPhyRaw.f32IinL;
			else
				g_stAnaPhyRaw.f32Iin  =g_stAnaPhyRaw.f32IinH;

			LPF(g_stAnaPhyRaw.f32Vin,   	g_stAnaPhyLpf.f32Vin,   			5000.0f,    		(float)(CTR_PERIOD * 0.000001f));

			LPF(g_stAnaPhyRaw.f32Iin,   		g_stAnaPhyLpf.f32Iin,   			1000.0f,    		(float)(CTR_PERIOD * 0.000001f));

			fast_diagnostic_task();


			if((g_u16LoopWorkMode  == LOOP_OPEN_MODE)&&(u16_get_auto_recv_diag() == 0x0000) && (u16_get_no_recv_diag() == 0x0000)){
					 f32Duty     			=  g_f32OpenDuty;
					 u16PwmSwitch 	= 1;
			}

			if(g_u16LoopWorkMode  == LOOP_CLOSE_MODE){
					 if ((u16_get_auto_recv_diag() == 0x0000) && (u16_get_no_recv_diag() == 0x0000)&&(u16_get_controller_cmd() == CONTROLLER_RUN_ON)) {
					     pfc_controller();
					     f32Duty 				= f32_get_pwm_duty();
						 u16PwmSwitch 	= 1;
					}else{
						pfc_controller_init();
						f32Duty 					= 0;
						 u16PwmSwitch 	= 0;
					}
			}

			if(u16PwmSwitch == 1){
				   set_pfc_pwm_duty(f32Duty,   u16PwmCounter);
				   pfc_drv_turn_on();
			}else{
				   pfc_drv_turn_off();
			}

			#if (DB_TOOL_ENABLE == TRUE)
				#define GEN_SW_SCOPE_ISR_CALL
				#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
				#undef GEN_SW_SCOPE_ISR_CALL
			#endif

			#if(TASK_CPU_LOAD_TEST == 1)
				ReloadTaskTestTimerStatus(u16TaskTestTimerStatus);
			#elif(ISR_CPU_LOAD_TEST == 1)
				ISR_EXE_VAR_CALL(ADCA1_ISR);
			#endif

			//Clear the interrupt flag
			 #ifndef DLLX64
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



