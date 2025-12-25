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

#define     XCAP_COMP_EN											1
#define 	 Cx																		2.22e-6
#ifndef  DLLX64
#pragma  CODE_SECTION(pfc_controller, 					".TI.ramfunc");
#pragma  CODE_SECTION(ctrl_pi_gain_position, 		".TI.ramfunc");
#pragma  CODE_SECTION(ctrl_pi_position, 				".TI.ramfunc");
#pragma  DATA_SECTION(gs_stIacPiGainCtrl, ".CtrlVariableSector");
#endif

STATIC PI_POS_T				    gs_stVpfcPiCtrl;
STATIC PI_GAIN_POS_T		gs_stIacPiGainCtrl;
STATIC float							    gs_f32FeedCoff;
PFC_CTR_OUT						g_stPfcOut;
//float						g_f32VpfcPiKpFast;
//float						g_f32VpfcPiKiTsFast;
float							g_f32VpfcPiKpSlow;
float							g_f32VpfcPiKiTsSlow;
float                        g_f32PowerOpenSet;
float 						f32DutyForwared;

void 	pfc_controller_init(void){
		gs_stVpfcPiCtrl.stCoff.f32IntegrateMax			= 3500.0f;   //output is the input power，maximum the input power
		gs_stVpfcPiCtrl.stCoff.f32IntegrateMin			= -1000.0f;

		gs_stVpfcPiCtrl.stCoff.f32OutMax				= 3500.0f;   //output is the input power,maximum the input power
		gs_stVpfcPiCtrl.stCoff.f32OutMin				= -1000.0f;

	//	g_f32VpfcPiKpFast									    = 100;
	//	g_f32VpfcPiKiTsFast									= 5 * 2*3.1415926f * 5 * CTR_PERIOD;

		g_f32VpfcPiKpSlow									    = 50.0f;
		g_f32VpfcPiKiTsSlow									= 6.2 * 2 * 3.1415926f * 5 * CTR_PERIOD;

		gs_stVpfcPiCtrl.stIn.f32Fb                          = 0.0f;
		gs_stVpfcPiCtrl.stIn.f32Ref                        = 0.0f;
		gs_stVpfcPiCtrl.stCoff.f32Kp						= g_f32VpfcPiKpSlow;
		gs_stVpfcPiCtrl.stCoff.f32KiTs					= g_f32VpfcPiKiTsSlow;
		gs_stVpfcPiCtrl.stInner.f32Integrate			= 0;
		gs_stVpfcPiCtrl.stInner.f32Err						= 0;

		gs_stIacPiGainCtrl.stCoff.f32IntegrateMax			= 0.95f;
		gs_stIacPiGainCtrl.stCoff.f32IntegrateMin			= -1.0f;

		gs_stIacPiGainCtrl.stCoff.f32OutMax					= 0.95f;
		gs_stIacPiGainCtrl.stCoff.f32OutMin					= -1.0f;

	//	gs_stIacPiGainCtrl.stCoff.f32Kp						= 0.02 * 380f;
	//	gs_stIacPiGainCtrl.stCoff.f32KiTs					= 0.2f * 666.6 * 380f/ 65000.0f; //0.02f*2*pi*1000/65000.0f
		gs_stIacPiGainCtrl.stCoff.f32Kp						= 20.0f;
		gs_stIacPiGainCtrl.stCoff.f32KiTs					= 20.0f * 4000.0f/ 65000.0f; //0.02f*2*pi*1000/65000.0f
		gs_stIacPiGainCtrl.stInner.f32Integrate			= 0;
		gs_stIacPiGainCtrl.stInner.f32Err					= 0;

		gs_f32FeedCoff											    = 1.0f;
		g_stPfcOut.f32Duty											= 0.0f;
}

