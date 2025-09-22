/*
 * DIAGNOSTIC_INF.H
 *
 *  Created on: 2024.9.20
 *      Author: hongbo.jiang
 */
#ifndef  _DIAGNOSTIC_INF_H
#define  _DIAGNOSTIC_INF_H

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

typedef struct {
    float     f32HvInOVP_Threshold;
    float     f32HvInUVP_Threshold;
    UINT32    u32DataFlag;
}PRTCT_THRD_INF_T;

typedef enum FAULT_LEVEL_ID
{
    NO_FAULT  = 0,
    FAULT_L1,
    FAULT_L2,
    FAULT_L3,
    FAULT_L0,
    FAULT_LEVEL_ID_MAX
}FAULT_LEVEL_ID_EM;

struct DIAG_FAULT_L0_BITS{
    UINT16 hwLV_VOUT_OVP_fault       :1;  //0x001
    UINT16 hwLV_VOUT_UVP_fault       :1;  //0x002
    UINT16 hwLV_IOUT_OCP_fault       :1;  //0x004
    UINT16 hwHV_IIN_OCP_fault        :1;  //0x008
    UINT16 hwProtectLock_fault       :1;  //0x010
    UINT16 LV_Vout_OCP_fault         :1;  //0x020
    UINT16 LV_Out_ShrtCirP_fault     :1;  //0x040
    UINT16 LV_Vout_UVP_Fault         :1;  //0x080
    UINT16 LV_Vout_OVP_Fault         :1;  //0x100
    UINT16 rsv_fault                 :7; //
};

typedef union  {
    UINT16  u16all;
    struct  DIAG_FAULT_L0_BITS  Bits;
}DIAG_FAULT_L0_U;

struct DIAG_FAULT_L1_BITS{
    UINT16 HvPri_OTP_fault           :1;  //0x001
    UINT16 LvSec_OTP_fault           :1;  //0x002
    UINT16 Case_OTP_fault            :1;  //0x004
    UINT16 LV_Vbat_OVP_fault         :1;  //0x008
    UINT16 rsv_fault                 :12; //
};

typedef union  {
    UINT16  u16all;
    struct  DIAG_FAULT_L1_BITS  Bits;
}DIAG_FAULT_L1_U;

struct DIAG_FAULT_L2_BITS{
    UINT32 LvBat_InvCnn_fault             :1;  //0x001
    UINT32 LVDC_1V24_fault                :1;  //0x002
    UINT32 LV_Vbat_Rationality_fault      :1;  //0x004
    UINT32 LV_Vout_Rationality_fault      :1;  //0x008
    UINT32 HV_Vin_OVP_fault               :1;  //0x010
    UINT32 HV_Vin_UVP_fault               :1;  //0x020
    UINT32 LV_Vbat_UVP_fault              :1;  //0x040
    UINT32 LV_Vout_UVP_fault              :1;  //0x080
    UINT32 hwLV_IOUT_OCP_fault            :1;  //0x100
    UINT32 hwLV_VOUT_UVP_fault            :1;  //0x200
    UINT32 hwLV_VOUT_OVP_fault            :1;  //0x400
    UINT32 hwProtectLock_fault            :1;  //0x800
    UINT32 hwHV_IIN_OCP_fault             :1;  //0x1000
    UINT32 LV_Vout_OCP_fault              :1;  //0x2000
    UINT32 LV_Out_ShrtCirP_fault          :1;  //0x4000
    UINT32 CanSignalBit_fualt             :1;  //0x8000
    UINT32 LV_Vout_OVP_fault              :1;  //0x10000
    UINT32 SoftStartTimeOut_fault         :1;  //0x20000
    UINT32 rsv_fault                      :14;  //0x20000
};

typedef union  {
    UINT32  u32all;
    struct  DIAG_FAULT_L2_BITS  Bits;
}DIAG_FAULT_L2_U;

struct DIAG_FAULT_L3_BITS{
    UINT16 DSP_Integrity_fault       :1;  //0x001
    UINT16 hwLvOutIsamp_fault        :1;  //0x002
    UINT16 hwHvInVsamp_fault         :1;  //0x004
    UINT16 hwLvOutVsamp_fault        :1;  //0x008
    UINT16 hwLvOutVsamp_R_fault      :1;  //0x010
    UINT16 hwLvBatVsamp_fault        :1;  //0x020
    UINT16 hwHvPriTsamp_fault        :1;  //0x040
    UINT16 hwLvSecTsamp_fault        :1;  //0x080
    UINT16 hwCaseTsamp_fault         :1;  //0x100
    UINT16 hwB2B_Mos_fault           :1;  //0x200
    UINT16 rsv_fault                 :6; //
};

