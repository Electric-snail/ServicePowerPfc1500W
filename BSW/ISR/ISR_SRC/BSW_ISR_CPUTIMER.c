/*********************************************************************
File name:       BSW_ISR_CPUTIMER.c
Purpose :         Handle timer0/1/2...


**********************************************************************/
#ifndef DLLX64
#include "common/include/f28x_Project.h"
#endif
#include "SOFTWARE_ENV_CFG.H"
#include  "ISR_INC/BSW_ISR_CPUTIMER.h"
#include  "HAL_INC/BSW_HAL_GPIO.H"

#ifndef DLLX64
#pragma CODE_SECTION(IsrCpuTimer2, ".TI.ramfunc");
#endif


/*************************************************
*  Function:       IsrCpuTimer2
*  Description:    ISR for Timer2
*  Calls:          Trigged by Interrupt
*  Input:          void
*  Output:         void
*  Quoted Variable:  // which variables are been quoted read some global variables without modification
*  Modified Variable: // which variables are been modified
*  Return:         void
*  Others:         //
*************************************************/
UINT32 g_u32SysTimerMs = 0;
#if(ISR_TEST_CPU_LOAD_TEST == 1)
ISR_EXE_VAR_ENTITY(CPU_TIMER2_ISR)
#endif

INTERRUPT void IsrCpuTimer2(void)   //200US
{
#ifndef DLLX64
    CpuTimer2Regs.TCR.bit.TIF = 1;
#endif
    g_u32SysTimerMs++;
}


