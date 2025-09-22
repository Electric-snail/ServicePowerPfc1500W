/*
 * BSW_MCAL_CMPSS.c
 *
 *  Created on: 2024.06.06
 *      Author: rjgslg
 */

#include <BSW/CHIP_PACK/common/include/F28x_Project.h>
#include <BSW/MCAL/MCAL_INC/BSW_MCAL_CMPSS.h>

extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;
volatile struct CMPSS_REGS *p_stCmpssChannel[] = {&Cmpss1Regs};

const ASYSCTL_CMPMXSEL gc_stAsysCmpssCfgParm[] = ASYSCTL_CMPMXSEL_TAB;
const CMPSS_DAC_CFG    gc_stCmpssDacCfgParm[]  = CMPSS_DAC_CFG_TAB;
const CMPSS_FIL_CFG    gc_stCmpssFilCfgParm[]  = CMPSS_FIL_CFG_TAB;
const CMPSS_CTL_CFG    gc_stCmpssCtlCfgParm[]  = CMPSS_CTL_CFG_TAB;

static inline void AsysCmpssCfg(ASYSCTL_CMPMXSEL AsysCmpssCfgParm);
static inline void CmpssDacCfg(CMPSS_DAC_CFG CmpssDacCfgParm);
static inline void CmpssFilCfg(CMPSS_FIL_CFG CmpssFilCfgParm);
static inline void CmpssCtlCfg(CMPSS_CTL_CFG CmpssCtlCfgParm);

static inline void AsysCmpssCfg(ASYSCTL_CMPMXSEL AsysCmpssCfgParm)
{
    UINT16 shif;
    shif = (UINT16)AsysCmpssCfgParm.emCmpssModule*3;
    EALLOW;
    AnalogSubsysRegs.CMPHPMXSEL.all |= AsysCmpssCfgParm.CMPxPMXSEL_H<<shif;
    AnalogSubsysRegs.CMPLPMXSEL.all |= AsysCmpssCfgParm.CMPxPMXSEL_L<<shif;
    EDIS;
}

static inline void CmpssDacCfg(CMPSS_DAC_CFG CmpssDacCfgParm)
{
    EALLOW;
    p_stCmpssChannel[CmpssDacCfgParm.emCmpssModule]->COMPDACHCTL.bit.SWLOADSEL = CmpssDacCfgParm.SwloadCLKSelect;
    p_stCmpssChannel[CmpssDacCfgParm.emCmpssModule]->COMPDACHCTL.bit.DACSOURCE = CmpssDacCfgParm.DACHVALA_SRC;
//   p_stCmpssChannel[CmpssDacCfgParm.emCmpssModule]->COMPDACLCTL.bit.DACSOURCE = CmpssDacCfgParm.DACLVALA_SRC;
    p_stCmpssChannel[CmpssDacCfgParm.emCmpssModule]->DACHVALS.bit.DACVAL       = CmpssDacCfgParm.CmpHiVal;
    p_stCmpssChannel[CmpssDacCfgParm.emCmpssModule]->DACLVALS.bit.DACVAL       = CmpssDacCfgParm.CmpLoVal;
    EDIS;
}

static inline void CmpssFilCfg(CMPSS_FIL_CFG CmpssFilCfgParm)
{
    EALLOW;
    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCLKCTL            = CmpssFilCfgParm.CTRIPFILT_ClkPreScal_H;
//jiang    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCTL.bit.FILTINSEL = CmpssFilCfgParm.CTRIPFILT_InSel_H;
    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCTL.bit.SAMPWIN   = CmpssFilCfgParm.CTRIPFILT_SampWin_H;
    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCTL.bit.THRESH    = CmpssFilCfgParm.CTRIPFILT_Thrshld_H;
    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPHFILCTL.bit.FILINIT   = CmpssFilCfgParm.CTRIPFILT_Init_H;

    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCLKCTL            = CmpssFilCfgParm.CTRIPFILT_ClkPreScal_L;
//jiang    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCTL.bit.FILTINSEL = CmpssFilCfgParm.CTRIPFILT_InSel_L;
    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCTL.bit.SAMPWIN   = CmpssFilCfgParm.CTRIPFILT_SampWin_L;
    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCTL.bit.THRESH    = CmpssFilCfgParm.CTRIPFILT_Thrshld_L;
    p_stCmpssChannel[CmpssFilCfgParm.emCmpssModule]->CTRIPLFILCTL.bit.FILINIT   = CmpssFilCfgParm.CTRIPFILT_Init_L;

    EDIS;
}




static inline void CmpssCtlCfg(CMPSS_CTL_CFG CmpssCtlCfgParm)
{
    UINT16 times = 0;

    EALLOW;
    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPHSOURCE  = CmpssCtlCfgParm.COMPCTL_CMPINSRC_H;
    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPHINV     = CmpssCtlCfgParm.COMPCTL_CMPOUTINV_H;
    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.CTRIPHSEL    = CmpssCtlCfgParm.COMPCTL_CTRIPSEL_H;
    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.CTRIPOUTHSEL = CmpssCtlCfgParm.COMPCTL_CTRIPOUTSEL_H;
    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.ASYNCHEN     = CmpssCtlCfgParm.COMPCTL_ASYNCEN_H;

    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPLSOURCE  = CmpssCtlCfgParm.COMPCTL_CMPINSRC_L;
    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPLINV     = CmpssCtlCfgParm.COMPCTL_CMPOUTINV_L;
    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.CTRIPLSEL    = CmpssCtlCfgParm.COMPCTL_CTRIPSEL_L;
    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.CTRIPOUTLSEL = CmpssCtlCfgParm.COMPCTL_CTRIPOUTSEL_L;
    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.ASYNCLEN     = CmpssCtlCfgParm.COMPCTL_ASYNCEN_L;

    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPHYSCTL.bit.COMPHYS = CmpssCtlCfgParm.emCOMPHYSCTL_HYSTSET;

    while ((p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPSTS.all != 0) && (times < 1000))
    {
        times ++;
        p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPSTSCLR.bit.HLATCHCLR = 1;
        p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPSTSCLR.bit.LLATCHCLR = 1;
    }

    p_stCmpssChannel[CmpssCtlCfgParm.emCmpssModule]->COMPCTL.bit.COMPDACE = CmpssCtlCfgParm.COMPCTL_CMPDACEN;

    EDIS;
}

void bsw_mcal_sf_cmpss_init(void)
{
    unsigned int i = 0;
    for(i = 0;i < (sizeof(gc_stAsysCmpssCfgParm)/sizeof(ASYSCTL_CMPMXSEL)); i++)
    {
        AsysCmpssCfg(gc_stAsysCmpssCfgParm[i]);
        CmpssDacCfg(gc_stCmpssDacCfgParm[i]);
        CmpssFilCfg(gc_stCmpssFilCfgParm[i]);
        CmpssCtlCfg(gc_stCmpssCtlCfgParm[i]);

    }

}

