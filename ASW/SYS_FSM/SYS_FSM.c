/*
 * SysFsm.c
 *
 *  Created on: 2022.9.19
 */
#include <PUBLIC_INC/MEM_HANDLE.H>
#include "HAL_INC/BSW_HAL_GPIO.h"
#include "HAL_INC/BSW_HAL_ADC.h"
#include "SVC/BSW_SVC_BASIC.h"
#include "ASW_BASIC.h"
#include "SYS_FSM/SYS_FSM.h"
#include "SYS_FSM/SYS_FSM_INF.h"
#include "POWER_FSM/POWER_FSM.h"
#include "MEASURE/MEASURE_INF.h"
#include "EXTERN_CAN_COMM/EXTERN_CAN_COMM_INF.h"
#include "DIAG_STORAGE_INFO/DIAG_STORAGE_INFO.h"
#include "DIAGNOSTIC/DIAGNOSTIC_INF.H"

#ifndef DLLX64
//#pragma DATA_SECTION(g_u32CLLCJumpBoot,".jumpboot");
#endif
//UINT32 g_u32CLLCJumpBoot;

/*******extern function declartion region ***********/
extern void ExitBoot(UINT32 EntryAddr);

/*******internal function declartion region ***********/
void  sys_init_in(void);
void  sys_init_exe(void);
UINT8 sys_init_cond(UINT16 u16TrigEven);

void  sys_standby_in(void);
void  sys_standby_exe(void);
UINT8 sys_standby_cond(UINT16 u16TrigEven);

void  sys_active_in(void);
void  sys_active_exe(void);
UINT8 sys_active_cond(UINT16 u16TrigEven);

void  sys_fault_in(void);
void  sys_fault_exe(void);
UINT8 sys_fault_cond(UINT16 u16TrigEven);

void  sys_bootloader_in(void);
void  sys_bootloader_exe(void);

void  sys_sleep_in(void);
void  sys_sleep_exe(void);

/************ Variable definition region *********************************/

//----------FSM name--------initial status id---------------------
REG_FSM_OBJ(SYS_FSM,        SYS_STATUS_INIT,\
//---fsm status id----------------------------fsm_in_func-------------fsm_exe_func-------------fsm_out_func--------------fsm_cond_func;
{SYS_STATUS_INIT,                       sys_init_in,                    sys_init_exe,                        NULL,                   sys_init_cond},\
{SYS_STATUS_STANDBY,              sys_standby_in, 	         sys_standby_exe,  		       NULL,          		    sys_standby_cond},\
{SYS_STATUS_ACTIVE,                 sys_active_in,                sys_active_exe,                    NULL,  		            sys_active_cond},\
{SYS_STATUS_FAULT,                   sys_fault_in,                  sys_fault_exe,                      NULL,   	            sys_fault_cond},\
{SYS_STATUS_SLEEP,                   sys_sleep_in,                  sys_sleep_exe,                     NULL,                   NULL},\
{SYS_STATUS_BOOTLOADER, 	    sys_bootloader_in,          sys_bootloader_exe,             NULL,   	            NULL},\
)

SYS_FSM_OUT_T   g_stSysFsmOut;
/*************************************************
*  Function:    sys_fsm_init
*  Description:
*  Called:
*  Call:
*
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Others:
*
*************************************************/
void sys_fsm_init(void) {
    memclr_user((UINT16 *)&g_stSysFsmOut, sizeof(SYS_FSM_OUT_T)/sizeof(UINT16));
	FSM_INIT_CALL(SYS_FSM)
    g_stSysFsmOut.emMDCDC_HW_WakeSts = MDCDC_HW_WAKEUP_INVALID;
}

/*************************************************
*  Function:    sys_fsm_5ms_task
*  Description:
*  Called:
*  Call:
*
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Others:
*
*************************************************/
void sys_fsm_5ms_task(void){
    FSM_OBJ_CALL(SYS_FSM)
}
/*************************************************
*  Function:   sys_init_in
*  Description:
*  Called:
*  Call:
*
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Others:
*
*************************************************/
void  sys_init_in(void)
{
}

/*************************************************
*  Function:    sys_init_exe
*  Description:
*  Called:
*  Call:
*
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Others:
*
*************************************************/
void  sys_init_exe(void){
}

