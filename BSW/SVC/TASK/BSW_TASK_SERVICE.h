/*********************************************************************
File name:       BSW_TASK_SERVICE.h
Purpose :
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
**********************************************************************/
#ifndef _BSW_TASKSERVICE_H_
#define _BSW_TASKSERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "SOFTWARE_ENV_CFG.h"

#define MAX_TASK_NUM       24

typedef void (*TaskFuncType)(void);

typedef struct
{
    TaskFuncType taskProc;    // Task process entity pointer
    const char *name;
    UINT16 enable;			  // Task enable word
    UINT16 u16Period;		  // Period timer of task
    UINT16 u16Offset;         // Offset timer of task
}TASK_ITEM_OBJ;

/**
 * Scheduler
 *
 * @numOfTasks   numbers of task
 * @TaskList     task list
 */
typedef struct
{
	UINT8    u8TaskCoreInitFlg;
    UINT8    u8NumOfTasks;
    UINT32   ua32TaskExeTimer[MAX_TASK_NUM];
    UINT32   ua32TaskRunMaxCnt[MAX_TASK_NUM];
    UINT32   ua32TaskRunMinCnt[MAX_TASK_NUM];
}TASK_SCHE_OBJ;


//-------------------------------------Task Run Timer -----------------------------------
extern void BSW_SVC_vScheInit(void);
extern void BSW_SVC_ScheExcuTask(void);
/* CAN_CYCLIC_TASK_PERIOD = 1 */
/* CPU_LOAD_TASK_PERIOD = 3 */
/***TaskFuncType taskProc       const char *name;           						enable   u16Period              u16Offset  *****/
#ifndef DLLX64
#define TASK_REG_TAB                      \
{\
    {measure_1ms_task,         			"measure_1ms_task",             				1,          1,                 0},\
    {power_fsm_1ms_task,        		"power_fsm_1ms_task",           			1,          1,                  1},\
    {diag_1ms_task,             				"diagnostic_1ms_task",          				1,          1,                  1},\
    {measure_10ms_task,         			"measure_10ms_task",            				1,          10,                 4},\
    {vpfc_mgt_10ms_task,         		"vpfc_mgt_10ms_task",            			1,          10,                 5},\
    {diag_10ms_task,           			 	"diagnostic_10ms_task",         			1,          10,                 6},\
    {diag_100ms_task,           			"diag_100ms_task",              				1,          100,                11},\
	{pfc_llc_msg_50ms_task,       	"pfc_llc_msg_50ms_task",               	1,          20,                 17},\
    {sw_scope_task,             			"sw_scope_task",              					1,          1,                    0},\
	{apl_main,                  					"apl_main",                   						1,          3,                  2},\
    {cpu_load_calc_task,        		    "cpu_load_calc_task",         				1,          3,                  1},\
    {stack_usage_calc_task,     			"stack_usage_calc_task",      				1,          100,              59},\
    {measure_time_calc_task,    		"measure_time_calc_task",     				1,          500,              157},\
 /* {sfra_fsm_task,             				"sfra_fsm_task",           						1,          2,                  0},*/\
}
#else
#define TASK_REG_TAB                      \
{\
      {measure_1ms_task,         "measure_10ms_task",             1,          1,                 0},\
      {power_fsm_1ms_task,        "power_fsm_1ms_task",           1,          1,                  1},\
      {diag_1ms_task,             "diagnostic_1ms_task",          1,          1,                  1},\
      {measure_10ms_task,         "measure_10ms_task",            1,          10,                 4},\
      {diag_10ms_task,            "diagnostic_10ms_task",         1,          10,                 5},\
      {diag_100ms_task,           "diag_100ms_task",              1,          100,                11},\
  /*    {cyclic_msg_10ms_task,      "cyclic_msg_10ms_task",       0,          10,                 7},*/\
  /*    {Loop_2p2zCtrlTest,         "Loop_2p2zCtrlTest",          0,          10,                 9},*/\
  /*    {cyclic_msg_100ms_task,     "cyclic_msg_100ms_task",      0,          100,                39},*/\
}
#endif

extern const TASK_ITEM_OBJ gc_stTaskItemTab[];
extern void bsw_svc_sche_exe_task(void);
extern void bsw_svc_vScheInit(void);
#ifdef __cplusplus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================

