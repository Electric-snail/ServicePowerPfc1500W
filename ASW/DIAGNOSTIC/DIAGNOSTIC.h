/*
 * DIAGNOSTIC.h
 *
 *  Created on: 2022/11/7
 *      Author: rjgslg
 */

#ifndef DIAGNOSTIC_H_
#define DIAGNOSTIC_H_

#include "DIAGNOSTIC/DIAGNOSTIC_INF.H"

#define SINGLE_P      0

#define TTL_LOW       0
#define TTL_HIGH      1


typedef struct
{
    UINT16 hwLV_VOUT_OVP_fault;
    UINT16 hwLV_VOUT_UVP_fault;
    UINT16 hwLV_IOUT_OCP_fault;
    UINT16 hwHV_IIN_OCP_fault;
    UINT16 hwProtectLock_fault;
    UINT16 LV_Iout_OCP_fault;
    UINT16 LV_Out_ShrtCirP_fault;
    UINT16 LV_Vout_UVP_fault;
    UINT16 LV_Vout_OVP_fault;
    UINT16 SoftStartTimeOut_fault;
}DIAG_PROTECT_FLAG_L0_T;

extern DIAG_PROTECT_FLAG_L0_T g_stDiagFaultFlagL0;    //CBC

typedef struct
{
    UINT16 HvPri_OTP_fault;
    UINT16 LvSec_OTP_fault;
    UINT16 Case_OTP_fault;
    UINT16 LV_Vbat_OVP_fault;

}DIAG_PROTECT_FLAG_L1_T;
extern DIAG_PROTECT_FLAG_L1_T g_stDiagFaultFlagL1;  //NOTREADY

typedef struct
{
    UINT32 LvBat_InvCnn_fault;
    UINT32 LVDC_1V24_fault;
    UINT32 LV_Vbat_Rationality_fault;
    UINT32 LV_Vout_Rationality_fault;
    UINT32 HV_Vin_OVP_fault;
    UINT32 HV_Vin_UVP_fault;
    UINT32 LV_Vbat_UVP_fault;
    UINT32 LV_Vout_UVP_fault;
    UINT32 hwLV_IOUT_OCP_fault;
    UINT32 hwLV_VOUT_UVP_fault;
    UINT32 hwLV_VOUT_OVP_fault;
    UINT32 hwProtectLock_fault;
    UINT32 hwHV_IIN_OCP_fault;
    UINT32 LV_Iout_OCP_fault;
    UINT32 LV_Out_ShrtCirP_fault;
    UINT32 CanSignalBit_fualt;
    UINT32 LV_Vout_OVP_fault;
    UINT32 SoftStartTimeOut_fault;

}DIAG_PROTECT_FLAG_L2_T;

extern DIAG_PROTECT_FLAG_L2_T g_stDiagFaultFlagL2;  //NOTREADY

typedef struct
{
    UINT16 DSP_Integrity_fault;
    UINT16 hwLvOutIsamp_fault;
    UINT16 hwHvInVsamp_fault;
    UINT16 hwLvOutVsamp_fault;
    UINT16 hwLvOutVsamp_R_fault;
    UINT16 hwLvBatVsamp_fault;
    UINT16 hwHvPriTsamp_fault;
    UINT16 hwLvSecTsamp_fault;
    UINT16 hwCaseTsamp_fault;
    UINT16 hwB2B_Mos_fault;
}DIAG_PROTECT_FLAG_L3_T;
extern DIAG_PROTECT_FLAG_L3_T g_stDiagFaultFlagL3;

typedef enum HW_DIAG_ID
{
    HW_LVOUT_OVP = 0,
    HW_LVOUT_UVP,
    HW_LVOUT_OCP,
    HW_HVIN_OCP,
    HW_LOCK_P,
    HW_DIAG_ID_MAX
}HW_DIAG_ID_EM ;


typedef enum SW_DIAG_ID
{
    HVPRI_OTP  = 0,
    LVSEC_OTP,
    CASE_OTP,
    HV_VIN_OVP_F,
    HV_VIN_OVP,
    HV_VIN_UVP_F,
    HV_VIN_UVP,
    LV_IOUT_OCP_F,
    LV_IOUT_OCP,
    LV_POUT_OPP_F,
    LV_POUT_OPP,
    LV_VOUT_OVP_F,
    LV_VOUT_OVP,
    LV_VOUT_UVP_F,
    LV_VOUT_UVP,
    LV_VBAT_OVP,
    LV_VBAT_UVP,
    SW_DIAG_ID_MAX
}SW_DIAG_ID_EM ;

