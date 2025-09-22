/*
 * SYS_FSM_INF.h
 *
 *  Created on: 2022.11.7.
 *      Author: xj8r1j
 */

#ifndef _SYS_FSM_INF_H
#define _SYS_FSM_INF_H
#include "SVC/FSM/BSW_FSM_CORE.h"

typedef enum PWR_FSM_MODE_CMD_TAG
{
    STANDBY_CMD = 0,
    BUCK_CMD,
    MAX_CMD,
}PWR_FSM_MODE_CMD_EM;

typedef enum MDCCDC_HW_WAKEUP_STS_TAG
{
    MDCDC_HW_WAKEUP_INVALID = 0,
    MDCDC_HW_WAKEUP_VALID,
}MDCCDC_HW_WAKEUP_STS_EM;
extern MDCCDC_HW_WAKEUP_STS_EM emMDCDC_HW_WAKEUP_STS;

typedef enum MDCCDC_HW_ON_OFF_CMD_TAG
{
    MDCDC_HW_ON_CMD = 0,
    MDCDC_HW_OFF_CMD,
}MDCDC_HW_ON_OFF_CMD_EM;

typedef enum MDCCDC_CAN_ON_OFF_CMD_TAG
{
    MDCDC_CAN_DEFAULT_CMD  = 0x00,
    MDCDC_CAN_STANDBY_CMD  = 0x01,
    MDCDC_CAN_ON_CMD       = 0x55,
    MDCDC_CAN_OFF_CMD      = 0xAA,
}MDCDC_CAN_ON_OFF_CMD_EM;

typedef enum
{
    SLEEP_MODE = 0,
    INIT_MODE,
    STANDBY_MODE ,
    CONST_V_MODE,
    CONST_I_MODE,
    FAULT_MODE,
    BOOT_MODE
}MDCDC_WORK_STS_EM;

typedef struct
{
    MDCDC_WORK_STS_EM        emMdcdcWorkMode;
    PWR_FSM_MODE_CMD_EM      emDCDCWorkCmd;
    MDCCDC_HW_WAKEUP_STS_EM  emMDCDC_HW_WakeSts;
    UINT16                   u16ReportSysFsm;
	//UINT16                   u16DCDCFaultClrCmd;
	UINT16                   u16PwrFsmReq;
	UINT16                   u16DiagStoreCnt;
}SYS_FSM_OUT_T;
extern SYS_FSM_OUT_T g_stSysFsmOut;
extern fsm_obj_t     fsm_obj_SYS_FSM;

#define u16_get_diag_store_cnt()         g_stSysFsmOut.u16DiagStoreCnt
#define en_get_wakeup_sts()              g_stSysFsmOut.emMDCDC_HW_WakeSts
#define get_mdcdc_work_mode()            g_stSysFsmOut.emMdcdcWorkMode
#define get_mdcdc_hw_onoff_cmd()         (GPIO_ReadPin_EX_HW_ONOFF_CMD())//
#define get_mdcdc_pwr_sts_req_cmd()      (g_stSysFsmOut.emDCDCWorkCmd)
//#define u16_get_DCDC_faultClr_cmd()      (g_stSysFsmOut.u16LLCFaultClrCmd)
#define u16_get_sys_status()             (fsm_obj_SYS_FSM.u8CurStateId)
#define u16_get_pwr_fsm_req()            g_stSysFsmOut.u16PwrFsmReq

#endif /* ASW_SYSFSM_SYS_FSM_TEST_INTF_H_ */
