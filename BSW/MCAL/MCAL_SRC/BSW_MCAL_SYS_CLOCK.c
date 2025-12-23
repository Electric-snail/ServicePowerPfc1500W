/*****************************************************************************************************************
* File name:       BSW_MCAL_SYS.c 
* Purpose  :        
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
******************************************************************************************************************/
#include "CHIP_PACK/common/include/F28x_Project.h"
#include "PUBLIC_INC/ASSERT.H"
#include "HARDWARE_ENV_CFG.h"
#include "MCAL_INC/BSW_MCAL_SYS_CLOCK.h"

const SYS_CLK_CFG gc_stSysClkParamCfg = SYS_CLK_CFG_TAB;

static float gs_f32SysClkFreq  = 0;
static float gs_f32LpsClkFreq  = 0;
static float gs_f32PllRawFreq  = 0; //PLL raw output frequency default
static float gs_f32PllVcoFreq   =  0;
static float gs_f32IntClkFreq   = 0;
#define   SYSREF_LOST_MCD_EN_BIT     6
#define   SYSREF_LOSTSCLR_BIT        		5
#define   MCLKCLR_BIT                				1

void InitPeripheralClocksUser(void)
{
    EALLOW;

    CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 0;
    CpuSysRegs.PCLKCR0.bit.CPUTIMER1 = 1;
    CpuSysRegs.PCLKCR0.bit.CPUTIMER2 = 1;
    //High precise pwm clock
    CpuSysRegs.PCLKCR0.bit.HRCAL = 1;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM2 = 0;
    CpuSysRegs.PCLKCR2.bit.EPWM3 = 0;
    CpuSysRegs.PCLKCR2.bit.EPWM4 = 0;
    CpuSysRegs.PCLKCR2.bit.EPWM5 = 0;
    CpuSysRegs.PCLKCR2.bit.EPWM6 = 0;
    CpuSysRegs.PCLKCR2.bit.EPWM7 = 0;

    CpuSysRegs.PCLKCR3.bit.ECAP1 = 0;
    CpuSysRegs.PCLKCR3.bit.ECAP2 = 0;

    CpuSysRegs.PCLKCR4.bit.EQEP1 = 0;

    CpuSysRegs.PCLKCR7.bit.SCI_A = 0;
    CpuSysRegs.PCLKCR7.bit.SCI_B = 1;
    CpuSysRegs.PCLKCR7.bit.SCI_C = 0;

    CpuSysRegs.PCLKCR8.bit.SPI_A = 0;

    CpuSysRegs.PCLKCR9.bit.I2C_A = 0;
    CpuSysRegs.PCLKCR9.bit.I2C_B = 0;

    CpuSysRegs.PCLKCR10.bit.CAN_A = 0;

    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_C = 1;

    CpuSysRegs.PCLKCR14.bit.CMPSS1 = 1;
    CpuSysRegs.PCLKCR14.bit.CMPSS2 = 0;
    CpuSysRegs.PCLKCR14.bit.CMPSS3 = 1;
    CpuSysRegs.PCLKCR14.bit.CMPSS4 = 0;

    CpuSysRegs.PCLKCR21.bit.DCC0  	= 1;

    CpuSysRegs.PCLKCR27.bit.EPG1  = 0;

    EDIS;
}

