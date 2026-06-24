/*
 * SysFsm.h
 *
 *  Created on: 2022.9.19.
 *      Author: xj8r1j
 */

#ifndef _SYS_FSM_H_
#define _SYS_FSM_H_


#define  BOOT_CHECK_STATUS        0
#define  BOOT_WAIT_STATUS         1
#define  BOOT_UPDATA_STATUS       2

extern void sys_fsm_init(void);

extern void sys_fsm_5ms_task(void);

extern unsigned short g_u16SysFsmStatus;

#define  u16_get_sys_fsm_status()        g_u16SysFsmStatus

#endif /* USER_APP_APP_SYSFSM_SYSFSM_H_ */
