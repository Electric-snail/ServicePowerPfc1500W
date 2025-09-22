/*
 *
 *  Created on: 2022.9.19.
 *      Author: x
 */
#ifndef POWER_FSM_H_
#define POWER_FSM_H_

#include "SVC/FSM/BSW_FSM_CORE.h"

#define PWR_STATUS_STOP                            0
#define PWR_STATUS_SOFT                            1
#define PWR_STATUS_RUN                              2


#define PWR_STANDBY_EVEN                        1
#define PWR_CLRHWFAULT_EVEN                 2
#define PWR_SELFTEST_EVEN                       3
#define PWR_SOFTSTART_EVEN                    4
#define PWR_BUCKRUN_EVEN                       5
#define PWR_FAULT_EVEN                              6

typedef struct{

}POWER_FSM_OUT_T;

extern fsm_obj_t     fsm_obj_POWER_FSM;
extern UINT16        g_u16WorkRequest_Sys_bak;

#define u16_get_pwr_status()             (fsm_obj_POWER_FSM.u8CurStateId)

extern void power_fsm_init(void);
extern void power_fsm_2ms_task(void);

#endif /* POWER_FSM_H_ */
