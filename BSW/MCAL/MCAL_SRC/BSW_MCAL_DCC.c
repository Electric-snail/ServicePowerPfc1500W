/*
 * BSW_MCAL_DCC.c
 *
 *  Created on: Sep 24, 2024
 *      Author: Hongbo.Jiang
 */

#include "MCAL_INC/BSW_MCAL_DCC.h"
#include "CHIP_PACK/driverlib/dcc.h"


//
// Globals
//


DCC_SELF_TEST_RESULT_T g_emDCC0SelfTestResult = DCC_SELF_TEST_INIT;

//freq1 act as the f32ObjFreq, freq0 act as the f32RefFreq
void dcc_counter_seeds_config(FLOAT32 f32ObjFreq,FLOAT32 f32RefFreq,FLOAT32 tolerance,FLOAT32 f32RefFreqErr, FLOAT32 f32SysFreq)
{
    FLOAT32 f32TotalErr;
    FLOAT32 f32DccErr;
    FLOAT32 window;
    UINT32 count0;
    UINT32 valid;
    UINT32 count1;
    // If Fclk1 > Fclk0,
    //    Async. Error (In Clock0 cycles) = 2 + 2*(Fsysclk/Fclk0)
    // If Fclk1 < Fclk0,
    //    Async. Error (In Clock0 cycles) = 2*(Fclk0/Fclk1) + 2*(Fsysclk/Fclk0)
    if(f32ObjFreq > f32RefFreq)
    {
        f32DccErr = (2.0F + (2.0F * (f32SysFreq / f32RefFreq)));
    }
    else
    {
        f32DccErr = ((2.0F * (f32RefFreq /f32ObjFreq)) +
                       (2.0F * (f32SysFreq / f32RefFreq)));
    }
    // Digitization error = 8 Clock0 cycles
    f32DccErr += 8.0F;
    // Window (in Cycles) = (Total Error) / (0.01 * Tolerance)
    window = f32DccErr / (0.01F * tolerance);
    // Error due to variance in clock frequency =
    // window * (Allowable Frequency Tolerance (in %) / 100)
    f32TotalErr = f32DccErr + window * (f32RefFreqErr / 100.0F);

    //
    // DCC counter configuration :
    // Counter0 = Window - Total Error
    // Valid0 = 2 * Total Error
    // Counter1 = Window * (Fclk1 / Fclk0)
    //
    count0 = (UINT32)(window - f32TotalErr);
    valid  = (UINT32)(2.0f * f32TotalErr);
    count1 = (UINT32)(window * f32ObjFreq/f32RefFreq);

    // Set Counter 0 Seed
    HWREG(DCC0_BASE + DCC_O_CNTSEED0) = count0 & 0xFFFFFUL;
  /*  HWREGH(base + DCC_O_CNTSEED0 + 2U) = (HWREGH(base + DCC_O_CNTSEED0 + 2U) &
                                          DCC_SEED_REG_MASK) |
                                         ((uint32_t)(counter0 &
                                          DCC_SEED_CNT_MASK) >> 16U);*/
    // Set Valid Duration Counter 0 Seed
    HWREGH(DCC0_BASE + DCC_O_VALIDSEED0) = valid;

    //
    // Set Counter 1 Seed
    //
    HWREG(DCC0_BASE + DCC_O_CNTSEED1) = count1 & 0xFFFFFUL;
}

// DCC ISR will be directly registered in BSW_MCAL_INT_CTRL
// This MCAL_DCC is just used for configuring the DCC moudle.

void bsw_mcal_sf_dcc_init(void){
    // Clear Error & Done Flag
    HWREGH(DCC0_BASE + DCC_O_STATUS)    = DCC_STATUS_ERR | DCC_STATUS_DONE;

    HWREGH(DCC0_BASE + DCC_O_GCTRL)     = 0x5055;  //Continual mode, done disable, error disable, dcc disable

    HWREGH(DCC0_BASE + DCC_O_CLKSRC0)   = 0xA002;   //INTOSC2  for counter0
    HWREGH(DCC0_BASE + DCC_O_CLKSRC1)   = 0xA000;   //SYSPLL for counter1

    dcc_counter_seeds_config(100.0f,  10.0f,  5.0f,  2.0f, 100.0f);
    EINT;
    NOP;
    NOP;
    NOP;
    HWREGH(DCC0_BASE + DCC_O_GCTRL)     = 0x5000;  //Continual mode, done disable, error enable, dcc enable
}
