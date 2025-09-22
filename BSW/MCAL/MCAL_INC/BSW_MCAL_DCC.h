/*
 * BSW_MCAL_DCC.h
 *
 *  Created on: Sep 24, 2024
 *      Author: g8mqmx
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_DCC_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_DCC_H_

#include "../BSW/ENV_CFG/SOFTWARE_ENV_CFG.h"

//Pengyuan Chen 09/24/2024.Since the system clock frequency is still set to 100MHz,
//which is not expected. But all components are configured to this system clock.
//From my perspective, I am not sure if this is on purpose such that I leave this part
//for your decision. The DCC will be configured accordingly to 100 MHz.


/*===========================================================================*
 * Exported Type Declarations
 *===========================================================================*/
typedef enum DCC_SELF_TEST_RESULT_TAG
{
    DCC_SELF_TEST_INIT = 0x00U,
    DCC_SELF_TEST_PASS = 0x01U,
    DCC_SELF_TEST_FAIL = 0x02U
}
DCC_SELF_TEST_RESULT_T;

/*===========================================================================*
 * Exported Object Declarations
 *===========================================================================*/
extern DCC_SELF_TEST_RESULT_T g_emDCC0SelfTestResult;
extern DCC_SELF_TEST_RESULT_T g_emDCC1SelfTestResult;



//Fclk0 = 10MHz, Fsysclk = 100MHz
// If Fclk1>Fclk0, Async. Error (In Clock0 cycles) = 2 + 2*(Fsysclk/Fclk0) = 22
// Digitization error (In Clock0 cycles) = 8
// DCC Error = Async. Error + Digitization error = 30
//
// Window (in Cycles) = (DCC Error) / (0.01 * Tolerance)
// Window = 30 / (0.01 * 1) = 3000
//
// Frequency Error Allowed (In Clock0 Cycles)
//                       = Window * (Allowable Frequency Tolerance (in %) / 100)
//                       = 3000 * (3/100) = 90
//
// Total Error = DCC Error + Frequency Error Allowed = 30 + 90 = 120
//
// Counter0 = Window - Total Error   = 3000 - 120      = 2880
// Valid0   = 2 * Total Error        = 2 * 120         = 240
// Counter1 = Window x (Fclk1/Fclk0) = 3000 * (100/10) = 30000
//
// To simulate an error, we could configure count1 seed value as 34000.
// If just use the DCC regular monitor, we just counfigure Counter1 = 30000
// Note : Update the values if you are using a different PLL frequency
//
#define DCC0_VALID   240
#define DCC0_COUNT0  2880
#define DCC0_COUNT1  30000 // Set with a variance of 3200 counts over 40800

extern void bsw_mcal_sf_dcc_init(void);


#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_DCC_H_ */
