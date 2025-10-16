/*****************************************************************************************************************
* File name:       BSW_MCAL_SYS.c
* Purpose  :       Including power system initial, DCSM module, DCC
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
******************************************************************************************************************/
#include "CHIP_PACK/common/include/F28x_Project.h"
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#include "MCAL_INC/BSW_MCAL_SYS.h"

#define   LOCK_BIT     15
#define   TYPE_BIT      0


void bsw_mcal_pie_err_isr(void){
    //enter the safety satatus;
    for(;;);
}

void bsw_mcal_sys_init(void)
{
    volatile unsigned long u32SysErrStatus;
    EALLOW;
    //Whether need to mask the EPG1_INT,RAM_ACC_VIOL system error??????
    SysStatusRegs.SYS_ERR_MASK.all              = 0xA5030810U;   //the relative FPU error will mask.

//jiang    SysStatusRegs.REGPARITY_ERR_FLG_MASK.all    = 0xA5000000U;   //No mask parity protection error
    //Clear the system error flag; Don't need EALLOW
    u32SysErrStatus = SysStatusRegs.SYS_ERR_INT_FLG.all;
    SysStatusRegs.SYS_ERR_INT_CLR.all           = u32SysErrStatus;
    //System error interrupt vector has been initialized in the BSW_MCAL_INT_CTRL.c

    CpuSysRegs.PIEVERRADDR.all                  = (UINT32)&bsw_mcal_pie_err_isr;

    //Configure the unused peripheral in the reset status;
    //jiang
    DevCfgRegs.ECAPTYPE.all                     = (1 << LOCK_BIT) | (1 << TYPE_BIT);
    DevCfgRegs.SOFTPRES2.all                    = 0x0000007E;                          //EPWM0 work in the normal status, EPWM1 ~EPWM7 work in the reset status
    DevCfgRegs.SOFTPRES3.all                    = 0x00000003;                          //the  ECAP2, ECAP1 in the reset status
    DevCfgRegs.SOFTPRES4.all                    = 0x00000001;                          //the EQEP1 in the reset status;
    DevCfgRegs.SOFTPRES7.all                    = 0x00000005;                          //the SCI_A,SCI_C in the reset status,  SCI_B in the normal status
    DevCfgRegs.SOFTPRES8.all                    = 0x00000001;                          //SPI_A in the reset status
    DevCfgRegs.SOFTPRES9.all                    = 0x00000003;                          //I2C_A,I2C_B in the reset status;
    DevCfgRegs.SOFTPRES10.all                   = 0x00000001;                          //CAN is in the reset status
    DevCfgRegs.SOFTPRES13.all                   = 0;                                   		  //ADC_A, ADC_C in the work status
    DevCfgRegs.SOFTPRES14.all                   = 0x0000000A;                        //CMPSS3 in the work status
    DevCfgRegs.SOFTPRES21.all                   = 0;                                   		//DCC0 is in the work status
    DevCfgRegs.SOFTPRES27.all                   = 0x00000001;                       //EPG1 is in the reset status
    DevCfgRegs.SOFTPRES28.all                   = 0;
    EDIS;

    Device_cal();
   // CsmUnlock();
}

