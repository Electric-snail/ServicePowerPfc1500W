/*
 * BSW_HAL_CMPSS.H
 *
 *  Created on: 2025/10/16/
 *      Author: Hongbo.Jiang
 */

#ifndef BSW_HAL_CMPSS_H_
#define BSW_HAL_CMPSS_H_
#include "ENV_CFG/HARDWARE_ENV_CFG.h"

#ifndef DLLX64
#include "common/include/F28x_Project.h"
#include "MCAL_INC/BSW_MCAL_CMPSS.h"

#define     read_vpfc_hw_ovp_flag()					CmpssLite3Regs.COMPSTS.bit.COMPLLATCH

#define     clr_vpfc_hw_ovp_flag()                      g_stCmpss3.f32LatchOut	= 0

#else

typedef struct {
	float f32InNegDac;
	float f32Vref;
	float f32InPos;
	float f32Out;
	float f32LatchOut;
	float f32LatchClr;
}SIM_CMPSS_T;

extern SIM_CMPSS_T g_stCmpss1;
extern SIM_CMPSS_T g_stCmpss3;

#define     read_vpfc_hw_ovp_flag()						g_stCmpss3.f32LatchOut	
#define     clr_vpfc_hw_ovp_flag()                      g_stCmpss3.f32LatchOut	= 0

#endif

#endif
