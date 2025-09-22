/*
 * BSW_TaskService.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
**********************************************************************/
#include "PUBLIC_INC/ASSERT.H"
#include "MCAL_INC/BSW_MCAL_INT_CTRL.h"
#include "HAL_INC/BSW_HAL_TIMER.h"
#include "ISR_INC/BSW_ISR_ADC.h"
#include "BSW_SVC_BASIC.h"
#include "BSW_TASK_SERVICE.h"

extern UINT32 TaskRegLoadStart;
extern UINT16 TaskRegLoadSize;

#if(TASK_CPU_LOAD_TEST == 1)
UINT32 g_u32CpuLoadTotalTimer = 0;
UINT16 g_u16CpuLoadCnt        = 0;
#endif

TASK_SCHE_OBJ g_TaskScheVars ={0};
/*************************************************
*  Function:       ScheM_Init
*  Description:    init the task var
*  Calls:          called in main function
*  Input:          void
*  Output:         void
*  Quoted Variable:  read the task table
*  Modified Variable: member of g_sScheMVars
*  Return:         void
*  Others:         //
*************************************************/
void BSW_SVC_vScheInit(void)
{
    UINT16 i;
    AUTO_REG_OBJ *p_auto_reg = NULL;
    TASK_ITEM_OBJ *p_task_reg = NULL;
    unsigned int u16TaskNum = (UINT16)((UINT32)&TaskRegLoadSize/sizeof(AUTO_REG_OBJ));
    p_auto_reg =(AUTO_REG_OBJ *)&TaskRegLoadStart;
    if(u16TaskNum <= MAX_TASK_NUM){
        for(i = 0;i < u16TaskNum; i++){
            p_task_reg = (TASK_ITEM_OBJ *)p_auto_reg[i].p_reg_data;
            g_TaskScheVars.ua32TaskExeTimer[i]   = p_task_reg->u16Offset;
            g_TaskScheVars.ua32TaskRunMaxCnt[i]  = 0xFFFFFFFF;
            g_TaskScheVars.ua32TaskRunMinCnt[i]  = 0x00000000;
        }
        g_TaskScheVars.u8NumOfTasks 	 = u16TaskNum;
        g_TaskScheVars.u8TaskCoreInitFlg = 1;
    }else{
    	g_TaskScheVars.u8TaskCoreInitFlg = 0;
    }

}

REG_SVC_INIT(SVC_TASK,	BSW_SVC_vScheInit)
/*************************************************
*  Function:       ScheM_ExcuTask
*  Description:    excute the ready task
*  Calls:          called  by main loop
*  Input:          void
*  Output:         void
*  Quoted Variable:  read the task table
*  Modified Variable: member of g_sScheMVars
*  Return:         void
*  Others:         //
*************************************************/
#ifndef DLLX64
#pragma CODE_SECTION(bsw_svc_task_run, ".TI.ramfunc");
#endif
extern UINT16 SvcRegLoadStart;
//6us -> 1.3us
void bsw_svc_task_run(void)
{
     UINT16 i;
     AUTO_REG_OBJ *p_auto_reg = NULL;
     TASK_ITEM_OBJ *p_task_reg = NULL;
     static UINT32 s_u32task_timer_pre = 0;
     UINT32 u32task_timer   = 0;
     p_auto_reg = (AUTO_REG_OBJ *)&TaskRegLoadStart;//&SvcRegLoadStart;//TaskRegLoadStart;

     if(g_TaskScheVars.u8TaskCoreInitFlg == 0) return;
     u32task_timer = get_sys_timer();
     if(u32task_timer > s_u32task_timer_pre){
        #if(TASK_CPU_LOAD_TEST == 1)
         UINT32  u32TaskTestTemp = 0xFFFFFFFF - GetTaskTestTimer();
        g_u32CpuLoadTotalTimer += u32TaskTestTemp;
        g_u16CpuLoadCnt ++;
        #endif
        s_u32task_timer_pre++;   //update the last time, in order to each task timer, the task scheduler only be called once.
        for(i = 0; i < g_TaskScheVars.u8NumOfTasks; i++)
        {
            p_task_reg = (TASK_ITEM_OBJ *)p_auto_reg[i].p_reg_data;

            if(p_task_reg != NULL){//Judge if the task register is normal.
                if((TIME_OVER_U32(g_TaskScheVars.ua32TaskExeTimer[i],u32task_timer)) \
                    &&(p_task_reg->enable == 1)){
                    if(p_task_reg->taskProc != NULL){ //Judge if the task is NULL
                       #if(TASK_CPU_LOAD_TEST == 1)
                       ResetTaskTestTimer();
                       #endif
                       p_task_reg->taskProc();
                       #if(TASK_CPU_LOAD_TEST == 1)
                       u32TaskTestTemp = GetTaskTestTimer();
                       g_TaskScheVars.ua32TaskRunMinCnt[i] = (u32TaskTestTemp > g_TaskScheVars.ua32TaskRunMinCnt[i])?u32TaskTestTemp:g_TaskScheVars.ua32TaskRunMinCnt[i];
                       g_TaskScheVars.ua32TaskRunMaxCnt[i] = (u32TaskTestTemp < g_TaskScheVars.ua32TaskRunMaxCnt[i])?u32TaskTestTemp:g_TaskScheVars.ua32TaskRunMaxCnt[i];
                       #endif
                       g_TaskScheVars.ua32TaskExeTimer[i] += p_task_reg->u16Period;
                    }
                }
             }
         }
        #if (TASK_CPU_LOAD_TEST == 1)
          ResetTaskTestTimer();
        #endif
     }

}





