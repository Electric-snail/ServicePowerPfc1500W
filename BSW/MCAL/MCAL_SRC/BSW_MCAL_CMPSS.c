/*
 * BSW_MCAL_CMPSS.c
 *
 *  Created on: 2024.06.06
 *      Author: rjgslg
 */

#include "common/include/F28x_Project.h"
#include "MCAL_INC/BSW_MCAL_CMPSS.h"

extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;

const 	CMPSS_CFG_T				gc_stCmpssCfgParm[] 			= CMPSS_CFG_TAB;
const 	CMPSS_CMP_CFG_T		gc_stCmpssCmpCfgParm[] 	= CMPSS_CMP_CFG_TAB;


static cmpss_cfg(const CMPSS_CFG_T *p_stCmpssCfg){
		volatile struct CMPSS_REGS *p_stCmpssChannel = &Cmpss1Regs;
	    EALLOW;
		if(p_stCmpssCfg->u16DacLoadSycnSrc == DAC_LOAD_SYNC_SYSCLK){
				p_stCmpssChannel->COMPDACHCTL.bit.SWLOADSEL = 0;
		}else{
				p_stCmpssChannel->COMPDACHCTL.bit.SWLOADSEL = 1;
		}
		if(p_stCmpssCfg->u16BlankEnable == 1){
			   p_stCmpssChannel->COMPDACHCTL.bit.BLANKSOURCE = p_stCmpssCfg->u16BlankSrc;
				p_stCmpssChannel->COMPDACHCTL.bit.BLANKEN 	       = 1;
		}else{
			  p_stCmpssChannel->COMPDACHCTL.bit.BLANKEN            = 0;
		}
		if(p_stCmpssCfg->u16RampGenEnable == 1) {
			p_stCmpssChannel->COMPDACHCTL.bit.DACSOURCE 				= 1;
			 p_stCmpssChannel->COMPDACHCTL.bit.RAMPLOADSEL       	= 1;        //default RAMPSTS load from the RAMPREFS register
		}
		else{
			p_stCmpssChannel->COMPDACHCTL.bit.DACSOURCE = 0;
		}
		 p_stCmpssChannel->COMPDACHCTL.bit.RAMPSOURCE         = p_stCmpssCfg->emRampOrClearLatchSrc;

		   if(p_stCmpssCfg->emLatchClearSrc == LAT_CLR_SW){
			   p_stCmpssChannel->COMPSTSCLR.bit.HSYNCCLREN = 0;
		   }else{
			   p_stCmpssChannel->COMPSTSCLR.bit.HSYNCCLREN = 1;
		   }
         EDIS;
};

static cmpss_lite_cfg(const CMPSS_CFG_T *p_stCmpssCfg){
			unsigned short u16CmpssLiteIndex  = p_stCmpssCfg->emCmpssModule - CMPSS2_ID;
			UINT32 u32RegAddr = (UINT32)&CmpssLite2Regs + 0x40 * u16CmpssLiteIndex;
			volatile struct CMPSS_LITE_REGS *p_stCmpssChannel = (volatile struct CMPSS_LITE_REGS *)u32RegAddr ;

			EALLOW;
			if(p_stCmpssCfg->u16DacLoadSycnSrc == DAC_LOAD_SYNC_SYSCLK){
					p_stCmpssChannel->COMPDACHCTL.bit.SWLOADSEL = 0;
			}else{
					p_stCmpssChannel->COMPDACHCTL.bit.SWLOADSEL = 1;
			}

			if(p_stCmpssCfg->u16BlankEnable == 1){
				   p_stCmpssChannel->COMPDACHCTL.bit.BLANKSOURCE = p_stCmpssCfg->u16BlankSrc;
					p_stCmpssChannel->COMPDACHCTL.bit.BLANKEN 	       = 1;
			}else{
				  p_stCmpssChannel->COMPDACHCTL.bit.BLANKEN            = 0;
			}
			 p_stCmpssChannel->COMPDACHCTL.bit.RAMPSOURCE         = p_stCmpssCfg->emRampOrClearLatchSrc;

			   if(p_stCmpssCfg->emLatchClearSrc == LAT_CLR_SW){
				   p_stCmpssChannel->COMPSTSCLR.bit.HSYNCCLREN = 0;
			   }else{
				   p_stCmpssChannel->COMPSTSCLR.bit.HSYNCCLREN = 1;
			   }
			   EDIS;
};


