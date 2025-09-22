/*
 * SysFsm.c
 *
 *  Created on: 2022.9.19
 */

#include "HAL_INC/BSW_HAL_PWM.h"
#include "HAL/HAL_INC/BSW_HAL_ADC.h"
#include "HAL/HAL_INC/BSW_HAL_GPIO.h"
#include "SVC/BSW_SVC_BASIC.h"
#include "SVC/FSM/BSW_FSM_CORE.h"
#include "SYS_FSM/SYS_FSM.h"
#include "POWER_FSM/POWER_FSM.h"
#include "POWER_FSM/POWER_FSM.h"
#include "DIAGNOSTIC/DIAGNOSTIC.H"
#include "SYS_FSM/SYS_FSM_INF.h"

/****** internal function declaration region ***********/
void  power_stop_in(void);
void  power_stop_exe(void);
UINT8 power_stop_cond(UINT16 u16TrigEven);

void  power_soft_exe(void);
UINT8 power_soft_cond(UINT16 u16TrigEven);

void  power_run_in(void);
void  power_run_exe(void);
void  power_run_out(void);
UINT8 power_run_cond(UINT16 u16TrigEven);

/************ Variable definition region *********************************/

//----------FSM name-----initial status id---------------------
REG_FSM_OBJ(POWER_FSM,   PWR_STATUS_STOP,\
//---fsm status id-------------------------fsm_in_func-------------fsm_exe_func---------------fsm_out_func-------------------fsm_cond_func;
{PWR_STATUS_STOP,              power_stop_in,              power_stop_exe,              NULL,                             power_stop_cond},\
{PWR_STATUS_SOFT,              NULL,                          power_soft_exe,              NULL,                             power_soft_cond},\
{PWR_STATUS_RUN,                power_run_in,               power_run_exe,                power_run_out,                power_run_cond},\
)
STATIC UINT16 gs_u16delay_cnt = 0;

/*************************************************
*  Function:   power_fsm_init
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
void power_fsm_init(void) {
//	FSM_INIT_CALL(POWER_FSM)
}

/*************************************************
*  Function:   power_fsm_2ms_task
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
void power_fsm_2ms_task(void){
//    FSM_OBJ_CALL(POWER_FSM)
}

/*************************************************
*  Function:   power_stop_in
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
void  power_stop_in(void)
{
}

/*************************************************
*  Function:   power_stop_exe
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
void  power_stop_exe(void)
{
}

/*************************************************
*  Function:  power_stop_cond
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
UINT8 power_stop_cond(UINT16 u16TrigEven)
{
    return PWR_STATUS_STOP;
}


/*************************************************
*  Function:  power_soft_startup_exe
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
void power_soft_exe(void)
{

}


/*************************************************
*  Function:
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
UINT8 power_soft_cond(UINT16 u16TrigEven){
    return PWR_STATUS_SOFT;
}

/*************************************************
*  Function:
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
void  power_run_in(void){
}

/*************************************************
*  Function:  power_run_exe
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
void  power_run_exe(void)
{
}

/*************************************************
*  Function:   power_run_out
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
void  power_run_out(void){
}

/*************************************************
*  Function:  power_buck_run_cond
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
UINT8 power_run_cond(UINT16 u16TrigEven){
    return PWR_STATUS_RUN;
}









