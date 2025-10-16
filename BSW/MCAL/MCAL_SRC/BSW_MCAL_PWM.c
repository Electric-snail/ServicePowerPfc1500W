/*********************************************************************
File name:       BSW_MCAL_PWM.c 
Purpose :
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 *
**********************************************************************/
#include "MCAL_INC/BSW_MCAL_PWM.h"

volatile struct EPWM_REGS *gp_stPwmChannel[] = {&EPwm1Regs,&EPwm2Regs,&EPwm3Regs,&EPwm4Regs,\
																								&EPwm5Regs,&EPwm6Regs,&EPwm7Regs};

const 		struct 		EPWMx_CFG_TB				gc_stEpwmTbCfgParam[] 		=  EPWM_CFG_TB_TAB;
const 		struct 		EPWMx_CFG_CC 				gc_stEpwmCcCfgParam[] 		=  EPWM_CFG_CC_TAB;
const 		struct 		EPWMx_CFG_AQ 				gc_stEpwmAqCfgParam[] 		=  EPWM_CFG_AQ_TAB;
const 		struct 		EPWMx_CFG_DB 				gc_stEpwmDbCfgParam[] 		=  EPWM_CFG_DB_TAB;
const 		struct 		EPWMx_CFG_TZ 				gc_stEpwmTzCfgParam[]   		=  EPWM_CFG_TZ_TAB;
const 		struct 		EPWMx_CFG_ET 				gc_stEpwmEtCfgParam[]   		=  EPWM_CFG_ET_TAB;
const 		struct 		EPWMx_CFG_DC 				gc_stEpwmDcCfgParam[] 		=  EPWM_CFG_DC_TAB;
const 		struct 		EPWMx_CFG_DC_FILT 	gc_stEpwmDcFiltCfgParam[] 	=  EPWM_CFG_DC_FILT_TAB;

//const struct EPWMx_CFG_HR gc_stEpwmHrCfgParam[] =  EPWM_CFG_HR_TAB;

static inline void EPWM_SetupTbSubmodule(const struct EPWMx_CFG_TB  *TbCfgInfo)
{
			EALLOW;
			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.HSPCLKDIV = TB_DIV1;
			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.CLKDIV = TB_DIV1;
			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.CTRMODE = TbCfgInfo->emCounterMode;
			if(TbCfgInfo->emPhsDirEn == PHS_DISABLE){
				 gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.PHSEN = 0;
			}else if(TbCfgInfo->emPhsDirEn == PHS_DIR_UP){
				 gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.PHSEN  = 1;
				 gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.PHSDIR = 1;
			}else{
			 gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.PHSEN  = 1;
			 gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.PHSDIR = 0;
			}

			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->EPWMSYNCINSEL.bit.SEL = TbCfgInfo->emSyncInSrc;
			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->EPWMSYNCOUTEN.all      = TbCfgInfo->emSyncOut;

			if(TbCfgInfo->u16PrdShadowEnable == 1){
			       gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.PRDLD 				= 0;
			       gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL2.bit.PRDLDSYNC 	= TbCfgInfo->emLoadMode;
			}else{
				gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTL.bit.PRDLD 	=  1;
			}

			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBPRD					 		= TbCfgInfo->u16PrdVal;
			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBPRDHR                    = 0x0000;

			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBPHS.bit.TBPHS 		= TbCfgInfo->u16PhaseVal;
			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBPHS.bit.TBPHSHR = 0x0000; //default HR phase set as 0
			gp_stPwmChannel[TbCfgInfo->emPwmChannel]->TBCTR						   = 0x0000;
			EDIS;
}

