/*
 * SYS_FSM_INF.h
 *
 *  Created on: 2022.11.7.
 *      Author: xj8r1j
 */

#ifndef _SYS_FSM_INF_H
#define _SYS_FSM_INF_H
#include "SVC/FSM/BSW_FSM_CORE.h"

#define   INVALID_MODE                          0
#define   GRID_ON_MODE							1
#define   CHARGE_MODE                           2
#define   GRID_OFF_MODE                         3

typedef struct
{
	UINT16                u16WorkModeSet;
}SYS_FSM_OUT_T;
extern SYS_FSM_OUT_T g_stSysFsmOut;
extern fsm_obj_t     fsm_obj_SYS_FSM;

#define u16_get_work_mode_set()             CHARGE_MODE  //(g_stSysFsmOut.u16WorkModeSet)
#endif /* ASW_SYSFSM_SYS_FSM_TEST_INTF_H_ */
