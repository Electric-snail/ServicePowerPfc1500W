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

#include "SOFTWARE_ENV_CFG.H"
#include "HARDWARE_ENV_CFG.H"
#include "common/include/F28x_Project.h"


#define 		DCLOCK_BIT     					4
#define 		TZCLRLOCK_BIT				3
#define 		TZCFGLOCK_BIT               2
#define 		GLLOCK_BIT               		1
#define       HRLOCK_BIT						0
// TBCTL (Time-Base Control)
static inline void BSW_MACL_SetTBCLKSYNC(UINT16 flag)
{
    EALLOW;                                 
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = flag;   
    EDIS;                                   
}

#define 	bsw_mcal_disable_tbclk_sync()             \
do                                          \
{                                           \
    EALLOW;                                 \
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;   \
    EDIS;                                   \
}while(0)



#define bsw_mcal_enable_tbclk_sync()              \
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


/*SYNCOSEL*/
#define  		TB_SYNC_SOFTWARE  					0

#define  		TB_SYNC_SYCIN     							0
#define  		TB_SYNC_CTR_ZERO  						1
#define  		TB_SYNC_CTR_CMPB  					2
#define  		TB_SYNC_EXTENDED  					3
#define  		TB_SYNC_DISABLE2  						4
#define  		TB_SYNC_CTR_CMPC  					TB_SYNC_EXTENDED | (1<<2)
#define  		TB_SYNC_CTR_CMPD  					TB_SYNC_EXTENDED | (2<<2)
#define  		TB_SYNC_RESERVED  						TB_SYNC_RESERVED | (3<<2)

/*AQCSFRC*/
/*CSFA/CSFB*/
#define AQ_CSFX_DISABLED     0x0
#define AQ_RLDCSF_LOW        0x1
#define AQ_RLDCSF_HIGH       0x2
#define AQ_RLDCSF_DISABLED   0x3



/* SHDWDBCTLMODE bits*/
#define DB_CTR_RED_FED_SHADOW     			    0x1
#define DB_CTR_RED_FED_IMMEDIATE  				0x0

/* LOADDBCTLMODE bits*/
#define DB_LD_CNT_ZERO      									0x0
#define DB_LD_CNT_PRD       									0x1
#define DB_LD_CNT_ZERO_PRD  							0x2
#define DB_LD_DISABLE    										0x3

/*OUTSWAP bits */
#define 		DB_AABB    			0X0
#define 		DB_AABA    			0X1
#define 		DB_ABBB    			0X2
#define 		DB_ABBA    			0X3

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

/*EPWMSYNCOUTEN   bits */
#define 		SYNCOUTEN_DISABLE       				0x00
#define	 	SYNCOUTEN_SW            					0x01
#define 		SYNCOUTEN_ZERO          				0x02
#define 		SYNCOUTEN_CMPB          				0x04
#define 		SYNCOUTEN_CMPC          				0x08
#define 		SYNCOUTEN_CMPD          				0x10
#define 		SYNCOUTEN_DCAEVT1       			0x20
#define 		SYNCOUTEN_DCBEVT1       			0x40

extern volatile struct EPWM_REGS *p_stPwmChannel[];

#define HR_COM_DISABLE   0
#define HR_COM_ENABLE    1

enum EPWM_SYNC_IN_SRC{
	   EPWM_SYNC_IN_NONE			 	= 0x00,
	   EPWM1_SYNCOUT      					=  0x01,
	   EPWM2_SYNCOUT      					=  0x02,
	   EPWM3_SYNCOUT      					=  0x03,
	   EPWM4_SYNCOUT      					=  0x04,
	   EPWM5_SYNCOUT      					=  0x05,
	   EPWM6_SYNCOUT      					=  0x06,
	   EPWM7_SYNCOUT      					=  0x07,
	   EPWM8_SYNCOUT      					=  0x08,
	   ECAP1_SYNCOUT     						=  0x11,
	   ECAP2_SYNCOUT     						=  0x12,
	   ECAP3_SYNCOUT     						=  0x13,
      INPUT15XBAR_SYNC      				=  0x18,
	  INPUT16XBAR_SYNC      				=  0x19,
};


