                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   /*********************************************************************
File name:       BSW_ISR_ADC.c 
Purpose :         Read the value from ADC registers  respectively

Copyright Notice:
 *  Created on:
 *      Author:
**********************************************************************/
#include <PUBLIC_INC/DF_MATH.H>
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#ifndef  DLLX64
#include "CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL_INC/BSW_MCAL_PWM.h"
#include "MCAL_INC/BSW_MCAL_GPIO.h"
#endif

#if(DB_TOOL_ENABLE == TRUE)
#include "DEBUG_PLATFORM/PARAMETER_CTRL/PARAMETER.H"
#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE.H"
#include "DEBUG_PLATFORM/SFRA/SFRA.H"
#endif

#include "HAL_INC/BSW_HAL_PWM.h"
#include "HAL_INC/BSW_HAL_ADC.h"
#include "HAL_INC/BSW_HAL_GPIO.h"
#include "HAL_INC/BSW_HAL_TIMER.h"
#include "ISR_INC/BSW_ISR_ADC.h"
//#include "ASW_BASIC.h"
#include "SYS_FSM/SYS_FSM_INF.h"
#include "MEASURE/MEASURE_INF.h"
#include "DIAGNOSTIC/DIAGNOSTIC_INF.h"
#include "SVC/TASK/BSW_TASK_SERVICE.h"

#ifndef  DLLX64
#pragma  CODE_SECTION(adcA1ISR, ".TI.ramfunc");
#endif

#if(ISR_CPU_LOAD_TEST == 1)
ISR_EXE_VAR_ENTITY(ADCA1_ISR)
#endif

#define ADC_INT1   0x0001
#define ADC_INT2   0x0002
#define ADC_INT3   0x0004
#define ADC_INT4   0x0008

/*********variable declaration region *************************************/
extern float fResult;

/************ Variable definition region *********************************/
extern UINT32           g_u32SysTimerMs;


__interrupt void adcA1ISR(void)
{
   // BSW_HAL_HwProtect_Reset_EN()  ;
    float f32TempData, f32VoutLv, f32IoutLv;

    static UINT16 s_u16Cnt = 0;

    //Clear the interrupt flag
     #ifndef DLLX64
     AdcaRegs.ADCINTFLGCLR.all |= ADC_INT1;
     // Check if overflow has occurred
     if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)       //ADCINT overflow occurred
     {
         AdcaRegs.ADCINTOVFCLR.all |= ADC_INT1 ;     //Clear overflow flag
         AdcaRegs.ADCINTFLGCLR.all |= ADC_INT1 ;     //Re-clear ADCINT flag
     }
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
     #endif

    #if(TASK_CPU_LOAD_TEST == 1)
     UINT16 u16TaskTestTimerStatus = GetTaskTestTimerStatus();
     StopTaskTestTimer();
    #elif(ISR_CPU_LOAD_TEST == 1)
     ResetTaskTestTimer();
    #endif

	#ifndef DLLX64
    IER = M_INT3;                              // enableINT3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    __asm("  NOP");
    EINT;                                     // Enable Global interrupt INTM
    #endif

    s_u16Cnt++;
    if(s_u16Cnt >= ((UINT16)(CTR_FRQ/1000.0f)))
    {
        g_u32SysTimerMs++;    //Task timer tick
        s_u16Cnt = 0;
    }

    #if (DB_TOOL_ENABLE == TRUE)
        #define GEN_SW_SCOPE_ISR_CALL
        #include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
        #undef GEN_SW_SCOPE_ISR_CALL
    #endif

	#if(TASK_CPU_LOAD_TEST == 1)
	    ReloadTaskTestTimerStatus(u16TaskTestTimerStatus);
	#elif(ISR_CPU_LOAD_TEST == 1)
	    ISR_EXE_VAR_CALL(ADCA1_ISR);
	#endif
}



