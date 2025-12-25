/*
 * DIAGNOSTIC.h
 *
 *  Created on: 2022/11/7
 *      Author: rjgslg
 */

#ifndef DIAGNOSTIC_H_
#define DIAGNOSTIC_H_

#define SINGLE_P      0

#define TTL_LOW       0
#define TTL_HIGH      1

typedef struct {
    unsigned short  b1VinRmsOvp : 1;
    unsigned short  b1VinRmsUvp : 1;
    unsigned short  b1VinOfp    : 1;
    unsigned short  b1VinUfp    : 1;
    unsigned short  b1VinDrop  : 1;
    unsigned short  b11Rvs      :  11;
}AUTO_RECV_FAULT_BITS;

typedef struct {
    unsigned short  b1VfpcHwOvp   	: 1;
    unsigned short  b1VpfcFastOvp 	: 1;
    unsigned short  b1VpfcSlowOvp 	: 1;
    unsigned short  b1VpfcFastUvp 	: 1;
    unsigned short  b1VpfcSlowUvp 	: 1;
    unsigned short  b1InOpp       			: 1;
    unsigned short  b1InRmsOcp    		: 1;
    unsigned short  b1IlCbbp      			: 1;
    unsigned short  b6Rvs         			: 8;
}NO_RECV_FAULT_BITS;

typedef union {
    unsigned short 			u16All;
    AUTO_RECV_FAULT_BITS    bits;
}AUTO_RECV_FAULT_WORD_U;

typedef union {
    unsigned short 			u16All;
    NO_RECV_FAULT_BITS      bits;
}NO_RECV_FAULT_WORD_U;



typedef struct {
    AUTO_RECV_FAULT_WORD_U  unAutoRecvFault;
    NO_RECV_FAULT_WORD_U    unNoRecvFault;
}DIAG_STATUS_T;


typedef enum SW_DIAG_ID
{
    VIN_RMS_OVP_ID = 0,
    VIN_RMS_UVP_ID,
    VIN_OFP_ID,
    VIN_UFP_ID,
    VPFC_OVP_HW_ID,
    IL_CBBP_ID,
    VPFC_FAST_OVP_ID,
    VPFC_SLOW_OVP_ID,
    VPFC_FAST_UVP_ID,
    VPFC_SLOW_UVP_ID,
    IN_OPP_ID,
    IN_RMS_OCP_ID,
    SW_DIAG_ID_MAX
}SW_DIAG_ID_EM;

typedef struct
{
    SW_DIAG_ID_EM emSwDiagId;
    UINT16        u16ErrCnt;
    UINT16        u16RcvrCnt;
    FLOAT32       f32PrtctThreshold;
    FLOAT32       f32RcvrThreshold;
}SWDIAG_PARAM_CFG_T;

/*---emSwDiagId-----------------u16ErrCnt-------u16RcvrCnt------f32PrtctThreshold------f32RcvrThreshold*/
#define DIAG_PARAM_TAB          \
{\
    { VIN_RMS_OVP_ID,               5,           10,            270,                    265},\
    { VIN_RMS_UVP_ID,               5,           10,             80,                     85 },\
    { VIN_OFP_ID,                   	   5,           10,             65,                     66 },\
    { VIN_UFP_ID,              	           5,           10,             44,                     45 },\
    { VPFC_OVP_HW_ID,             1,           0,              0.5,                    0 },\
    { IL_CBBP_ID,                			100,          0,              0.5,                    0 },\
    { VPFC_FAST_OVP_ID,          10,          0,              440,                    0 },\
    { VPFC_SLOW_OVP_ID,          20,          0,            435,                    0},\
    { VPFC_FAST_UVP_ID,            5,           0,              280,                     0},\
    { VPFC_SLOW_UVP_ID,          20,          0,             260,                     0},\
    { IN_OPP_ID,                    			5,           0,              1000,                   0 },\
    { IN_RMS_OCP_ID,               		5,           0,              15,                     0 },\
};

