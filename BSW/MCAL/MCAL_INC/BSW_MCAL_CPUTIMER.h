/*********************************************************************
File name:       BSW_MCAL_CPUTIMER.h

 *  Created on:  2022-07-13
 *      Author:  Hongbo.jiang
**********************************************************************/

#ifndef BSW_MCAL_TIMER_H
#define BSW_MCAL_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL/BSW_MCAL_BASIC.h"

enum CPU_TIMER_NUM
{
    CPU_TMER0 = 0,
    CPU_TMER1,
    CPU_TMER2,
    CPU_TIMER_MAX_NUM,
};

typedef enum{
    TIMER_MODE = 0x00,
    COUTER_MODE,
}CPU_TIMER_MODE;
//f32freq: uS;
struct CPU_TIMER_CFG_PARAM{
    enum CPU_TIMER_NUM  emTimerNum;
    CPU_TIMER_MODE emMode;
    UINT8  u8IntEna;
    float  f32Period;
};
//---emTimerNum ---------emMode---------u8IntEna---------f32Period
#define CPU_TIMER_CFG_TAB \
{\
    {CPU_TMER1,     COUTER_MODE,  		0,   			3000.0},\
    {CPU_TMER2,     TIMER_MODE,   		    1,   			1000.0},\
}

#define  GetCpuTimer1Inv()               10.0f

extern void bsw_mcal_cpu_timer_init(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================
