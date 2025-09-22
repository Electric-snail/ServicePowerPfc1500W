/*
 * BSW_MCAL_CMPSSLITE.h
 *
 *  Created on: 2024.06.06
 *      Author: rjgslg
 */

#ifndef BSW_MCAL_CMPSSLITE_H_
#define BSW_MCAL_CMPSSLITE_H_

#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "../ENV_CFG/HARDWARE_ENV_CFG.h"
#include "../MCAL/BSW_MCAL_BASIC.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_CMPSS_COMM.h"

#if 0



#define CMP3_GPIO226_HPMXSEL_0    0
#define CMP3_GPIO226_LPMXSEL_0    0

/*COMPDACHCTL-  SWLOADSEL*/
#define SWLOADSEL_SYSCLK           0
#define SWLOADSEL_EPWMSYNCPER      1

/*COMPCTL-  COMPHSOURCE/COMPLSOURCE*/
#define CMPINSRC_IN_DAC            0
#define CMPINSRC_EXT_PIN           1

/*COMPCTL-  COMPHINV/COMPLINV*/
#define CMPOUTINV_NOTINV           0
#define CMPOUTINV_INV              1

/*COMPCTL-  CTRIPHSEL/CTRIPLSEL/CTRIPOUTHSEL/CTRIPOUTLSEL*/
#define CTRIPxSEL_ASYNC            0
#define CTRIPxSEL_SYNC             1
#define CTRIPxSEL_DFILT            2
#define CTRIPxSEL_DFILTLATCH       3

/*COMPCTL-  ASYNCHEN/ASYNCLEN*/
#define ASYNC_ORDFILTLATCH_EN      1
#define ASYNC_ORDFILTLATCH_DIS     0

/*COMPCTL-  COMPDACE*/
#define COMPDAC_EN                 1
#define COMPDAC_DIS                0

/*COMPHYSCTL - COMPHYS*/
typedef enum{
    COMPHYS_None = 0,
    COMPHYS_1xTypeHyst,
    COMPHYS_2xTypeHyst,
    COMPHYS_3xTypeHyst,
    COMPHYS_4xTypeHyst,
}COMPHYS_TYPEHYST;
#endif

typedef enum{
    CMPSSLITE_RSV = 0,
    CMPSSLITE2,
    CMPSSLITE3,
    CMPSSLITE4,
    CMPSSLITE_MODULE_MAX
}CMPSS_MODULE;

#define CMPSS_OUT_VR              CMPSSLITE3

typedef struct{
    CMPSS_MODULE emCmpssModule;
    UINT16       CMPxPMXSEL_H;
    UINT16       CMPxPMXSEL_L;
}ASYSCTL_CMPMXSEL;

typedef struct{
    CMPSS_MODULE emCmpssModule;
    UINT16       SwloadCLKSelect;
    UINT16       CmpHiVal;   //12bits
    UINT16       CmpLoVal;  //12bits
}CMPSSLITE_DAC_CFG;

typedef struct{
    CMPSS_MODULE emCmpssModule       ;
    UINT16 CTRIPFILT_ClkPreScal_H    ;
    UINT16 CTRIPFILT_InSel_H      : 3;
    UINT16 CTRIPFILT_SampWin_H    : 6;
    UINT16 CTRIPFILT_Thrshld_H    : 6;
    UINT16 CTRIPFILT_Init_H       : 1;
    UINT16 CTRIPFILT_ClkPreScal_L    ;
    UINT16 CTRIPFILT_InSel_L      : 3;
    UINT16 CTRIPFILT_SampWin_L    : 6;
    UINT16 CTRIPFILT_Thrshld_L    : 6;
    UINT16 CTRIPFILT_Init_L       : 1;
}CMPSSLITE_CTRIPFILT_CFG;

typedef struct{
    CMPSS_MODULE emCmpssModule;
    UINT16 COMPCTL_CMPINSRC_H     :1 ;
    UINT16 COMPCTL_CMPOUTINV_H    :1 ;
    UINT16 COMPCTL_CTRIPSEL_H     :2 ;
    UINT16 COMPCTL_CTRIPOUTSEL_H  :2 ;
    UINT16 COMPCTL_ASYNCEN_H      :1 ;
    UINT16 COMPCTL_RSV            :1 ;
    UINT16 COMPCTL_CMPINSRC_L     :1 ;
    UINT16 COMPCTL_CMPOUTINV_L    :1 ;
    UINT16 COMPCTL_CTRIPSEL_L     :2 ;
    UINT16 COMPCTL_CTRIPOUTSEL_L  :2 ;
    UINT16 COMPCTL_ASYNCEN_L      :1 ;
    UINT16 COMPCTL_CMPDACEN       :1 ;
    COMPHYS_TYPEHYST emCOMPHYSCTL_HYSTSET;
}CMPSSLITE_CTL_CFG;

/*---emCmpssModule-----CMPHPMXSEL----CMPLPMXSEL*/
#define  ASYSCTL_CMPMXSEL_TAB  \
{\
    {CMPSS_OUT_VR,        0,            0},\
}  //TRM Table 15-2. Analog Pins and Internal Connections   //A3 A7/C3

/*---emCmpssModule----SwloadCLKSelect-----------CmpHiVal------------------CmpLoVal*/
#define CMPSSLITE_DAC_CFG_TAB \
{\
    {CMPSS_OUT_VR,      SWLOADSEL_SYSCLK,         2048,                      10},\
}

/*---emCmpssModule---CTRIPFILT_ClkPreScal_H--CTRIPFILT_InSel_H--CTRIPFILT_SampWin_H--CTRIPFILT_Thrshld_H--CTRIPFILT_Init_H--CmpFilLVotThrshold*/
#define CMPSSLITE_FIL_CFG_TAB \
{\
    {CMPSS_OUT_VR,         2,                 15,                10,                2,                  15,              10},\
}

/*-emCmpssModule--COMPCTL_CMPINSRC_H--COMPCTL_CMPOUTINV_H--COMPCTL_CTRIPSEL_H---COMPCTL_CTRIPOUTSEL_H--COMPCTL_ASYNCEN_H--COMPCTL_RSV--COMPCTL_CMPINSRC_L--COMPCTL_CMPOUTINV_L--COMPCTL_CTRIPSEL_L---COMPCTL_CTRIPOUTSEL_L--COMPCTL_ASYNCEN_L--COMPCTL_CMPDACEN--emCOMPHYSCTL_HYSTSET*/
#define CMPSSLITE_CTL_CFG_TAB \
{\
    {CMPSS_OUT_VR,  CMPINSRC_IN_DAC,   CMPOUTINV_NOTINV,     CTRIPxSEL_DFILT,     CTRIPxSEL_DFILT,      ASYNC_ORDFILTLATCH_DIS,   0,     CMPINSRC_IN_DAC,   CMPOUTINV_INV,     CTRIPxSEL_DFILT,     CTRIPxSEL_DFILT,      ASYNC_ORDFILTLATCH_DIS,   COMPDAC_EN,    COMPHYS_2xTypeHyst},\
}

extern void BSW_MCAL_CmpssLiteInit(void);

#endif /*BSW_MCAL_CMPSSLITE_H_ */