enum TB_COUNTER_MODE{
      TB_COUNTER_UP     				=    0,
      TB_COUNTER_DOWN        		=    1,
     TB_COUNTER_UP_DOWN      =    2,
};

enum PHS_DIR_EN{
      PHS_DISABLE     				=    0,
	  PHS_DIR_UP        				=    1,
	  PHS_DIR_DOWN     			 =    2,
};

enum PRD_LOAD_MODE{
	 PRD_LOAD_CTR_ZERO  = 0x0,
	 PRD_LOAD_CTR_ZERO_AND_SYNC,
	 PRD_LOAD_SYNC,
	 PRD_LOAD_RVS,
};

//can multiple combinations
enum EPWM_SYNC_OUT{
	EPWM_SYNC_OUT_NONE			=		0x0000,
   EPWM_SYCN_SW                  			=		(1L  << 0),
   EPWM_SYCN_ZERO                  		=		(1L  << 1),
   EPWM_SYCN_CMPB                  		=	    (1L  << 2),
   EPWM_SYCN_CMPC                 		=     (1L  << 3),
   EPWM_SYCN_CMPD                  		=	   (1L  << 4),
   EPWM_SYCN_OUT_DCAEVT1     =      (1L  << 5),
   EPWM_SYCN_OUT_DCBEVT1    =       (1L  << 6),
};

enum CC_LOAD_MODE{
	CC_LOAD_CTR_ZERO,
	CC_LOAD_CTR_PERIOD,
	CC_LOAD_CTR_ZERO_OR_PERIOD,
	CC_LOAD_SYNC,
	CC_LOAD_SYNC_AND_CTR_ZERO,
	CC_LOAD_SYNC_AND_CTR_PERIOD,
	CC_LOAD_SYNC_AND_CTR_ZERO_OR_PERIOD,
};

enum ET_SOC_SEL{
	ET_SOC_DCxEVT1_SOC = 0,
	ET_SOC_CTR_ZERO,
	ET_SOC_CTR_PERIOD,
	ET_SOC_CTR_ZERO_PERIOD,
	ET_SOC_CTRU_COMPA,
	ET_SOC_CTRU_COMPC,
	ET_SOC_CTRU_COMPB,
	ET_SOC_CTRU_COMPD,
	ET_SOC_CTRD_COMPA,
	ET_SOC_CTRD_COMPC,
	ET_SOC_CTRD_COMPB,
	ET_SOC_CTRD_COMPD,
	ET_SOC_DISABLE,
};

enum ET_INT_SEL{
	ET_INT_DISABLE 						= 0,
	ET_INT_CTR_ZERO,
	ET_INT_CTR_PERIOD,
	ET_INT_CTR_ZERO_PERIOD,
	ET_INT_CTRU_COMPA,
	ET_INT_CTRU_COMPC,
	ET_INT_CTRU_COMPB,
	ET_INT_CTRU_COMPD,
	ET_INT_CTRD_COMPA,
	ET_INT_CTRD_COMPC,
	ET_INT_CTRD_COMPB,
	ET_INT_CTRD_COMPD,
};

enum ET_PRESCALE{
	ET_ACTION_DISABLE = 0,
	ET_FIRST_ACTION ,
	ET_SECOND_ACTION,
	ET_THIRD_ACTION,
};

enum PWM_TZ_ACTION{
     FORCE_HIZ = 0x00,
	 FORCE_HI  =  0x01,
	 FORCE_LO =  0x02,
	 FORCE_TOGGLE = 0x03,
	 DO_NOTHING = 0x07,
};