static cmpss_cmp_cfg(const 	CMPSS_CMP_CFG_T  *p_stCmpssCmpCfg){
	        volatile struct CMPSS_REGS *p_stCmpssChannel = &Cmpss1Regs;
	        EALLOW;
			if((p_stCmpssCmpCfg->emCmpModule & 0xF0) == 0x00){    //high side the comparator
					AnalogSubsysRegs.CMPHPMXSEL.bit.CMP1HPMXSEL  = p_stCmpssCmpCfg->u16PosSrc;
					if(p_stCmpssCmpCfg->u16NegSrc == CMP1H_N_DAC){
							 p_stCmpssChannel->COMPCTL.bit.COMPHSOURCE  		= 0;
							 p_stCmpssChannel->DACHVALS.all 									= p_stCmpssCmpCfg->u16DacValue;
					}else{
							 p_stCmpssChannel->COMPCTL.bit.COMPHSOURCE  		= 1;
							 AnalogSubsysRegs.CMPHNMXSEL.bit.CMP1HNMXSEL 	= p_stCmpssCmpCfg->u16NegSrc;
					}
					p_stCmpssChannel->COMPCTL.bit.COMPHINV =  p_stCmpssCmpCfg->u16OutInvEnable;

				   if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_ASYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 0;
				   }else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_SYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 1;

				   }else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_FILT){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 2;

				   }else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_FILT_LATCH){
					   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN = 0;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 3;
				   }else{
					   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN = 1;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 3;
				   }

				   if(p_stCmpssCmpCfg->emOutToOutputSel == CMPOUT_ASYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 0;
				   }else if(p_stCmpssCmpCfg->emOutToOutputSel  == CMPOUT_SYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 1;

				   }else if(p_stCmpssCmpCfg->emOutToOutputSel  == CMPOUT_FILT){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 2;

				   }else if(p_stCmpssCmpCfg->emOutToOutputSel == CMPOUT_FILT_LATCH){
					   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN 			=	0;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 3;
				   }else{
					   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN 			= 1;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 3;
				   }
			}else{
			     	 AnalogSubsysRegs.CMPLPMXSEL.bit.CMP1LPMXSEL  = p_stCmpssCmpCfg->u16PosSrc;
					if(p_stCmpssCmpCfg->u16NegSrc == CMP1L_N_DAC){
						   p_stCmpssChannel->COMPCTL.bit.COMPLSOURCE  		= 0;
						   p_stCmpssChannel->DACLVALS.all  											= p_stCmpssCmpCfg->u16DacValue;
					}else{
						   p_stCmpssChannel->COMPCTL.bit.COMPLSOURCE  		= 1;
						   AnalogSubsysRegs.CMPLNMXSEL.bit.CMP1LNMXSEL 	= p_stCmpssCmpCfg->u16NegSrc;
					}
					p_stCmpssChannel->COMPCTL.bit.COMPLINV 	=  p_stCmpssCmpCfg->u16OutInvEnable;
					if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_ASYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 0;
					}else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_SYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 1;

					}else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_FILT){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 2;

					}else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_FILT_LATCH){
					   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN = 0;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 3;
					}else{
					   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN = 1;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 3;
					}

					if(p_stCmpssCmpCfg->emOutToOutputSel == CMPOUT_ASYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 0;
					}else if(p_stCmpssCmpCfg->emOutToOutputSel  == CMPOUT_SYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 1;

					}else if(p_stCmpssCmpCfg->emOutToOutputSel  == CMPOUT_FILT){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 2;

					}else if(p_stCmpssCmpCfg->emOutToOutputSel == CMPOUT_FILT_LATCH){
					   p_stCmpssChannel->COMPCTL.bit.ASYNCLEN 			=	0;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 3;
					}else{
					   p_stCmpssChannel->COMPCTL.bit.ASYNCLEN 			= 1;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 3;
					}
		}
		p_stCmpssChannel->COMPCTL.bit.COMPDACE = 1;   //Enable the comparator and DAC
		__asm(" NOP");
		__asm(" NOP");
		__asm(" NOP");
		if((p_stCmpssCmpCfg->emCmpModule & 0xF0) == 0x00)    //high side the comparator
			p_stCmpssChannel->COMPSTSCLR.bit.HLATCHCLR  = 1;   //Clear the output
		else
			p_stCmpssChannel->COMPSTSCLR.bit.LLATCHCLR  = 1;   //Clear the output
		EDIS;
};