static inline void EPWM_SetupCcSubmodule(const struct EPWMx_CFG_CC *CcCfgInfo)
{
    EALLOW;
	if(CcCfgInfo->u16ABCDShadowEnable == 1){
			gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.SHDWAMODE 	= 0;   //enable shadow register
			gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.SHDWBMODE 	= 0;
			gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.SHDWCMODE  = 0;
			gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.SHDWDMODE = 0;
			switch(CcCfgInfo->emLoadMode){
					case CC_LOAD_CTR_ZERO:{
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADAMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADASYNC  = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBSYNC  = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCSYNC  = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDSYNC  = 0;
					}break;
					case CC_LOAD_CTR_PERIOD:{
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADAMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADASYNC  = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBSYNC  = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCSYNC  = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDSYNC  = 0;
					}break;
					case CC_LOAD_CTR_ZERO_OR_PERIOD:{
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADAMODE = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADASYNC  = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBMODE = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBSYNC  = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCSYNC  = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDSYNC  = 0;
					}break;
					case CC_LOAD_SYNC:{
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADAMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADASYNC  = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBSYNC  = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCMODE = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCSYNC  = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDMODE = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDSYNC  = 2;
					}break;
					case CC_LOAD_SYNC_AND_CTR_ZERO:{
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADAMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADASYNC  = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBMODE = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBSYNC  = 0;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCSYNC  = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDSYNC  = 1;
					}break;
					case CC_LOAD_SYNC_AND_CTR_PERIOD:{
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADAMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADASYNC  = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBSYNC  = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCSYNC  = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDSYNC  = 1;
					}break;
					case CC_LOAD_SYNC_AND_CTR_ZERO_OR_PERIOD:{
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADAMODE = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADASYNC  = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBMODE = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.LOADBSYNC  = 2;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADCSYNC  = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDMODE = 1;
						gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.LOADDSYNC  = 1;
					}break;
			}
	}else{
			gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.SHDWAMODE 	= 1;   //enable shadow register
			gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL.bit.SHDWBMODE 	= 1;
			gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.SHDWCMODE  = 1;
			gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPCTL2.bit.SHDWDMODE = 1;
	}
    gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPA.all = CcCfgInfo->u32CmpaVal;    /* Set compare A value including HR */
    gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPB.all = CcCfgInfo->u32CmpbVal;    /* Set Compare B value including HR */
    gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPC      = CcCfgInfo->u16CmpcVal;
    gp_stPwmChannel[CcCfgInfo->emPwmChannel]->CMPD      = CcCfgInfo->u16CmpdVal;
    EDIS;
}

static inline void EPWM_SetupAqSubmodule(struct EPWMx_CFG_AQ AqCfgInfo)
{
    EALLOW;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.CAD = AqCfgInfo.AQ_CTLA_CAD;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.CAU = AqCfgInfo.AQ_CTLA_CAU;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.CBD = AqCfgInfo.AQ_CTLA_CBD;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.CBU = AqCfgInfo.AQ_CTLA_CBU;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.PRD = AqCfgInfo.AQ_CTLA_PRD;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLA.bit.ZRO = AqCfgInfo.AQ_CTLA_ZRO;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.CAD = AqCfgInfo.AQ_CTLB_CAD;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.CAU = AqCfgInfo.AQ_CTLB_CAU;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.CBD = AqCfgInfo.AQ_CTLB_CBD;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.CBU = AqCfgInfo.AQ_CTLB_CBU;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.PRD = AqCfgInfo.AQ_CTLB_PRD;
    gp_stPwmChannel[AqCfgInfo.emPwmChannel]->AQCTLB.bit.ZRO = AqCfgInfo.AQ_CTLB_ZRO;
    EDIS;
}

