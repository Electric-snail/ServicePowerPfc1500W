/*
 * BSW_MCAL_XBAR.c
 *
 *  Created on: 2022/8/9
 *      Author: rjgslg
 */
#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL_INC/BSW_MCAL_XBAR.h"

const struct 		XBAR_INPUT_CFG_PARAM 			gc_stXbarInputCfgParam[] 	 =  INPUT_XBAR_CFG_TAB;
const struct 		XBAR_EPWM_CFG_PARAM     		gc_stXbarEpwmCfgParam[]  =  EPWM_XBAR_CFG_TAB;
const struct 		XBAR_OUTPUT_CFG_PARAM      	gc_stXbarOutputCfgParam[] =  OUTPUT_XBAR_CFG_TAB;

 void  input_xbar_cfg( const struct XBAR_INPUT_CFG_PARAM  *p_stXbarInputCfg)
{
		 volatile unsigned int *p_u16InputXbarReg = &InputXbarRegs.INPUT1SELECT;
		UINT16 u16RegIndex = p_stXbarInputCfg->emXbarInputId - XBAR_INPUT1_ID;
		p_u16InputXbarReg += u16RegIndex;
        // Write the requested pin to the appropriate input select register.
        EALLOW;
        *p_u16InputXbarReg = (UINT16)p_stXbarInputCfg->emXbarIputSrc;
        EDIS;
}

void epwm_xbar_cfg(const struct XBAR_EPWM_CFG_PARAM *p_stXbarPwmCfg){
	volatile   union   TRIP4MUX0TO15CFG_REG 		*p_TripxMux0To15CfgReg   	=  &EPwmXbarRegs.TRIP4MUX0TO15CFG;
	volatile 	union   TRIP4MUX16TO31CFG_REG 		*p_TripxMux16To31CfgReg 	= 	 &EPwmXbarRegs.TRIP4MUX16TO31CFG;
	volatile   union   TRIP4MUXENABLE_REG            *p_TripxEnableReg				 	= 	 &EPwmXbarRegs.TRIP4MUXENABLE;
	UINT16 u16RegIndex = p_stXbarPwmCfg->emEpwmTripId - XBAR_EPWM_TRIP4;
	UINT16 u16TempData0,  	u16TempData1;
	p_TripxMux0To15CfgReg 		+= (u16RegIndex << 1);
	p_TripxMux16To31CfgReg		+= (u16RegIndex << 1);
	p_TripxEnableReg						+= u16RegIndex;
	EALLOW;
	if(p_stXbarPwmCfg->u16OutInvEnable == 1)
		EPwmXbarRegs.TRIPOUTINV.all 	|=		(1 << u16RegIndex);
	else
		EPwmXbarRegs.TRIPOUTINV.all &=	~(1 << u16RegIndex);

	if(p_stXbarPwmCfg ->emXbarEpwmSrc0 != EPWM_SRC_INVALID){
		u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc0 & 0xF000) >> 8;
		if(u16TempData0 != 0x0000){
			u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc0 & 0x0F00) >> 8;
			p_TripxMux16To31CfgReg->all &=~ (3UL << u16TempData0);
			u16TempData1 = p_stXbarPwmCfg ->emXbarEpwmSrc0 & 0x00FF;
			p_TripxMux16To31CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}else{  //16 to 31
			u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc0 & 0x0F00) >> 8;
			p_TripxMux0To15CfgReg->all &=~ (3UL <<u16TempData0);
			u16TempData1 = p_stXbarPwmCfg ->emXbarEpwmSrc0 & 0x00FF;
			p_TripxMux0To15CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}
		u16TempData0 =  (p_stXbarPwmCfg ->emXbarEpwmSrc0 & 0xFF00) >> 8;
		p_TripxEnableReg->all |= (1 << u16TempData0);
	}
	if(p_stXbarPwmCfg ->emXbarEpwmSrc1 != EPWM_SRC_INVALID ){
		u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc1 & 0xF000) >> 8;
		if(u16TempData0 != 0x0000){
			u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc1 & 0x0F00) >> 8;
			p_TripxMux16To31CfgReg->all &=~ (3UL << u16TempData0);
			u16TempData1 = p_stXbarPwmCfg ->emXbarEpwmSrc1 & 0x00FF;
			p_TripxMux16To31CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}else{  //16 to 31
			u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc1 & 0x0F00) >> 8;
			p_TripxMux0To15CfgReg->all &=~ (3UL <<u16TempData0);
			u16TempData1 = p_stXbarPwmCfg ->emXbarEpwmSrc1 & 0x00FF;
			p_TripxMux0To15CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}
		u16TempData0 =  (p_stXbarPwmCfg ->emXbarEpwmSrc1 & 0xFF00) >> 8;
		p_TripxEnableReg->all |= (1 << u16TempData0);
	}
	if(p_stXbarPwmCfg ->emXbarEpwmSrc2 != EPWM_SRC_INVALID){
		u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc2 & 0xF000) >> 8;
		if(u16TempData0 != 0x0000){
			u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc2 & 0x0F00) >> 8;
			p_TripxMux16To31CfgReg->all &=~ (3UL << u16TempData0);
			u16TempData1 = p_stXbarPwmCfg ->emXbarEpwmSrc2 & 0x00FF;
			p_TripxMux16To31CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}else{  //16 to 31
			u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc2 & 0x0F00) >> 8;
			p_TripxMux0To15CfgReg->all &=~ (3UL <<u16TempData0);
			u16TempData1 = p_stXbarPwmCfg ->emXbarEpwmSrc2 & 0x00FF;
			p_TripxMux0To15CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}
		u16TempData0 =  (p_stXbarPwmCfg ->emXbarEpwmSrc2 & 0xFF00) >> 8;
		p_TripxEnableReg->all |= (1 << u16TempData0);
	}
	if(p_stXbarPwmCfg ->emXbarEpwmSrc3 != EPWM_SRC_INVALID){
		u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc3 & 0xF000) >> 8;
		if(u16TempData0 != 0x0000){
			u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc3 & 0x0F00) >> 8;
			p_TripxMux16To31CfgReg->all &=~ (3UL << u16TempData0);
			u16TempData1 = p_stXbarPwmCfg ->emXbarEpwmSrc3 & 0x00FF;
			p_TripxMux16To31CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}else{  //16 to 31
			u16TempData0 = (p_stXbarPwmCfg ->emXbarEpwmSrc3 & 0x0F00) >> 8;
			p_TripxMux0To15CfgReg->all &=~ (3UL <<u16TempData0);
			u16TempData1 = p_stXbarPwmCfg ->emXbarEpwmSrc3 & 0x00FF;
			p_TripxMux0To15CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}
		u16TempData0 =  (p_stXbarPwmCfg ->emXbarEpwmSrc3 & 0xFF00) >> 8;
		p_TripxEnableReg->all |= (1 << u16TempData0);
	}
	EDIS;
}


