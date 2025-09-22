/*
 * DIAGNOSTIC.c
 *
 *  Created on: 2022/11/7/
 *      Author:   Hongbo.Jiang
 */
#include "PUBLIC_INC/MEM_HANDLE.H"
#include "PUBLIC_INC/DC_MATH.H"
#include "HAL_INC/BSW_HAL_PWM.h"
#include "HAL_INC/BSW_HAL_GPIO.h"
//#include "STORAGE/BSW_STORAGE.h"
#include "TASK/BSW_TASK_SERVICE.h"
#include "ASW_BASIC.h"
#include "MEASURE/MEASURE_INF.h"
#include "DIAGNOSTIC/DIAGNOSTIC.h"
#include "SYS_FSM/SYS_FSM_INF.h"
#include "POWER_FSM/POWER_FSM.h"
#include "MEASURE/MEASURE_INF.h"
/********* function declaration region *************************************/


/*********variable declaration region *************************************/



/************ Variable definition region *********************************/
STATIC UINT16             gs_u16PrtctThrdUpdateFlg = 0;
STATIC FLOAT32            g_f32HvInOVP_Threshold   = 935;
STATIC FLOAT32            g_f32HvInUVP_Threshold   = 390;
UINT16                    g_u16BuckSelfSts         = 0;
unsigned long g_u32DevSelfTestStatus = 0;
DIAG_PROTECT_FLAG_L0_T    g_stDiagFaultFlagL0;
DIAG_PROTECT_FLAG_L1_T    g_stDiagFaultFlagL1;
DIAG_PROTECT_FLAG_L2_T    g_stDiagFaultFlagL2;
DIAG_PROTECT_FLAG_L3_T    g_stDiagFaultFlagL3;

DIAG_FAULT_INFO_T         g_stDiagFaultInfo;

UINT16 g_u16HwDiagCount[HW_DIAG_ID_MAX] = {0};
/*---emHwDiagId-----u16ErrCnt---u16RcvrCnt---ERR_TTL---*/
const HWDIAG_PARAM_CFG_T  gc_stHwdiagCfgParam[HW_DIAG_ID_MAX] = {
   {HW_LVOUT_OVP,     2,          3,        TTL_HIGH},
   {HW_LVOUT_UVP,     2,          3,        TTL_HIGH},
   {HW_LVOUT_OCP,     2,          3,        TTL_HIGH},
   {HW_HVIN_OCP,      2,          16000,    TTL_HIGH},
   {HW_LOCK_P,        2,          3,        TTL_HIGH},
};

UINT16 g_u16SwDiagCount[SW_DIAG_ID_MAX] = {0};
/*---emSwDiagId--------------u16ErrCnt---u16RcvrCnt---f32PrtctThreshold---f32RcvrThreshold*/
const SWDIAG_PARAM_CFG_T  gc_stSwdiagCfgParam[SW_DIAG_ID_MAX] = {
   {HVPRI_OTP,                 30,          30,        100,              80} ,     // 30 * 100ms
   {LVSEC_OTP,                 30,          30,        105,              80} ,     // 30 * 100ms
   {CASE_OTP,                  30,          30,        110,              80} ,     // 30 * 100ms
   {HV_VIN_OVP_F,              40,          0,         960,               0} ,     // 40 * 1ms
   {HV_VIN_OVP,                100,         100,       935,             930} ,     //100 * 10ms
   {HV_VIN_UVP_F,              40,          0,         380,               0} ,     // 40 * 1ms
   {HV_VIN_UVP,                100,         100,       390,             395} ,     //100 * 10ms
   {LV_IOUT_OCP_F,             200,         0,         40,                0} ,     //200 * 0.025ms
   {LV_IOUT_OCP,               100,         0,         25,                0} ,     //100 * 10ms
   {LV_POUT_OPP_F,             4,           0,         450,               0} ,     //No implement
   {LV_POUT_OPP,               10,          0,         360,               0} ,     //No implement
   {LV_VOUT_OVP_F,             80,          0,         17.5,              0} ,     //80 * 0.025ms
   {LV_VOUT_OVP,               50,          50,        16.5,           16.0} ,     //50 * 10ms
   {LV_VOUT_UVP_F,             80,          0,         7.0,               0} ,     //80 * 0.025ms No implement
   {LV_VOUT_UVP,               50,          50,        8.5,            10.0} ,     //50 * 10ms No implement
   {LV_VBAT_OVP,               10,          50,        16.5,           16.0} ,     //10 * 10ms
   {LV_VBAT_UVP,               10,          50,        8.5,             9.0} ,     //10 * 10ms
};
/*************************************************
*  Function:       diag_1ms_task
*  Description:
*  Called:         clr_diag_fault_flag_handle
*  Input:
*
*  Quoted Variable:
*  Modified Variable: No
*  Return:
*  Others:
*
*************************************************/
void diag_1ms_task(void)
{
}
/*************************************************
*  Function:       diag_10ms_task
*  Description:
*  Called:
*  Input:
*
*  Quoted Variable:
*  Modified Variable: No
*  Return:
*  Others:
*
*************************************************/
void diag_10ms_task(void)
{
}
/*************************************************
*  Function:       diag_100ms_task
*  Description:
*  Called:
*  Input:
*
*  Quoted Variable:
*  Modified Variable: No
*  Return:
*  Others:
*
*************************************************/
void diag_100ms_task(void)
{
}
/*************************************************
*  Function:       UnRcvSwFaultOverUnitTest
*  Description:
*  Called:
*  Input:
*
*  Quoted Variable:
*  Modified Variable: No
*  Return:
*  Others:
*
*************************************************/