/*************************************************
*  Function:   sys_init_cond
*  Description:
*  Called:
*  Call:
*
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Others:
*
*************************************************/
UINT8 sys_init_cond(UINT16 u16TrigEven){
    return SYS_STATUS_INIT;
}

/*************************************************
*  Function:       sys_standby_in
*  Description:
*  Calls:
*  Input:          NONE
*  Quoted Variable:
*  Modified Variable:
*  Return:         NONE
*  Autor:          Hongbo.jiang
*  Date:           2022/11/09
*************************************************/
void sys_standby_in(void)
{
}

/*************************************************
*  Function:       		sys_standby_exe
*  Description:
*  Calls:
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:         		NONE
*  Autor:          		Hongbo.jiang
*  Date:           		2022/11/09
*************************************************/
void  sys_standby_exe(void)
{
}

/*************************************************
*  Function:       		sys_standby_cond
*  Description:
*  Calls:
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:         		The next status.
*  Author:              Hongbo.jiang
*  Date:           		2022/11/09
*************************************************/
UINT8 sys_standby_cond(UINT16 u16TrigEven){
    return SYS_STATUS_STANDBY;
}


/*************************************************
*  Function:       		sys_active_in
*  Description:
*  Calls:
*  Input:          		NONE
*  Quoted Variable:
*  Modified Variable:
*  Return:         		NONE
*  Author:              Hongbo.jiang
*  Date:           		2022/11/09
*************************************************/
void  sys_active_in(void)
{
}

/*************************************************
*  Function:       		sys_active_exe
*  Description:
*  Calls:
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:         		NONE
*  Author:              Hongbo.jiang
*  Date:           		2022/11/09
*************************************************/
void sys_active_exe(void){
}

/*************************************************
*  Function:       		sys_active_cond
*  Description:
*  Calls:
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Author:
*  Date:
*************************************************/
UINT8 sys_active_cond(UINT16 u16TrigEven){
      return SYS_STATUS_ACTIVE;
}

/*************************************************
*  Function:       		sys_fault_in
*  Description:    		clear the gs_u16NextStatusHold, and  gs_u16MoniTimerCnt to use in the sys_dischrg_exe.
*  Calls:          		before jump in the SYS_STATUS_RECV status
*  Input:          		NONE
*  Quoted Variable:
*  Modified Variable:   gs_u16NextStatusHold,gs_u16MoniTimerCnt
*  Return:         		NONE
*  Author:              Hongbo.jiang
*  Date:           		2022/11/09
*************************************************/
void sys_fault_in(void){
}

/*************************************************
*  Function:       		sys_fault_exe
*  Description:
*  Calls:
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:         		NONE
*  Author:
*  Date:
***************************************************/
void sys_fault_exe(void){
}

/*************************************************
*  Function:   sys_fault_cond
*  Description:
*  Called:
*  Call:
*
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Others:
*
*************************************************/
UINT8 sys_fault_cond(UINT16 u16TrigEven){
    return SYS_STATUS_FAULT;
}

/*************************************************
*  Function:   sys_sleep_in
*  Description:
*  Called:
*  Call:
*
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Others:
*
*************************************************/
void sys_sleep_in(void){
}

/*************************************************
*  Function:   sys_sleep_exe
*  Description:
*  Called:
*  Call:
*
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Others:
*
*************************************************/
void  sys_sleep_exe(void)
{
}

/*************************************************
*  Function:   sys_bootloader_in
*  Description:
*  Called:
*  Call:
*
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:
*  Others:
*
*************************************************/
void sys_bootloader_in(void)
{
}


/*************************************************
*  Function:       		sys_bootloader_exe
*  Description:    		Jump to bootloader zoom in this function
*  Calls:          		sys_bootloader_exe only work in once, then enter bootloader zoom.
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:         		NONE
*  Author:          	Hongbo.jiang
*  Date:           		2022/11/09
***************************************************/
void sys_bootloader_exe(void){
   //Add from this jump to bootloader
   UINT32 *p_u32CLLCJumpBoot = (UINT32 *)0x8000;
    *p_u32CLLCJumpBoot = 0xA3A4A1BF;
//   ExitBoot(0x80000); //Wait for the watch dog overflow to jump bootload
}


