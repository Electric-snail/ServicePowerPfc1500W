/*********************************************************************
File name:       BSW_MCAL_Timer.c 

 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/
#include "MCAL_INC/BSW_MCAL_CPUTIMER.h"
#include "MCAL_INC/BSW_MCAL_SYS_CLOCK.h"

volatile struct  CPUTIMER_REGS * const p_CpuTimer[] ={&CpuTimer0Regs,&CpuTimer1Regs,&CpuTimer2Regs};

const  struct CPU_TIMER_CFG_PARAM gc_stTimerCfgParam[] =  CPU_TIMER_CFG_TAB;

void BSW_MCAL_ConfigCpuTimers(enum CPU_TIMER_NUM emTimerNum, float f32period, CPU_TIMER_MODE emTimerMode, UINT8 u8IntEna)
{
    volatile struct  CPUTIMER_REGS *p_sTCpuTimer;
    Uint32 temp;
    float f32SysClk = SYS_CLK_GetSysClkFreq();
    if(emTimerNum >= CPU_TIMER_MAX_NUM)
        return;
    p_sTCpuTimer = p_CpuTimer[emTimerNum];

  //  ConfigCpuTimer(p_sTCpuTimer, f32freq, f32period);
    // Initialize timer period, kH * ms
    temp = (long) (f32SysClk * f32period);
    // Set pre-scale counter to divide by 1 (SYSCLKOUT)
    p_sTCpuTimer->TPR.all  = 0;
    p_sTCpuTimer->TPRH.all  = 0;
    // 1 = Stop timer, 0 = Start/Restart Timer
    //
    p_sTCpuTimer->TCR.bit.TSS = 1;
    p_sTCpuTimer->TCR.bit.SOFT = 0;
    // Timer Free Run Disabled
    p_sTCpuTimer->TCR.bit.FREE = 0;
    if(emTimerMode == TIMER_MODE){
        p_sTCpuTimer->PRD.all = temp;
        // 1 = reload timer
        p_sTCpuTimer->TCR.bit.TRB = 1;
    }else{
        p_sTCpuTimer->PRD.all = 0xFFFFFFFF;
    }
    // 0 = Disable 1 = Enable Timer Interrupt
    if(u8IntEna == 1){
        p_sTCpuTimer->TCR.bit.TIF = 1; //Clear the interrupt flag
        p_sTCpuTimer->TCR.bit.TIE = 1;
    }
    else{
        p_sTCpuTimer->TCR.bit.TIE = 0;
    }
    p_sTCpuTimer->TCR.bit.TSS = 0;
}


void bsw_mcal_cpu_timer_init(void)
{
    UINT8 i = 0;
    InitCpuTimers();

    for(i = 0;i < (sizeof(gc_stTimerCfgParam)/sizeof(struct CPU_TIMER_CFG_PARAM)); i++){
        BSW_MCAL_ConfigCpuTimers(gc_stTimerCfgParam[i].emTimerNum, gc_stTimerCfgParam[i].f32Period,\
                                 gc_stTimerCfgParam[i].emMode,gc_stTimerCfgParam[i].u8IntEna);

    }
}


// Start Timer:
//
/*void BSW_MCAL_StartCpuTimer(UINT16 u16TimerNum)
{
    struct CPUTIMER_VARS *p_sTCpuTimer;
     if(u16TimerNum > 2)
         return;
     p_sTCpuTimer = p_CpuTimer[u16TimerNum];
     p_sTCpuTimer->RegsAddr->TCR.bit.TSS = 0;
}*/

//
// Stop Timer:
//
/*static void BSW_MCAL_StopCpuTimer(UINT16 u16TimerNum)
{
    if(u16TimerNum > 2)
       return;
    p_CpuTimer[u16TimerNum]->RegsAddr->TCR.bit.TSS = 1;
}*/

//
// Reload Timer With period Value:
//
/*static void BSW_MCAL_ReloadCpuTimer(UINT16 u16TimerNum)
{
    if(u16TimerNum > 2)
       return;
    p_CpuTimer[u16TimerNum]->RegsAddr->TCR.bit.TRB = 1;
}*/

//
// Read 32-Bit Timer overflow flag:
//
/*static INT32 BSW_MCAL_ReadCpuTimerIntFlag(UINT16 u16TimerNum)
{
    if(u16TimerNum > 2)
        return -1;
    return p_CpuTimer[u16TimerNum]->RegsAddr->TCR.bit.TIF;
}*/

//
// Clear 32-Bit Timer overflow flag:
//
/*static void BSW_MCAL_ClearCpuTimerIntFlag(UINT16 u16TimerNum)
{
    if(u16TimerNum > 2)
        return;
    p_CpuTimer[u16TimerNum]->RegsAddr->TCR.bit.TIF = 1;
}*/
//
// Read 32-Bit Timer Value:
//
/*static UINT32 BSW_MCAL_ReadCpuTimerCounter(UINT16 u16TimerNum)
{
    return p_CpuTimer[u16TimerNum]->RegsAddr->TIM.all;
}*/

//
// Read 32-Bit Period Value:
//
/*static UINT32 BSW_MCAL_ReadCpuTimerPeriod(UINT16 u16TimerNum)
{
    return p_CpuTimer[u16TimerNum]->RegsAddr->PRD.all;
}

static UINT32 BSW_MCAL_ReadCpuTimerInterruptCount(UINT16 u16TimerNum)
{
    return p_CpuTimer[u16TimerNum]->InterruptCount;
}*/


