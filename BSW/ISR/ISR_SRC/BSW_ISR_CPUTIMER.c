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

#if(DB_TOOL_ENABLE == TRUE)
#include "DEBUG_PLATFORM/PERFORMACE_TEST/PERFORMACE_TEST.h"
#endif

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
 /*   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    IER = M_INT1;
    __asm("  NOP");
    bsw_mcal_enable_global_int();        */                                 // Enable Global interrupt INTM
    CpuTimer2Regs.TCR.bit.TIF = 1;
#endif
    /*    #if(TASK_CPU_LOAD_TEST == 1)
     UINT16 u16TaskTestTimerStatus = GetTaskTestTimerStatus();
     StopTaskTestTimer();
    #elif(ISR_CPU_LOAD_TEST == 1)
     ResetTaskTestTimer();
    #endif		*/

    g_u32SysTimerMs++;

  /*   #if(TASK_CPU_LOAD_TEST == 1)
      ReloadTaskTestTimerStatus(u16TaskTestTimerStatus);
    #elif(ISR_CPU_LOAD_TEST == 1)
      ISR_EXE_VAR_CALL(CPU_TIMER2_ISR)
    #endif    */
}


