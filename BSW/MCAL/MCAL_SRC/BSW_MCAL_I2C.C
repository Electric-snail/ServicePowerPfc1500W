/*
 * BSW_MCAL_I2C.C
 *
 *  Created on: 2025.8.20
 *      Author: jhb72
 */
#include "CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL_INC/BSW_MCAL_I2C.h"

const static I2C_ITEM_CFG gc_stI2cItemCfg[] = REG_I2C_ITEM_CFG_TAB;

void bsw_mcal_i2c_init(void){
	unsigned short i;
//jiang	float  f32LpsClkFreqK = 0;
	volatile struct I2C_REGS *pstI2ciReg;
	for(i = 0; i < sizeof(gc_stI2cItemCfg)/sizeof(I2C_ITEM_CFG); i ++){
		if(gc_stI2cItemCfg[i].emI2cId >= I2C_MAX_ID)
			continue;
		if(gc_stI2cItemCfg[i].emI2cId == I2CA_ID)  			pstI2ciReg = &I2caRegs;
		else if(gc_stI2cItemCfg[i].emI2cId == I2CB_ID) 		pstI2ciReg = &I2cbRegs;
		else continue;
		 EALLOW;
		 pstI2ciReg->I2CMDR.bit.IRS 	= 0;   //I2C in the reset mode
		 if(gc_stI2cItemCfg[i].emI2cMode == I2C_SLAVER){
				 pstI2ciReg->I2CMDR.bit.MST  = 0;  			//I2C in the slaver mode
				 pstI2ciReg->I2CMDR.bit.TRX  = 0;  				//I2C in the receive status
				 pstI2ciReg->I2CMDR.bit.BC 	= 0x0U;   		// Set the bit count to 8 bits per data byte
				 pstI2ciReg->I2COAR.all       		= gc_stI2cItemCfg[i].u8Addr;

		 }else{
			 pstI2ciReg->I2CMDR.bit.MST  = 1;  //I2C in the master mode
		 }
		 pstI2ciReg->I2CMDR.bit.FREE = 0x1; 	    // Set emulation mode to FREE
		 pstI2ciReg->I2CSTR.all 			= 0xFFFF;
		 pstI2ciReg->I2CIER.all 				= 0x78;     // Enable I2C Interrupts- Addressed as slave, Stop condition detected, Transmit-data-ready and Receive-data-ready
		 pstI2ciReg->I2CMDR.bit.IRS 	= 1;   //I2C in the normal mode
		 EDIS;
	}
}

void i2ca_reset(void){
	 EALLOW;
	I2caRegs.I2CMDR.bit.IRS 	= 0;   //I2C in the reset mode
	__asm(" NOP");
	__asm(" NOP");
	__asm(" NOP");
	__asm(" NOP");
	__asm(" NOP");
	__asm(" NOP");
	I2caRegs.I2CMDR.bit.IRS 	= 1;   //I2C in the normal mode
	 EDIS;
}

void i2cb_reset(void){
	 EALLOW;
	I2cbRegs.I2CMDR.bit.IRS 	= 0;   //I2C in the reset mode
	__asm(" NOP");
	__asm(" NOP");
	__asm(" NOP");
	__asm(" NOP");
	__asm(" NOP");
	__asm(" NOP");
	I2cbRegs.I2CMDR.bit.IRS 	= 1;   //I2C in the normal mode
	 EDIS;
}