enum PWM_CBC_CLR{
	CBC_CLR_ZERO  = 0,
	CBC_CLR_PERIOD,
	CBC_CLR_ZERO_PERIOD,
	CBC_CLR_NONE,
};
#define   	TZ_CBC_SEL_NONE      0
#define       TZ_CBC_TZ1                  (1 << 0)
#define       TZ_CBC_TZ2                  (1 << 1)
#define       TZ_CBC_TZ3                  (1 << 2)
#define       TZ_CBC_TZ4                  (1 << 3)
#define       TZ_CBC_TZ5                  (1 << 4)
#define       TZ_CBC_TZ6                  (1 << 5)
#define       TZ_CBC_DCAEVT2      (1 << 6)
#define       TZ_CBC_DCBEVT2      (1 << 7)
#define   	TZ_OST_SEL_NONE      0
#define       TZ_OST_TZ1                  (1 << 8)
#define       TZ_OST_TZ2                  (1 << 9)
#define       TZ_OST_TZ3                  (1 << 10)
#define       TZ_OST_TZ4                  (1 << 11)
#define       TZ_OST_TZ5                  (1 << 12)
#define       TZ_OST_TZ6                  (1 << 13)
#define       TZ_OST_DCAEVT1      (1 << 14)
#define       TZ_OST_DCBEVT1      (1 << 15)


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


struct EPWMx_CFG_TB{
    enum PWM_CHANNEL 									emPwmChannel;
    enum TB_COUNTER_MODE                       emCounterMode;
    enum PHS_DIR_EN           								emPhsDirEn;
    enum EPWM_SYNC_IN_SRC                       emSyncInSrc;
    enum EPWM_SYNC_OUT          		            emSyncOut;
    UINT16          													u16PrdShadowEnable;
    enum PRD_LOAD_MODE                             emLoadMode;
    UINT16          													u16PrdVal;
    UINT16           													u16PhaseVal;
};

/*--emPwmChannel--------------------------emCounterMode--------------------emPhsDirEn------------emSyncInSrc---------------------------emSyncOut-------------------u16PrdShadowEnable-----------emLoadMode----------------------u16PrdVal------------------u16PhaseVal*/
#define EPWM_CFG_TB_TAB  \
{\
    {PFC_PWM_CHANNEL, 			TB_COUNTER_UP_DOWN,           PHS_DISABLE, 		  EPWM_SYNC_IN_NONE, 	       		 EPWM_SYNC_OUT_NONE, 				1,				PRD_LOAD_CTR_ZERO,			PFC_PWM_TBPRD,                      0},\
}


struct EPWMx_CFG_CC{
    enum PWM_CHANNEL 					   emPwmChannel;
    UINT16        										   u16ABCDShadowEnable;
    enum CC_LOAD_MODE                   emLoadMode;
    UINT32           										u32CmpaVal;
    UINT32           										u32CmpbVal;
    UINT16           										u16CmpcVal;
    UINT16           										u16CmpdVal;
};
/*-----PWM_CHANNEL-----------------u16ABCDShadowEnable--------emLoadMode-----------------------------u32CmpaVal---------------------u32CmpbVal(HR-low 16bit)---------------u16CmpCVal--------u16CmpDVal--------*/
#define EPWM_CFG_CC_TAB  \
{\
    {PFC_PWM_CHANNEL, 		                1, 				               	CC_LOAD_CTR_ZERO, 							 (UINT32)0,   					           3UL* 65536,												0,								0},\
}

struct EPWMx_CFG_AQ{
    enum PWM_CHANNEL emPwmChannel;
    Uint32           AQ_CTLA_CAD   :2;
    Uint32           AQ_CTLA_CAU   :2;
    Uint32           AQ_CTLA_CBD   :2;
    Uint32           AQ_CTLA_CBU   :2;
    Uint32           AQ_CTLA_PRD   :2;
    Uint32           AQ_CTLA_ZRO   :2;
    Uint32           AQ_CTLB_CAD   :2;
    Uint32           AQ_CTLB_CAU   :2;
    Uint32           AQ_CTLB_CBD   :2;
    Uint32           AQ_CTLB_CBU   :2;
    Uint32           AQ_CTLB_PRD   :2;
    Uint32           AQ_CTLB_ZRO   :2;
    Uint32           reserve           :8;
};

