/*********************************************************************
File name:       BSW_MCAL_PWM.c 
Purpose :
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 *
**********************************************************************/
#include "../MCAL/MCAL_INC/BSW_MCAL_PWM.h"

volatile struct EPWM_REGS *p_stPwmChannel[] = {&EPwm1Regs,&EPwm2Regs,&EPwm3Regs,&EPwm4Regs,\
                                               &EPwm5Regs,&EPwm6Regs,&EPwm7Regs};

const struct EPWMx_CFG_TB gc_stEpwmTbCfgParam[] =  EPWM_CFG_TB_TAB;
const struct EPWMx_CFG_CC gc_stEpwmCcCfgParam[] =  EPWM_CFG_CC_TAB;
const struct EPWMx_CFG_AQ gc_stEpwmAqCfgParam[] =  EPWM_CFG_AQ_TAB;
const struct EPWMx_CFG_DB gc_stEpwmDbCfgParam[] =  EPWM_CFG_DB_TAB;
const struct EPWMx_CFG_TZ gc_stEpwmTzCfgParam[] =  EPWM_CFG_TZ_TAB;
const struct EPWMx_CFG_ET gc_stEpwmEtCfgParam[] =  EPWM_CFG_ET_TAB;
const struct EPWMx_CFG_DC gc_stEpwmDcCfgParam[] =  EPWM_CFG_DC_TAB;
const struct EPWMx_CFG_HR gc_stEpwmHrCfgParam[] =  EPWM_CFG_HR_TAB;
const struct SYNC_CFG_OUT_IN_SRC gc_stSyncCfgPara =  EPWM_CFG_SYNCSELECT_TAB;

