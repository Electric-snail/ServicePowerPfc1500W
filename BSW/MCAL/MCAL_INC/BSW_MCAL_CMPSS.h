/*
 * BSW_MCAL_CMPSS.h
 *
 *  Created on: 2024.06.06
 *      Author: rjgslg
 */

#ifndef BSW_MCAL_CMPSS_H_
#define BSW_MCAL_CMPSS_H_

#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "../ENV_CFG/HARDWARE_ENV_CFG.h"
#include "../MCAL/BSW_MCAL_BASIC.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_CMPSS_COMM.h"

typedef enum{
    CMPSS1 = 0,
    CMPSS_MODULE_MAX
}CMPSS_MODULE;

typedef struct{
    CMPSS_MODULE emCmpssModule;
    UINT16       CMPxPMXSEL_H;
    UINT16       CMPxPMXSEL_L;
}ASYSCTL_CMPMXSEL;

typedef struct{
    CMPSS_MODULE emCmpssModule;
    UINT16       SwloadCLKSelect;
    UINT16       DACHVALA_SRC;
    UINT16       DACLVALA_SRC;
    UINT16       CmpHiVal;   //12bits
    UINT16       CmpLoVal;  //12bits
}CMPSS_DAC_CFG;

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
}CMPSS_FIL_CFG;

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
}CMPSS_CTL_CFG;

/*---emCmpssModule-----CMPHPMXSEL----CMPLPMXSEL*/
#define  ASYSCTL_CMPMXSEL_TAB  \
{\
    {CMPSS1,             1,             1},\
}  //TRM Table 15-2. Analog Pins and Internal Connections   //A3 A7/C3

/*---emCmpssModule----emSwloadCLKSelec------------emDACHSrc-----------------emDACHSrc------------CmpHiVal------------------CmpLoVal*/
#define CMPSS_DAC_CFG_TAB \
{\
    {CMPSS1,          SWLOADSEL_SYSCLK,      DACHVALA_SRC_DACxVALAS,  DACHVALA_SRC_DACxVALAS,       2048,                     10},\
}

/*---emCmpssModule---CTRIPFILT_ClkPreScal_H--CTRIPFILT_InSel_H--CTRIPFILT_SampWin_H--CTRIPFILT_Thrshld_H--CTRIPFILT_Init_H--CmpFilLVotThrshold*/
#define CMPSS_FIL_CFG_TAB \
{\
    {CMPSS1,         2,                 15,                10,                2,                  15,              10},\
}

/*-emCmpssModule--COMPCTL_CMPINSRC_H--COMPCTL_CMPOUTINV_H--COMPCTL_CTRIPSEL_H---COMPCTL_CTRIPOUTSEL_H--COMPCTL_ASYNCEN_H--COMPCTL_RSV--COMPCTL_CMPINSRC_L--COMPCTL_CMPOUTINV_L--COMPCTL_CTRIPSEL_L---COMPCTL_CTRIPOUTSEL_L--COMPCTL_ASYNCEN_L--COMPCTL_CMPDACEN--emCOMPHYSCTL_HYSTSET*/
#define CMPSS_CTL_CFG_TAB \
{\
    {CMPSS1,  CMPINSRC_IN_DAC,   CMPOUTINV_NOTINV,     CTRIPxSEL_DFILT,     CTRIPxSEL_DFILT,      ASYNC_ORDFILTLATCH_DIS,   0,     CMPINSRC_IN_DAC,   CMPOUTINV_NOTINV,     CTRIPxSEL_DFILT,     CTRIPxSEL_DFILT,      ASYNC_ORDFILTLATCH_DIS,   COMPDAC_EN,    COMPHYS_2xTypeHyst},\
}

extern void bsw_mcal_sf_cmpss_init(void);

#endif /*BSW_MCAL_CMPSS_H_ */
