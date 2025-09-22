/*********************************************************************
File name:       BSW_TASK_SERVICE.h
Purpose :
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
**********************************************************************/
#ifndef BSW_SERVICE_TASK_BSW_TASKSERVICE_H_
#define BSW_SERVICE_TASK_BSW_TASKSERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "SOFTWARE_ENV_CFG.h"
#include "PUBLIC_INC/AUTO_REGISTER.H"

#define MAX_TASK_NUM       24

typedef void (*TaskFuncType)(void);

typedef struct
{
    TaskFuncType taskProc;    // Task process entity pointer
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
extern void bsw_svc_task_run(void);

#define REG_TASK_SECTION  __attribute__ ((used,section(".TASK_REG_SECTION")))

#define REG_TASK_ITEM(name,p_user_data)  const AUTO_REG_OBJ _auto_reg_##name REG_TASK_SECTION = {#name,AUTO_REG_TASK,p_user_data};

///-------register task
#define REG_TASK(task_func,enable,period,offset) \
                const static TASK_ITEM_OBJ task_##task_func = {task_func,enable,period,offset};\
                REG_TASK_ITEM(task_func,(void*)&task_##task_func)

#ifdef __cplusplus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================

