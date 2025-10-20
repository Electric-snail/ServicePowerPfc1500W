/*
 * SysFsm.h
 *
 *  Created on: 2022.9.19.
 *      Author: xj8r1j
 */

#ifndef _SYS_FSM_H_
#define _SYS_FSM_H_

#include "FSM/BSW_FSM_CORE.h"

#define STANDBY_RQT_EVEN              0
#define BUCK_CONST_V_RQT_EVEN         1
#define BUCK_CONST_I_RQT_EVEN         2
#define FAULT_EVEN                    3
#define SLEEP_RQT_EVEN                4
#define BOOTLOADER_RQT_EVEN           5


#define SYS_STATUS_INIT               0
#define SYS_STATUS_STANDBY            1
#define SYS_STATUS_BUCK_CONST_V       2
#define SYS_STATUS_BUCK_CONST_I       3
#define SYS_STATUS_FAULT              4
#define SYS_STATUS_SLEEP              5
#define SYS_STATUS_BOOTLOADER         6

#define SYS_STATUS_INVALID            0xFF

extern void sys_fsm_init(void);
extern void sys_fsm_5ms_task(void);
#endif /* USER_APP_APP_SYSFSM_SYSFSM_H_ */
