/*********************************************************************
File name:       BSW_MCAL_PWM.h

 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/

#ifndef BSW_MCAL_PWM_H
#define BSW_MCAL_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <PUBLIC_INC/AUTO_REGISTER.H>
#include "../MCAL/BSW_MCAL_BASIC.h"
#include "../CHIP_PACK/common/include/F28x_Project.h"



#define COUNTER_UP                  0
#define COUNTER_DOWN                0
#define COUNTER_UP_DOWN             1
//
// Defines
//

//
// TBCTL (Time-Base Control)
static inline void BSW_MACL_SetTBCLKSYNC(UINT16 flag)
{
    EALLOW;                                 
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = flag;   
    EDIS;                                   
}

#define BSW_MCAL_DisTBCLKSYNC()             \
do                                          \
{                                           \
    EALLOW;                                 \
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;   \
    EDIS;                                   \
}while(0)



#define BSW_MCAL_EnTBCLKSYNC()              \
do                                          \
{                                           \
    EALLOW;                                 \
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;   \
    EDIS;                                   \
}while(0)


/******if the pwm configure mode change, the u32CompCnt calculation shall be changed.  ***/
enum PWM_CHANNEL
{
    ePWM1_CHANNEL = 0,
    ePWM2_CHANNEL,
    ePWM3_CHANNEL,
    ePWM4_CHANNEL,
    ePWM5_CHANNEL,
    ePWM6_CHANNEL,
    ePWM7_CHANNEL,
    ePWM8_CHANNEL,
    ePWM_MAX_CHANNEL,
};

//#define  CPU_CLOCK_FRQ          120000000.0f
#define  PWM_CLOCK_DIV          1.0f
#define  PWM_COUNTER_MODE       COUNTER_UP

#define  LLC_PWM_FRQ           300000.0f
#define  LLC_PWM_TBPRD         166//((unsigned int)((CPU_CLOCK_FRQ/PWM_CLOCK_DIV)/PSFP_PWM_FRQ)>>PWM_COUNTER_MODE)



/*SYNCOSEL*/
#define  TB_SYNC_SOFTWARE  0
#define  TB_SYNC_SYCIN     0
#define  TB_SYNC_CTR_ZERO  1
#define  TB_SYNC_CTR_CMPB  2
#define  TB_SYNC_EXTENDED  3
#define  TB_SYNC_DISABLE2  4
#define  TB_SYNC_CTR_CMPC  TB_SYNC_EXTENDED | (1<<2)
#define  TB_SYNC_CTR_CMPD  TB_SYNC_EXTENDED | (2<<2)
#define  TB_SYNC_RESERVED  TB_SYNC_RESERVED | (3<<2)

/*AQCSFRC*/
/*CSFA/CSFB*/
#define AQ_CSFX_DISABLED     0x0
#define AQ_RLDCSF_LOW        0x1
#define AQ_RLDCSF_HIGH       0x2
#define AQ_RLDCSF_DISABLED   0x3

/* IN MODE bits*/
#define DBA_ALL          0x0
#define DBB_RED_DBA_FED  0x1
#define DBA_RED_DBB_FED  0x2
#define DBB_ALL          0x3

/* SHDWDBCTLMODE bits*/
#define DB_SHADOW     0x1
#define DB_IMMEDIATE  0x0

/* LOADDBCTLMODE bits*/
#define DB_CTR_ZERO      0x0
#define DB_CTR_PRD       0x1
#define DB_CTR_ZERO_PRD  0x2
#define DB_LD_DISABLE    0x3

/*OUTSWAP bits */
#define DB_AABB    0X0
#define DB_AABA    0X1
#define DB_ABBB    0X2
#define DB_ABBA    0X3

/*DCAHTRIPSEL bits */
#define TRIPINPUT_NULL   0X0000
#define TRIPINPUT1       0X0001
#define TRIPINPUT2       0X0002
#define TRIPINPUT3       0X0004
#define TRIPINPUT4       0X0008
#define TRIPINPUT5       0X0010
#define TRIPINPUT6       0X0020
#define TRIPINPUT7       0X0040
#define TRIPINPUT8       0X0080
#define TRIPINPUT9       0X0100
#define TRIPINPUT10      0X0400
#define TRIPINPUT12      0X0800
#define TRIPINPUT14      0X2000
#define TRIPINPUT15      0X4000

