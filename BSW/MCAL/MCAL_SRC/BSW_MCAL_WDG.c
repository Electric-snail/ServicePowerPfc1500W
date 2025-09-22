/*********************************************************************
File name:       BSW_MCAL_WDG.c 
Purpose :
**********************************************************************/
#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "../MCAL/BSW_MCAL_BASIC.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_INT_CTRL.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_WDG.h"
#if(EXTERN_WATCHDOG_ENABLE == 1)
#include "WD/Wdg_driver/ex_wdg.h"
#endif

const WDG_PARAM_CFG gc_stWdgParamCfg = WDG_CFG_TAB;

/*-------------------------------------------------------------------
Function: BSW_MCAL_WDGInit
Description: Enable the watch-dog timer
Input: none
Output: none
Return: none
----------------------------------------------------------------------*/
void bsw_mcal_watchdog_init(void)
{
#if (EXTERN_WATCHDOG_ENABLE == 0)
    UINT16 u16WdCr_val       = 0;

     EALLOW;

         WdRegs.SCSR.all = (gc_stWdgParamCfg.emWdgActType == WDG_RESET_TYPE)? 0x00:0x02;

     /*--WDPRECLKDIV[11-8]= gc_stWdgParamCfg.emWdgPeriod_ms;RSV[7]= 0;WDDIS[6]= 0;WDCHK[5-3]= 101; WDPS[2-0] = 111;*/
     u16WdCr_val = ((UINT16)gc_stWdgParamCfg.emWdgPeriod_ms)<<8 | 0b101111;
     //WdRegs.WDCR.all  = 0;//Enable the WDG
     WdRegs.WDCR.all  = u16WdCr_val;
     EDIS;

    bsw_mcal_feed_watchdog();
#else
     extern_watchdog_init();
#endif
}

//
// ServiceDog - This function resets the watchdog timer.
// Enable this function for using ServiceDog in the application
//
void bsw_mcal_feed_watchdog(void)
{
    EALLOW;
    WdRegs.WDKEY.bit.WDKEY = 0x55;
    WdRegs.WDKEY.bit.WDKEY = 0xAA;
    EDIS;
}


//
// DisableDog - This function disables the watchdog timer.
//
void bsw_mcal_disable_watchdog(void)
{
    volatile Uint16 temp;
    EALLOW;

    //
    // Grab the clock config so we don't clobber it
    //
    temp = WdRegs.WDCR.all & 0x0F07;
    WdRegs.WDCR.all = 0x0068 | temp;
    EDIS;
}