/*--PWM_CHANNEL------------------CTLA_CAD------------CTLA_CAU-------------CTLA_CBD---------------CTLA_CBU-------------------CTLA_PRD--------------CTLA_ZRO---------------------CTLB_CAD-----------------CTLB_CAU-----------CTLB_CBD------------------CTLB_CBU-------------------CTLB_PRD---------------CTLB_ZRO---------reserve*/
#define EPWM_CFG_AQ_TAB  \
{\
    {PFC_PWM_CHANNEL, 			AQ_SET,  			 		     AQ_CLEAR, 				   	AQ_NO_ACTION, 			AQ_NO_ACTION, 			AQ_NO_ACTION, 		   AQ_NO_ACTION,       		AQ_NO_ACTION, 			AQ_NO_ACTION, 			AQ_NO_ACTION, 			AQ_NO_ACTION, 				AQ_NO_ACTION, 		AQ_NO_ACTION, 			0},\
}

struct EPWMx_CFG_DB{
    enum PWM_CHANNEL emPwmChannel;
    Uint16           DB_OUT_MODE        											:2;
    Uint16           DB_IN_MODE         												:2;
    Uint16           DB_OUTSWAP         												:2;
    Uint16           DB_POLSEL          											   		:2;
    Uint16           DB_S8									   		  							:1;
    Uint16           DB_SHDW_RED_FED_CTR_MODE   				:1;
    Uint16           DB_LOAD_RED_FED_CTR_MODE    	            :2;
    Uint16           reserve                					          							 :4;
    Uint16           u16RedVal;
    Uint16           u16Fedval;
};

/*--------PWM_CHANNEL-------------OUT_MODE------------IN_MODE--------------------OUTSWAP----------------POLSEL-------------DB_S8-- -------DB_SHDWDBCTLMODE---------LOAD_DB_RED_FED_MODE---------u16Redval---u16Fedval*/
#define EPWM_CFG_DB_TAB  \
{\
    {PFC_PWM_CHANNEL,  		   DB_DISABLE,  			 DBA_RED_DBB_FED, 		 	DB_AABB, 					DB_ACTV_HI, 				 	0,		     DB_CTR_RED_FED_SHADOW, 						DB_LD_CNT_ZERO,  						00, 					00},\
}



struct EPWMx_CFG_TZ{
    enum PWM_CHANNEL 							emPwmChannel;
    enum PWM_TZ_ACTION         				emDcaEvt1;
    enum PWM_TZ_ACTION         				emDcaEvt2;
    enum PWM_TZ_ACTION         				emDcbEvt1;
    enum PWM_TZ_ACTION         				emDcbEvt2;
    enum PWM_TZ_ACTION        				 emTza;
    enum PWM_TZ_ACTION        				 emTzb;
    enum PWM_CBC_CLR                           emCbcClrSel;
    UINT16                                                      u16TzCbcSel;
    UINT16                                                      u16TzOstSel;
};

//Note: the DCA/BEVT1/2 can directly to the TZ, or route through the CBC, or OST submode,
//if using the first method, using the TZCTLDCA[DCAEVTxD,DCAEVTxU],  TZCTLDCB register to control, in order to simply, the DCAEVT1/DCAEVT2 on the up or down all the same.  this method is default disable
//default using the TZCTL to control for TZ, DCAB, the TZCTL2 is ignored
//if using the later method,  又有两种方式，一种方式是DCAEVT1/2 直接通过TZCTL[DCAEVT1/2]只作用在EPWMxA，DCBEVT1/2 直接通过TZCTL[DCBEVT1/2] 只作用在EPWMxB
//另一种方式，是与TZx 一样，连接到CBC, 或者OST模块，但是DCA/BEVT1 只连接到OST模块，DCA/BEVT2只连接到CBC模块；但作用的是整个EPWM，包括EPWMA/EPWMB.
//如果使能了第一种方式，即 emDcxEvtY != DO_NOTHING,  第二种方式最好不选择其作为对应的CBC或者OST功能
//TZA, TZB mode configure the same.
/*-----PWM_CHANNEL---------------- emDcaEvt1----------emDcaEvt2-------------- emDcbEvt1-----------emDcbEvt2----------emTza------------------emTzb------------- emCbcClrSel--------------u16TzCbcSel------------u16TzOstSel-----------*/
#define EPWM_CFG_TZ_TAB  \
{\
    {PFC_PWM_CHANNEL, 			 DO_NOTHING,    	   DO_NOTHING,    	 DO_NOTHING,    	   DO_NOTHING, 	 	 FORCE_LO,  		DO_NOTHING,	 	CBC_CLR_PERIOD,		TZ_CBC_DCAEVT2,       TZ_OST_DCAEVT1},\
}

