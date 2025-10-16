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
#include "ENV_CFG/HARDWARE_ENV_CFG.H"
#endif


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


#define 		bsw_hal_calc_vin_l()    							((FLOAT32)AdcaResultRegs.ADCRESULT2    * 	VIN_L_KP    -  VIN_L_OFFSET)
#define 		bsw_hal_calc_vin_n()    							((FLOAT32)AdccResultRegs.ADCRESULT2    * 	VIN_N_KP    -  VIN_N_OFFSET)

#define 		bsw_hal_calc_iin_l()									((FLOAT32)AdcaResultRegs.ADCRESULT1    * 	IIN_L_KP    -  IIN_L_OFFSET)
#define 		 bsw_hal_calc_iin_h()								((FLOAT32)AdccResultRegs.ADCRESULT1    * 	IIN_H_KP    -  IIN_H_OFFSET)

#define 		bsw_hal_calc_vpfc()                     				((FLOAT32)AdcaResultRegs.ADCRESULT3    * 	VPFC_KP    -    VPFC_OFFSET)
#define       bsw_hal_calc_cur_inductor_ave_l()      ((FLOAT32)AdcaResultRegs.ADCRESULT0    * 	CUR_INDUCTOR_L_KP    -    CUR_INDUCTOR_L_OFFSET)
#define       bsw_hal_calc_cur_inductor_ave_h()      ((FLOAT32)AdccResultRegs.ADCRESULT0    * 	CUR_INDUCTOR_H_KP    -    CUR_INDUCTOR_H_OFFSET)

#endif /* BSW_HAL_ADC_H_ */