void 	pfc_controller(void){
	//	static unsigned short s_u16VpfcFeedFlag = 0;
	//	static unsigned short s_u16VpfcPiCoffLevel = 0;
		float f32Duty;
	    float f32VacPll		= f32_get_vac_volt_pll();
		float f32VpfcNpf    = f32_get_vpfc_npf();
		float f32VpfcLpf    = f32_get_vpfc_isr_lpf();
		float f32VinAbs		= ABSF(f32_get_vin_raw());
		float f32VinRms		= f32_get_vin_rms_flt();
		float f32Temp;
		float f32IlRefTemp;

		gs_stVpfcPiCtrl.stIn.f32Ref = f32_get_vpfc_set();
		gs_stVpfcPiCtrl.stIn.f32Fb = f32VpfcNpf;  //f32VpfcLpf;
		
		/*		f32VpfcErrAbs = ABSF(gs_stVpfcPiCtrl.stIn.f32Ref - gs_stVpfcPiCtrl.stIn.f32Fb);
   	   if (f32VpfcErrAbs < 10) {
			gs_stVpfcPiCtrl.stCoff.f32Kp	    = g_f32VpfcPiKpSlow;
			gs_stVpfcPiCtrl.stCoff.f32KiTs	= g_f32VpfcPiKiTsSlow;
		}
		else {
			gs_stVpfcPiCtrl.stCoff.f32Kp     = ((f32VpfcErrAbs - 10) * 0.1 + 1.0f)*g_f32VpfcPiKpSlow;
			gs_stVpfcPiCtrl.stCoff.f32KiTs  = ((f32VpfcErrAbs - 10) * 0.1 + 1.0f) * g_f32VpfcPiKiTsSlow;
		}*/
		gs_stVpfcPiCtrl.stCoff.f32Kp	    = g_f32VpfcPiKpSlow;
		gs_stVpfcPiCtrl.stCoff.f32KiTs	= g_f32VpfcPiKiTsSlow;

		ctrl_pi_position(&gs_stVpfcPiCtrl);
		//in case of the vpfc overshoot too high
		f32Temp	   = f32VpfcLpf -  15.0f;
		if(f32Temp	 > gs_stVpfcPiCtrl.stIn.f32Ref){
			gs_stVpfcPiCtrl.stInner.f32Integrate = 0.0f;
			gs_stVpfcPiCtrl.stOut.f32Out           = 0.0f;
		}

		if (f32VinRms < 35.0f)  f32VinRms = 35.0f;

		#if(XCAP_COMP_EN == 1)
				f32Temp 			           	= Cx * 1.414f * 2 * pi * 50.0f * f32_get_vac_volt_q_pll() * (-1.0f);
				f32IlRefTemp				= gs_stVpfcPiCtrl.stOut.f32Out * f32VacPll / (f32VinRms * f32VinRms) + f32Temp;

				f32Temp						= f32VacPll * f32IlRefTemp;

				//if need to compensate the reative power, set as the zero, becasue this topology can't to compensate the reative power
				if (f32Temp <= 0)
					gs_stIacPiGainCtrl.stIn.f32Ref = 0;
				else
					gs_stIacPiGainCtrl.stIn.f32Ref = ABSF(f32IlRefTemp);
		#else
				f32IlRefTemp								= gs_stVpfcPiCtrl.stOut.f32Out * f32VacPll / (f32VinRms * f32VinRms);
				gs_stIacPiGainCtrl.stIn.f32Ref	= ABSF(f32IlRefTemp);
		#endif

		#if defined IL_CLOSE_LOOP_MODE
				gs_stIacPiGainCtrl.stIn.f32Ref	= g_f32PowerOpenSet * ABSF(f32VacPll)/(f32VinRms * f32VinRms);
		#endif

		gs_stIacPiGainCtrl.stIn.f32Fb	= f32_get_curr_inductor_ave();

		if(f32VpfcLpf  < 100.0f)    f32VpfcLpf = 100.0f;

		gs_stIacPiGainCtrl.stIn.f32Gain = 1/f32VpfcLpf;

		ctrl_pi_gain_position(&gs_stIacPiGainCtrl);

		//占空比前馈 feedforwared for vin & vout
	 
		f32DutyForwared = gs_f32FeedCoff * (f32VpfcLpf - f32VinAbs) /f32VpfcLpf;  //防止除以0

		f32Duty = f32DutyForwared + gs_stIacPiGainCtrl.stOut.f32Out;

		g_stPfcOut.f32Duty =  LIMIT(f32Duty, 0.0f, 0.98f);

		/*if (f32Duty > 0.98f) {  //限最大值输出，以及防止正向饱和
			g_stPfcOut.f32Duty = 0.98f;
		//	f32Temp = 1.0f - f32DutyForwared;
		//	set_pi_position_integrate(&gs_stIacPiGainCtrl, f32Temp);
		}
		else if (f32Duty < 0.0f) {  // 限最小输出，以及防止反向饱和
			g_stPfcOut.f32Duty = 0.0f;
		//	f32Temp = 0.0f - f32DutyForwared;
		//	set_pi_position_integrate(&gs_stIacPiGainCtrl, f32Temp);
		}
		else {
			g_stPfcOut.f32Duty = f32Duty;
		}*/



}