static inline void EPWM_SetupDbSubmodule(struct EPWMx_CFG_DB DbCfgInfo)
{
    EALLOW;
    gp_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL.bit.OUT_MODE 					= DbCfgInfo.DB_OUT_MODE;
    gp_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL.bit.POLSEL 							= DbCfgInfo.DB_POLSEL;
    gp_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL.bit.IN_MODE 						= DbCfgInfo.DB_IN_MODE;
    gp_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL.bit.OUTSWAP 						= DbCfgInfo.DB_OUTSWAP;
    gp_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL.bit.DEDB_MODE                = DbCfgInfo.DB_S8;
    gp_stPwmChannel[DbCfgInfo.emPwmChannel]->DBRED.bit.DBRED 							= DbCfgInfo.u16RedVal;
    gp_stPwmChannel[DbCfgInfo.emPwmChannel]->DBFED.bit.DBFED 							= DbCfgInfo.u16Fedval;
    gp_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL2.bit.SHDWDBCTLMODE 	= DbCfgInfo.DB_SHDW_RED_FED_CTR_MODE;
    gp_stPwmChannel[DbCfgInfo.emPwmChannel]->DBCTL2.bit.LOADDBCTLMODE 	= DbCfgInfo.DB_LOAD_RED_FED_CTR_MODE;
    EDIS;

}
#if 0
void EPWM_SetupPcSubmodule(struct EPWMx_CFG_PC PcCfgInfo)
{
    //gp_stPwmChannel[PcCfgInfo.emPwmChannel]->PCCTL.bit.CHPEN = 0;
}
#endif

void EPWM_SetupTzSubmodule(struct EPWMx_CFG_TZ TzCfgInfo)
{
    EALLOW;

    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZSEL.all                         = (TzCfgInfo.u16TzCbcSel) | (TzCfgInfo.u16TzOstSel);
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.DCAEVT1   = TzCfgInfo.emDcaEvt1 ;
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.DCAEVT2   =  TzCfgInfo.emDcaEvt2 ;
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.DCBEVT1   = TzCfgInfo.emDcbEvt1 ;
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.DCBEVT2   = TzCfgInfo.emDcbEvt2 ;
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.TZA   			  = TzCfgInfo.emTza ;
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL.bit.TZB   			  = TzCfgInfo.emTzb ;
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCTL2.bit.ETZE          = 0;   //only using the TZCTL register.
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCLR.all                        = (TzCfgInfo.emCbcClrSel <<  14) | 0x007F;
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZCBCCLR.all               = 0x00FF;
    gp_stPwmChannel[TzCfgInfo.emPwmChannel]->TZOSTCLR.all               = 0x00FF;
    EDIS;
}

