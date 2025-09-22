/*********************************************************************
File name:       BSW_MCAL_WDG.h
Purpose :

 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 *
**********************************************************************/

#ifndef BSW_MCAL_WDG_H
#define BSW_MCAL_WDG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <PUBLIC_INC/AUTO_REGISTER.H>

enum WDG_ACTION_TYPE{
    WDG_RESET_TYPE      = 0,
    WDG_INTERRUPT_TYPE  = 1,
};

enum WDG_PERIOD_MS{
    WDG_PERIOD_26MS    = 0xB,
    WDG_PERIOD_52MS    = 0xC,
    WDG_PERIOD_104MS   = 0xD,
    WDG_PERIOD_209MS   = 0xE,
    WDG_PERIOD_419MS   = 0xF,
    WDG_PERIOD_838MS   = 0x0,
    WDG_PERIOD_1677MS  = 0x1,
    WDG_PERIOD_3355MS  = 0x2,
    WDG_PERIOD_6710MS  = 0x3,
};

typedef struct {
      enum WDG_PERIOD_MS    emWdgPeriod_ms;        //Unit: mS;
      enum WDG_ACTION_TYPE  emWdgActType;
}WDG_PARAM_CFG;

/***emWdgPeriod_ms****emWdgActType***/
#define  WDG_CFG_TAB        \
{\
    WDG_PERIOD_52MS,  WDG_RESET_TYPE    \
}

extern void bsw_mcal_feed_watchdog(void);
extern void bsw_mcal_disable_watchdog(void);
extern void bsw_mcal_watchdog_init(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================
