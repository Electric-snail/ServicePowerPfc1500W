/*
 * BSW_HAL_TIMER.h
 *
 *  Created on: 2022Äê12ÔÂ16ÈÕ
 *      Author: xj8r1j
 */

#ifndef _BSW_HAL_TIMER_H_
#define _BSW_HAL_TIMER_H_
#ifndef DLLX64
#include "MCAL/MCAL_INC/BSW_MCAL_CPUTIMER.h"
#endif
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

extern unsigned short g_u16TimerLockFlag;
extern unsigned long  g_u32TimerCnt;
#define ResetTaskTestTimer()                {CpuTimer1Regs.TIM.all = 0xFFFFFFFF; CpuTimer1Regs.TCR.bit.TSS  = 0;}
#define GetTaskTestTimer()                  (CpuTimer1Regs.TIM.all)
#define StopTaskTestTimer()                 (CpuTimer1Regs.TCR.bit.TSS = 1)
#define GetTaskTestTimerStatus()            (CpuTimer1Regs.TCR.all)
#define ReloadTaskTestTimerStatus(Status)   (CpuTimer1Regs.TCR.all = Status)
#define GetTaskTestTimeInv()                GetCpuTimer1Inv()

#if(MEASURE_TIME_TEST == 1)
#define ResetMeasureTimerLock()                    if(g_u16TimerLockFlag == 0){ CpuTimer1Regs.TIM.all = 0xFFFFFFFF; CpuTimer1Regs.TCR.bit.TSS  = 0; g_u16TimerLockFlag = 1;}
#define GetMeasureTimerUnlock()                    if(g_u16TimerLockFlag == 1){ g_u32TimerCnt = 0xFFFFFFFFUL - CpuTimer1Regs.TIM.all;  g_u16TimerLockFlag = 0;}
#else
#define ResetMeasureTimerLock()
#define GetMeasureTimerUnlock()
#endif

#endif /*_BSW_HAL_TIMER_H_ */
