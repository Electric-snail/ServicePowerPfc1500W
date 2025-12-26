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


#define reset_performace_test_timer()                			{CpuTimer1Regs.TIM.all = 0xFFFFFFFF; CpuTimer1Regs.TCR.bit.TSS  = 0;}
#define get_performace_test_timer()                 				 CpuTimer1Regs.TIM.all
#define stop_performace_test_timer()                 			 CpuTimer1Regs.TCR.bit.TSS = 1
#define get_performace_test_timer_status()            					 CpuTimer1Regs.TCR.all
#define reload_performace_test_timer_status(Status)     CpuTimer1Regs.TCR.all = Status
#define get_performace_test_timer_inv()                        GetCpuTimer1Inv()

#endif /*_BSW_HAL_TIMER_H_ */