static inline void EPWM_SetupTbSubmodule(struct EPWMx_CFG_TB TbCfgInfo)
{
    p_stPwmChannel[TbCfgInfo.emPwmChannel]->TBCTL.bit.HSPCLKDIV = TB_DIV1;
    p_stPwmChannel[TbCfgInfo.emPwmChannel]->TBCTL.bit.CLKDIV = TB_DIV1;
    p_stPwmChannel[TbCfgInfo.emPwmChannel]->TBCTL.bit.CTRMODE = TbCfgInfo.TB_CTRMODE_VAL;
    p_stPwmChannel[TbCfgInfo.emPwmChannel]->TBCTL.bit.PHSEN = TbCfgInfo.TB_PHSEN_VAL;
    p_stPwmChannel[TbCfgInfo.emPwmChannel]->TBCTL.bit.PRDLD = TbCfgInfo.TB_PRDLD_VAL;

    p_stPwmChannel[TbCfgInfo.emPwmChannel]->TBCTL.bit.PHSDIR = TbCfgInfo.TB_PHSDIR_VAL;

    p_stPwmChannel[TbCfgInfo.emPwmChannel]->EPWMSYNCINSEL.bit.SEL = TbCfgInfo.SYNCINSEL_VAL;
    p_stPwmChannel[TbCfgInfo.emPwmChannel]->EPWMSYNCOUTEN.all = TbCfgInfo.SYNCOUTEN_VAL;

    p_stPwmChannel[TbCfgInfo.emPwmChannel]->TBPRD= TbCfgInfo.u16PrdLdVal;
    p_stPwmChannel[TbCfgInfo.emPwmChannel]->TBPHS.bit.TBPHS = TbCfgInfo.u16PhaseVal;        /* Disable phase loading */
    p_stPwmChannel[TbCfgInfo.emPwmChannel]->TBCTR= 0x0000;
}
static inline void EPWM_SetupCcSubmodule(struct EPWMx_CFG_CC CcCfgInfo)
{
    p_stPwmChannel[CcCfgInfo.emPwmChannel]->CMPCTL.bit.SHDWAMODE = CcCfgInfo.CC_SHDWAMODE_VAL;   //enable shadow register
    p_stPwmChannel[CcCfgInfo.emPwmChannel]->CMPCTL.bit.SHDWBMODE = CcCfgInfo.CC_SHDWBMODE_VAL;
    p_stPwmChannel[CcCfgInfo.emPwmChannel]->CMPCTL.bit.LOADAMODE = CcCfgInfo.CC_LOADAMODE_VAL; /* Load on PRD */
    p_stPwmChannel[CcCfgInfo.emPwmChannel]->CMPCTL.bit.LOADBMODE = CcCfgInfo.CC_LOADBMODE_VAL;

    p_stPwmChannel[CcCfgInfo.emPwmChannel]->CMPA.bit.CMPA = CcCfgInfo.u16CmpaVal;    /* Set compare A value */
    p_stPwmChannel[CcCfgInfo.emPwmChannel]->CMPB.bit.CMPB = CcCfgInfo.u16CmpbVal;    /* Set Compare B value */
}
static inline void EPWM_SetupAqSubmodule(struct EPWMx_CFG_AQ AqCfgInfo)
{
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.CAD = AqCfgInfo.AQ_CTLA_CAD_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.CAU = AqCfgInfo.AQ_CTLA_CAU_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.CBD = AqCfgInfo.AQ_CTLA_CBD_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.CBU = AqCfgInfo.AQ_CTLA_CBU_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.PRD = AqCfgInfo.AQ_CTLA_PRD_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.ZRO = AqCfgInfo.AQ_CTLA_ZRO_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.CAD = AqCfgInfo.AQ_CTLB_CAD_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.CAU = AqCfgInfo.AQ_CTLB_CAU_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.CBD = AqCfgInfo.AQ_CTLB_CBD_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.CBU = AqCfgInfo.AQ_CTLB_CBU_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.PRD = AqCfgInfo.AQ_CTLB_PRD_VAL;
    p_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.ZRO = AqCfgInfo.AQ_CTLB_ZRO_VAL;
}
static inline void EPWM_SetupDbSubmodule(struct EPWMx_CFG_DB DbCfgInfo)
{
    p_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL.bit.OUT_MODE = DbCfgInfo.DB_OUT_MODE_VAL;
    p_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL.bit.POLSEL = DbCfgInfo.DB_POLSEL_VAL;
    p_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL.bit.IN_MODE = DbCfgInfo.DB_IN_MODE_VAL;
    p_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL.bit.OUTSWAP = DbCfgInfo.DB_OUTSWAP_VAL;

    p_stPwmChannel[DbCfgInfo.emPwmChannel]->DBRED.bit.DBRED = DbCfgInfo.u16REDval;
    p_stPwmChannel[DbCfgInfo.emPwmChannel]->DBFED.bit.DBFED = DbCfgInfo.u16CFEDval;
    p_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL2.bit.SHDWDBCTLMODE = DbCfgInfo.DB_SHDWDBCTLMODE_VAL;
    p_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL2.bit.LOADDBCTLMODE = DbCfgInfo.DB_LOADDBCTLMODE_VAL;
}
#if 0
void EPWM_SetupPcSubmodule(struct EPWMx_CFG_PC PcCfgInfo)
{
    //p_stPwmChannel[PcCfgInfo.emPwmChannel]->PCCTL.bit.CHPEN = 0;
}
#endif
void EPWM_SetupTzSubmodule(struct EPWMx_CFG_TZ TzCfgInfo)
{
    EALLOW;
    p_stPwmChannel[TzCfgInfo.emPwmChannel]->TZSEL.bit.OSHT1 = TzCfgInfo.TZ_SEL_OSHT1_VAL;
    p_stPwmChannel[TzCfgInfo.emPwmChannel]->TZSEL.bit.DCAEVT1 = TzCfgInfo.TZ_SET_DCAEVT1_VAL;
    p_stPwmChannel[TzCfgInfo.emPwmChannel]->TZSEL.bit.DCAEVT2 = TzCfgInfo.TZ_SET_DCAEVT2_VAL;
    p_stPwmChannel[TzCfgInfo.emPwmChannel]->TZDCSEL.bit.DCAEVT1 = TzCfgInfo.TZ_DCSEL_DCAEVT1_VAL;
    p_stPwmChannel[TzCfgInfo.emPwmChannel]->TZDCSEL.bit.DCAEVT2 = TzCfgInfo.TZ_DCSEL_DCAEVT2_VAL;

    p_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.DCAEVT1   = TZ_NO_CHANGE ;
    p_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.DCAEVT2   = TZ_NO_CHANGE ;
    p_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.TZA   = TzCfgInfo.TZ_CTL_TZA_VAL ;
    p_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.TZB   = TzCfgInfo.TZ_CTL_TZB_VAL ;
    EDIS;
}
static inline void EPWM_SetupEtSubmodule(struct EPWMx_CFG_ET EtCfgInfo)
{
    /*ET submodule*/

    p_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCAEN = EtCfgInfo.ET_SOCAEN_VAL;             // Disable SOC on A group
    p_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL = EtCfgInfo.ET_SOCASEL_VAL;  // Select SOC on up-count
    p_stPwmChannel[EtCfgInfo.emPwmChannel]->ETPS.bit.SOCAPRD = EtCfgInfo.ET_SOCAPRD_VAL;         // Generate pulse on 1st event

    //PFC_EPWM_REGS.ETSEL.bit.INTSELCMP =
    p_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSEL = EtCfgInfo.ET_INTSEL_VAL;
    p_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTEN  = EtCfgInfo.ET_INTEN_VAL;             //ENABLE int
    p_stPwmChannel[EtCfgInfo.emPwmChannel]->ETPS.bit.INTPRD = EtCfgInfo.ET_INTPRD_VAL;         // Generate pulse on 1st event
}
void EPWM_SetupDcSubmodule(struct EPWMx_CFG_DC DcCfgInfo)
{
    EALLOW;
    p_stPwmChannel[DcCfgInfo.emPwmChannel]->DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMBINATION;
    p_stPwmChannel[DcCfgInfo.emPwmChannel]->DCAHTRIPSEL.all = DcCfgInfo.u16DC_DCAHTRIPSEL_VAL;
    p_stPwmChannel[DcCfgInfo.emPwmChannel]->DCACTL.bit.EVT2SRCSEL = DC_EVT2;
    EDIS;
}