/*SYNCOUT bits */
#define EPWM1SYNCOUT    0X0
#define EPWM2SYNCOUT    0X1
#define EPWM3SYNCOUT    0X2
#define EPWM4SYNCOUT    0X3
#define EPWM5SYNCOUT    0X4
#define EPWM6SYNCOUT    0X5
#define EPWM7SYNCOUT    0X6
#define EPWM8SYNCOUT    0X7
#define ECAP1SYNCOUT    0X18
#define ECAP2SYNCOUT    0X19
#define ECAP3SYNCOUT    0X1A

/*EPWMSYNCINSEL  SEL bits */
#define SYNCIN_DISABLE          0X0
#define SYNCIN_EPWM1SYNCOUT     0X1
#define SYNCIN_EPWM2SYNCOUT     0X2
#define SYNCIN_EPWM3SYNCOUT     0X3
#define SYNCIN_EPWM4SYNCOUT     0X4
#define SYNCIN_EPWM5SYNCOUT     0X5
#define SYNCIN_EPWM6SYNCOUT     0X6
#define SYNCIN_EPWM7SYNCOUT     0X7
#define SYNCIN_EPWM8SYNCOUT     0X8
#define SYNCIN_ECAP1SYNCOUT     0X11
#define SYNCIN_ECAP2SYNCOUT     0X12
#define SYNCIN_ECAP3SYNCOUT     0X13
#define SYNCIN_INPUT15XBAR      0X18
#define SYNCIN_INPUT16XBAR      0X19

/*EPWMSYNCOUTEN   bits */
#define SYNCOUTEN_DISABLE       0X0
#define SYNCOUTEN_SW            0X1
#define SYNCOUTEN_ZERO          0X2
#define SYNCOUTEN_CMPB          0X4
#define SYNCOUTEN_CMPC          0X8
#define SYNCOUTEN_CMPD          0X10
#define SYNCOUTEN_DCAEVT1       0X20
#define SYNCOUTEN_DCBEVT1       0X40

extern volatile struct EPWM_REGS *p_stPwmChannel[];

#define HR_COM_DISABLE   0
#define HR_COM_ENABLE    1


#define LLC_PRI_PWM_CHANNEL       ePWM3_CHANNEL


struct SYNC_CFG_OUT_IN_SRC{
    Uint16           SYNC_OUT_VAL         :5;
    Uint16           reserve              :11;
};

struct EPWMx_CFG_TB{
    enum PWM_CHANNEL emPwmChannel;
    Uint16           TB_SYNCOSEL_VAL  :4;                 // 9:7 High Speed TBCLK Pre-scaler
    Uint16           TB_PHSDIR_VAL    :2;                 // 12:10 Time Base Clock Pre-scaler
    Uint16           TB_CTRMODE_VAL   :2;                 // 1:0 Counter Mode
    Uint16           TB_PHSEN_VAL     :1;                 // 2 Phase Load Enable
    Uint16           TB_PRDLD_VAL     :1;                 // 3 Active Period Load
    Uint16           SYNCINSEL_VAL    :5;
    Uint16           reserve          :1;
    Uint16           SYNCOUTEN_VAL;
    Uint16           u16PrdLdVal;
    Uint16           u16PhaseVal;
};

struct EPWMx_CFG_CC{
    enum PWM_CHANNEL emPwmChannel;
    Uint16           CC_SHDWAMODE_VAL   :1;
    Uint16           CC_SHDWBMODE_VAL   :1;
    Uint16           CC_LOADAMODE_VAL   :2;
    Uint16           CC_LOADBMODE_VAL   :2;
    Uint16           reserve            :10;
    Uint16           u16CmpaVal;
    Uint16           u16CmpbVal;
};

struct EPWMx_CFG_AQ{
    enum PWM_CHANNEL emPwmChannel;
    Uint32           AQ_CTLA_CAD_VAL   :2;
    Uint32           AQ_CTLA_CAU_VAL   :2;
    Uint32           AQ_CTLA_CBD_VAL   :2;
    Uint32           AQ_CTLA_CBU_VAL   :2;
    Uint32           AQ_CTLA_PRD_VAL   :2;
    Uint32           AQ_CTLA_ZRO_VAL   :2;
    Uint32           AQ_CTLB_CAD_VAL   :2;
    Uint32           AQ_CTLB_CAU_VAL   :2;
    Uint32           AQ_CTLB_CBD_VAL   :2;
    Uint32           AQ_CTLB_CBU_VAL   :2;
    Uint32           AQ_CTLB_PRD_VAL   :2;
    Uint32           AQ_CTLB_ZRO_VAL   :2;
    Uint32           reserve           :8;
};

