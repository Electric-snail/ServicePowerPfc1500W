/*
 *
 *  Created on: 2022.9.19.
 *      Author: x
 */
#ifndef POWER_FSM_H_
#define POWER_FSM_H_

#include "SVC/FSM/BSW_FSM_CORE.h"


#define			PWR_STATUS_STANDBY                    0
#define 		PWR_STATUS_SOFTSTART                  1
#define 		PWR_STATUS_RUN                        2
#define 		PWR_STATUS_FAULT                      3

#define 		PWR_PRE_CHG_CMP							1
#define 		PWR_SOFTSTART_CMP						2
#define 		PWR_SOFTSTART_REQ_EVEN                  3
#define 		PWR_FAULT_EVEN							4
#define 		PWR_FAULT_CLR_EVEN						5

#define 		CONTROLLER_RUN_ON						1

typedef struct {
	unsigned short u16CtrCmd;
	float f32VpfcSet;
}POWER_FSM_OUT_T;


extern		fsm_obj_t			fsm_obj_POWER_FSM;

extern		POWER_FSM_OUT_T		g_stPwrFsmOut;

#define 		u16_get_controller_cmd()         		g_stPwrFsmOut.u16CtrCmd
#define         f32_get_vpfc_set()						g_stPwrFsmOut.f32VpfcSet			

#define 		u16_get_pwr_status()             		(fsm_obj_POWER_FSM.u8CurStateId)

extern void power_fsm_init(void);
extern void power_fsm_1ms_task(void);

#endif /* POWER_FSM_H_ */
