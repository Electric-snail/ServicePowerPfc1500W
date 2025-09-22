/*
 * Data_Rec_Cfg.h
 *
 *  Created on: 2022-9-13
 *      Author: xj8r1j
 */
#include "DEBUG_PLATFORM/DATA_REC/DATA_REC_DEFINE.h"

#ifndef 		DATA_REC_SETTING
#define         DATA_REC_SETTING
#define         DATA_REC_AUTO_TX_ENABLE   		   1
#define    		DATA_LOG_MIN_INTERVAL                 100
#define         DATA_REC_AUTO_PERIOD                  200
#endif


extern float f32VoltRaw;
extern float g_f32VoltLpf;


//the data record group must be less than 3, the maximum variable counter is defined by DATA_REC_MAX_CNT
DATA_REC_START(PFC_DATA,  0x00)

DATA_REC_ITEM(eu_fp32,		f32VoltRaw)
DATA_REC_ITEM(eu_fp32,		g_f32VoltLpf)

DATA_REC_END()