static inline void EPWM_SetupEtSubmodule(struct 	EPWMx_CFG_ET 	EtCfgInfo)
{
			//ET submodule
			if(EtCfgInfo.emEtIntSel == ET_INT_DISABLE){
				gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTEN = 0;
			}else{
				   switch(EtCfgInfo.emEtIntSel){
						   case  	ET_INT_CTRU_COMPA:{
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSELCMP 		= 0;
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSEL          		= 4;
						   }break;
						   case  	ET_INT_CTRU_COMPC:{
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSELCMP 		= 1;
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSEL          	= 4;

						   }break;
						   case  	ET_INT_CTRD_COMPA:{
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSELCMP 		= 0;
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSEL         	= 5;
						   }break;
						   case  	ET_INT_CTRD_COMPC:{
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSELCMP 		= 1;
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSEL          	= 5;
						   }break;
						   case  	ET_INT_CTRU_COMPB:{
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSELCMP 		= 0;
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSEL          	= 6;
						   }break;
						   case  	ET_INT_CTRU_COMPD:{
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSELCMP 		= 1;
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSEL          	= 6;

						   }break;
						   case  	ET_INT_CTRD_COMPB:{
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSELCMP 		= 0;
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSEL         		= 7;
						   }break;
						   case  	ET_INT_CTRD_COMPD:{
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSELCMP 		= 1;
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSEL     			= 7;
						   }break;
						   default:{
								   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTSELCMP 		= EtCfgInfo.emEtSocaSel;
						   }break;
				   }
				gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETPS.bit.INTPSSEL 					= 0; //using the ETPS as the interrrupt event prescale.
				gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETPS.bit.INTPRD     				     = EtCfgInfo.emEtIntPrescale;
				gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETCNTINITCTL.bit.INTINITEN = 0;
				gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETCNTINIT.bit.INTINIT              = 0;
				gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.INTEN     					= 1;

			}

			gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETPS.bit.SOCPSSEL     = 0;
		   if(EtCfgInfo.emEtSocaSel == ET_SOC_DISABLE){
			   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCAEN = 0;
		   }else{
					   switch(EtCfgInfo.emEtSocaSel){
							   case  	ET_SOC_CTRU_COMPA:{
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASELCMP = 0;
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL          = 4;
							   }break;
							   case  	ET_SOC_CTRU_COMPC:{
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASELCMP = 1;
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL          = 4;

							   }break;
							   case  	ET_SOC_CTRD_COMPA:{
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASELCMP = 0;
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL         = 5;
							   }break;
							   case  	ET_SOC_CTRD_COMPC:{
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASELCMP = 1;
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL          = 5;
							   }break;
							   case  	ET_SOC_CTRU_COMPB:{
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASELCMP = 0;
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL          = 6;
							   }break;
							   case  	ET_SOC_CTRU_COMPD:{
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASELCMP = 1;
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL          = 6;

							   }break;
							   case  	ET_SOC_CTRD_COMPB:{
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASELCMP = 0;
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL         = 7;
							   }break;
							   case  	ET_SOC_CTRD_COMPD:{
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASELCMP = 1;
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL          = 7;
							   }break;
							   default:{
									   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCASEL 			   = EtCfgInfo.emEtSocaSel;
							   }break;
					   }
					   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETPS.bit.SOCAPRD  						= EtCfgInfo.emEtSocaPrescale;
					   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETCNTINITCTL.bit.SOCAINITEN = 0;
					   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETCNTINIT.bit.SOCAINIT              = 0;
					   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCAEN  						 = 1;
		   }

		   if(EtCfgInfo.emEtSocbSel == ET_SOC_DISABLE){
			   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBEN = 0;
		   }else{
			   switch(EtCfgInfo.emEtSocbSel){
					   case  	ET_SOC_CTRU_COMPA:{
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSELCMP = 0;
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSEL          = 4;
					   }break;
					   case  	ET_SOC_CTRU_COMPC:{
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSELCMP = 1;
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSEL          = 4;

					   }break;
					   case  	ET_SOC_CTRD_COMPA:{
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSELCMP = 0;
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSEL         = 5;
					   }break;
					   case  	ET_SOC_CTRD_COMPC:{
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSELCMP = 1;
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSEL          = 5;
					   }break;
					   case  	ET_SOC_CTRU_COMPB:{
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSELCMP = 0;
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSEL          = 6;
					   }break;
					   case  	ET_SOC_CTRU_COMPD:{
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSELCMP = 1;
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSEL          = 6;

					   }break;
					   case  	ET_SOC_CTRD_COMPB:{
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSELCMP = 0;
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSEL         = 7;
					   }break;
					   case  	ET_SOC_CTRD_COMPD:{
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSELCMP = 1;
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSEL          = 7;
					   }break;
					   default:{
							   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBSEL 					= EtCfgInfo.emEtSocbSel;
					   }break;
			   }
			   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETPS.bit.SOCBPRD  							= EtCfgInfo.emEtSocbPrescale;
				gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETCNTINITCTL.bit.SOCBINITEN 	= 0;
				gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETCNTINIT.bit.SOCBINIT              	= 0;
			   gp_stPwmChannel[EtCfgInfo.emPwmChannel]->ETSEL.bit.SOCBEN  							= 1;
		   }
}