struct EPWMx_CFG_ET{
    enum PWM_CHANNEL 					 emPwmChannel;
    enum ET_SOC_SEL       					 emEtSocaSel;
    enum ET_PRESCALE                      emEtSocaPrescale;
    enum ET_SOC_SEL       		             emEtSocbSel;
    enum ET_PRESCALE                      emEtSocbPrescale;
    enum ET_INT_SEL        				     emEtIntSel;
    enum ET_PRESCALE     					 emEtIntPrescale;
};
/*--PWM_CHANNEL---------------------ET_SOCA_SEL---------------emEtSocaPrescale------------ emEtSocbSel----------emEtSocbPrescale--------------emEtIntSel-------------emEtIntPrescale----*/
#define EPWM_CFG_ET_TAB  \
{\
    {PFC_PWM_CHANNEL, 		ET_SOC_CTRD_COMPB, 	      ET_FIRST_ACTION,         ET_SOC_DISABLE,   	ET_ACTION_DISABLE,         ET_INT_DISABLE,         ET_ACTION_DISABLE},\
}


#define		DC_SEL_NONE       	0x0000
#define		DC_SEL_TRIPIN1    	0x0001
#define		DC_SEL_TRIPIN2	 	0x0002
#define		DC_SEL_TRIPIN3	 	0x0004
#define		DC_SEL_TRIPIN4	 	0x0008
#define		DC_SEL_TRIPIN5	 	0x0010
#define		DC_SEL_TRIPIN6	 	0x0020
#define		DC_SEL_TRIPIN7	 	0x0040
#define		DC_SEL_TRIPIN8	 	0x0080
#define		DC_SEL_TRIPIN9		 0x0100
#define		DC_SEL_TRIPIN10 		 0x0200
#define		DC_SEL_TRIPIN11 		 0x0400
#define		DC_SEL_TRIPIN12 		 0x0800
#define		DC_SEL_TRIPIN14 		0x2000
#define		DC_SEL_TRIPIN15		0x4000

//I = ignore
enum DCxEVT_CFG{
	EVT_DISABLE = 0x00,
	DCxHL_LI        = 0x01,
	DCxHH_LI       = 0x02,
	DCxHI_LL       =  0x03,
	DCxHI_LH      =  0x04,
	DCxHL_LH	  =  0x05,
};


#define   DCxEVT1_OUT_NONE              0
#define   DCxEVT2_OUT_NONE              0
//DCxEVT1_OUT_FORCE is default enable
#define   DCxEVT1_OUT_FORCE             0
#define   DCxEVT1_OUT_SOC          		(1 <<   0)
#define    DCxEVT1_OUT_INT          		(1 <<   1)
#define    DCxEVT1_OUT_SYNC     			(1 <<   2)
//DCxEVT2_OUT_FORCE is default enable
#define   DCxEVT2_OUT_FORCE             0
#define    DCxEVT2_OUT_INT         			(1 <<   3)

struct EPWMx_CFG_DC{
    enum PWM_CHANNEL emPwmChannel;
    UINT16       					  u16DCAH_SEL;
    UINT16       					  u16DCAL_SEL;
    UINT16       					  u16DCBH_SEL;
    UINT16       					  u16DCBL_SEL;
    enum DCxEVT_CFG     emDCAEVT1_CFG;
    UINT16                            u16DcaEvt1Out;
    enum DCxEVT_CFG     emDCAEVT2_CFG;
    UINT16                            u16DcaEvt2Out;
    enum DCxEVT_CFG     emDCBEVT1_CFG;
    UINT16                            u16DcbEvt1Out;
    enum DCxEVT_CFG     emDCBEVT2_CFG;
    UINT16                            u16DcbEvt2Out;
};

