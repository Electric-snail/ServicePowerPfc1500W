/*
 * BSW_TaskService.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
**********************************************************************/
#include "TASK/BSW_TASK_SERVICE.h"
#ifndef DLLX64
#include "MCAL_INC/BSW_MCAL_INT_CTRL.h"
#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE.H"
#include "DEBUG_PLATFORM/SFRA/SFRA.h"
#include "DEBUG_PLATFORM/PERFORMACE_TEST/PERFORMACE_TEST.H"
#include "COMM_STACK/DP_STACK/APL/APL_STACK.H"
#endif

#include "ISR_INC/BSW_ISR_CPUTIMER.h"
#include "PUBLIC_INC/ASSERT.H"
#include "ASW_BASIC.h"
#include "MEASURE/MEASURE.h"
#include "DIAGNOSTIC/DIAGNOSTIC.h"
#include "DERATING/DERATING.h"
#include "SYS_FSM/SYS_FSM.h"
#include "POWER_FSM/POWER_FSM.h"
#include "PFC_LLC_COMM/PFC_LLC_COMM.H"

extern UINT32 TaskRegLoadStart;
extern UINT16 TaskRegLoadSize;

const TASK_ITEM_OBJ gc_stTaskItemTab[] = TASK_REG_TAB;

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
void bsw_svc_vScheInit(void)
{
    UINT16 i;
    const TASK_ITEM_OBJ *p_task_reg = gc_stTaskItemTab;
    unsigned int u16TaskNum = (UINT16)(sizeof(gc_stTaskItemTab)/sizeof(TASK_ITEM_OBJ));
    if(u16TaskNum <= MAX_TASK_NUM){
        for(i = 0;i < u16TaskNum; i++){
            g_TaskScheVars.ua32TaskExeTimer[i]   = p_task_reg->u16Offset;
            g_TaskScheVars.ua32TaskRunMaxCnt[i]  = 0xFFFFFFFF;
            g_TaskScheVars.ua32TaskRunMinCnt[i]  = 0x00000000;
            p_task_reg++;
        }
        g_TaskScheVars.u8NumOfTasks 	         = u16TaskNum;
        g_TaskScheVars.u8TaskCoreInitFlg         = 1;
    }else{
    	g_TaskScheVars.u8TaskCoreInitFlg         = 0;
    }

}

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
#pragma CODE_SECTION(BSW_SVC_ScheExcuTask, ".TI.ramfunc");
#endif

//6us -> 1.3us
void bsw_svc_sche_exe_task(void)
{
     UINT16 i;
     const TASK_ITEM_OBJ *p_task_reg = gc_stTaskItemTab;
     static UINT32 s_u32task_timer_pre = 0;

     if(g_TaskScheVars.u8TaskCoreInitFlg == 0) return;
     UINT32 u32task_timer = get_sys_timer();
     if(TIME_OVER_U32(s_u32task_timer_pre,u32task_timer)){
        #if(TASK_CPU_LOAD_TEST == 1)
        UINT32 u32TaskTestTemp = 0xFFFFFFFF - GetTaskTestTimer();
        g_u32CpuLoadTotalTimer += u32TaskTestTemp;
        g_u16CpuLoadCnt ++;
        #endif
        s_u32task_timer_pre++;   //update the last time, in order to each task timer, the task scheduler only be called once.
        for(i = 0; i < g_TaskScheVars.u8NumOfTasks; i++)
        {
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
            p_task_reg++;
         }
        #if (TASK_CPU_LOAD_TEST == 1)
          ResetTaskTestTimer();
        #endif
     }

}





