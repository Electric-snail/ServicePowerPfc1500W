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

#define HW_ADC_REF_VOLT                   3.3f   /* ADC reference voltage*/
#define SW_ADC_MAX_VAL                    4096.0f

#define FULL_RANGE_HVIN_V                 1031.25f//986.84f
#define FULL_RANGE_LVBAT_V                66.0f//
#define FULL_RANGE_LVOUT_V                19.8f//20.497f
#define FULL_RANGE_LVOUT_V_R              21.06f//19.8f
#define FULL_RANGE_LVOUT_I                110.0f//73.3f
#define FULL_RANGE_1V24_V                 3.3f//
#define FULL_RANGE_HW_REV_V               3.3f//

#define HW_OFFSET_HVIN_V_SAMPLE_POINT     0.0f      /* hardware offset Voltage for HVIN_V   */
#define HW_OFFSET_LVBAT_V_SAMPLE_POINT    1.648f      /* hardware offset Voltage for LVBAT_V  */
#define HW_OFFSET_LVOUT_V_SAMPLE_POINT    0.0f      /* hardware offset Voltage for LVOUT_V  */
#define HW_OFFSET_LVOUT_V_R_SAMPLE_POINT  0.0f      /* hardware offset Voltage for LVOUT_V_R*/
#define HW_OFFSET_LVOUT_I_SAMPLE_POINT    1.648f     /* hardware offset Current for LVOUT_I  */
#define HW_OFFSET_1V24_V_SAMPLE_POINT     0.0f      /* hardware offset Voltage for 1V25_V   */
#define HW_OFFSET_HW_REV_V_SAMPLE_POINT   0.0f      /* hardware    */

#define HVIN_V_KP                         (FULL_RANGE_HVIN_V/ SW_ADC_MAX_VAL)
#define HVIN_V_OFFSET                     (HW_OFFSET_HVIN_V_SAMPLE_POINT * FULL_RANGE_HVIN_V/ HW_ADC_REF_VOLT)

#define LVBAT_V_KP                        (FULL_RANGE_LVBAT_V/ SW_ADC_MAX_VAL)
#define LVBAT_V_OFFSET                    (HW_OFFSET_LVBAT_V_SAMPLE_POINT * FULL_RANGE_LVBAT_V/ HW_ADC_REF_VOLT)

#define LVOUT_V_KP                        (FULL_RANGE_LVOUT_V/ SW_ADC_MAX_VAL)
#define LVOUT_V_OFFSET                    (HW_OFFSET_LVOUT_V_SAMPLE_POINT * FULL_RANGE_LVOUT_V/ HW_ADC_REF_VOLT)

#define LVOUT_V_R_KP                      (FULL_RANGE_LVOUT_V_R/ SW_ADC_MAX_VAL)
#define LVOUT_V_R_OFFSET                  (HW_OFFSET_LVOUT_V_R_SAMPLE_POINT * FULL_RANGE_LVOUT_V_R/ HW_ADC_REF_VOLT)

#define LVOUT_I_KP                        (FULL_RANGE_LVOUT_I/ SW_ADC_MAX_VAL)
#define LVOUT_I_OFFSET                    (HW_OFFSET_LVOUT_I_SAMPLE_POINT * FULL_RANGE_LVOUT_I/ HW_ADC_REF_VOLT)

#define LV1V24_V_KP                       (FULL_RANGE_1V24_V/ SW_ADC_MAX_VAL)
#define LV1V24_V_OFFSET                   (HW_OFFSET_1V24_V_SAMPLE_POINT * FULL_RANGE_1V24_V/ HW_ADC_REF_VOLT)

#define HW_REV_V_KP                       (FULL_RANGE_HW_REV_V/ SW_ADC_MAX_VAL)
#define HW_REV_V_OFFSET                   (HW_OFFSET_HW_REV_V_SAMPLE_POINT * FULL_RANGE_HW_REV_V/ HW_ADC_REF_VOLT)

#ifndef DLLX64
#if (OVERSAMPLED == 0)
#define u16GetLVOUT_V_AdcVal()          AdcaResultRegs.ADCRESULT1
#define u16GetLVBAT_V_AdcVal()          AdcaResultRegs.ADCRESULT2

#define u16GetLVOUT_I_AdcVal()          AdccResultRegs.ADCRESULT0
#define u16GetLVOUT_V_R_AdcVal()        AdccResultRegs.ADCRESULT1
#define u16GetHVIN_V_AdcVal()           AdccResultRegs.ADCRESULT2
#define u16Get1V24_V_AdcVal()           AdccResultRegs.ADCRESULT4
#else