typedef struct
{
    HW_DIAG_ID_EM emHwDiagId;
    UINT16        u16ErrCnt ;
    UINT16        u16RcvrCnt ;
    UINT16        u16errTTL ;
}HWDIAG_PARAM_CFG_T;

typedef struct
{
    SW_DIAG_ID_EM emSwDiagId;
    UINT16        u16ErrCnt ;
    UINT16        u16RcvrCnt ;
    FLOAT32       f32PrtctThreshold ;
    FLOAT32       f32RcvrThreshold ;
}SWDIAG_PARAM_CFG_T;

extern FLOAT32 g_f32HvInOVP_Threshold;
extern FLOAT32 g_f32HvInUVP_Threshold;

#define  ASW_DiagHWFault(Flag, IOState, ERR_TTL, u16Count, ERR_CNT, RCVR_CNT)   \
         if(Flag == 0)                                                           \
         {                                                                       \
            if(IOState == ERR_TTL)                                              \
            {                                                                    \
                u16Count ++;                                                     \
               if(u16Count >= ERR_CNT)                                           \
               {                                                                 \
                  Flag = 1;                                                      \
                  u16Count = 0;                                                  \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u16Count = 0;                                                    \
            }                                                                    \
         }                                                                       \
         else                                                                    \
         {                                                                       \
            if(IOState == (1 - ERR_TTL))                                        \
            {                                                                    \
                u16Count ++;                                                     \
               if(u16Count >= RCVR_CNT)                                          \
               {                                                                 \
                  Flag = 0;                                                      \
                  u16Count = 0;                                                  \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u16Count = 0;                                                       \
            }                                                                    \
         }


#define  ASW_DiagSWFaultOver(Flag, PhysVal, PrtctThreshold, RcvrThreshold, u16Count, ERR_CNT, RCVR_CNT)  \
         if(Flag == 0)                                                           \
         {                                                                       \
            if(PhysVal > PrtctThreshold)                                         \
            {                                                                    \
                u16Count ++;                                                         \
               if(u16Count >= ERR_CNT)                                            \
               {                                                                 \
                  Flag = 1;                                                      \
                  u16Count = 0;                                                     \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u16Count = 0;                                                       \
            }                                                                    \
         }                                                                       \
         else                                                                    \
         {                                                                       \
            if(PhysVal < RcvrThreshold)                                          \
            {                                                                    \
                u16Count ++;                                                         \
               if(u16Count >= RCVR_CNT)                                             \
               {                                                                 \
                  Flag = 0;                                                      \
                  u16Count = 0;                                                     \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u16Count = 0;                                                       \
            }                                                                    \
         }

#define  ASW_DiagSWFaultUnder(Flag, PhysVal, PrtctThreshold, RcvrThreshold, u16Count, ERR_CNT, RCVR_CNT)  \
         if(Flag == 0)                                                           \
         {                                                                       \
            if(PhysVal < PrtctThreshold)                                         \
            {                                                                    \
                u16Count ++;                                                     \
               if(u16Count >= ERR_CNT)                                              \
               {                                                                 \
                  Flag = 1;                                                      \
                  u16Count = 0;                                                  \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u16Count = 0;                                                    \
            }                                                                    \
         }                                                                       \
         else                                                                    \
         {                                                                       \
            if(PhysVal > RcvrThreshold)                                          \
            {                                                                    \
                u16Count ++;                                                     \
               if(u16Count >= RCVR_CNT)                                          \
               {                                                                 \
                  Flag = 0;                                                      \
                  u16Count = 0;                                                  \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u16Count = 0;                                                    \
            }                                                                    \
         }

#define UnRcvrSWFaultOverP(Flag, PhysVal, PrtctThreshold,  u16Count, CNT_THRD)    \
        if (Flag == 0)                                                      \
        {                                                                   \
            if((PhysVal > PrtctThreshold) )                                 \
            {                                                               \
                u16Count ++;                                                \
                if(u16Count >= CNT_THRD)                                    \
                {                                                           \
                    Flag = 1;                                               \
                }                                                           \
            }                                                               \
            else                                                            \
            {                                                               \
                u16Count = 0;                                               \
            }                                                               \
        }

#define UnRcvrSWFaultUnderP(Flag, PhysVal, PrtctThreshold,  u16Count, CNT_THRD)    \
        if (Flag == 0)                                                      \
        {                                                                   \
            if((PhysVal < PrtctThreshold) )                                 \
            {                                                               \
                u16Count ++;                                                \
                if(u16Count >= CNT_THRD)                                    \
                {                                                           \
                    Flag = 1;                                               \
                }                                                           \
            }                                                               \
            else                                                            \
            {                                                               \
                u16Count = 0;                                               \
            }                                                               \
        }



#endif /* DIAGNOSTIC_H_ */
