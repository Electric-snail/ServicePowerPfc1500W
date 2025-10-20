/*********************************************************************
File name:       BSW_ISR_Timer.h

 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/

#ifndef BSW_ISR_TIMER_H
#define BSW_ISR_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif
#include  "SOFTWARE_ENV_CFG.h"

extern INTERRUPT void IsrCpuTimer2(void);
extern UINT32 g_u32SysTimerMs;
#define get_sys_timer()     g_u32SysTimerMs

#ifdef __cplusplus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================