#endif
#define u16GetHW_VER_AdcVal()               AdcaResultRegs.ADCRESULT0
#define u16GetCASE_T_AdcVal()				AdcaResultRegs.ADCRESULT3
#define u16GetLV_SEC_T_AdcVal()				AdcaResultRegs.ADCRESULT4
#define u16GetHwWakeUp_AdcVal()				AdcaResultRegs.ADCRESULT5
#define u16GetHV_PRI_T_AdcVal()             AdccResultRegs.ADCRESULT3
#define BSW_HAL_GetHvInVoltVal()     \
        ((FLOAT32)u16GetHVIN_V_AdcVal()    * HVIN_V_KP    - HVIN_V_OFFSET)
#define BSW_HAL_GetLvBatVoltVal()     \
        ((FLOAT32)u16GetLVBAT_V_AdcVal()   * LVBAT_V_KP   - LVBAT_V_OFFSET)
#define BSW_HAL_GetLvOutVoltVal()     \
        ((FLOAT32)u16GetLVOUT_V_AdcVal()   * LVOUT_V_KP   - LVOUT_V_OFFSET)
#define BSW_HAL_GetLvOutRVoltVal()     \
        ((FLOAT32)u16GetLVOUT_V_R_AdcVal() * LVOUT_V_R_KP - LVOUT_V_R_OFFSET)
#define BSW_HAL_GetLvOutCurrVal()     \
        ((FLOAT32)u16GetLVOUT_I_AdcVal()   * LVOUT_I_KP   - LVOUT_I_OFFSET)
#define BSW_HAL_Get1V24VoltVal()     \
        ((FLOAT32)u16Get1V24_V_AdcVal()    * LV1V24_V_KP  - LV1V24_V_OFFSET)
#define BSW_HAL_GetHwVerVoltVal()     \
        ((FLOAT32)u16GetHW_VER_AdcVal()    * HW_REV_V_KP  - HW_REV_V_OFFSET)
#else
typedef struct {
	unsigned short u16HwVer;
	unsigned short u16CaseT;
	unsigned short u16SecT;
	unsigned short u16WakeUp;
	unsigned short u16PriT;
	unsigned short u16LvVout;
	unsigned short u16LvBat;
	unsigned short u16LvIout;
	unsigned short u16LvVoutR;
	unsigned short u16HvVin;
	unsigned short u16Vref1_24;
}SIM_SAMPLE_ADC_T;
extern SIM_SAMPLE_ADC_T g_stAdc;

#define u16GetHW_VER_AdcVal()             g_stAdc.u16HwVer
#define u16GetCASE_T_AdcVal()             g_stAdc.u16CaseT
#define u16GetLV_SEC_T_AdcVal()           g_stAdc.u16SecT
#define u16GetHwWakeUp_AdcVal()           g_stAdc.u16WakeUp
#define u16GetHV_PRI_T_AdcVal()           g_stAdc.u16PriT

#define u16GetLVOUT_V_AdcVal()            g_stAdc.u16LvVout  
#define u16GetLVBAT_V_AdcVal()            g_stAdc.u16LvBat

#define u16GetLVOUT_I_AdcVal()            g_stAdc.u16LvIout
#define u16GetLVOUT_V_R_AdcVal()          g_stAdc.u16LvVoutR  
#define u16GetHVIN_V_AdcVal()             g_stAdc.u16HvVin
#define u16Get1V24_V_AdcVal()             g_stAdc.u16Vref1_24

#define BSW_HAL_GetHvInVoltVal()     \
        ((FLOAT32)u16GetHVIN_V_AdcVal()    * HVIN_V_KP    - HVIN_V_OFFSET)
#define BSW_HAL_GetLvBatVoltVal()     \
        ((FLOAT32)u16GetLVBAT_V_AdcVal()   * LVBAT_V_KP   - LVBAT_V_OFFSET)
#define BSW_HAL_GetLvOutVoltVal()     \
        ((FLOAT32)u16GetLVOUT_V_AdcVal()   * LVOUT_V_KP   - LVOUT_V_OFFSET)
#define BSW_HAL_GetLvOutRVoltVal()     \
        ((FLOAT32)u16GetLVOUT_V_R_AdcVal() * LVOUT_V_R_KP - LVOUT_V_R_OFFSET)
#define BSW_HAL_GetLvOutCurrVal()     \
        ((FLOAT32)u16GetLVOUT_I_AdcVal()   * LVOUT_I_KP   - LVOUT_I_OFFSET)
#define BSW_HAL_Get1V24VoltVal()     \
        ((FLOAT32)u16Get1V24_V_AdcVal()    * LV1V24_V_KP  - LV1V24_V_OFFSET)

#endif

#endif /* BSW_HAL_ADC_H_ */
