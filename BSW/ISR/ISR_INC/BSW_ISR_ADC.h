/*********************************************************************
File name:       BSW_ISR_ADC..h
Purpose :         1. Define macro
                          2.  Define data type, such as structure/enum
                          3. import variables  by  including head file(s)
                          4. export variables by keywords( extern)
 
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/

#ifndef BSW_ISR_ADC_H
#define BSW_ISR_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

extern __interrupt void adcA1ISR(void);
extern      UINT32                g_u32SysTimerMs;
#define     get_sys_timer()       g_u32SysTimerMs
#ifdef __cplusplus
}
#endif // extern "C"

//extern UINT16 probe_var;

#endif
//===========================================================================
// End of file.
//===========================================================================
