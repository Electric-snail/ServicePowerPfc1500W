/*
 * SysFsm.c
 *
 *  Created on: 2022.9.19
 */
#include "BOOTLOADER/BOOTLOAD.h"
#include "HAL_INC/BSW_HAL_GPIO.h"
#include "HAL_INC/BSW_HAL_ADC.h"
#include "SVC/BSW_SVC_BASIC.h"
#include "ASW_BASIC.h"
#include "SYS_FSM/SYS_FSM.h"
#include "SYS_FSM/SYS_FSM_INF.h"
#include "POWER_FSM/POWER_FSM.h"
#include "PUBLIC_INC/mem_handle.h"

#ifndef DLLX64
#pragma DATA_SECTION(g_u32CLLCJumpBoot,".jumpboot");
#endif

UINT32 g_u32CLLCJumpBoot;

extern void ExitBoot(UINT32 EntryAddr);

SYS_FSM_OUT_T g_stSysFsmOut;

static UINT16 gs_u16NextStatusHold = SYS_STATUS_INVALID;
static UINT16 gs_u16MoniTimerCnt   = 0;

void  sys_init_in(void);
void  sys_init_exe(void);
UINT8 sys_init_cond(UINT16 u16TrigEven);

void  sys_standby_in(void);
void  sys_standby_exe(void);
UINT8 sys_standby_cond(UINT16 u16TrigEven);

void  sys_buck_const_volt_in(void);
void  sys_buck_const_volt_exe(void);
UINT8 sys_buck_const_volt_cond(UINT16 u16TrigEven);

void  sys_buck_const_curr_in(void);
void  sys_buck_const_curr_exe(void);
UINT8 sys_buck_const_curr_cond(UINT16 u16TrigEven);

void  sys_fault_in(void);
void  sys_fault_exe(void);
UINT8 sys_fault_cond(UINT16 u16TrigEven);

void  sys_bootloader_exe(void);

void  sys_sleep_in(void);
void  sys_sleep_exe(void);

//----------FSM name--------initial status id---------------------
REG_FSM_OBJ(SYS_FSM,        SYS_STATUS_INIT,\
//---fsm status id----------fsm_in_func-------------fsm_exe_func-------------fsm_out_func----------fsm_cond_func;
{SYS_STATUS_INIT,           sys_init_in,            sys_init_exe,            NULL,                  sys_init_cond},\
{SYS_STATUS_STANDBY,  		sys_standby_in, 	    sys_standby_exe,  		 NULL,          		sys_standby_cond},\
{SYS_STATUS_BUCK_CONST_V,   sys_buck_const_volt_in, sys_buck_const_volt_exe, NULL,  		        sys_buck_const_volt_cond},\
{SYS_STATUS_BUCK_CONST_I,   sys_buck_const_curr_in, sys_buck_const_curr_exe, NULL,                  sys_buck_const_curr_cond},\
{SYS_STATUS_FAULT,          sys_fault_in,           sys_fault_exe,           NULL,   	            sys_fault_cond},\
{SYS_STATUS_SLEEP,          sys_sleep_in,           sys_sleep_exe,           NULL,                  NULL},\
{SYS_STATUS_BOOTLOADER, 	NULL,   			    sys_bootloader_exe,      NULL,   	            NULL},\
)

void sys_fsm_init(void) {
	FSM_INIT_CALL(SYS_FSM)
}

void sys_fsm_5ms_task(void){
    FSM_OBJ_CALL(SYS_FSM)
}

void  sys_init_in(void)
{
}

void  sys_init_exe(void)
{
}
UINT8 sys_init_cond(UINT16 u16TrigEven)
{
}

/*************************************************
*  Function:       sys_standby_in
*  Description:    clear the system FSM output variable, and initial some key parameter.
*  Calls:          when entry STANDBY status,the sys_standby_in function will be call in once
*  Input:          NONE
*  Quoted Variable:
*  Modified Variable: g_stSysFsmOut: the system fsm module output
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
*  Modified Variable:   g_stSysFsmOut: the system fsm module output;
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
*  Date:           		
*************************************************/

UINT8 sys_standby_cond(UINT16 u16TrigEven){
}


/*************************************************
*  Function:       		sys_BuckConstVolt_in
*  Description:    		
*  Calls:          		
*  Input:          		NONE
*  Quoted Variable:
*  Modified Variable:   
*  Return:         		NONE
*  Author:              Hongbo.jiang
*  Date:           		
*************************************************/
void  sys_buck_const_volt_in(void)
{
}

/*************************************************
*  Function:       		sys_BuckConstVolt_exe
*  Description:    		
*  Calls:          		
*  Input:          		
*  Quoted Variable:
*  Modified Variable:  
*  Return:         		NONE
*  Author:              Hongbo.jiang
*  Date:           		
*************************************************/
void sys_buck_const_volt_exe(void){
}

/*************************************************
*  Function:       		
*  Description:    		
*  Calls:          		
*  Input:          		
*  Quoted Variable:
*  Modified Variable:
*  Return:         		
*  Author:
*  Date:
*************************************************/

UINT8 sys_buck_const_volt_cond(UINT16 u16TrigEven){
}


/*************************************************
*  Function:            
*  Description:        
*  Calls:             
*  Input:               NONE
*  Quoted Variable:
*  Modified Variable:  
*  Return:              NONE
*  Author:
*  Date:
*************************************************/
void  sys_buck_const_curr_in(void)
{
}

/*************************************************
*  Function:           
*  Description:         
*  Calls:               
*  Input:               
*  Quoted Variable:
*  Modified Variable:   
*  Return:              NONE
*  Author:
*  Date:
*************************************************/
void sys_buck_const_curr_exe(void){
}

/*************************************************
*  Function:            
*  Description:         
*  Calls:               
*  Input:               
*  Quoted Variable:
*  Modified Variable:
*  Return:              
*  Author:
*  Date:
*************************************************/

UINT8 sys_buck_const_curr_cond(UINT16 u16TrigEven){
}

/*************************************************
*  Function:       		
*  Description:    		
*  Calls:          		
*  Input:          		
*  Quoted Variable:
*  Modified Variable:   
*  Return:         		
*  Author:              Hongbo.jiang
*  Date:           		
*************************************************/
void sys_fault_in(void){
}

/*************************************************
*  Function:       		
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

UINT8 sys_fault_cond(UINT16 u16TrigEven){
}

void  sys_sleep_in(void)
{
}
void  sys_sleep_exe(void)
{
}


/*************************************************
*  Function:       		
*  Description:    		
*  Calls:          		
*  Input:
*  Quoted Variable:
*  Modified Variable:
*  Return:         	
*  Author:          	Hongbo.jiang
*  Date:           		
***************************************************/
void  sys_bootloader_exe(void){
}  


