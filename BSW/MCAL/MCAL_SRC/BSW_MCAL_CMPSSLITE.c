/*
 * BSW_MCAL_CMPSSLITE.c
 *
 *  Created on: 2024.06.06
 *      Author: rjgslg
 */

#include <BSW/CHIP_PACK/common/include/F28x_Project.h>
#include <BSW/MCAL/MCAL_INC/BSW_MCAL_CMPSSLITE.h>

extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;
volatile struct CMPSS_LITE_REGS *p_stCmpssLiteChannel[] = {&CmpssLite2Regs,&CmpssLite3Regs,&CmpssLite4Regs};

const ASYSCTL_CMPMXSEL          gc_stAsysCmpssLiteCfgParm[] = ASYSCTL_CMPMXSEL_TAB;
const CMPSSLITE_DAC_CFG         gc_stCmpssLiteDacCfgParm[]  = CMPSSLITE_DAC_CFG_TAB;
const CMPSSLITE_CTRIPFILT_CFG   gc_stCmpssLiteFiltCfgParm[]  = CMPSSLITE_FIL_CFG_TAB;
const CMPSSLITE_CTL_CFG         gc_stCmpssLiteCtlCfgParm[]  = CMPSSLITE_CTL_CFG_TAB;

static inline void AsysCmpssCfg(ASYSCTL_CMPMXSEL AsysCmpssCfgParm)
{
    UINT16 shif;
    shif = (UINT16)AsysCmpssCfgParm.emCmpssModule*3;
    EALLOW;
    AnalogSubsysRegs.CMPHPMXSEL.all |= AsysCmpssCfgParm.CMPxPMXSEL_H<<shif;
    AnalogSubsysRegs.CMPLPMXSEL.all |= AsysCmpssCfgParm.CMPxPMXSEL_L<<shif;
    EDIS;
}

static inline void CmpssDacCfg(CMPSSLITE_DAC_CFG CmpssDacCfgParm)
{
    EALLOW;
    p_stCmpssLiteChannel[CmpssDacCfgParm.emCmpssModule]->COMPDACHCTL.bit.SWLOADSEL = CmpssDacCfgParm.SwloadCLKSelect;
    p_stCmpssLiteChannel[CmpssDacCfgParm.emCmpssModule]->DACHVALS.bit.DACVAL       = CmpssDacCfgParm.CmpHiVal;
    p_stCmpssLiteChannel[CmpssDacCfgParm.emCmpssModule]->DACLVALS.bit.DACVAL       = CmpssDacCfgParm.CmpLoVal;
    EDIS;
}

static inline void CmpssFilCfg(CMPSSLITE_CTRIPFILT_CFG CmpssFilCfgParm)
{
    EALLOW;
    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCLKCTL            = CmpssFilCfgParm.CTRIPFILT_ClkPreScal_H;
//    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCTL.bit.FILTINSEL = CmpssFilCfgParm.CTRIPFILT_InSel_H;
    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCTL.bit.SAMPWIN   = CmpssFilCfgParm.CTRIPFILT_SampWin_H;
    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCTL.bit.THRESH    = CmpssFilCfgParm.CTRIPFILT_Thrshld_H;
    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCTL.bit.FILINIT   = CmpssFilCfgParm.CTRIPFILT_Init_H;

    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCLKCTL            = CmpssFilCfgParm.CTRIPFILT_ClkPreScal_L;
//    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCTL.bit.FILTINSEL = CmpssFilCfgParm.CTRIPFILT_InSel_L;
    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCTL.bit.SAMPWIN   = CmpssFilCfgParm.CTRIPFILT_SampWin_L;
    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCTL.bit.THRESH    = CmpssFilCfgParm.CTRIPFILT_Thrshld_L;
    p_stCmpssLiteChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCTL.bit.FILINIT   = CmpssFilCfgParm.CTRIPFILT_Init_L;

    EDIS;
}



static inline void CmpssCtlCfg(CMPSSLITE_CTL_CFG CmpssCtlCfgParm)
{
    UINT16 times = 0;

    EALLOW;
    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPHSOURCE  = CmpssCtlCfgParm.COMPCTL_CMPINSRC_H;
    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPHINV     = CmpssCtlCfgParm.COMPCTL_CMPOUTINV_H;
    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.CTRIPHSEL    = CmpssCtlCfgParm.COMPCTL_CTRIPSEL_H;
    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.CTRIPOUTHSEL = CmpssCtlCfgParm.COMPCTL_CTRIPOUTSEL_H;
    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.ASYNCHEN     = CmpssCtlCfgParm.COMPCTL_ASYNCEN_H;

    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPLSOURCE  = CmpssCtlCfgParm.COMPCTL_CMPINSRC_L;
    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPLINV     = CmpssCtlCfgParm.COMPCTL_CMPOUTINV_L;
    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.CTRIPLSEL    = CmpssCtlCfgParm.COMPCTL_CTRIPSEL_L;
    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.CTRIPOUTLSEL = CmpssCtlCfgParm.COMPCTL_CTRIPOUTSEL_L;
    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.ASYNCLEN     = CmpssCtlCfgParm.COMPCTL_ASYNCEN_L;

    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPHYSCTL.bit.COMPHYS = CmpssCtlCfgParm.emCOMPHYSCTL_HYSTSET;

    while ((p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPSTS.all != 0) && (times < 1000))
    {
        times ++;
        p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPSTSCLR.bit.HLATCHCLR = 1;
        p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPSTSCLR.bit.LLATCHCLR = 1;
    }

    p_stCmpssLiteChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPDACE = CmpssCtlCfgParm.COMPCTL_CMPDACEN;

    EDIS;
}

void BSW_MCAL_CMPSSLITEInit(void)
{
    UINT16 i = 0;

    for(i = 0;i < (sizeof(gc_stAsysCmpssLiteCfgParm)/sizeof(ASYSCTL_CMPMXSEL)); i++)
    {
        AsysCmpssCfg(gc_stAsysCmpssLiteCfgParm[i]);
        CmpssDacCfg(gc_stCmpssLiteDacCfgParm[i]);
        CmpssFilCfg(gc_stCmpssLiteFiltCfgParm[i]);
        CmpssCtlCfg(gc_stCmpssLiteCtlCfgParm[i]);


    }

}

