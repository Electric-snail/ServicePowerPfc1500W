/*
 * BSW_HAL_ADC.h
 *
 *  Created on: 2022/9/23/
 *      Author: rjgslg
 */

#ifndef BSW_HAL_ADC_H_
#define BSW_HAL_ADC_H_

#ifndef DLLX64
#include "MCAL/MCAL_INC/BSW_MCAL_ADC.h"
#endif
#include "HARDWARE_ENV_CFG.H"

#define 	VIN_L_KP                              		 				(FULL_RANGE_VIN_L/4095)
//#define 	VIN_L_OFFSET                     						(HW_OFFSET_VIN_L * FULL_RANGE_VIN_L/ HW_ADC_REF_VOLT)

#define 	VIN_N_KP                              						(FULL_RANGE_VIN_N/4095)
//#define 	VIN_N_OFFSET                    		 				(HW_OFFSET_VIN_N * FULL_RANGE_VIN_N/ HW_ADC_REF_VOLT)

#define 	VPFC_KP                               						(FULL_RANGE_VPFC/4095)
#define 	VPFC_OFFSET                     						(HW_OFFSET_VPFC* FULL_RANGE_VPFC/ HW_ADC_REF_VOLT)

#define 	CUR_INDUCTOR_L_KP             				(FULL_RANGE_CUR_INDUCTOR_L/4095)
#define 	CUR_INDUCTOR_L_OFFSET           		(HW_OFFSET_CUR_INDUCTOR_L *  FULL_RANGE_CUR_INDUCTOR_L/ HW_ADC_REF_VOLT)

#define 	CUR_INDUCTOR_H_KP             				(FULL_RANGE_CUR_INDUCTOR_H/4095)
#define 	CUR_INDUCTOR_H_OFFSET         			 (HW_OFFSET_CUR_INDUCTOR_H *  FULL_RANGE_CUR_INDUCTOR_H/ HW_ADC_REF_VOLT)

#define 	IIN_L_KP             											(FULL_RANGE_IIN_L/4095)
#define 	IIN_L_OFFSET           									(HW_OFFSET_IIN_L *  FULL_RANGE_IIN_L/ HW_ADC_REF_VOLT)

#define 	IIN_H_KP             											(FULL_RANGE_IIN_H/4095)
#define 	IIN_H_OFFSET           									(HW_OFFSET_IIN_H *  FULL_RANGE_IIN_H/ HW_ADC_REF_VOLT)

#ifndef DLLX64
#define 		bsw_hal_calc_vin_l()    							((FLOAT32)AdcaResultRegs.ADCRESULT2    * 	VIN_L_KP    -  VIN_L_OFFSET)
#define 		bsw_hal_calc_vin_n()    							((FLOAT32)AdccResultRegs.ADCRESULT2    * 	VIN_N_KP    -  VIN_N_OFFSET)

#define 		bsw_hal_calc_iin_l()								((FLOAT32)AdcaResultRegs.ADCRESULT1    * 	IIN_L_KP    -  IIN_L_OFFSET)
#define 		 bsw_hal_calc_iin_h()								((FLOAT32)AdccResultRegs.ADCRESULT1    * 	IIN_H_KP    -  IIN_H_OFFSET)

#define 		bsw_hal_calc_vpfc()                     				((FLOAT32)AdcaResultRegs.ADCRESULT3    * 	VPFC_KP    -    VPFC_OFFSET)
#define       bsw_hal_calc_cur_inductor_ave_l()      ((FLOAT32)AdcaResultRegs.ADCRESULT0    * 	CUR_INDUCTOR_L_KP    -    CUR_INDUCTOR_L_OFFSET)
#define       bsw_hal_calc_cur_inductor_ave_h()      ((FLOAT32)AdccResultRegs.ADCRESULT0    * 	CUR_INDUCTOR_H_KP    -    CUR_INDUCTOR_H_OFFSET)

#else

typedef struct {
    unsigned short u16VinL;
    unsigned short u16VinN;
    unsigned short u16Vpfc;
    unsigned short u16CurInductorL;
    unsigned short u16CurInductorH;
    unsigned short u16IinL;
    unsigned short u16IinH;
}SIM_SAMPLE_ADC_T;

extern SIM_SAMPLE_ADC_T g_stAdc;

#define 		bsw_hal_calc_vin_l()    							((FLOAT32)g_stAdc.u16VinL   * 	VIN_L_KP    -  VIN_L_OFFSET)
#define 		bsw_hal_calc_vin_n()    							((FLOAT32)g_stAdc.u16VinN   * 	VIN_N_KP    -  VIN_N_OFFSET)

#define 		bsw_hal_calc_iin_l()								((FLOAT32)g_stAdc.u16IinL   * IIN_L_KP    -  IIN_L_OFFSET)
#define 		 bsw_hal_calc_iin_h()								((FLOAT32)g_stAdc.u16IinH    * IIN_H_KP    -  IIN_H_OFFSET)

#define 		bsw_hal_calc_vpfc()                     				((FLOAT32)g_stAdc.u16Vpfc    * 	VPFC_KP    -    VPFC_OFFSET)
#define       bsw_hal_calc_cur_inductor_ave_l()      ((FLOAT32)g_stAdc.u16CurInductorL    * 	CUR_INDUCTOR_L_KP    -    CUR_INDUCTOR_L_OFFSET)
#define       bsw_hal_calc_cur_inductor_ave_h()      ((FLOAT32)g_stAdc.u16CurInductorH    * 	CUR_INDUCTOR_H_KP    -    CUR_INDUCTOR_H_OFFSET)

#endif
#endif /* BSW_HAL_ADC_H_ */
