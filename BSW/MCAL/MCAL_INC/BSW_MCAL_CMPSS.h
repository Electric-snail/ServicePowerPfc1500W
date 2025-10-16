/*
 * BSW_MCAL_CMPSS.h
 *
 *  Created on: 2024.06.06
 *      Author: rjgslg
 */

#ifndef BSW_MCAL_CMPSS_H_
#define BSW_MCAL_CMPSS_H_
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#include "ENV_CFG/HARDWARE_ENV_CFG.h"

enum  CMPSS_MODULE{
    CMPSS1_ID = 0,
	CMPSS2_ID,
	CMPSS3_ID,
	CMPSS4_ID,
    CMPSS_ID_MAX
};

enum RAMP_SRC{
	EPWM1SYNCPER = 0,
	EPWM2SYNCPER,
	EPWM3SYNCPER,
	EPWM4SYNCPER,
	EPWM5SYNCPER,
	EPWM6SYNCPER,
	EPWM7SYNCPER,
};

enum BLANK_SRC{
	EPWM1BLANK = 0,
	EPWM2BLANK,
	EPWM3BLANK,
	EPWM4BLANK,
	EPWM5BLANK,
	EPWM6BLANK,
	EPWM7BLANK,
};

//define the positive input / negative input gpio of any comss
#define       CMP1H_P_AGPIO224						   0
#define       CMP1H_P_AIO237						   		   1
#define       CMP1H_P_AGPIO228                          2
#define       CMP1H_P_AIO233						   		   3
#define       CMP1H_P_AIO232						   		   4

#define       CMP1H_N_AIO233						   		   0
#define       CMP1H_N_AIO237						   		   1
#define       CMP1H_N_DAC						   		       2

#define       CMP1L_P_AGPIO224						      0
#define       CMP1L_P_AIO237						   		   1
#define       CMP1L_P_AGPIO228                            2
#define       CMP1L_P_AIO233						   		   3
#define       CMP1L_P_AIO232						   		   4

#define       CMP1L_N_AIO233						   		   0
#define       CMP1L_N_AIO237						   		   1
#define       CMP1L_N_DAC						   		       2

#define       CMP2L_N_DAC						   		         2
#define       CMP2H_N_DAC						   		         2

#define       CMP3H_P_AGPIO226						   		0
#define       CMP3H_P_AIO244						   		    1
#define       CMP3H_P_AIO231                          		2
#define       CMP3H_P_AGPIO242						   		3
#define       CMP3H_P_AIO239						   		    4

#define       CMP3H_N_AGPIO242						   0
#define       CMP3H_N_AIO244						   		   1
#define       CMP3H_N_DAC						   		        2

#define       CMP3L_P_AGPIO226						   		0
#define       CMP3L_P_AIO244						   		    1
#define       CMP3L_P_AIO231                          		    2
#define       CMP3L_P_AGPIO242						   		3
#define       CMP3L_P_AIO239						   		    4

#define       CMP3L_N_AGPIO242						         0
#define       CMP3L_N_AIO244						   		     1
#define       CMP3L_N_DAC						   		         2


#define       CMP4L_N_DAC						   		         2
#define       CMP4H_N_DAC						   		         2

#define       DAC_LOAD_SYNC_SYCCLK              				0
#define       DAC_LOAD_SYNC_EPWMSYNCPER           1
//There is no latch function for 	CMPOUT_ASYNC,CMPOUT_SYNC,  CMPOUT_FILT,
enum         CMPOUT_SEL{
	CMPOUT_ASYNC = 0,
	CMPOUT_SYNC,
	CMPOUT_FILT,
	CMPOUT_FILT_LATCH,
	CMPOUT_FILT_LATCH_OR_ASYNC,
};

enum     LATCH_CLEAR_SRC{
	LAT_CLR_RAMP_OR_SW = 0,
	LAT_CLR_SW,
};

typedef struct{
	enum  CMPSS_MODULE 					emCmpssModule;
    UINT16                          						u16DacOutEnable;
    UINT16                                      			u16RampGenEnable;
    enum RAMP_SRC                    			emRampOrClearLatchSrc;      // if the latch output signal is not selected by using emCmpOutSel, it doesn't effect the comparator output. or the comparator output latch clear source is not from ramp source,   it is ignored.
    UINT16                          						u16DacLoadSycnSrc;            //if the RampGen Enable, this word is ignored. the DAC is load immediately
    UINT16                          						u16BlankEnable;
    UINT16                          						u16BlankSrc;                       //if the u16BlankEnable == 0, the word is ignored
	enum     	LATCH_CLEAR_SRC       	emLatchClearSrc;      // if the latch output signal is not selected by using emCmpOutSel, it is ignored
}CMPSS_CFG_T;
/*---emCmpssModule--------u16DacOutEnable--------u16RampGenEnable-----------    emRampOrClearLatchSrc----------u16DacLoadSycnSrc-----------u16BlankEnable-----------emBlankSrc--------------emLatchClearSrc-----*/
#define  CMPSS_CFG_TAB  \
{\
    {CMPSS1_ID,            					 0,             					0,												EPWM1SYNCPER,					DAC_LOAD_SYNC_SYCCLK,		         0,                        EPWM1BLANK,			LAT_CLR_SW},\
    {CMPSS3_ID,            					 0,             					0,												EPWM1SYNCPER,					DAC_LOAD_SYNC_SYCCLK,		         0,                         EPWM1BLANK,			LAT_CLR_SW},\
}

enum CMP_MODULE{
	    CMP1_H_ID = 0x00,
	    CMP1_L_ID  = 0x10,
	    CMP2_H_ID = 0x01,
	    CMP2_L_ID  = 0x11,
	    CMP3_H_ID = 0x02,
	    CMP3_L_ID  = 0x12,
	    CMP4_H_ID = 0x03,
	    CMP4_L_ID  = 0x13,
};

typedef struct{
	enum  CMP_MODULE 		   								emCmpModule;
	UINT16       															u16PosSrc;
	UINT16      															u16NegSrc;
	UINT16      															u16DacValue;
	UINT16      															u16OutInvEnable;
	enum     CMPOUT_SEL   									emOutToEpwmSel;
	enum     CMPOUT_SEL   									emOutToOutputSel;
}CMPSS_CMP_CFG_T;


//---emCmpModule---------u16PosSrc--------------------------u16NegSrc-----------u16DacValue----------u16OutInv------emOutToEpwmSel-----------------emOutToOutputSel---------------
#define CMPSS_CMP_CFG_TAB \
{\
    {CMP1_L_ID,         		 CMP1L_P_AGPIO224,         CMP1L_N_DAC,			2048,      					0,		         CMPOUT_SYNC,		   				CMPOUT_SYNC},\
    {CMP3_L_ID,         		 CMP3L_P_AIO244,        		  CMP3L_N_DAC,			2048,      					0,		         CMPOUT_FILT_LATCH,		   	CMPOUT_FILT_LATCH},\
}

extern void bsw_mcal_cmpss_init(void);

#endif /*BSW_MCAL_CMPSS_H_ */
