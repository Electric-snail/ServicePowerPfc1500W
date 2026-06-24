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
	{apl_main,                  					"apl_main",                   	1,          3,                  2},\
    {sys_fsm_5ms_task,                              "sys_fsm_5ms_task",             1,          5,                  1},\
    {led_ctrl_500ms_task,                           "led_ctrl_500ms_task",          1,          200,                199},\
}


#else
#define TASK_REG_TAB                      \
{\
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

