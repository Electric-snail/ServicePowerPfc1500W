/*
 * BSW_HAL_PWM.h
 *
 *  Created on: 2022/8/15
 *      Author: nj7vgg
 */

#ifndef BSW_HAL_PWM_H_
#define BSW_HAL_PWM_H_

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

#ifndef DLLX64
#include "MCAL/MCAL_INC/BSW_MCAL_PWM.h"
#define 	pfc_drv_turn_off()   																do{EALLOW; gp_stPwmChannel[PFC_PWM_CHANNEL]->TZFRC.bit.OST = 1;EDIS;}while(0)

#define 	pfc_drv_turn_on()    																do{EALLOW; gp_stPwmChannel[PFC_PWM_CHANNEL]->TZCLR.bit.OST = 1;EDIS;}while(0)

#define     set_pfc_pwm_duty(f32Duty,   u16CouterTemp)         			do{u16CouterTemp = (unsigned short)(f32Duty  * PFC_PWM_TBPRD);\
																											  	  	 gp_stPwmChannel[PFC_PWM_CHANNEL]->CMPA.bit.CMPA = u16CouterTemp; }while(0)

#define     read_pfc_drv_dcaevt2_flag()												    gp_stPwmChannel[PFC_PWM_CHANNEL]->TZFLG.bit.DCAEVT2
#define     clr_pfc_drv_deaevt2_flag()                                                  do{EALLOW; gp_stPwmChannel[PFC_PWM_CHANNEL]->TZCLR.bit.DCAEVT2 = 1;EDIS;}while(0)

#define     read_pfc_drv_dcaevt1_flag()												    gp_stPwmChannel[PFC_PWM_CHANNEL]->TZFLG.bit.DCAEVT2
#define     clr_pfc_drv_deaevt1_flag()                                                  do{EALLOW; gp_stPwmChannel[PFC_PWM_CHANNEL]->TZCLR.bit.DCAEVT1 = 0;\
																													gp_stPwmChannel[PFC_PWM_CHANNEL]->TZCLR.bit.OST = 1;EDIS;}while(0)

#else

typedef struct {
	UINT16 u16Enable;
	UINT16 u16PeriodCnt;
	UINT16 u16DutyCnt;
	UINT16 u16PhaseCnt;
}SIM_PWM_T;

extern SIM_PWM_T g_stEpwm1;

#define     read_pfc_drv_dcaevt2_flag()						0	
#define     clr_pfc_drv_deaevt2_flag()                       


#define 	pfc_drv_turn_off()   							g_stEpwm1.u16Enable = 0
 
#define 	pfc_drv_turn_on()    							g_stEpwm1.u16Enable = 1

#define     set_pfc_pwm_duty(f32Duty,   u16CouterTemp)      g_stEpwm1.u16DutyCnt = (unsigned short)(f32Duty  * PFC_PWM_TBPRD);


#endif

#endif /* BSW_HAL_PWM_H_ */