void bsw_mcal_sys_clock_init(void)
{
    UINT16 u16clock_source;
    UINT16 u16SysDivReg = 0;
    UINT16 u16OdivReg     = 0;
    UINT16 u16ImultReg    = 0;
    UINT16 u16RefDivReg = 0;
    float f32SrcClkFrq = gc_stSysClkParamCfg.f32ClkSrcFreq;
    //Add the u16imult,u16fmult,u16divsel the calculate based on clock_source.  jiang
    ASSERT_RETURN(f32SrcClkFrq   <   4.0);
    ASSERT_RETURN((gc_stSysClkParamCfg.u16SysClkOutFreqIndex != SYS_CLK_OUT_FREQ_60M_INDEX)\
				  	  	  	  	  &&(gc_stSysClkParamCfg.u16SysClkOutFreqIndex != SYS_CLK_OUT_FREQ_80M_INDEX)\
								  &&(gc_stSysClkParamCfg.u16SysClkOutFreqIndex != SYS_CLK_OUT_FREQ_100M_INDEX)\
								  &&(gc_stSysClkParamCfg.u16SysClkOutFreqIndex != SYS_CLK_OUT_FREQ_120M_INDEX));

    u16clock_source = gc_stSysClkParamCfg.emSysClkSrc;
    //0.1 is the error tolerance
    if(f32SrcClkFrq <= 10)					u16RefDivReg = 1;
    else if(f32SrcClkFrq <= 15)			u16RefDivReg = 2;
    else  												u16RefDivReg = 3;

	gs_f32IntClkFreq = f32SrcClkFrq/(u16RefDivReg + 1);

    switch(gc_stSysClkParamCfg.u16SysClkOutFreqIndex){
        case SYS_CLK_OUT_FREQ_60M_INDEX:
        	gs_f32PllRawFreq = 120.0f;
            gs_f32SysClkFreq = 60.0f;
            gs_f32PllVcoFreq  = 480.0f;
        break;
        case SYS_CLK_OUT_FREQ_80M_INDEX:
        	gs_f32PllRawFreq = 160.0f;
            gs_f32SysClkFreq = 80.0f;
            gs_f32PllVcoFreq  = 480.0f;
        break;
        case SYS_CLK_OUT_FREQ_100M_INDEX:
        	gs_f32PllRawFreq = 200.0f;
            gs_f32SysClkFreq = 100.0f;
            gs_f32PllVcoFreq  = 400.0f;
        break;
        case SYS_CLK_OUT_FREQ_120M_INDEX:
        	gs_f32PllRawFreq = 120.0f;
            gs_f32SysClkFreq = 120.0f;
            gs_f32PllVcoFreq  = 480.0f;
        break;
        default:
            break;
    }
    u16SysDivReg       = (UINT16)(gs_f32PllRawFreq/(gs_f32SysClkFreq * 2.0f));
    u16OdivReg          = ((UINT16)(gs_f32PllVcoFreq/gs_f32PllRawFreq)) - 1;
    u16ImultReg 			= gs_f32PllVcoFreq/gs_f32IntClkFreq;

    InitSysPll(u16clock_source,  		 u16ImultReg, 			u16RefDivReg, 			u16OdivReg, 			u16SysDivReg, 			SYSCTL_DCC_BASE0);
    //Configure the low peripheral lock prescale
    EALLOW;
    ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = gc_stSysClkParamCfg.emLspClkPrec;
    EDIS;

    if (gc_stSysClkParamCfg.emLspClkPrec)
    {
        gs_f32LpsClkFreq = gs_f32SysClkFreq/(gc_stSysClkParamCfg.emLspClkPrec*2);
    }
    else
    {
        gs_f32LpsClkFreq = gs_f32SysClkFreq;
    }

    //Check the clock configure is right  jiang
    InitPeripheralClocksUser();

    //MCD initial; using the INTOSC1 to monitor the OSCLK(XTAL_OSC_SRC); as the OSCLK is the 7bit counter,
    //the OSCLK is the 13bit counter, so when the OSCLK is below the 10M/64 = 156.25k, the error will happlen
    EALLOW;
    //OSCCLK Connected, and MCD circuit enable, clear all the flag
    ClkCfgRegs.MCDCR.all = (1U << SYSREF_LOST_MCD_EN_BIT) | (1U << SYSREF_LOSTSCLR_BIT) | (1 << MCLKCLR_BIT);
    EDIS;
}

float SYS_CLK_GetSysClkFreq(void)
{
    return gs_f32SysClkFreq;
}

float SYS_CLK_GetLpsClkFreq(void)
{
    return gs_f32LpsClkFreq;
}

float SYS_CLK_GetPllRawClkFreq(void)
{
    return gs_f32PllRawFreq;
}

