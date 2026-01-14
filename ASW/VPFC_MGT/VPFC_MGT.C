/*
 * VPFC_MGT.C
 *
 *  Created on: 2025Äê10ÔÂ20ÈÕ
 *      Author: Administrator
 */
#include "MEASURE/MEASURE.H"
#include "VPFC_MGT/VPFC_MGT.H"

float g_f32VpfcSetTarget = 0;


void vpfc_mgt_init(void){
	g_f32VpfcSetTarget = VPFC_TARGET_DEFAULT;
}

#define     EFF_K0           0.92f
#define     EFF_K1           0.93f
#define     EFF_K2           0.94f
#define     EFF_K3           0.95f

void vpfc_mgt_10ms_task(void){
	float f32VinPower = f32_get_pin_lpf();
	float f32Temp = f32_get_vin_rms();;
	float f32VpfcMin = 1.414f * f32Temp + 5.0f;

	if(f32VinPower <  (307.0f/EFF_K0)){
		f32Temp = 400.0f;
	}else if(f32VinPower < (369.0f/EFF_K1)){
		f32Temp  = 400.0f + (f32VinPower -(307.0f/EFF_K0))*5.0f/( (369.0f/EFF_K1) - (307.0f/EFF_K0));
	}else if(f32VinPower < (1144.0f/EFF_K2)){
		f32Temp  = 405.0f;
	}else if(f32VinPower < (1353.0f/EFF_K3)){
		f32Temp  = 405.0f + (f32VinPower - (1144.0f/EFF_K2))*17.0f/((1353.0f/EFF_K3) - (1144.0f/EFF_K2));
	}else{
		f32Temp  = 422.0f;
	}

	if(f32Temp < f32VpfcMin )
		g_f32VpfcSetTarget = f32VpfcMin;
	else
		g_f32VpfcSetTarget = f32Temp;
}

