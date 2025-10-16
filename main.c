/*
 * main.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL/BSW_MCAL_BASIC.h"
#include "BSW_SVC_BASIC.h"
#include "TASK/BSW_TASK_SERVICE.h"
#if(DB_TOOL_ENABLE == TRUE)
#include "DEBUG_PLATFORM/PARAMETER_CTRL/PARAMETER.H"
#endif
#include "BSW_HAL_BASIC.h"
#include "ASW_BASIC.h"

float f32VoltRaw;
float g_f32VoltLpf;

REG_CFG_ITEM_F32(VOUT_RAW,		f32VoltRaw,    		VAR_WR,			0,			-1000000,			1000000);
REG_CFG_ITEM_F32(VOUT_LPF,      	g_f32VoltLpf,  		VAR_RD,		0,			-1000000,			1000000);

/******************* Global Variable Decration *******************/
int main(void)
{
    bsw_mcal_init();  //The controller peripheral initial, including ADC, SCI, PWM, ISR,

    bsw_svc_init();      //The service layer initial, including state machine core, task schedule core, parameter configure core;

    asw_init();

    EINT;
    ERTM;
    for(;;)
    {
    	bsw_svc_task_run();
    }
}

