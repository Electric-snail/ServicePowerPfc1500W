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
#define LLC_PRI_EPWM_OFF()   do{EALLOW; p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->TZFRC.bit.OST = 1;EDIS;}while(0)

#define LLC_PRI_EPWM_ON()    do{EALLOW; p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->TZCLR.bit.OST = 1;\
                                      p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->TZOSTCLR.bit.OST1 = 1;EDIS;}while(0)
#else

typedef struct {
	UINT16 u16Enable;
	UINT16 u16PeriodCnt;
	UINT16 u16DutyCnt;
	UINT16 u16PhaseCnt;
}SIM_PWM_T;

typedef struct {
	UINT16 u16Enable;
	UINT16 u16PeriodHrCnt;
	UINT16 u16DutyHrCnt;
	UINT16 u16PhaseHrCnt;
}SIM_HRPWM_T;

extern SIM_PWM_T g_stEpwm3;

#define LLC_PRI_EPWM_OFF()      g_stEpwm3.u16Enable = 0
#define LLC_PRI_EPWM_ON()		g_stEpwm3.u16Enable = 1

#endif

#endif /* BSW_HAL_PWM_H_ */