struct EPWMx_CFG_DB{
    enum PWM_CHANNEL emPwmChannel;
    Uint16           DB_OUT_MODE_VAL        :2;
    Uint16           DB_IN_MODE_VAL         :2;
    Uint16           DB_OUTSWAP_VAL         :2;
    Uint16           DB_POLSEL_VAL          :2;
    Uint16           DB_SHDWDBCTLMODE_VAL   :1;
    Uint16           DB_LOADDBCTLMODE_VAL   :2;
    Uint16           reserve                :5;
    Uint16           u16REDval;
    Uint16           u16CFEDval;
};

struct EPWMx_CFG_TZ{
    enum PWM_CHANNEL emPwmChannel;
    Uint16           TZ_SEL_OSHT1_VAL       :1;
    Uint16           TZ_SET_DCAEVT1_VAL     :1;
    Uint16           TZ_SET_DCAEVT2_VAL     :1;
    Uint16           TZ_DCSEL_DCAEVT1_VAL   :3;
    Uint16           TZ_DCSEL_DCAEVT2_VAL   :3;
    Uint16           TZ_CTL_TZA_VAL         :2;
    Uint16           TZ_CTL_TZB_VAL         :2;
    Uint16           reserve                :3;
};

struct EPWMx_CFG_ET{
    enum PWM_CHANNEL emPwmChannel;
    Uint16           ET_SOCASEL_VAL         :3;
    Uint16           ET_INTSEL_VAL          :3;
    Uint16           ET_SOCAPRD_VAL         :4;
    Uint16           ET_INTPRD_VAL          :2;
    Uint16           ET_SOCAEN_VAL          :1;
    Uint16           ET_INTEN_VAL           :1;
    Uint16           reserve                :4;
};

struct EPWMx_CFG_DC{
    enum PWM_CHANNEL emPwmChannel;
    Uint16           u16DC_DCAHTRIPSEL_VAL;
};


struct EPWMx_CFG_HR{
    enum PWM_CHANNEL emPwmChannel;
    Uint16           HR_EDGMODE_VAL         :2;
    Uint16           HR_CTLMODE_VAL         :1;
    Uint16           HR_HRLOAD_VAL          :2;
    Uint16           HR_EDGMODEB_VAL        :2;
    Uint16           HR_CTLMODEB_VAL        :1;
    Uint16           HR_HRLOADB_VAL         :2;
    Uint16           HR_AUTOCONV_VAL        :1;
    Uint16           HR_TBPHSHRLOADE_VAL    :1;
    Uint16           HR_HRPE_VAL            :1;
    Uint16           reserve                :3;
};

/*-------------------------SYNCOUT------------reserve*/
#define EPWM_CFG_SYNCSELECT_TAB {EPWM1SYNCOUT,    0}

/*--PWM_CHANNEL-----------SYNCOSEL-------PHSDIR---CTRMODE---------PHSEN--------PRDLD----SYNCINSEL_VAL-----reserve--SYNCOUTEN_VAL----u16PrdLdVal--u16PhaseVal*/
#define EPWM_CFG_TB_TAB  \
{\
    {LLC_PRI_PWM_CHANNEL, TB_SYNC_SYCIN, TB_UP, TB_COUNT_UPDOWN, TB_DISABLE, TB_SHADOW, SYNCIN_DISABLE,      0,   SYNCOUTEN_DISABLE,  LLC_PWM_TBPRD,      0},\
}
/*-----PWM_CHANNEL----------SHDWAMODE---SHDWBMODE--LOADAMODE---LOADBMODE---reserve---u16CmpaVal---u16CmpbVal*/
#define EPWM_CFG_CC_TAB  \
{\
    {LLC_PRI_PWM_CHANNEL, CC_SHADOW, CC_SHADOW, CC_CTR_ZERO, CC_CTR_ZERO,   0,  40,   126},\
}

/*--PWM_CHANNEL---------------CTLA_CAD----CTLA_CAU----CTLA_CBD------CTLA_CBU-----CTLA_PRD-----CTLA_ZRO--------CTLB_CAD-----CTLB_CAU-----CTLB_CBD----CTLB_CBU--CTLB_PRD---CTLB_ZRO----reserve*/
#define EPWM_CFG_AQ_TAB  \
{\
    {LLC_PRI_PWM_CHANNEL, AQ_NO_ACTION,  AQ_CLEAR, AQ_NO_ACTION, AQ_NO_ACTION, AQ_NO_ACTION, AQ_SET,       AQ_NO_ACTION, AQ_NO_ACTION, AQ_CLEAR, AQ_NO_ACTION, AQ_SET, AQ_NO_ACTION, 0},\
}