void EPWM_SetupDcSubmodule(struct EPWMx_CFG_DC DcCfgInfo)
{
    EALLOW;
    //the DCAEVT1 is disable
    if(DcCfgInfo.u16DCAH_SEL !=  DC_SEL_NONE){
		  gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCTRIPSEL.bit.DCAHCOMPSEL = 0x0f;   //trip combination input
		  gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCAHTRIPSEL.all                           = DcCfgInfo.u16DCAH_SEL;
    }
    if(DcCfgInfo.u16DCAL_SEL !=  DC_SEL_NONE){
		  gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCTRIPSEL.bit.DCALCOMPSEL = 0x0f;   //trip combination input
		  gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCALTRIPSEL.all                           = DcCfgInfo.u16DCAL_SEL;
    }
    if(DcCfgInfo.u16DCBH_SEL !=  DC_SEL_NONE){
		  gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCTRIPSEL.bit.DCBHCOMPSEL = 0x0f;   //trip combination input
		  gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBHTRIPSEL.all                           = DcCfgInfo.u16DCBH_SEL;
    }
    if(DcCfgInfo.u16DCBL_SEL !=  DC_SEL_NONE){
		  gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCTRIPSEL.bit.DCBLCOMPSEL = 0x0f;   //trip combination input
		  gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBLTRIPSEL.all                           = DcCfgInfo.u16DCBL_SEL;
    }

    if(DcCfgInfo.emDCAEVT1_CFG == EVT_DISABLE){
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCACTL.bit.EVT1SOCE 				= 0;
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZEINT.bit.DCAEVT1     				= 0;
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCACTL.bit.EVT1SYNCE 			= 0;
    }else{
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZDCSEL.bit.DCAEVT1       			= DcCfgInfo.emDCAEVT1_CFG;
    	if(DcCfgInfo.u16DcaEvt1Out & ( DCxEVT1_OUT_SOC))			gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCACTL.bit.EVT1SOCE 		= 1;
       	if(DcCfgInfo.u16DcaEvt1Out & ( DCxEVT1_OUT_INT))			gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZEINT.bit.DCAEVT1     		= 1;
       	if(DcCfgInfo.u16DcaEvt1Out & ( DCxEVT1_OUT_SYNC))		gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCACTL.bit.EVT1SYNCE 	= 1;

        gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCACTL.bit.EVT1LATSEL  		  = 1;                  //DCAEVT1.force come from latch signal;
        gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCACTL.bit.EVT1LATCLRSEL = 0;                 //CNT_ZERO event clears DCAEVT1 latch
    }

    if(DcCfgInfo.emDCAEVT2_CFG == EVT_DISABLE){
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZEINT.bit.DCAEVT2     		= 0;
    }else{
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZDCSEL.bit.DCAEVT2       = DcCfgInfo.emDCAEVT2_CFG;
       	if(DcCfgInfo.u16DcaEvt2Out & ( DCxEVT2_OUT_INT))			gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZEINT.bit.DCAEVT2     		= 1;

        gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCACTL.bit.EVT2LATSEL  		  = 1;                  //DCAEVT1.force come from latch signal;
        gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCACTL.bit.EVT2LATCLRSEL = 0;                 //CNT_ZERO event clears DCAEVT1 latch
    }

    if(DcCfgInfo.emDCBEVT1_CFG == EVT_DISABLE){
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBCTL.bit.EVT1SOCE 		= 0;
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZEINT.bit.DCBEVT1     		= 0;
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBCTL.bit.EVT1SYNCE 	= 0;
    }else{
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZDCSEL.bit.DCBEVT1       = DcCfgInfo.emDCBEVT1_CFG;
    	if(DcCfgInfo.u16DcbEvt1Out & ( DCxEVT1_OUT_SOC))			gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBCTL.bit.EVT1SOCE 		= 1;
       	if(DcCfgInfo.u16DcbEvt1Out & ( DCxEVT1_OUT_INT))			gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZEINT.bit.DCBEVT1     		= 1;
       	if(DcCfgInfo.u16DcbEvt1Out & ( DCxEVT1_OUT_SYNC))		gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBCTL.bit.EVT1SYNCE 	= 1;

        gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBCTL.bit.EVT1LATSEL  		  = 1;                  //DCBEVT1.force come from latch signal;
        gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBCTL.bit.EVT1LATCLRSEL = 0;                 //CNT_ZERO event clears DCBEVT1 latch
    }


    if(DcCfgInfo.emDCBEVT2_CFG == EVT_DISABLE){
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZEINT.bit.DCBEVT2     		= 0;
    }else{
    	gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZDCSEL.bit.DCBEVT2       = DcCfgInfo.emDCBEVT2_CFG;
       	if(DcCfgInfo.u16DcbEvt2Out & ( DCxEVT2_OUT_INT))			 gp_stPwmChannel[DcCfgInfo.emPwmChannel]->TZEINT.bit.DCBEVT2     		= 1;
        gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBCTL.bit.EVT2LATSEL  		  = 1;                  //DCBEVT1.force come from latch signal;
        gp_stPwmChannel[DcCfgInfo.emPwmChannel]->DCBCTL.bit.EVT2LATCLRSEL = 0;                 //CNT_ZERO event clears DCAEVT1 latch
    }
    EDIS;
}


