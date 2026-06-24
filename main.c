/*
 * main.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#include "common/include/F28x_Project.h"
#include "MCAL_INC/BSW_MCAL_RAM.h"
#include "MCAL_INC/BSW_MCAL_FLASH.h"
#include "MCAL_INC/BSW_MCAL_SYS.h"
#include "MCAL_INC/BSW_MCAL_SYS_CLOCK.h"
#include "MCAL_INC/BSW_MCAL_INT_CTRL.h"
#include "MCAL_INC/BSW_MCAL_CPUTIMER.h"
#include "MCAL_INC/BSW_MCAL_GPIO.h"
#include "MCAL_INC/BSW_MCAL_SCI.h"
#include "MCAL_INC/BSW_MCAL_WDG.h"
#include "COMM_STACK/DP_STACK/APL/APL_STACK.H"
#include "TASK/BSW_TASK_SERVICE.h"
#include "SYS_FSM/SYS_FSM.H"
#include "BOOT_PROCE/BOOT_PROCE.H"

#pragma DATA_SECTION(gc_u32AppEraseTest,   ".APP_TEST");

const unsigned long gc_u32AppEraseTest = 0xaa55aa55;

 /******************* Global Variable Decration *******************/

int main(void)
{
    bsw_mcal_ram_init();
    bsw_mcal_flash_init();
    bsw_mcal_sys_init();
    bsw_mcal_sys_clock_init();
    bsw_mcal_pie_ctrl_init();
    bsw_mcal_cpu_timer_init();
    bsw_mcal_gpio_init();
    bsw_mcal_sci_init();
    bsw_mcal_wdg_init();

    bsw_svc_vScheInit();
    apl_init();

    sys_fsm_init();
    boot_proce_init();

   	EINT;
   	ERTM;
    for (;;)
    {
         bsw_svc_sche_exe_task();
    }
}
