/*
 * main.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#include "common/include/F28x_Project.h"
#include "BSW_MCAL_BASIC.h"
#include "BSW_ISR_BASIC.H"
#include "BSW_SVC_BASIC.h"
#include "TASK/BSW_TASK_SERVICE.h"
#include "ASW_BASIC.h"

 /******************* Global Variable Decration *******************/

int main(void)
{
    bsw_mcal_init();  //The controller peripheral initial, including ADC, SCI, PWM, ISR,

    bsw_isr_init();

    bsw_svc_init();      //The service layer initial, including state machine core, task schedule core, parameter configure core;

    asw_init();

   	EINT;
   	ERTM;
    for (;;)
    {
         bsw_svc_sche_exe_task();
    }
}