void EPWM_SetupHRSubmodule(struct EPWMx_CFG_HR HrCfgInfo)
{
    EALLOW;
    p_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.EDGMODE      = HrCfgInfo.HR_EDGMODE_VAL;
    p_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.CTLMODE      = HrCfgInfo.HR_CTLMODE_VAL;
    p_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.HRLOAD       = HrCfgInfo.HR_HRLOAD_VAL;
    p_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.EDGMODEB     = HrCfgInfo.HR_EDGMODEB_VAL;
    p_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.CTLMODEB     = HrCfgInfo.HR_CTLMODEB_VAL;
    p_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.HRLOADB      = HrCfgInfo.HR_HRLOADB_VAL;
    p_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.AUTOCONV     = HrCfgInfo.HR_AUTOCONV_VAL;
    p_stPwmChannel[HrCfgInfo.emPwmChannel]->HRPCTL.bit.TBPHSHRLOADE = HrCfgInfo.HR_TBPHSHRLOADE_VAL;
    p_stPwmChannel[HrCfgInfo.emPwmChannel]->HRPCTL.bit.HRPE         = HrCfgInfo.HR_HRPE_VAL;
    EDIS;
}

void SYNC_SocInit (void)
{
    EALLOW;
    SyncSocRegs.SYNCSELECT.bit.SYNCOUT = gc_stSyncCfgPara.SYNC_OUT_VAL;
    EDIS;
}
void bsw_mcal_sf_ePWM_init(void)
{
    unsigned int i = 0;

    BSW_MCAL_DisTBCLKSYNC();
    SYNC_SocInit();
    for(i = 0;i < (sizeof(gc_stEpwmTbCfgParam)/sizeof(struct EPWMx_CFG_TB)); i++)
    {
        EPWM_SetupTbSubmodule(gc_stEpwmTbCfgParam[i]);
        EPWM_SetupCcSubmodule(gc_stEpwmCcCfgParam[i]);
        EPWM_SetupAqSubmodule(gc_stEpwmAqCfgParam[i]);
        EPWM_SetupDbSubmodule(gc_stEpwmDbCfgParam[i]);
        p_stPwmChannel[i]->PCCTL.bit.CHPEN = 0;
        EPWM_SetupTzSubmodule(gc_stEpwmTzCfgParam[i]);
        EPWM_SetupEtSubmodule(gc_stEpwmEtCfgParam[i]);
        EPWM_SetupDcSubmodule(gc_stEpwmDcCfgParam[i]);

        EPWM_SetupHRSubmodule(gc_stEpwmHrCfgParam[i]);
    }
    EPWM_CLOSE();
    BSW_MCAL_EnTBCLKSYNC();
}