void EPWM_SetupDcFiltSubmodule(struct EPWMx_CFG_DC_FILT DcFiltCfgInfo)
{
    EALLOW;
	if(DcFiltCfgInfo.u16DcaEvt1Src == DCEVTFILT_SRC)
      gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCACTL.bit.EVT1SRCSEL = 1;  //Come from filter
	else
    gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCACTL.bit.EVT1SRCSEL    = 0;  //Come from DCAEVT1

	if(DcFiltCfgInfo.u16DcaEvt2Src == DCEVTFILT_SRC)
      gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCACTL.bit.EVT2SRCSEL = 1;  //Come from filter
	else
    gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCACTL.bit.EVT2SRCSEL    = 0;  //Come from DCAEVT2

	if(DcFiltCfgInfo.u16DcbEvt1Src == DCEVTFILT_SRC)
      gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCBCTL.bit.EVT1SRCSEL = 1;  //Come from filter
	else
    gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCBCTL.bit.EVT1SRCSEL    = 0;  //Come from DCBEVT1

	if(DcFiltCfgInfo.u16DcbEvt2Src == DCEVTFILT_SRC)
	      gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCBCTL.bit.EVT2SRCSEL = 1;  //Come from filter
	else
		gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCBCTL.bit.EVT2SRCSEL    = 0;  //Come from DCBEVT2

	if(DcFiltCfgInfo.emBlankStart < START_PULSE_ZERO){
	     gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCFCTL.bit.PULSESEL    = DcFiltCfgInfo.emBlankStart;
	}else{
		 gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCFCTL.bit.PULSESEL       =  3;
	     gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->BLANKPULSEMIXSEL.all  = (1 << (DcFiltCfgInfo.emBlankStart - START_PULSE_ZERO));
	}

	 gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCFCTL.bit.SRCSEL                  = DcFiltCfgInfo.emDcEvtFiltSrc;
	 gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCFCTL.bit.BLANKINV            = 0;
	 gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCFCTL.bit.BLANKE                = 1;
	 gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCFOFFSET								= DcFiltCfgInfo.u16Offset;
	 gp_stPwmChannel[DcFiltCfgInfo.emPwmChannel]->DCFWINDOW                             = DcFiltCfgInfo.u16BlankWindow;
    EDIS;
}