/*--------PWM_CHANNEL--------OUT_MODE-------IN_MODE---OUTSWAP---POLSEL---SHDWDBCTLMODE---LOADDBCTLMODE---reserve---u16REDval---u16CFEDval*/
#define EPWM_CFG_DB_TAB  \
{\
    {LLC_PRI_PWM_CHANNEL,  DB_FULL_ENABLE,  DBA_ALL, DB_AABB, DB_ACTV_HIC, DB_IMMEDIATE, DB_CTR_PRD,   0, 20, 20},\
}

/*-----PWM_CHANNEL----------SEL_OSHT1---SET_DCAEVT1---SET_DCAEVT2-----DCSEL_DCAEVT1---DCSEL_DCAEVT2---TZA----------TZB--------reserve------*/
#define EPWM_CFG_TZ_TAB  \
{\
    {LLC_PRI_PWM_CHANNEL, TZ_DISABLE, TZ_DISABLE,  TZ_DISABLE,     TZ_DCAH_HI,     TZ_DCAH_HI,  TZ_FORCE_LO, TZ_FORCE_LO,  0},\
}

/*--PWM_CHANNEL-------------ET_SOCASEL---ET_INTSEL--ET_SOCAPRD---ET_INTPRD_---ET_SOCAEN---ET_INTEN---reserve*/
#define EPWM_CFG_ET_TAB  \
{\
    {LLC_PRI_PWM_CHANNEL, ET_CTR_ZERO, ET_CTR_PRD,  ET_2ND,   ET_1ST,         0,          1,         0},\
}

/*--PWM_CHANNEL----------u16DC_DCAHTRIPSEL_VAL---*/
#define EPWM_CFG_DC_TAB  \
{\
    {LLC_PRI_PWM_CHANNEL, TRIPINPUT_NULL|TRIPINPUT4},\
}

/*-------PWM_CHANNEL-----EDGMODE--CTLMODE---HRLOAD---EDGMODEB---CTLMODEB---HRLOADB---AUTOCONV--------TBPHSHRLOADE------HRPE---reserve */
#define EPWM_CFG_HR_TAB  \
{\
    {LLC_PRI_PWM_CHANNEL, HR_FEP, HR_CMP, HR_CTR_ZERO, HR_FEP,  HR_CMP,   HR_CTR_PRD, HR_COM_ENABLE, HR_COM_DISABLE,HR_COM_DISABLE, 0},\
}



#define LLC_PRI_PWM_TZ_FRC_P()   do{EALLOW; p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->TZFRC.bit.OST = 1;EDIS;}while(0)

#define LLC_PRI_PWM_FLAG_CLEAR() do{EALLOW; p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->TZCLR.bit.OST = 1;\
                                      p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->TZOSTCLR.bit.OST1 = 1;EDIS;}while(0)

#if 1
#if 0

#define LLC_PRI_EPWM_OFF()       do{p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->AQCSFRC.bit.CSFA = AQ_RLDCSF_LOW; \
                                    p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->AQCSFRC.bit.CSFB = AQ_RLDCSF_LOW;  \
                                    p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->DBCTL.bit.OUT_MODE = DB_DISABLE;}while(0)

#define LLC_PRI_EPWM_ON()        do{p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->AQCSFRC.bit.CSFA = AQ_CSFX_DISABLED; \
                                    p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->AQCSFRC.bit.CSFB = AQ_CSFX_DISABLED;  \
                                    p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;}while(0)

#else

#define LLC_PRI_EPWM_OFF()   do{EALLOW; p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->TZFRC.bit.OST = 1;EDIS;}while(0)

#define LLC_PRI_EPWM_ON() do{EALLOW; p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->TZCLR.bit.OST = 1;\
                                      p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->TZOSTCLR.bit.OST1 = 1;EDIS;}while(0)
#endif
#else

#define  LLC_PRI_EPWM_OFF()  p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->AQCSFRC.all = 0x05
#define LLC_PRI_EPWM_ON()    p_stPwmChannel[LLC_PRI_PWM_CHANNEL]->AQCSFRC.all = 0x00
#endif


static inline void EPWM_CLOSE(void)
{
    LLC_PRI_PWM_FLAG_CLEAR();
  //  LLC_PRI_EPWM_OFF();
}



extern void bsw_mcal_sf_ePWM_init(void);

#ifdef __cpluslus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================
