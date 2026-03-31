/*
 * VPFC_ADJUST.C
 *
 *  Created on: 2026.3.10
 *      Author: Administrator
 */
#include "MEASURE/MEASURE.h"
#include "PFC_LLC_COMM/PFC_LLC_COMM.H"

float g_f32VpfcPiKpLv;
float g_f32VpfcPiKiTsLv;
float g_f32VpfcPiGainLv;
float g_f32VpfcPiKpMv;
float g_f32VpfcPiKiTsMv;
float g_f32VpfcPiGainMv;
float g_f32VpfcPiKpHv;
float g_f32VpfcPiKiTsHv;
float g_f32VpfcPiGainHv;
extern float g_f32VpfcPiGain;
extern float g_f32VpfcPiKpSlow;
extern float g_f32VpfcPiKiTsSlow;

void vpfc_adjust_init(void){
	g_f32VpfcPiKpLv 		= 5.0f;//30.0f;
	g_f32VpfcPiKiTsLv 	= 0.0025f;
	g_f32VpfcPiGainLv    = 1.0f;
	g_f32VpfcPiKpMv		= 5.0f;//30.0f;
	g_f32VpfcPiKiTsMv	= 0.0015f;
	g_f32VpfcPiGainMv   = 0.8f;
	g_f32VpfcPiKpHv		= 20.0f;//30.0f;
	g_f32VpfcPiKiTsHv	= 0.005f;
	g_f32VpfcPiGainHv   = 1.2f;
}
float f32_get_vpfc_adjust(void){
	float f32VpfcRef;
	float f32VrmsValue = f32_get_vin_rms();
	if (u16_get_vin_type() == AC_TYPE){
		if(f32VrmsValue <= 275.0f){
				f32VpfcRef = 400.0f;
				g_f32VpfcPiKpSlow    = g_f32VpfcPiKpLv;
				g_f32VpfcPiKiTsSlow = g_f32VpfcPiKiTsLv;
				g_f32VpfcPiGain         = g_f32VpfcPiGainLv;
		}else if(f32VrmsValue <= 285.0f){
				f32VpfcRef = 400.0f + 2.0*(f32VrmsValue - 275.0f);
				g_f32VpfcPiKpSlow    = g_f32VpfcPiKpMv;
				g_f32VpfcPiKiTsSlow = g_f32VpfcPiKiTsMv;
				g_f32VpfcPiGain         = g_f32VpfcPiGainMv;
		}else if(f32VrmsValue >= 295.0f){
			g_f32VpfcPiKpSlow    = g_f32VpfcPiKpHv;
			g_f32VpfcPiKiTsSlow = g_f32VpfcPiKiTsHv;
			g_f32VpfcPiGain         = g_f32VpfcPiGainHv;
			f32VpfcRef 					= 430.0f;
		}else{
			g_f32VpfcPiKpSlow    = g_f32VpfcPiKpHv;
			g_f32VpfcPiKiTsSlow = g_f32VpfcPiKiTsHv;
			g_f32VpfcPiGain         = g_f32VpfcPiGainHv;
			f32VpfcRef 					= 420.0f + (f32VrmsValue - 285.0f);
		}
	}else{
		f32VpfcRef = 400.0f;
	}
/*	if(g_f32VpfcTestTarget > 300.0f){
		f32VpfcRef = g_f32VpfcTestTarget;
	}*/
	if(f32_get_comm_vpfc_set() > f32VpfcRef)
		f32VpfcRef = f32_get_comm_vpfc_set() ;
	return f32VpfcRef;
}



