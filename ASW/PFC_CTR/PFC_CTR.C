/*
 * PFC_CTR.C
 *
 *  Created on: 2025.9.30
 *      Author:   Hongbo.Jiang
 */
#include "PFC_CTR/PFC_CTR.H"
#include "ISR_INC/BSW_ISR_ADC.H"
#include "SOFTWARE_ENV_CFG.H"
#include "ASW_BASIC.H"
#include "POWER_FSM/POWER_FSM.H"
#include "MEASURE/MEASURE.h"
#include "PUBLIC_INC/DC_MATH.H"

#define     XCAP_COMP_EN											0
#define 	 Cx																		2.22e-6
#ifndef  DLLX64
#pragma  CODE_SECTION(pfc_controller, 					".TI.ramfunc");
#pragma  CODE_SECTION(ctrl_pi_gain_position, 			".TI.ramfunc");
#pragma  CODE_SECTION(ctrl_pi_position, 				".TI.ramfunc");
#pragma  DATA_SECTION(gs_stIacPiGainCtrl, ".CtrlVariableSector");
#endif

STATIC PI_POS_T				    gs_stVpfcPiCtrl;
STATIC PI_GAIN_POS_T		gs_stIacPiGainCtrl;
STATIC float							gs_f32FeedCoff;
PFC_CTR_OUT						g_stPfcOut;
float										g_f32VpfcPiKpSlow;
float										g_f32VpfcPiKiTsSlow;
float										g_f32VpfcPiKpDcSlow;
float										g_f32VpfcPiKiTsDcSlow;
float                                        g_f32IacRmsRef;
float                            			g_f32VpfcPiGain;
float                        				g_f32PowerOpenSet;
float 										f32DutyForwared;
float                                       g_f32IacKpDc;
float                                       g_f32IacKiTsDc;
float                                       g_f32IacFeedCoffDc;
// 低压直流电流环GUI调试参数
float                                       g_f32IacKpDcLv;
float                                       g_f32IacKiTsDcLv;
float                                       g_f32IacFeedCoffDcLv;
unsigned short                              g_u16IacCtrlTuneEnable;
float                                       g_f32IacKpAc;
float                                       g_f32IacKiTsAc;
float                                       g_f32IacFeedCoffAc;
// 260 V以上交流输入电流环GUI调试参数
float                                       g_stIacPiGainCtrlGuiKpHv;
float                                       g_stIacPiGainCtrlGuiKiTsHv;
float                                       g_f32FeedCoffGuiHv;

void 	pfc_controller_init(void){
		gs_stVpfcPiCtrl.stCoff.f32IntegrateMax		= 4600.0f;   //output is the input power，maximum the input power
		gs_stVpfcPiCtrl.stCoff.f32IntegrateMin		= -1000.0f;

		gs_stVpfcPiCtrl.stCoff.f32OutMax				= 4600.0f;   //output is the input power,maximum the input power
		gs_stVpfcPiCtrl.stCoff.f32OutMin				= -1000.0f;

	//	g_f32VpfcPiKpFast									    = 100;
	//	g_f32VpfcPiKiTsFast									= 5 * 2*3.1415926f * 5 * CTR_PERIOD;

		g_f32VpfcPiKpSlow									= 5;//30.0f;
		g_f32VpfcPiKiTsSlow								=  0.0025f;//0.005f;  //6.2 * 2 * 3.1415926f * 5 * CTR_PERIOD;

		g_f32VpfcPiKpDcSlow                              = 50.0f;
		g_f32VpfcPiKiTsDcSlow							=  0.015f;//0.005f;  //6.2 * 2 * 3.1415926f * 5 * CTR_PERIOD;

		g_f32VpfcPiGain                                        = 1.0f;

		gs_stVpfcPiCtrl.stIn.f32Fb                          = 0.0f;
		gs_stVpfcPiCtrl.stIn.f32Ref                        = 0.0f;
		gs_stVpfcPiCtrl.stCoff.f32Kp						= g_f32VpfcPiKpSlow;
		gs_stVpfcPiCtrl.stCoff.f32KiTs					= g_f32VpfcPiKiTsSlow;
		gs_stVpfcPiCtrl.stInner.f32Integrate			= -1000.0f;;
		gs_stVpfcPiCtrl.stInner.f32Err					= 0;

		gs_stIacPiGainCtrl.stCoff.f32IntegrateMax			= 0.95f;
		gs_stIacPiGainCtrl.stCoff.f32IntegrateMin			= -1.0f;

		gs_stIacPiGainCtrl.stCoff.f32OutMax					= 0.95f;
		gs_stIacPiGainCtrl.stCoff.f32OutMin					= -1.0f;

	//	gs_stIacPiGainCtrl.stCoff.f32Kp						= 0.02 * 380f;
	//	gs_stIacPiGainCtrl.stCoff.f32KiTs					= 0.2f * 666.6 * 380f/ 65000.0f; //0.02f*2*pi*1000/65000.0f
		gs_stIacPiGainCtrl.stCoff.f32Kp						= 3.0f;
		gs_stIacPiGainCtrl.stCoff.f32KiTs					= 0.3f; //1.0f; //20.0f * 8000.0f/ 65000.0f; //0.02f*2*pi*1000/65000.0f
		g_f32IacKpDc                                        = 0.8f;
		g_f32IacKiTsDc                                      = 0.00f;
		g_f32IacFeedCoffDc                                  = 0.36f;
		g_f32IacKpDcLv                                      = 1.2f;
		g_f32IacKiTsDcLv                                    = 0.0001f;
		g_f32IacFeedCoffDcLv                                = 0.36f;
		g_u16IacCtrlTuneEnable                              = 0;
		g_f32IacKpAc                                        = 3.0f;
		g_f32IacKiTsAc                                      = 0.3f;
		g_f32IacFeedCoffAc                                  = 0.65f;
		g_stIacPiGainCtrlGuiKpHv                            = 10.0f;
		g_stIacPiGainCtrlGuiKiTsHv                          = 0.3f;
		g_f32FeedCoffGuiHv                                  = 0.8f;
		gs_stIacPiGainCtrl.stInner.f32Integrate			    = -1.0f;
		gs_stIacPiGainCtrl.stInner.f32Err					= 0;
		gs_f32FeedCoff										= 0.65f;
		g_stPfcOut.f32Duty									= 0.0f;

		g_f32IacRmsRef                                              = 0.0f;
}


