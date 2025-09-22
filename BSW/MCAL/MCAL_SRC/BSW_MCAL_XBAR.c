/*
 * BSW_MCAL_XBAR.c
 *
 *  Created on: 2022/8/9
 *      Author: rjgslg
 */
#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_XBAR.h"

const struct XBAR_INPUTNUM_CFG_PARAM gc_stXbarInputCfgParam[] =  INPUT_XBAR_CFG_TAB;
const struct XBAR_EPWM_CFG_PARAM     gc_stXbarEpwmCfgParam[]  =  EPWM_XBAR_CFG_TAB;
const struct XINTx_CFG_PARAM         gc_stXINTxCfgParam[]     =  XINTX_CFG_TAB;

 void  GPIO_setInputXbar( struct XBAR_INPUTNUM_CFG_PARAM XbarInputCfgInfo)
{
     volatile UINT16 *inputSelect_reg;
    /* Check the argument.*/
    if ((XbarInputCfgInfo.emGpioNum < GPIO_MAX_NUM) ||
        ((XbarInputCfgInfo.emGpioNum >= AGPIO224_NUM) &&
         (XbarInputCfgInfo.emGpioNum < AGPIO_MAX_NUM)))
    {
        inputSelect_reg = (volatile UINT16 *)&InputXbarRegs + ((UINT16)XbarInputCfgInfo.emInputSelect);

        /* Write the requested pin to the appropriate input select register.*/
        EALLOW;
        *inputSelect_reg = (UINT16)XbarInputCfgInfo.emGpioNum;
        EDIS;
    };
}

 volatile UINT32 *EPwm_xBarBaseAddr;
 volatile UINT32 *TripMuxCFG_reg;
 volatile UINT32 *TripMuxENABLE_reg;
 static void setEpwmXbar(struct XBAR_EPWM_CFG_PARAM XbarEpwmCfgInfo)
 {

     UINT16 shift = 0;

     shift = (UINT16)XbarEpwmCfgInfo.MUXES_NUM_VAL%16;

     EPwm_xBarBaseAddr = (Uint32 *)&EPwmXbarRegs;

     if(XbarEpwmCfgInfo.MUXES_NUM_VAL < XBAR_MUX16)
     {
         TripMuxCFG_reg = EPwm_xBarBaseAddr + ((UINT16)XbarEpwmCfgInfo.emTripNum>>1);
     }
     else
     {
         TripMuxCFG_reg = EPwm_xBarBaseAddr + (((UINT16)XbarEpwmCfgInfo.emTripNum >>1)+1);
     }

     TripMuxENABLE_reg = EPwm_xBarBaseAddr + 16 + ((UINT16)XbarEpwmCfgInfo.emTripNum>>2);
     /* Write the requested pin to the appropriate input select register.*/
     EALLOW;

     *TripMuxCFG_reg &= ~((UINT32)XbarEpwmCfgInfo.MUXES_VAL << (shift<<1));
     *TripMuxCFG_reg |= ((UINT32)XbarEpwmCfgInfo.MUXES_VAL << (shift<<1));

     *TripMuxENABLE_reg &= ~((UINT32)XbarEpwmCfgInfo.MUX_ENABLE_VAL << (UINT16)XbarEpwmCfgInfo.MUXES_NUM_VAL) ;
     *TripMuxENABLE_reg |= ((UINT32)XbarEpwmCfgInfo.MUX_ENABLE_VAL << (UINT16)XbarEpwmCfgInfo.MUXES_NUM_VAL) ;
     EPwmXbarRegs.TRIPOUTINV.all &= ~(UINT32)XbarEpwmCfgInfo.TRIPOUTINV_VAL;
     EPwmXbarRegs.TRIPOUTINV.all |=  (UINT32)XbarEpwmCfgInfo.TRIPOUTINV_VAL;
     EDIS;
 }



 void  setXINTx( struct XINTx_CFG_PARAM XINTxCfgInfo)
{
     UINT16 *XintBaseAddr;
     UINT16 *Xint_reg;
     XintBaseAddr = (UINT16 *)&XintRegs;
     Xint_reg = XintBaseAddr + (UINT16)XINTxCfgInfo.emXintSelect;

     *Xint_reg  = 0;
     *Xint_reg  |= (XINTxCfgInfo.CR_ENABLE_VAL | (XINTxCfgInfo.CR_POLARITY_VAL << 2));
}

void BSW_MCAL_xBarInit(void)
{
    UINT16 i = 0;

    for(i = 0;i < (sizeof(gc_stXbarInputCfgParam)/sizeof(struct XBAR_INPUTNUM_CFG_PARAM)); i++)
    {
        GPIO_setInputXbar(gc_stXbarInputCfgParam[i]);
    }

    for(i = 0;i < (sizeof(gc_stXbarEpwmCfgParam)/sizeof(struct XBAR_EPWM_CFG_PARAM)); i++)
    {
        setEpwmXbar(gc_stXbarEpwmCfgParam[i]);
    }

    for(i = 0;i < (sizeof(gc_stXINTxCfgParam)/sizeof(struct XINTx_CFG_PARAM)); i++)
    {
        setXINTx(gc_stXINTxCfgParam[i]);
    }
}