typedef union  {
    UINT16  u16all;
    struct  DIAG_FAULT_L3_BITS  Bits;
}DIAG_FAULT_L3_U;

struct DIAG_FAULT_ALL_BITS{
    UINT16 diag_fault_L3         :1;  //0x001
    UINT16 diag_fault_L2         :1;  //0x002
    UINT16 diag_fault_L1         :1;  //0x004
    UINT16 diag_fault_L0         :1;  //0x008
    UINT16 rsv_fault             :12; //
};

typedef union  {
    UINT16  u16all;
    struct  DIAG_FAULT_ALL_BITS  Bits;
}DIAG_FAULT_ALL_U;

typedef struct{
    DIAG_FAULT_L0_U      UnFaultBitsStatusL0;
    DIAG_FAULT_L1_U      UnFaultBitsStatusL1;
    DIAG_FAULT_L2_U      UnFaultBitsStatusL2;
    DIAG_FAULT_L3_U      UnFaultBitsStatusL3;
    DIAG_FAULT_ALL_U     UnTotalFaultFlag;
    FAULT_LEVEL_ID_EM    EnFaultLevel;
    unsigned short       u16SnapAppCmd;
}DIAG_FAULT_INFO_T;

typedef enum MDCCDC_HW_SHUTDOWN_STS_TAG
{
    MDCDC_HW_SHUTDOWN_INVALID = 0,
    MDCDC_HW_SHUTDOWN_VALID,
}MDCCDC_HW_SHUTDOWN_STS_T;
extern MDCCDC_HW_SHUTDOWN_STS_T enHW_SHUTDOWN_STS;

extern DIAG_FAULT_INFO_T g_stDiagFaultInfo;

extern UINT16  g_u16PrtctThrdUpdateFlg;

extern UINT16  g_u16BuckSelfSts;

#define get_buckSelfSts()               g_u16BuckSelfSts

#define get_diagFault_L0()              g_stDiagFaultInfo.UnFaultBitsStatusL0.u16all //g_u16FaultBitsStatusL0
#define clr_diagFault_L0()              g_stDiagFaultInfo.UnFaultBitsStatusL0.u16all = 0 //g_u16FaultBitsStatusL0 = 0

#define get_diagFault_L1()              g_stDiagFaultInfo.UnFaultBitsStatusL1.u16all
#define clr_diagFault_L1()              g_stDiagFaultInfo.UnFaultBitsStatusL1.u16all = 0

#define get_diagFault_L2()              g_stDiagFaultInfo.UnFaultBitsStatusL2.u32all
#define clr_diagFault_L2()              g_stDiagFaultInfo.UnFaultBitsStatusL2.u32all = 0

#define get_diagFault_L3()              g_stDiagFaultInfo.UnFaultBitsStatusL3.u16all
#define clr_diagFault_L3()              g_stDiagFaultInfo.UnFaultBitsStatusL3.u16all = 0

#define get_fault_Level()               g_stDiagFaultInfo.EnFaultLevel

#if DEBUG_MODE == 1
#define u16_get_total_diag_fault()      0
#else
#define u16_get_total_diag_fault()      g_stDiagFaultInfo.UnTotalFaultFlag.u16all
#endif
#define clr_total_diag_fault()          g_stDiagFaultInfo.u32TotalFaultFlag = 0

#define en_get_shutdown_sts()           enHW_SHUTDOWN_STS

#define get_f32HvInOVP_Threshold()      g_stPrtctThrdInfoData[0].f32HvInOVP_Threshold
#define get_f32HvInUVP_Threshold()      g_stPrtctThrdInfoData[0].f32HvInUVP_Threshold
#define get_app_snap_data_cmd()         g_stDiagFaultInfo.u16SnapAppCmd
#define clr_app_snap_data_cmd()         g_stDiagFaultInfo.u16SnapAppCmd = 0
#define set_app_snap_data_cmd()         g_stDiagFaultInfo.u16SnapAppCmd = 0xbb


extern void diag_ctrl_isr_task(void);
extern void diag_1ms_task(void);
extern void diag_10ms_task(void);
extern void diag_100ms_task(void);
extern void diag_cfg_param_init(void);
extern void b2b_mos_off_power_on_check(void);
#endif
