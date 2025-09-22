/*
 * MEASURE_INF.h
 *
 *  Created on: 2022.11.29.
 *      Author: xj8r1j
 */

#ifndef _MEASURE_INF_H_
#define _MEASURE_INF_H_

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

 /*****data type definition region ***************/
typedef struct
{
    FLOAT32 f32Vdc_HvIn;
    FLOAT32 f32Vdc_bat;
    FLOAT32 f32Vdc_out;
    FLOAT32 f32Vdc_outR;
    FLOAT32 f32Vdc_1v24;
    FLOAT32 f32Idc_out;
    FLOAT32 f32Idc_out_abs;
    FLOAT32 f32Vdc_out_canData;
    FLOAT32 f32Idc_outR_canData;
    FLOAT32 f32Vdc_bat_canData;
    FLOAT32 f32Idc_out_canData;
    FLOAT32 f32Vdc_HvIn_canData;
    FLOAT32 f32B2bVoltDiff;
    FLOAT32 f32OutVoltDiff;
    FLOAT32 f32CtrlCompse;
    FLOAT32 f32HvPriT;
    FLOAT32 f32LvSecT;
    FLOAT32 f32CaseT;
    FLOAT32 f32MdcdcAhIntgl;
    FLOAT32 f32MdcdcWhIntgl;
    FLOAT32 f32TotalAH;
    FLOAT32 f32TotalEgr;
    FLOAT32 f32MdcdcAhIntgl_ALL;
    FLOAT32 f32MdcdcWhIntgl_ALL;
}MEASURE_T;

typedef struct {
    float     f32AhIntglRealTimeVal;
    float     f32WhIntglRealTimeVal;
    float     f32MdcdcWhIntgl_ALL;
    float     f32MdcdcAhIntgl_ALL;
}AHWH_INFO_INF_T;

/********* variable declaration region *********************************/
extern UINT16                     g_u16AhIntglFrzFlag;
extern UINT16                     g_u16HwVerHexVal;
extern AHWH_INFO_INF_T            g_stAhWhIntglInfoData[1];
extern MEASURE_T                  g_stMeasureAve;
extern MEASURE_T                  g_stMeasureRaw;

#define u16_get_AhIntglFrzFlag()           g_u16AhIntglFrzFlag
#define clr_AhIntglFrzFlag()               g_u16AhIntglFrzFlag = 0

#define u16_get_HwVerHexVal()              g_u16HwVerHexVal

#define f32_get_HVDCinV_Raw()              (g_stMeasureRaw.f32Vdc_HvIn)
#define f32_get_LVDCoutV_Raw()             (g_stMeasureRaw.f32Vdc_out)
#define f32_get_LVDCoutV_R_Raw()           (g_stMeasureRaw.f32Vdc_outR)
#define f32_get_LVDCbatV_Raw()             (g_stMeasureRaw.f32Vdc_bat)
#define f32_get_LVDCoutI_Raw()             (g_stMeasureRaw.f32Idc_out)
#define f32_get_Ref1V24V_Raw()             (g_stMeasureRaw.f32Vdc_1v24)

#define f32_get_vdc_outR_avg()             (g_stMeasureAve.f32Vdc_outR)
#define f32_get_vdc_hv_avg()               (g_stMeasureAve.f32Vdc_HvIn)
#define f32_get_Vdc_batAvg()               (g_stMeasureAve.f32Vdc_bat)
#define f32_get_Vdc_outAvg()               (g_stMeasureAve.f32Vdc_out)
#define f32_get_Idc_outAvg()               (g_stMeasureAve.f32Idc_out)
#define f32_get_Vdc_1v24Avg()              (g_stMeasureAve.f32Vdc_1v24)
#define f32_get_MdcdcAhIntglFrzVal()       (g_stMeasureAve.f32MdcdcAhIntgl)
#define f32_get_MdcdcWhIntglFrzVal()       (g_stMeasureAve.f32MdcdcWhIntgl)
#define f32_get_MdcdcAhIntglRealTimeVal()  (g_stMeasureAve.f32TotalAH)
#define f32_get_MdcdcWhIntglRealTimeVal()  (g_stMeasureAve.f32TotalEgr)
#define f32_get_MdcdcAhIntgl_AllVal()      (g_stMeasureAve.f32MdcdcAhIntgl_ALL)
#define f32_get_MdcdcWhIntgl_AllVal()      (g_stMeasureAve.f32MdcdcWhIntgl_ALL)

#define f32_set_MdcdcAhIntglRealTimeVal(x)  (g_stMeasureAve.f32TotalAH  = x)
#define f32_set_MdcdcWhIntglRealTimeVal(x)  (g_stMeasureAve.f32TotalEgr = x)

#define f32_get_Vdc_batAvg_canData()        (g_stMeasureAve.f32Vdc_bat_canData)
#define f32_get_Vdc_outAvg_canData()        (g_stMeasureAve.f32Vdc_out_canData)
#define f32_get_Idc_outAvg_canData()        (g_stMeasureAve.f32Idc_out_canData)
#define f32_get_Vdc_hvInAvg_canData()       (g_stMeasureAve.f32Vdc_HvIn_canData)
#define f32_get_B2B_VoltDiff()              (g_stMeasureAve.f32B2bVoltDiff)
#define f32_get_CtrlCompseVolt()            (g_stMeasureAve.f32CtrlCompse)
#define f32_get_OutVoltDiff()               (g_stMeasureAve.f32OutVoltDiff)

#define f32_get_HvPri_temp()                (g_stMeasureAve.f32HvPriT)
#define f32_get_LvSec_temp()                (g_stMeasureAve.f32LvSecT)
#define f32_get_Case_temp()                 (g_stMeasureAve.f32CaseT)

#endif /* ASW_MEASURE_MEASURE_INF_H_ */
