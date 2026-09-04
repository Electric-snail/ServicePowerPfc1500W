/*
 * Data_Rec_Cfg.h
 *
 *  Created on: 2022-9-13
 *      Author: xj8r1j
 */
#include "DEBUG_PLATFORM/DATA_REC/DATA_REC_DEFINE.h"

#include "MEASURE/MEASURE.H"
#include "PFC_LLC_COMM/PFC_LLC_COMM.H"
#include "ISR_INC/BSW_ISR_ADC.H"
#include "PFC_CTR/PFC_CTR.H"

#ifndef 		DATA_REC_SETTING
#define         DATA_REC_SETTING
#define         DATA_REC_AUTO_TX_ENABLE   		   		0
#define    	  	DATA_LOG_MIN_INTERVAL                   100
#define         DATA_REC_AUTO_PERIOD                    200
#endif

extern 		float     			gs_f32FeedCoff;
extern         UINT16   		g_u16RestartCnt;
extern         UINT16           g_u16TestCnt;

//the data record group must be less than 3, the maximum variable counter is defined by DATA_REC_MAX_CNT
DATA_REC_START(PFC_DATA,  0x00)
DATA_REC_ITEM(eu_fp32,	    gs_stIacPiGainCtrl.stOut.f32Out)
DATA_REC_ITEM(eu_fp32,      gs_stIacPiGainCtrl.stIn.f32Fb)
DATA_REC_ITEM(eu_fp32,      gs_stIacPiGainCtrl.stIn.f32Ref)
DATA_REC_ITEM(eu_fp32,      gs_stIacPiGainCtrl.stIn.f32Gain)
DATA_REC_ITEM(eu_fp32,      gs_stIacPiGainCtrl.stCoff.f32Kp)
DATA_REC_ITEM(eu_fp32,      gs_stIacPiGainCtrl.stCoff.f32KiTs)
DATA_REC_ITEM(eu_fp32,      gs_stIacPiGainCtrl.stInner.f32Integrate)
DATA_REC_ITEM(eu_fp32,      gs_stIacPiGainCtrl.stInner.f32Err)
DATA_REC_END()

