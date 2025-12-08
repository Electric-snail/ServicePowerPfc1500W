/*
 * Data_Rec_Cfg.h
 *
 *  Created on: 2022-9-13
 *      Author: xj8r1j
 */
#include "DEBUG_PLATFORM/DATA_REC/DATA_REC_DEFINE.h"

#include "MEASURE/MEASURE.H"
#include "PFC_CTR/PFC_CTR.H"

#ifndef 		DATA_REC_SETTING
#define         DATA_REC_SETTING
#define         DATA_REC_AUTO_TX_ENABLE   		   		0
#define    	  	DATA_LOG_MIN_INTERVAL                   100
#define         DATA_REC_AUTO_PERIOD                    200
#endif


//the data record group must be less than 3, the maximum variable counter is defined by DATA_REC_MAX_CNT
DATA_REC_START(PFC_DATA,  0x00)
DATA_REC_ITEM(eu_fp32,	g_stMeasureOut.f32VinRmsLpf)
DATA_REC_ITEM(eu_fp32,	g_stMeasureOut.f32IinRmsLpf)
DATA_REC_ITEM(eu_fp32,	g_stMeasureOut.f32VpfcLpf)
DATA_REC_ITEM(eu_fp32,	g_stPfcOut.f32Duty)
DATA_REC_ITEM(eu_fp32,	g_stMeasureOut.stIinRmsObj.stOut.f32Rms)
DATA_REC_ITEM(eu_fp32,	g_stMeasureOut.stPinAveObj.stOut.f32Ave)
DATA_REC_ITEM(eu_fp32,	g_stMeasureOut.stVinPolFrqObj.stOut.f32Frq)
DATA_REC_END()