static cmpss_lite_cmp_cfg(const 	CMPSS_CMP_CFG_T 	*p_stCmpssCmpCfg){
	unsigned short u16CmpssLiteIndex  = (p_stCmpssCmpCfg->emCmpModule & 0x0F) -  CMPSS2_ID;
	UINT32 u32RegAddr = (UINT32)&CmpssLite2Regs + 0x40 * u16CmpssLiteIndex;
	volatile struct CMPSS_LITE_REGS *p_stCmpssChannel = (volatile struct CMPSS_LITE_REGS *)u32RegAddr ;
    EALLOW;
	if((p_stCmpssCmpCfg->emCmpModule & 0xF0) == 0x00){    //high side the comparator
					   if(u16CmpssLiteIndex == 0){
						   AnalogSubsysRegs.CMPHPMXSEL.bit.CMP2HPMXSEL  = p_stCmpssCmpCfg->u16PosSrc;
						   if(p_stCmpssCmpCfg->u16NegSrc == CMP2H_N_DAC){
								   p_stCmpssChannel->COMPCTL.bit.COMPHSOURCE  		= 0;
								   p_stCmpssChannel->DACHVALS.all 											= p_stCmpssCmpCfg->u16DacValue;
						   }else{
								   p_stCmpssChannel->COMPCTL.bit.COMPHSOURCE  		= 1;
								   AnalogSubsysRegs.CMPHNMXSEL.bit.CMP2HNMXSEL 	= p_stCmpssCmpCfg->u16NegSrc;
						   }

					   }else if(u16CmpssLiteIndex == 01){
						   AnalogSubsysRegs.CMPHPMXSEL.bit.CMP3HPMXSEL  = p_stCmpssCmpCfg->u16PosSrc;
						   if(p_stCmpssCmpCfg->u16NegSrc == CMP3H_N_DAC){
								p_stCmpssChannel->COMPCTL.bit.COMPHSOURCE  		= 0;
								p_stCmpssChannel->DACHVALS.all 											= p_stCmpssCmpCfg->u16DacValue;
						  }else{
								p_stCmpssChannel->COMPCTL.bit.COMPHSOURCE  		= 1;
								AnalogSubsysRegs.CMPHNMXSEL.bit.CMP3HNMXSEL 	= p_stCmpssCmpCfg->u16NegSrc;
						 }
					   }else if(u16CmpssLiteIndex == 02){
						   AnalogSubsysRegs.CMPHPMXSEL.bit.CMP4HPMXSEL  		= p_stCmpssCmpCfg->u16PosSrc;
						   if(p_stCmpssCmpCfg->u16NegSrc == CMP4H_N_DAC){
								p_stCmpssChannel->COMPCTL.bit.COMPHSOURCE  		= 0;
								   p_stCmpssChannel->DACHVALS.all  										= p_stCmpssCmpCfg->u16DacValue;
						  }else{
								p_stCmpssChannel->COMPCTL.bit.COMPHSOURCE  		= 1;
								AnalogSubsysRegs.CMPHNMXSEL.bit.CMP4HNMXSEL 	= p_stCmpssCmpCfg->u16NegSrc;
						 }
					   }
					   p_stCmpssChannel->COMPCTL.bit.COMPHINV =  p_stCmpssCmpCfg->u16OutInvEnable;

					   if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_ASYNC){
						   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 0;
					   }else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_SYNC){
						   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 1;

					   }else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_FILT){
						   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 2;

					   }else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_FILT_LATCH){
						   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN = 0;
						   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 3;
					   }else{
						   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN = 1;
						   p_stCmpssChannel->COMPCTL.bit.CTRIPHSEL  = 3;
					   }

					   if(p_stCmpssCmpCfg->emOutToOutputSel == CMPOUT_ASYNC){
						   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 0;
					   }else if(p_stCmpssCmpCfg->emOutToOutputSel  == CMPOUT_SYNC){
						   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 1;

					   }else if(p_stCmpssCmpCfg->emOutToOutputSel  == CMPOUT_FILT){
						   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 2;

					   }else if(p_stCmpssCmpCfg->emOutToOutputSel == CMPOUT_FILT_LATCH){
						   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN 			=	0;
						   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 3;
					   }else{
						   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN 			= 1;
						   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTHSEL  = 3;
					   }
	}else{
				   if(u16CmpssLiteIndex == 0){
					   AnalogSubsysRegs.CMPLPMXSEL.bit.CMP2LPMXSEL  = p_stCmpssCmpCfg->u16PosSrc;
					   if(p_stCmpssCmpCfg->u16NegSrc == CMP2L_N_DAC){
							   p_stCmpssChannel->COMPCTL.bit.COMPLSOURCE  		= 0;
							   p_stCmpssChannel->DACLVALS.all  											= p_stCmpssCmpCfg->u16DacValue;
					   }else{
							   p_stCmpssChannel->COMPCTL.bit.COMPLSOURCE  		= 1;
							   AnalogSubsysRegs.CMPLNMXSEL.bit.CMP2LNMXSEL 	= p_stCmpssCmpCfg->u16NegSrc;
					   }

				   }else if(u16CmpssLiteIndex == 1){
					   AnalogSubsysRegs.CMPLPMXSEL.bit.CMP3LPMXSEL  = p_stCmpssCmpCfg->u16PosSrc;
					   if(p_stCmpssCmpCfg->u16NegSrc == CMP3L_N_DAC){
							p_stCmpssChannel->COMPCTL.bit.COMPLSOURCE  		= 0;
							p_stCmpssChannel->DACLVALS.all  										= p_stCmpssCmpCfg->u16DacValue;
					  }else{
							p_stCmpssChannel->COMPCTL.bit.COMPLSOURCE  		= 1;
							AnalogSubsysRegs.CMPLNMXSEL.bit.CMP3LNMXSEL 	= p_stCmpssCmpCfg->u16NegSrc;
					 }
				   }else if(u16CmpssLiteIndex == 2){
					   AnalogSubsysRegs.CMPLPMXSEL.bit.CMP4LPMXSEL  		= p_stCmpssCmpCfg->u16PosSrc;
					   if(p_stCmpssCmpCfg->u16NegSrc == CMP4L_N_DAC){
							p_stCmpssChannel->COMPCTL.bit.COMPLSOURCE  		= 0;
							p_stCmpssChannel->DACLVALS.all  										= p_stCmpssCmpCfg->u16DacValue;
					  }else{
							p_stCmpssChannel->COMPCTL.bit.COMPLSOURCE  		= 1;
							AnalogSubsysRegs.CMPLNMXSEL.bit.CMP4LNMXSEL 	= p_stCmpssCmpCfg->u16NegSrc;
					 }
				   }
				   p_stCmpssChannel->COMPCTL.bit.COMPLINV 	=  p_stCmpssCmpCfg->u16OutInvEnable;

				   if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_ASYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 0;
				   }else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_SYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 1;

				   }else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_FILT){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 2;

				   }else if(p_stCmpssCmpCfg->emOutToEpwmSel == CMPOUT_FILT_LATCH){
					   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN = 0;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 3;
				   }else{
					   p_stCmpssChannel->COMPCTL.bit.ASYNCHEN = 1;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPLSEL  = 3;
				   }

				   if(p_stCmpssCmpCfg->emOutToOutputSel == CMPOUT_ASYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 0;
				   }else if(p_stCmpssCmpCfg->emOutToOutputSel  == CMPOUT_SYNC){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 1;

				   }else if(p_stCmpssCmpCfg->emOutToOutputSel  == CMPOUT_FILT){
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 2;

				   }else if(p_stCmpssCmpCfg->emOutToOutputSel == CMPOUT_FILT_LATCH){
					   p_stCmpssChannel->COMPCTL.bit.ASYNCLEN 			=	0;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 3;
				   }else{
					   p_stCmpssChannel->COMPCTL.bit.ASYNCLEN 			= 1;
					   p_stCmpssChannel->COMPCTL.bit.CTRIPOUTLSEL  = 3;
				   }
	}
	p_stCmpssChannel->COMPCTL.bit.COMPDACE = 1;   //Enable the comparator and DAC
	__asm(" NOP");
	__asm(" NOP");
	__asm(" NOP");
	if((p_stCmpssCmpCfg->emCmpModule & 0xF0) == 0x00)    //high side the comparator
			p_stCmpssChannel->COMPSTSCLR.bit.HLATCHCLR  = 1;   //Clear the output
	else
		    p_stCmpssChannel->COMPSTSCLR.bit.LLATCHCLR  = 1;   //Clear the output
	EDIS;
};

void bsw_mcal_cmpss_init(void)
{
    unsigned int i = 0;
    for(i = 0;i < (sizeof(gc_stCmpssCfgParm)/sizeof(CMPSS_CFG_T)); i++)
    {
    	   if(gc_stCmpssCfgParm[i].emCmpssModule == CMPSS1_ID){
    		   	   	   cmpss_cfg(&gc_stCmpssCfgParm[i]);
    	   }else{
	   	   	         cmpss_lite_cfg(&gc_stCmpssCfgParm[i]);
    	   }
    }

    for(i = 0;i < (sizeof(gc_stCmpssCmpCfgParm)/sizeof(CMPSS_CMP_CFG_T)); i++)
    {
    	   if((gc_stCmpssCmpCfgParm[i].emCmpModule  & 0x0F) == CMPSS1_ID){
    		   	   	cmpss_cmp_cfg(&gc_stCmpssCmpCfgParm[i]);
    	   }else{
	   	   	        cmpss_lite_cmp_cfg(&gc_stCmpssCmpCfgParm[i]);
    	   }
    }
}

