/*
 * SysFsm.h
 *
 *  Created on: 2022.9.19.
 *      Author: xj8r1j
 */

#ifndef _SYS_FSM_H_
#define _SYS_FSM_H_

#include "FSM/BSW_FSM_CORE.h"
#include "SYS_FSM/SYS_FSM.h"

#define SYS_STATUS_INIT                          0
#define SYS_STATUS_STANDBY                 1
#define SYS_STATUS_ACTIVE                     2
#define SYS_STATUS_FAULT                       3
#define SYS_STATUS_SLEEP                       4
#define SYS_STATUS_BOOTLOADER         5

#define SYS_STATUS_INVALID                    0xFF

extern void sys_fsm_init(void);
extern void sys_fsm_5ms_task(void);
#endif /* USER_APP_APP_SYSFSM_SYSFSM_H_ */
