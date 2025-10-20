/*
 * BSW_MCAL_BASIC.c
 *
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 */

#include "BSW_MCAL_BASIC.h"
#include "CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL_INC/BSW_MCAL_RAM.h"
#include "MCAL_INC/BSW_MCAL_FLASH.h"
#include "MCAL_INC/BSW_MCAL_WDG.h"
#include "MCAL_INC/BSW_MCAL_SYS.h"
#include "MCAL_INC/BSW_MCAL_SP.h"
#include "MCAL_INC/BSW_MCAL_SYS_CLOCK.h"
#include "MCAL_INC/BSW_MCAL_INT_CTRL.h"
#include "MCAL_INC/BSW_MCAL_CPUTIMER.h"
//#include "MCAL_INC/BSW_MCAL_CLA.h"
#include "MCAL_INC/BSW_MCAL_XBAR.h"
#include "MCAL_INC/BSW_MCAL_PWM.h"
#include "MCAL_INC/BSW_MCAL_CMPSS.h"
#include "MCAL_INC/BSW_MCAL_ADC.h"
#include "MCAL_INC/BSW_MCAL_GPIO.h"
#include "MCAL_INC/BSW_MCAL_SCI.h"
#include "MCAL_INC/BSW_MCAL_I2C.h"
#include "MCAL_INC/BSW_MCAL_WDG.h"
//#include "MCAL_INC/BSW_MCAL_SPI.h"

const MCAL_DRIVE_OBJ g_fst_McalDrvEntity[] = MCAL_DRV_REG_TAB;

void bsw_mcal_init(void)
{
    UINT16 i;

    bsw_mcal_disable_global_int();          //During MCAL initial timer, disable the global interrupt
    bsw_mcal_disable_watchdog();        //During MCAL initial timer, disable the internal watchdog

    const MCAL_DRIVE_OBJ  *p_mcal_drv = NULL;
    pf_mcal_init    pf_mcal_init = NULL;

    UINT16   auto_reg_item = (UINT16)((UINT32)sizeof(g_fst_McalDrvEntity) / sizeof(MCAL_DRIVE_OBJ));

    p_mcal_drv = g_fst_McalDrvEntity;

    for(i = 0; i < auto_reg_item; i++)
    {
        //is the id of each item  kept same with sequence with the driver register table
       if(i != p_mcal_drv->mcal_id)
           while(1);                 //keep the cpu stop.
       pf_mcal_init = p_mcal_drv->mcal_init;
       if((pf_mcal_init != NULL)&&(p_mcal_drv->is_auto_init == 1)){
           pf_mcal_init();
       }
       p_mcal_drv++;
    }
}


