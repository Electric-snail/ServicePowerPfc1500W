/*********************************************************************
File name:       BSW_ISR_CPUTIMER.c
Purpose :         Handle timer0/1/2...


**********************************************************************/
#include "common/include/f28x_Project.h"
#include  "ISR_INC/BSW_ISR_CPUTIMER.h"
#include "HAL_INC/BSW_HAL_GPIO.H"
#include "DEBUG_PLATFORM/PERFORMACE_TEST/PERFORMACE_TEST.h"

#pragma CODE_SECTION(IsrCpuTimer2, ".TI.ramfunc");

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

__interrupt void IsrCpuTimer2(void)   //200US
{
    static unsigned char s_u8Status = 0;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1 | PIEACK_GROUP12;
    IER = M_INT1 | M_INT12;
    __asm("  NOP");
    EINT;                                         // Enable Global interrupt INTM

    #if(TASK_CPU_LOAD_TEST == 1)
     UINT16 u16TaskTestTimerStatus = GetTaskTestTimerStatus();
     StopTaskTestTimer();
    #elif(ISR_CPU_LOAD_TEST == 1)
     ResetTaskTestTimer();
    #endif

    CpuTimer2Regs.TCR.bit.TIF = 1;
    g_u32SysTimerMs++;

    if(s_u8Status == 0){
    	BSW_HAL_YELLOW_ON();
    	s_u8Status = 1;
    }
    else{
    	BSW_HAL_YELLOW_OFF();
    	s_u8Status = 0;
    }
    #if(TASK_CPU_LOAD_TEST == 1)
      ReloadTaskTestTimerStatus(u16TaskTestTimerStatus);
    #elif(ISR_CPU_LOAD_TEST == 1)
      ISR_EXE_VAR_CALL(CPU_TIMER2_ISR)
    #endif

}