void EPWM_SetupHRSubmodule(struct EPWMx_CFG_HR HrCfgInfo)
{
    EALLOW;
    gp_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.EDGMODE      		= HrCfgInfo.HR_EDGMODE_VAL;
    gp_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.CTLMODE      	    = HrCfgInfo.HR_CTLMODE_VAL;
    gp_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.HRLOAD       	    = HrCfgInfo.HR_HRLOAD_VAL;
    gp_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.EDGMODEB    	= HrCfgInfo.HR_EDGMODEB_VAL;
    gp_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.CTLMODEB     	 = HrCfgInfo.HR_CTLMODEB_VAL;
    gp_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.HRLOADB      		 = HrCfgInfo.HR_HRLOADB_VAL;
    gp_stPwmChannel[HrCfgInfo.emPwmChannel]->HRCNFG.bit.AUTOCONV    		 = HrCfgInfo.HR_AUTOCONV_VAL;
    gp_stPwmChannel[HrCfgInfo.emPwmChannel]->HRPCTL.bit.TBPHSHRLOADE = HrCfgInfo.HR_TBPHSHRLOADE_VAL;
    gp_stPwmChannel[HrCfgInfo.emPwmChannel]->HRPCTL.bit.HRPE         				 = HrCfgInfo.HR_HRPE_VAL;
    EDIS;
}

void SYNC_SocInit (void)
{
/*    EALLOW;
    SyncSocRegs.SYNCSELECT.bit.SYNCOUT = gc_stSyncCfgPara.SYNC_OUT_VAL;
    EDIS;*/
}

void  bsw_mcal_epwm_init(void)
{
    unsigned int i = 0;

    bsw_mcal_disable_tbclk_sync();
    SYNC_SocInit();
    for(i = 0;i < (sizeof(gc_stEpwmTbCfgParam)/sizeof(struct EPWMx_CFG_TB)); i++)
    {
    	if((gc_stEpwmTbCfgParam[i].emPwmChannel != gc_stEpwmCcCfgParam[i].emPwmChannel)\
    	   ||(gc_stEpwmTbCfgParam[i].emPwmChannel != gc_stEpwmAqCfgParam[i].emPwmChannel)\
		   ||(gc_stEpwmTbCfgParam[i].emPwmChannel != gc_stEpwmDbCfgParam[i].emPwmChannel)\
	       ||(gc_stEpwmTbCfgParam[i].emPwmChannel != gc_stEpwmTzCfgParam[i].emPwmChannel)\
 		   ||(gc_stEpwmTbCfgParam[i].emPwmChannel != gc_stEpwmEtCfgParam[i].emPwmChannel)\
		  ||(gc_stEpwmTbCfgParam[i].emPwmChannel != gc_stEpwmDcCfgParam[i].emPwmChannel)\
		  ||(gc_stEpwmTbCfgParam[i].emPwmChannel != gc_stEpwmDcFiltCfgParam[i].emPwmChannel))
		/*   ||(gc_stEpwmTbCfgParam[i].emPwmChannel != gc_stEpwmHrCfgParam[i].emPwmChannel))*/
    		 while(1); //continue;

        EPWM_SetupTbSubmodule(&gc_stEpwmTbCfgParam[i]);
        EPWM_SetupCcSubmodule(&gc_stEpwmCcCfgParam[i]);
        EPWM_SetupAqSubmodule(gc_stEpwmAqCfgParam[i]);
        EPWM_SetupDbSubmodule(gc_stEpwmDbCfgParam[i]);

        gp_stPwmChannel[i]->PCCTL.bit.CHPEN = 0;    //by pass the PC submodule
        EPWM_SetupTzSubmodule(gc_stEpwmTzCfgParam[i]);
        EPWM_SetupEtSubmodule(gc_stEpwmEtCfgParam[i]);
        EPWM_SetupDcSubmodule(gc_stEpwmDcCfgParam[i]);
        EPWM_SetupDcFiltSubmodule(gc_stEpwmDcFiltCfgParam[i]);
      //  EPWM_SetupHRSubmodule(gc_stEpwmHrCfgParam[i]);
        gp_stPwmChannel[gc_stEpwmTbCfgParam[i].emPwmChannel]->EPWMLOCK.all = (0xA5A5UL << 16) | ( 1 << DCLOCK_BIT) | (1 << TZCFGLOCK_BIT);
    }
    bsw_mcal_enable_tbclk_sync();
}
