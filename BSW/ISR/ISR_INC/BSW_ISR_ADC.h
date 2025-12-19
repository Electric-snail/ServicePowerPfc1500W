/*********************************************************************
File name:       BSW_ISR_ADC..h
Purpose :         1. Define macro
                          2.  Define data type, such as structure/enum
                          3. import variables  by  including head file(s)
                          4. export variables by keywords( extern)
 
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/

#ifndef BSW_ISR_ADC_H
#define BSW_ISR_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#include "PUBLIC_INC/DIGITAL_PLL.H"
#include "PUBLIC_INC/DF_MATH.H"

typedef struct {
	float f32Vpfc;
	float f32IlAve;
	float f32IlAveL;
	float f32IlAveH;
	float f32VinL;
	float f32VinN;
	float f32Vin;
	float f32IinL;
	float f32IinH;
	float f32Iin;
}ANA_PHY_VALUE_T;


#define        LOOP_INVALID_MODE              	    0
#define        LOOP_OPEN_MODE                 	    1
#define        LOOP_VOLT_OPEN_IL_CLOSE		2
#define        LOOP_CLOSE_MODE 				  	    3

extern 	volatile ANA_PHY_VALUE_T 			g_stAnaPhyRaw;
extern 	volatile SOGI_OBJ_T   						gs_stSogi;
extern 	volatile NOTCH_OBJ_T					gs_stVpfcNotchFilt;
extern 	volatile ORTH_PLL_OBJ_T  				gs_stOrthPll;
extern      volatile unsigned short						g_u16FaultDetetFlag;
extern 	unsigned short										g_u16LoopWorkMode;
extern		 float														g_f32OpenDuty;
extern volatile float                  g_f32VpfcIsrLpf;
#define f32_get_vac_volt_pll()              gs_stOrthPll.stOut.f32SigAlpha

#define f32_get_vac_volt_q_pll()			gs_stOrthPll.stOut.f32SigBeta	

#define	f32_get_vpfc_raw()    				g_stAnaPhyRaw.f32Vpfc

#define	f32_get_vpfc_npf()    				gs_stVpfcNotchFilt.stOut.f32Out

#define	f32_get_vin_raw()    				g_stAnaPhyRaw.f32Vin

#define	f32_get_iin_low_raw()    			g_stAnaPhyRaw.f32IinL

#define f32_get_curr_inductor_ave()         g_stAnaPhyRaw.f32IlAve

#define f32_get_vpfc_isr_lpf()               g_f32VpfcIsrLpf
#define IsFastFaultDetect()                     g_u16FaultDetetFlag
#define ClrFastFaultDetectFlag()            g_u16FaultDetetFlag = 0

extern INTERRUPT void adcA1ISR(void);

extern void adc_isr_init(void);

#ifdef __cplusplus
}
#endif // extern "C"

//extern UINT16 probe_var;

#endif
//===========================================================================
// End of file.
//===========================================================================