#define  ASW_DiagSWFaultOverNoRecv(Flag, PhysVal, PrtctThreshold, u8Count, ERR_CNT)  \
         if(Flag == 0)                                                           		\
         {                                                                       		\
            if(PhysVal > PrtctThreshold)                                         		\
            {                                                                    		\
               u8Count ++;                                                      		\
               if(u8Count >= ERR_CNT)                                            		\
               {                                                                 		\
                  Flag = 1;                                                      		\
                  u8Count = 0;                                                   		\
               }                                                                 		\
            }                                                                    		\
            else                                                                 		\
            {                                                                    		\
                u8Count = 0;                                                    		\
            }                                                                    		\
         }                                                                      

#define  ASW_DiagSWFaultUnderNoRecv(Flag, PhysVal, PrtctThreshold, u8Count, ERR_CNT)  \
         if(Flag == 0)                                                           		\
         {                                                                       		\
            if(PhysVal < PrtctThreshold)                                         		\
            {                                                                    		\
               u8Count ++;                                                      		\
               if(u8Count >= ERR_CNT)                                            		\
               {                                                                 		\
                  Flag = 1;                                                      		\
                  u8Count = 0;                                                   		\
               }                                                                 		\
            }                                                                    		\
            else                                                                 		\
            {                                                                    		\
                u8Count = 0;                                                    		\
            }                                                                    		\
         }  

#define  ASW_DiagSWFaultOverRecv(Flag, PhysVal, PrtctThreshold, RcvrThreshold, u8Count, ERR_CNT, RECV_CNT)  \
         if(Flag == 0)                                                           \
         {                                                                       \
            if(PhysVal > PrtctThreshold)                                         \
            {                                                                    \
                u8Count ++;                                                      \
               if(u8Count >= ERR_CNT)                                            \
               {                                                                 \
                  Flag = 1;                                                      \
                  u8Count = 0;                                                   \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u8Count = 0;                                                    \
            }                                                                    \
         }                                                                       \
         else                                                                    \
         {                                                                       \
            if(PhysVal < RcvrThreshold)                                          \
            {                                                                    \
                u8Count ++;                                                     \
               if(u8Count >= RECV_CNT)                                          \
               {                                                                 \
                  Flag = 0;                                                      \
                  u8Count = 0;                                                  \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u8Count = 0;                                                    \
            }                                                                    \
         }

#define  ASW_DiagSWFaultUnderRecv(Flag, PhysVal, PrtctThreshold, RcvrThreshold, u8Count, ERR_CNT, RECV_CNT)  \
         if(Flag == 0)                                                           \
         {                                                                       \
            if(PhysVal < PrtctThreshold)                                         \
            {                                                                    \
                u8Count ++;                                                      \
               if(u8Count >= ERR_CNT)                                            \
               {                                                                 \
                  Flag = 1;                                                      \
                  u8Count = 0;                                                   \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u8Count = 0;                                                    \
            }                                                                    \
         }                                                                       \
         else                                                                    \
         {                                                                       \
            if(PhysVal > RcvrThreshold)                                          \
            {                                                                    \
                u8Count ++;                                                     \
               if(u8Count >= RECV_CNT)                                          \
               {                                                                 \
                  Flag = 0;                                                      \
                  u8Count = 0;                                                  \
               }                                                                 \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                u8Count = 0;                                                    \
            }                                                                    \
         }

extern  DIAG_STATUS_T 					  	g_stDiagStatus;
extern  DIAG_STATUS_T 				 	  	g_stDiagHisStatus;
#define	u16_get_auto_recv_diag()       g_stDiagStatus.unAutoRecvFault.u16All
#define 	u16_get_no_recv_diag()          g_stDiagStatus.unNoRecvFault.u16All
#define	clr_no_recv_diag_fault()			  g_stDiagStatus.unNoRecvFault.u16All = 0
#define  	u16_clr_fault_flag()                 g_u16FaultDetetFlag = 0
#define 	u16_get_fault_flag()                 g_u16FaultDetetFlag

extern void diagnostic_init(void);
extern void diagnostic_fast_task(void);
extern void diag_1ms_task(void);
extern void diag_10ms_task(void);
extern void diag_100ms_task(void);
#endif /* DIAGNOSTIC_H_ */