void  output_xbar_cfg( const struct XBAR_OUTPUT_CFG_PARAM  *p_stXbarOutputCfg)
{
	volatile   union   OUTPUT1MUX0TO15CFG_REG 		*p_OutputMux0To15CfgReg   	=  &OutputXbarRegs.OUTPUT1MUX0TO15CFG;
	volatile 	union   OUTPUT1MUX16TO31CFG_REG 		*p_OutputMux16To31CfgReg 	= 	 &OutputXbarRegs.OUTPUT1MUX16TO31CFG;
	volatile   union   OUTPUT1MUXENABLE_REG             *p_OutputEnableReg				 	= 	 &OutputXbarRegs.OUTPUT1MUXENABLE;
	UINT16 u16RegIndex = p_stXbarOutputCfg->emXbarOutputId - XBAR_OUTPUT1_ID;
	UINT16 u16TempData0,  	u16TempData1;
	p_OutputMux0To15CfgReg 		+= (u16RegIndex << 1);
	p_OutputMux16To31CfgReg	+= (u16RegIndex << 1);
	p_OutputEnableReg				    += u16RegIndex;
	EALLOW;
	if(p_stXbarOutputCfg->u16OutLatchEnable == 1)
		OutputXbarRegs.OUTPUTLATCHENABLE.all |= (1 << u16RegIndex);
	else
		OutputXbarRegs.OUTPUTLATCHENABLE.all &=	~(1 << u16RegIndex);

	if(p_stXbarOutputCfg->u16OutInvEnable == 1)
		OutputXbarRegs.OUTPUTINV.all |= (1 << u16RegIndex);
	else
		OutputXbarRegs.OUTPUTINV.all &=~(1 << u16RegIndex);

	if(p_stXbarOutputCfg ->emXbarOutputSrc0 != OUTPUT_SRC_INVALID){
		u16TempData0 = (p_stXbarOutputCfg ->emXbarOutputSrc0 & 0xF000) >> 8;
		if(u16TempData0 != 0x0000){
			u16TempData0 = (p_stXbarOutputCfg ->emXbarOutputSrc0 & 0x0F00) >> 8;
			p_OutputMux16To31CfgReg->all &=~ (3UL << u16TempData0);
			u16TempData1 = p_stXbarOutputCfg ->emXbarOutputSrc0 & 0x00FF;
			p_OutputMux16To31CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}else{  //16 to 31
			u16TempData0 = (p_stXbarOutputCfg->emXbarOutputSrc0 & 0x0F00) >> 8;
			p_OutputMux0To15CfgReg->all &=~ (3UL <<u16TempData0);
			u16TempData1 = p_stXbarOutputCfg ->emXbarOutputSrc0 & 0x00FF;
			p_OutputMux0To15CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}
		u16TempData0 =  (p_stXbarOutputCfg -> emXbarOutputSrc0 & 0xFF00) >> 8;
		p_OutputEnableReg->all |= (1 << u16TempData0);
	}

	if(p_stXbarOutputCfg ->emXbarOutputSrc1 != OUTPUT_SRC_INVALID){
		u16TempData0 = (p_stXbarOutputCfg ->emXbarOutputSrc1 & 0xF000) >> 8;
		if(u16TempData0 != 0x0000){
			u16TempData0 = (p_stXbarOutputCfg ->emXbarOutputSrc1 & 0x0F00) >> 8;
			p_OutputMux16To31CfgReg->all &=~ (3UL << u16TempData0);
			u16TempData1 = p_stXbarOutputCfg ->emXbarOutputSrc1 & 0x00FF;
			p_OutputMux16To31CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}else{  //16 to 31
			u16TempData0 = (p_stXbarOutputCfg->emXbarOutputSrc1 & 0x0F00) >> 8;
			p_OutputMux0To15CfgReg->all &=~ (3UL <<u16TempData0);
			u16TempData1 = p_stXbarOutputCfg ->emXbarOutputSrc1 & 0x00FF;
			p_OutputMux0To15CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}
		u16TempData0 =  (p_stXbarOutputCfg -> emXbarOutputSrc1 & 0xFF00) >> 8;
		p_OutputEnableReg->all |= (1 << u16TempData0);
	}

	if(p_stXbarOutputCfg ->emXbarOutputSrc2 != OUTPUT_SRC_INVALID){
		u16TempData0 = (p_stXbarOutputCfg ->emXbarOutputSrc2 & 0xF000) >> 8;
		if(u16TempData0 != 0x0000){
			u16TempData0 = (p_stXbarOutputCfg ->emXbarOutputSrc2 & 0x0F00) >> 8;
			p_OutputMux16To31CfgReg->all &=~ (3UL << u16TempData0);
			u16TempData1 = p_stXbarOutputCfg ->emXbarOutputSrc2 & 0x00FF;
			p_OutputMux16To31CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}else{  //16 to 31
			u16TempData0 = (p_stXbarOutputCfg->emXbarOutputSrc2 & 0x0F00) >> 8;
			p_OutputMux0To15CfgReg->all &=~ (3UL <<u16TempData0);
			u16TempData1 = p_stXbarOutputCfg ->emXbarOutputSrc2 & 0x00FF;
			p_OutputMux0To15CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}
		u16TempData0 =  (p_stXbarOutputCfg -> emXbarOutputSrc2 & 0xFF00) >> 8;
		p_OutputEnableReg->all |= (1 << u16TempData0);
	}

	if(p_stXbarOutputCfg ->emXbarOutputSrc3 != OUTPUT_SRC_INVALID){
		u16TempData0 = (p_stXbarOutputCfg ->emXbarOutputSrc3 & 0xF000) >> 8;
		if(u16TempData0 != 0x0000){
			u16TempData0 = (p_stXbarOutputCfg ->emXbarOutputSrc3 & 0x0F00) >> 8;
			p_OutputMux16To31CfgReg->all &=~ (3UL << u16TempData0);
			u16TempData1 = p_stXbarOutputCfg ->emXbarOutputSrc3 & 0x00FF;
			p_OutputMux16To31CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}else{  //16 to 31
			u16TempData0 = (p_stXbarOutputCfg->emXbarOutputSrc3 & 0x0F00) >> 8;
			p_OutputMux0To15CfgReg->all &=~ (3UL <<u16TempData0);
			u16TempData1 = p_stXbarOutputCfg ->emXbarOutputSrc3 & 0x00FF;
			p_OutputMux0To15CfgReg->all |=(u16TempData1 <<  u16TempData0);
		}
		u16TempData0 =  (p_stXbarOutputCfg -> emXbarOutputSrc3 & 0xFF00) >> 8;
		p_OutputEnableReg->all |= (1 << u16TempData0);
	}
	EDIS;
}

