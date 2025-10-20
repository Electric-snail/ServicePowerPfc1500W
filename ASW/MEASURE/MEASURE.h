/*
 * measure.h
 *
 *  Created on: 2022/11/24
 *      Author: rjgslg
 */

#ifndef MEASURE_H_
#define MEASURE_H_

#include "PUBLIC_INC/POWER_CALC.H"
/******macros definition region**************/
#define VDC_BUSAVG_FC_HZ            10.0f
#define VDC_OUTAVG_FC_HZ            10.0f
#define IDC_OUTAVG_FC_HZ            10.0f

#define TEMP_OUTAVG_FC_HZ           1.0f
#define TASK_10MS_TS                0.01f

#define B2B_DIFF_OUTAVG_FC_HZ       1.0f
#define OUT_DIFF_OUTAVG_FC_HZ       1.0f


/*****data type definition region ***************/
typedef struct {
	RMS_CALC_OBJ_T          		stVinRmsObj;
	RMS_CALC_OBJ_T          		stIinRmsObj;
	AVE_CALC_OBJ_T          		stPinAveObj;
	POL_FRQ_CALC_OBJ_T      stVinPolFrqObj;
	float f32Temperature;
	float f32VpfcLpf;
	float f32VinRmsLpf;
	float f32IinRmsLpf;
}MEASURE_OUT_T;


/********* function declaration region *********************************/
extern void measure_fast_task(void);
extern void measure_1ms_task(void);
extern void measure_10ms_task(void);
extern void measure_init(void);

extern		MEASURE_OUT_T					    g_stMeasureOut;

#define		f32_get_vin_rms_flt()				g_stMeasureOut.f32VinRmsLpf
#define		f32_get_vin_rms()					   g_stMeasureOut.stVinRmsObj.stOut.f32Rms

#define		f32_get_iin_rms_flt()				g_stMeasureOut.f32IinRmsLpf
#define     f32_get_iin_rms()					    g_stMeasureOut.stIinRmsObj.stOut.f32Rms

#define     u16_get_vin_type()              	g_stMeasureOut.stVinPolFrqObj.stOut.u16Type
#define     u16_get_vin_pol()              		g_stMeasureOut.stVinPolFrqObj.stOut.u16Pol
#define     f32_get_vin_freq()              	g_stMeasureOut.stVinPolFrqObj.stOut.f32Frq
#define     f32_get_pin_ave()					g_stMeasureOut.stIinRmsObj.stOut.f32Rms

#define     f32_get_vpfc_lpf()					g_stMeasureOut.f32VpfcLpf

#endif /* MEASURE_H_ */
