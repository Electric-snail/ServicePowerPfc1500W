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



extern 	volatile ANA_PHY_VALUE_T 	g_stAnaPhyRaw;
extern 	volatile ANA_PHY_VALUE_T 	g_stAnaPhyLpf;

#define	f32_get_vpfc_volt_raw()    			g_stAnaPhyRaw.f32Vpfc
#define	f32_get_vin_volt_raw()    			g_stAnaPhyRaw.f32Vin

extern __interrupt void adcA1ISR(void);
#ifdef __cplusplus
}
#endif // extern "C"

//extern UINT16 probe_var;

#endif
//===========================================================================
// End of file.
//===========================================================================