void bsw_mcal_xbar_init(void)
{
    UINT16 i = 0;

    for(i = 0;		i < (sizeof(gc_stXbarInputCfgParam)/sizeof( struct XBAR_INPUT_CFG_PARAM)); 		i++)
    {
    		input_xbar_cfg(&gc_stXbarInputCfgParam[i]);
    }

    for(i = 0;		i < (sizeof(gc_stXbarEpwmCfgParam)/sizeof(struct XBAR_EPWM_CFG_PARAM)); 	i++)
    {
        	epwm_xbar_cfg(&gc_stXbarEpwmCfgParam[i]);
    }

    for(i = 0;		i < (sizeof(gc_stXbarOutputCfgParam)/sizeof(struct XBAR_OUTPUT_CFG_PARAM)); 		i++)
    {
    		output_xbar_cfg(&gc_stXbarOutputCfgParam[i]);
    }

    XbarRegs.XBARCLR1.all = 0xFFFFFFFF;  //Clear all the flag
    XbarRegs.XBARCLR2.all = 0xFFFFFFFF;  //Clear all the flag
    XbarRegs.XBARCLR3.all = 0xFFFFFFFF;  //Clear all the flag
    XbarRegs.XBARCLR4.all = 0xFFFFFFFF;  //Clear all the flag
}