//Even the DCAEVT1/2,   DCBEVT1/2 is defined by TZDSEL in the TZ submodule, but it defined in follow.
/*--PWM_CHANNEL----------------DCAH_SEL--------------DCAL_SEL--------------DCBH_SEL----------DCBL_SEL--------DCAEVT1_CFG-------u16DcaEvt1Out--------------DCAEVT2_CFG--------u16DcaEvt2Out----------------DCBEVT1_CFG--------u16DcbEvt1Out-------------DCBEVT2_CFG------u16DcbEvt2Out--*/
#define EPWM_CFG_DC_TAB  \
{\
	{PFC_PWM_CHANNEL, 		DC_SEL_TRIPIN4,       DC_SEL_TRIPIN5,	    DC_SEL_NONE,		DC_SEL_NONE,			DCxHH_LI,		  DCxEVT1_OUT_FORCE,			DCxHI_LH,		 DCxEVT1_OUT_FORCE,			EVT_DISABLE,	  DCxEVT1_OUT_NONE,			EVT_DISABLE,	  DCxEVT2_OUT_NONE},\
}


#define   DCAEVT1_SRC       0
#define   DCAEVT2_SRC       0
#define   DCBEVT1_SRC       0
#define   DCBEVT2_SRC       0
#define   DCEVTFILT_SRC    1


enum DC_EVT_FILT_SRC{
	FILT_DCAEVT1_SRC        =    0,
	FILT_DCAEVT2_SRC	      =	 1,
	FILT_DCBEVT1_SRC 	  =    2,
	FILT_DCBEVT2_SRC  	 =	    3,
};


enum BLANK_START{
	START_PERIOD	      				  		=	    0,
	START_ZERO       		  				  		=      1,
	START_ZERO_PERIOD       	 	 	=      2,
	START_PULSE_ZERO  	         		=	    3,
	START_PULSE_PERIOD                =	    4,
	START_PULSE_CAU  	                    =	    5,
	START_PULSE_CAD  	                    =	    6,
	START_PULSE_CBU  	                    =	    7,
	START_PULSE_CBD  	                    =	    8,
	START_PULSE_CCU  	                    =	    9,
	START_PULSE_CCD  	                    =	    10,
	START_PULSE_CDU  	                    =	    11,
	START_PULSE_CDD  	                    =	    12,
};


struct EPWMx_CFG_DC_FILT{
    enum PWM_CHANNEL 			emPwmChannel;
	UINT16   									u16DcaEvt1Src;
	UINT16   									u16DcaEvt2Src;
	UINT16  									u16DcbEvt1Src;
	UINT16   									u16DcbEvt2Src;
	enum DC_EVT_FILT_SRC 	emDcEvtFiltSrc;
	enum BLANK_START      	   emBlankStart;
	UINT16                                      u16Offset;
	UINT16                                      u16BlankWindow;
};
//In the offset, the signal is valid
/*--PWM_CHANNEL----------------- u16DcaEvt1Src----------u16DcaEvt2Src-------u16DcbEvt1Src----------u16DcbEvt2Src-----------emDcEvtFiltSrc-----------------emBlankStart-------------u16Offset--------u16BlankWindow-*/
#define EPWM_CFG_DC_FILT_TAB  \
{\
    {PFC_PWM_CHANNEL, 		    DCAEVT1_SRC,         DCEVTFILT_SRC,	       DCBEVT1_SRC,		   DCBEVT2_SRC,			FILT_DCAEVT2_SRC,		START_PULSE_CAD,      		0,      					30},\
}


/*-------PWM_CHANNEL----------------EDGMODE--------CTLMODE-------------HRLOAD-------------EDGMODEB-----------CTLMODEB----------HRLOADB--------------AUTOCONV-----------TBPHSHRLOADE----------------HRPE------------------reserve */
#define EPWM_CFG_HR_TAB  \
{\
    {PFC_PWM_CHANNEL, 		HR_FEP, 			   HR_CMP, 				HR_CTR_ZERO, 				HR_FEP,  					HR_CMP,   		HR_CTR_PRD, 			HR_COM_ENABLE, 		HR_COM_DISABLE,				HR_COM_DISABLE, 			0},\
}

extern volatile struct EPWM_REGS *gp_stPwmChannel[] ;

extern void bsw_mcal_epwm_init(void);

#ifdef __cpluslus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================