void 	pfc_controller(void){
        static unsigned short s_u16VinRmsForILoop = 0;
		float f32Duty;
	    float f32VacPll		        = f32_get_vac_volt_pll();
		float f32VpfcNpf            = f32_get_vpfc_npf();
		float f32VinAbs		        = ABSF(f32_get_vin_raw());
		float f32VinRmsFltTemp		= f32_get_vin_rms_flt();
		float f32VinRmsTemp	        = f32_get_vin_rms();
		float f32VpfcErr0, f32VpfcErr1;
		float f32Temp;
		float f32IlRefTemp;
		float f32VpfcFastLpf = f32_get_vpfc_isr_lpf();

		gs_stVpfcPiCtrl.stIn.f32Ref = f32_get_vpfc_set();
		gs_stVpfcPiCtrl.stIn.f32Fb  = f32VpfcNpf;  //f32VpfcLpf;
		

	 //  f32VpfcErrAbs = ABSF(gs_stVpfcPiCtrl.stIn.f32Ref - gs_stVpfcPiCtrl.stIn.f32Fb);

		if(u16_get_vin_type() == AC_TYPE){
			f32VpfcErr0 = gs_stVpfcPiCtrl.stIn.f32Ref - f32VpfcFastLpf - 15.0f;
			f32VpfcErr1 =395.0f - f32VpfcFastLpf;
			if(((f32VpfcErr0 > 0.0f)||(f32VpfcErr1 > 0))&&(PWR_STATUS_RUN == u16_get_pwr_status())){
				//fast jump from the integration saturation status.
				  if(gs_stVpfcPiCtrl.stInner.f32Integrate < 0)
					  gs_stVpfcPiCtrl.stInner.f32Integrate = 0;
				  if(f32VpfcErr0 > f32VpfcErr1){
					  	  gs_stVpfcPiCtrl.stCoff.f32Kp     = (f32VpfcErr0 * g_f32VpfcPiGain + 1.0f)*g_f32VpfcPiKpSlow;//f32VpfcErr0 * g_f32VpfcPiGain + g_f32VpfcPiKpSlow
					  	  gs_stVpfcPiCtrl.stCoff.f32KiTs  = (f32VpfcErr0 * g_f32VpfcPiGain + 1.0f)*g_f32VpfcPiKiTsSlow; //f32VpfcErr0 * g_f32VpfcPiGain + g_f32VpfcPiKiTsSlow;
				  }else{
				  	      gs_stVpfcPiCtrl.stCoff.f32Kp     = (f32VpfcErr1 * g_f32VpfcPiGain + 1.0f)*g_f32VpfcPiKpSlow;//f32VpfcErr1 * g_f32VpfcPiGain + g_f32VpfcPiKpSlow;
				  	      gs_stVpfcPiCtrl.stCoff.f32KiTs  = (f32VpfcErr1 * g_f32VpfcPiGain + 1.0f)*g_f32VpfcPiKiTsSlow;//f32VpfcErr1 * g_f32VpfcPiGain +  g_f32VpfcPiKiTsSlow;
				  }
			}
			else {
				  gs_stVpfcPiCtrl.stCoff.f32Kp	   = g_f32VpfcPiKpSlow;
				  gs_stVpfcPiCtrl.stCoff.f32KiTs   = g_f32VpfcPiKiTsSlow;
			}
			//in case of the vpfc overshoot too high
			f32Temp	   = f32VpfcFastLpf -  35.0f;
		}else{
			//fast jump from the integration saturation status.
			if ((f32VpfcFastLpf <= 395.0f)&&(PWR_STATUS_RUN == u16_get_pwr_status())){
				  if(gs_stVpfcPiCtrl.stInner.f32Integrate < 0)
					  gs_stVpfcPiCtrl.stInner.f32Integrate = 0;
				  gs_stVpfcPiCtrl.stCoff.f32Kp     = ((395.0f - f32VpfcFastLpf) * 0.4 + 1.0f) * g_f32VpfcPiKpDcSlow;
				  gs_stVpfcPiCtrl.stCoff.f32KiTs   = ((395.0f - f32VpfcFastLpf) * 0.4 + 1.0f) * g_f32VpfcPiKiTsDcSlow;
			}else{
				  gs_stVpfcPiCtrl.stCoff.f32Kp	   = g_f32VpfcPiKpDcSlow;
				  gs_stVpfcPiCtrl.stCoff.f32KiTs   = g_f32VpfcPiKiTsDcSlow;
			}
			//in case of the vpfc overshoot too high
			f32Temp	   = f32VpfcFastLpf -  10.0f;
		}

		if((f32Temp >= gs_stVpfcPiCtrl.stIn.f32Ref)||(f32VpfcFastLpf >= 465.0f)){
			gs_stVpfcPiCtrl.stInner.f32Integrate 				= -500.0f;
			gs_stIacPiGainCtrl.stInner.f32Integrate			= -1.0f;
		}
		ctrl_pi_position(&gs_stVpfcPiCtrl);
		//in case of the vpfc overshoot too high
#if defined IL_CLOSE_LOOP_MODE
		gs_stVpfcPiCtrl.stOut.f32Out = g_f32PowerOpenSet;
#endif

		if (f32VinRmsFltTemp < 35.0f)  f32VinRmsFltTemp = 35.0f;

		g_f32IacRmsRef = gs_stVpfcPiCtrl.stOut.f32Out/f32VinRmsFltTemp;

		f32IlRefTemp     = g_f32IacRmsRef * f32VacPll / f32VinRmsFltTemp;

		if (gs_stVpfcPiCtrl.stOut.f32Out <= 0) {
				gs_stIacPiGainCtrl.stIn.f32Ref = -1.0f;
		}
		else {
            #if(XCAP_COMP_EN == 1)
				f32Temp = Cx * 1.414f * 2 * pi * 50.0f * f32_get_vac_volt_q_pll();
				f32IlRefTemp = f32IlRefTemp + f32Temp;
				f32Temp		 = f32IlRefTemp * f32VacPll;
				if (f32Temp >= 0)
					gs_stIacPiGainCtrl.stIn.f32Ref  = ABSF(f32IlRefTemp);
				else
					gs_stIacPiGainCtrl.stIn.f32Ref = -0.1f;
			#else
				gs_stIacPiGainCtrl.stIn.f32Ref= ABSF(f32IlRefTemp);
            #endif
		}

		gs_stIacPiGainCtrl.stIn.f32Fb	= f32_get_curr_inductor_ave();

		if(f32VpfcFastLpf  < 100.0f)    f32VpfcFastLpf = 100.0f;

		gs_stIacPiGainCtrl.stIn.f32Gain = 1/f32VpfcFastLpf;

		if(u16_get_vin_type() == AC_TYPE){
	        if(f32VinRmsTemp > 175.0f){
	                gs_stVpfcPiCtrl.stCoff.f32IntegrateMax      = 4500.0f;   //output is the input power，maximum the input power
	                gs_stVpfcPiCtrl.stCoff.f32IntegrateMin      = -1000.0f;
	                gs_stVpfcPiCtrl.stCoff.f32OutMax            = 4500.0f;   //output is the input power,maximum the input power
	                gs_stVpfcPiCtrl.stCoff.f32OutMin            = -1000.0f;
	        }else if(f32VinRmsTemp < 170.0f){
	            gs_stVpfcPiCtrl.stCoff.f32IntegrateMax          = 2000.0f;   //output is the input power，maximum the input power
	            gs_stVpfcPiCtrl.stCoff.f32IntegrateMin          = -500.0f;
	            gs_stVpfcPiCtrl.stCoff.f32OutMax                = 2000.0f;   //output is the input power,maximum the input power
	            gs_stVpfcPiCtrl.stCoff.f32OutMin                = -500.0f;
	        }
	        if(s_u16VinRmsForILoop == 0){
	            if(f32VinRmsTemp >= 240.0f){
	                s_u16VinRmsForILoop = 1;
	            }
	        }else{
	             if(f32VinRmsTemp < 236.0f){
	                 s_u16VinRmsForILoop = 0;
	             }
	        }
	        if(s_u16VinRmsForILoop == 0){
	            if(g_f32IacRmsRef < 0.5f){
	                f32Temp = 40;
	                gs_stIacPiGainCtrl.stCoff.f32KiTs  = 0.8f;
	            }else if(g_f32IacRmsRef < 0.75f){
	                f32Temp = 80.0f - g_f32IacRmsRef * 80.0f;
                    gs_stIacPiGainCtrl.stCoff.f32KiTs  = 0.7f;
	            }else{
                    f32Temp = 20.43875f - g_f32IacRmsRef * 0.585f;
                    gs_stIacPiGainCtrl.stCoff.f32KiTs  = 0.6f;
	            }
                gs_stIacPiGainCtrl.stCoff.f32Kp     = LIMIT(f32Temp,        15.0f,      40.0f);

                f32Temp = 0.03f + g_f32IacRmsRef  * 0.55f;
                gs_f32FeedCoff  = LIMIT(f32Temp,        0.50f,      0.95f);
	        }else{
                gs_stIacPiGainCtrl.stCoff.f32Kp   = g_stIacPiGainCtrlGuiKpHv;
                gs_stIacPiGainCtrl.stCoff.f32KiTs = g_stIacPiGainCtrlGuiKiTsHv;
                gs_f32FeedCoff                    = g_f32FeedCoffGuiHv;
	        }
	        // GUI调试使能时，交流电流环参数由在线配置值接管
	        if(g_u16IacCtrlTuneEnable != 0U){
	            gs_stIacPiGainCtrl.stCoff.f32Kp     = g_f32IacKpAc;
	            gs_stIacPiGainCtrl.stCoff.f32KiTs   = g_f32IacKiTsAc;
	            gs_f32FeedCoff                      = g_f32IacFeedCoffAc;
	        }
		}else{
		    // 直流输入功率上限和电流环参数采用190/195 V滞回切换
		    if(f32VinRmsTemp > 195.0f){
		        gs_stVpfcPiCtrl.stCoff.f32IntegrateMax      = 4500.0f;   //output is the input power，maximum the input power
		        gs_stVpfcPiCtrl.stCoff.f32IntegrateMin      = -1000.0f;
		        gs_stVpfcPiCtrl.stCoff.f32OutMax            = 4500.0f;   //output is the input power,maximum the input power
		        gs_stVpfcPiCtrl.stCoff.f32OutMin            = -1000.0f;
		        gs_stIacPiGainCtrl.stCoff.f32Kp             = g_f32IacKpDc;
		        gs_stIacPiGainCtrl.stCoff.f32KiTs           = g_f32IacKiTsDc;
		        gs_f32FeedCoff                              = g_f32IacFeedCoffDc;
		    }else if(f32VinRmsTemp < 190.0f){
		        gs_stVpfcPiCtrl.stCoff.f32IntegrateMax      = 3500.0f;   //output is the input power，maximum the input power
		        gs_stVpfcPiCtrl.stCoff.f32IntegrateMin      = -500.0f;
		        gs_stVpfcPiCtrl.stCoff.f32OutMax            = 3500.0f;   //output is the input power,maximum the input power
		        gs_stVpfcPiCtrl.stCoff.f32OutMin            = -500.0f;
		        gs_stIacPiGainCtrl.stCoff.f32Kp             = g_f32IacKpDcLv;
		        gs_stIacPiGainCtrl.stCoff.f32KiTs           = g_f32IacKiTsDcLv;
		        gs_f32FeedCoff                              = g_f32IacFeedCoffDcLv;
		    }
		}

		ctrl_pi_gain_position(&gs_stIacPiGainCtrl);

		//占空比前馈 feedforwared for vin & vout
		f32DutyForwared = gs_f32FeedCoff * (f32VpfcFastLpf - f32VinAbs) /f32VpfcFastLpf;  //防止除以0

		f32Duty = f32DutyForwared + gs_stIacPiGainCtrl.stOut.f32Out;
		g_stPfcOut.f32Duty =  LIMIT(f32Duty, 0.0f, 0.98f);
}

