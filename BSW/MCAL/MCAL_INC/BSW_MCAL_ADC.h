/*********************************************************************
File name:       BSW_MCAL_ADC.h
Purpose :         1. Define macro
                  2. Define data type, such as structure/enum
                  3. import variables  by  including head file(s)
                  4. export variables by keywords( extern)
 
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/

#ifndef BSW_MCAL_ADC_H
#define BSW_MCAL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "MCAL/BSW_MCAL_BASIC.h"
#include "PUBLIC_INC/AUTO_REGISTER.H"
#include "common/include/F28x_Project.h"
// Definitions for ADCSOC Acquisition Prescale
#define ADC_SOC_ACQPS                   				6
#define ADC_SOC_ACQPS_MIN               		20
#define ADC_SOC_ACQPS_MAX               		512

// Definitions for Delay times of completed config ADC
#define ADC_USDELAY                     1000L  //Delay timer 1ms
// Definitions for  ADC INT Select
#define ADC_INT_SEL_EOC0                0
#define ADC_INT_SEL_EOC1                1
#define ADC_INT_SEL_EOC2                2
#define ADC_INT_SEL_EOC3                3
#define ADC_INT_SEL_EOC4                4
#define ADC_INT_SEL_EOC5                5
#define ADC_INT_SEL_EOC6                6
#define ADC_INT_SEL_EOC7                7
#define ADC_INT_SEL_EOC8                8
#define ADC_INT_SEL_EOC9                9
#define ADC_INT_SEL_EOC10               10
#define ADC_INT_SEL_EOC11               11
#define ADC_INT_SEL_EOC12               12
#define ADC_INT_SEL_EOC13               13
#define ADC_INT_SEL_EOC14               14
#define ADC_INT_SEL_EOC15               15

//
// Definitions for  ADC INT Enable
//
#define ADC_INT_DISABLE                 0   
#define ADC_INT_ENABLE                  1

//
// Definitions for  ADC_SOC_PRIORITY_SEL
//
#define ADC_PRIORITY_DEFALUT            0
#define ADC_PRIORITY_SOC0_HIGH          1
#define ADC_PRIORITY_SOC0_SOC1_HIGH     2 
#define ADC_PRIORITY_SOC0_SOC2_HIGH     3
#define ADC_PRIORITY_SOC0_SOC3_HIGH     4
#define ADC_PRIORITY_SOC0_SOC4_HIGH     5
#define ADC_PRIORITY_SOC0_SOC5_HIGH     6
#define ADC_PRIORITY_SOC0_SOC6_HIGH     7
#define ADC_PRIORITY_SOC0_SOC7_HIGH     8 
#define ADC_PRIORITY_SOC0_SOC8_HIGH     9 
#define ADC_PRIORITY_SOC0_SOC9_HIGH     10
#define ADC_PRIORITY_SOC0_SOC10_HIGH    11
#define ADC_PRIORITY_SOC0_SOC11_HIGH    12
#define ADC_PRIORITY_SOC0_SOC12_HIGH    13
#define ADC_PRIORITY_SOC0_SOC13_HIGH    14
#define ADC_PRIORITY_SOC0_SOC14_HIGH    15
#define ADC_PRIORITY_ALL                16

//
// Definitions for  ADC channel select 
//
#define ADC_CHANNEL_0                   0
#define ADC_CHANNEL_1                   1
#define ADC_CHANNEL_2                   2
#define ADC_CHANNEL_3                   3
#define ADC_CHANNEL_4                   4
#define ADC_CHANNEL_5                   5
#define ADC_CHANNEL_6                   6
#define ADC_CHANNEL_7                   7
#define ADC_CHANNEL_8                   8
#define ADC_CHANNEL_9                   9
#define ADC_CHANNEL_10                  10
#define ADC_CHANNEL_11                  11
#define ADC_CHANNEL_12                  12
#define ADC_CHANNEL_13                  13
#define ADC_CHANNEL_14                  14
#define ADC_CHANNEL_15                  15
//
// Definitions for ADC Capture Trigger Select
//
#define ADC_TRIG_SOFT                   0
#define ADC_TRIG_CPUTIME0               1
#define ADC_TRIG_CPUTIME1               2
#define ADC_TRIG_CPUTIME2               3
#define ADC_TRIG_GPIO                   4
#define ADC_TRIG_EPWM1SOCA              5
#define ADC_TRIG_EPWM1SOCB              6
#define ADC_TRIG_EPWM2SOCA              7
#define ADC_TRIG_EPWM2SOCB              8
#define ADC_TRIG_EPWM3SOCA              9
#define ADC_TRIG_EPWM3SOCB              10
#define ADC_TRIG_EPWM4SOCA              11
#define ADC_TRIG_EPWM4SOCB              12
#define ADC_TRIG_EPWM5SOCA              13
#define ADC_TRIG_EPWM5SOCB              14
#define ADC_TRIG_EPWM6SOCA              15
#define ADC_TRIG_EPWM6SOCB              16
#define ADC_TRIG_EPWM7SOCA              17
#define ADC_TRIG_EPWM7SOCB              18
#define ADC_TRIG_EPWM8SOCA              19
#define ADC_TRIG_EPWM8SOCB              20

// Define ADCResultNum
#define ADCA0                           AdcaResultRegs.ADCRESULT0   /* SOC0 -- A0 -- */
#define ADCA1                           AdcaResultRegs.ADCRESULT1   /* SOC1 -- A1 -- */
#define ADCA2                           AdcaResultRegs.ADCRESULT2   /* SOC2 -- A2 -- */
#define ADCA3                           AdcaResultRegs.ADCRESULT3   /* SOC3 -- A3 -- */
#define ADCA4                           AdcaResultRegs.ADCRESULT4   /* SOC4 -- A4 -- */
#define ADCA5                           AdcaResultRegs.ADCRESULT5   /* SOC5 -- A0 -- */
#define ADCA6                           AdcaResultRegs.ADCRESULT6   /* SOC6 -- A1 -- */
#define ADCA7                           AdcaResultRegs.ADCRESULT7   /* SOC7 -- A2 -- */
#define ADCA8                           AdcaResultRegs.ADCRESULT8   /* SOC8 -- A3 -- */
#define ADCA9                           AdcaResultRegs.ADCRESULT9   /* SOC9 -- A4 -- */
#define ADCA10                          AdcaResultRegs.ADCRESULT10
#define ADCA11                          AdcaResultRegs.ADCRESULT11
#define ADCA12                          AdcaResultRegs.ADCRESULT12
#define ADCA13                          AdcaResultRegs.ADCRESULT13
#define ADCA14                          AdcaResultRegs.ADCRESULT14  /* SOC14 -- A8 -- Temperature1         */
#define ADCA15                          AdcaResultRegs.ADCRESULT15  /* SOC15 -- A9 -- Temperature2         */


/*
#define ADCC0                           AdccResultRegs.ADCRESULT0
#define ADCC1                           AdccResultRegs.ADCRESULT1
#define ADCC2                           AdccResultRegs.ADCRESULT2
#define ADCC3                           AdccResultRegs.ADCRESULT3
#define ADCC4                           AdccResultRegs.ADCRESULT4
#define ADCC5                           AdccResultRegs.ADCRESULT5
#define ADCC6                           AdccResultRegs.ADCRESULT6
#define ADCC7                           AdccResultRegs.ADCRESULT7
#define ADCC8                           AdccResultRegs.ADCRESULT8
#define ADCC9                           AdccResultRegs.ADCRESULT9
#define ADCC10                          AdccResultRegs.ADCRESULT10
#define ADCC11                          AdccResultRegs.ADCRESULT11
#define ADCC12                          AdccResultRegs.ADCRESULT12
#define ADCC13                          AdccResultRegs.ADCRESULT13
#define ADCC14                          AdccResultRegs.ADCRESULT14
#define ADCC15                          AdccResultRegs.ADCRESULT15
*/
//*****************************************************************************
//
// Values that can be passed to ADC_forceMultipleSOC() as socMask parameter.
// These values can be OR'd together to trigger multiple SOCs at a time.
//
//*****************************************************************************
#define ADC_FORCE_SOC0         0x0001U //!< SW trigger ADC SOC 0
#define ADC_FORCE_SOC1         0x0002U //!< SW trigger ADC SOC 1
#define ADC_FORCE_SOC2         0x0004U //!< SW trigger ADC SOC 2
#define ADC_FORCE_SOC3         0x0008U //!< SW trigger ADC SOC 3
#define ADC_FORCE_SOC4         0x0010U //!< SW trigger ADC SOC 4
#define ADC_FORCE_SOC5         0x0020U //!< SW trigger ADC SOC 5
#define ADC_FORCE_SOC6         0x0040U //!< SW trigger ADC SOC 6
#define ADC_FORCE_SOC7         0x0080U //!< SW trigger ADC SOC 7
#define ADC_FORCE_SOC8         0x0100U //!< SW trigger ADC SOC 8
#define ADC_FORCE_SOC9         0x0200U //!< SW trigger ADC SOC 9
#define ADC_FORCE_SOC10        0x0400U //!< SW trigger ADC SOC 10
#define ADC_FORCE_SOC11        0x0800U //!< SW trigger ADC SOC 11
#define ADC_FORCE_SOC12        0x1000U //!< SW trigger ADC SOC 12
#define ADC_FORCE_SOC13        0x2000U //!< SW trigger ADC SOC 13
#define ADC_FORCE_SOC14        0x4000U //!< SW trigger ADC SOC 14
#define ADC_FORCE_SOC15        0x8000U //!< SW trigger ADC SOC 15


//! Values that can be passed to ADC_setPrescaler() as the \e clkPrescale
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_CLK_DIV_1_0 = 0U,            //!< ADCCLK = (input clock) / 1.0
    ADC_CLK_DIV_2_0 = 2U,            //!< ADCCLK = (input clock) / 2.0
    ADC_CLK_DIV_3_0 = 4U,            //!< ADCCLK = (input clock) / 3.0
    ADC_CLK_DIV_4_0 = 6U,            //!< ADCCLK = (input clock) / 4.0
    ADC_CLK_DIV_5_0 = 8U,            //!< ADCCLK = (input clock) / 5.0
    ADC_CLK_DIV_6_0 = 10U,           //!< ADCCLK = (input clock) / 6.0
    ADC_CLK_DIV_7_0 = 12U,           //!< ADCCLK = (input clock) / 7.0
    ADC_CLK_DIV_8_0 = 14U            //!< ADCCLK = (input clock) / 8.0
} ADC_ClkPrescale;

//*****************************************************************************
//
//! Values that can be passed to ADC_setupSOC() as the \e trigger
//! parameter to specify the event that will trigger a conversion to start.
//! It is also used with ADC_setBurstModeConfig().
//
//*****************************************************************************
typedef enum
{
    ADC_TRIGGER_SW_ONLY     = 0U,     //!< Software only
    ADC_TRIGGER_CPU1_TINT0  = 1U,     //!< CPU1 Timer 0, TINT0
    ADC_TRIGGER_CPU1_TINT1  = 2U,     //!< CPU1 Timer 1, TINT1
    ADC_TRIGGER_CPU1_TINT2  = 3U,     //!< CPU1 Timer 2, TINT2
    ADC_TRIGGER_GPIO        = 4U,     //!< GPIO, ADCEXTSOC
    ADC_TRIGGER_EPWM1_SOCA  = 5U,     //!< ePWM1, ADCSOCA
    ADC_TRIGGER_EPWM1_SOCB  = 6U,     //!< ePWM1, ADCSOCB
    ADC_TRIGGER_EPWM2_SOCA  = 7U,     //!< ePWM2, ADCSOCA
    ADC_TRIGGER_EPWM2_SOCB  = 8U,     //!< ePWM2, ADCSOCB
    ADC_TRIGGER_EPWM3_SOCA  = 9U,     //!< ePWM3, ADCSOCA
    ADC_TRIGGER_EPWM3_SOCB  = 10U,    //!< ePWM3, ADCSOCB
    ADC_TRIGGER_EPWM4_SOCA  = 11U,    //!< ePWM4, ADCSOCA
    ADC_TRIGGER_EPWM4_SOCB  = 12U,    //!< ePWM4, ADCSOCB
    ADC_TRIGGER_EPWM5_SOCA  = 13U,    //!< ePWM5, ADCSOCA
    ADC_TRIGGER_EPWM5_SOCB  = 14U,    //!< ePWM5, ADCSOCB
    ADC_TRIGGER_EPWM6_SOCA  = 15U,    //!< ePWM6, ADCSOCA
    ADC_TRIGGER_EPWM6_SOCB  = 16U,    //!< ePWM6, ADCSOCB
    ADC_TRIGGER_EPWM7_SOCA  = 17U,    //!< ePWM7, ADCSOCA
    ADC_TRIGGER_EPWM7_SOCB  = 18U,    //!< ePWM7, ADCSOCB
    ADC_TRIGGER_EPWM8_SOCA  = 19U,    //!< ePWM8, ADCSOCA
    ADC_TRIGGER_EPWM8_SOCB  = 20U    //!< ePWM8, ADCSOCB
} ADC_Trigger;

//*****************************************************************************
//
//! Values that can be passed to ADC_setupSOC() as the \e channel
//! parameter. This is the input pin on which the signal to be converted is
//! located.
//
//*****************************************************************************
typedef enum
{
    ADC_CH_ADCIN0  = 0U,          //!< ADCIN0 is converted
    ADC_CH_ADCIN1  = 1U,          //!< ADCIN1 is converted
    ADC_CH_ADCIN2  = 2U,          //!< ADCIN2 is converted
    ADC_CH_ADCIN3  = 3U,          //!< ADCIN3 is converted
    ADC_CH_ADCIN4  = 4U,          //!< ADCIN4 is converted
    ADC_CH_ADCIN5  = 5U,          //!< ADCIN5 is converted
    ADC_CH_ADCIN6  = 6U,          //!< ADCIN6 is converted
    ADC_CH_ADCIN7  = 7U,          //!< ADCIN7 is converted
    ADC_CH_ADCIN8  = 8U,          //!< ADCIN8 is converted
    ADC_CH_ADCIN9  = 9U,          //!< ADCIN9 is converted
    ADC_CH_ADCIN10 = 10U,         //!< ADCIN10 is converted
    ADC_CH_ADCIN11 = 11U,         //!< ADCIN11 is converted
    ADC_CH_ADCIN12 = 12U,         //!< ADCIN12 is converted
    ADC_CH_ADCIN13 = 13U,         //!< ADCIN13 is converted
    ADC_CH_ADCIN14 = 14U,         //!< ADCIN14 is converted
    ADC_CH_ADCIN15 = 15U,         //!< ADCIN15 is converted
    ADC_CH_ADCIN16 = 16U,         //!< ADCIN11 is converted
    ADC_CH_ADCIN17 = 17U,         //!< ADCIN12 is converted
    ADC_CH_ADCIN18 = 18U,         //!< ADCIN13 is converted
    ADC_CH_ADCIN19 = 19U,         //!< ADCIN14 is converted
    ADC_CH_ADCIN20 = 20U          //!< ADCIN15 is converted
} ADC_Channel;

//*****************************************************************************
//
//! Values that can be passed to ADC_setInterruptPulseMode() as the
//! \e pulseMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Occurs at the end of the acquisition window
    ADC_PULSE_END_OF_ACQ_WIN = 0x00U,
    //! Occurs at the end of the conversion
    ADC_PULSE_END_OF_CONV    = 0x04U
} ADC_PulseMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_enableInterrupt(), ADC_disableInterrupt(),
//! and ADC_getInterruptStatus() as the \e adcIntNum parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_INT_NUMBER1 = 0U,        //!< ADCINT1 Interrupt
    ADC_INT_NUMBER2 = 1U,        //!< ADCINT2 Interrupt
    ADC_INT_NUMBER3 = 2U,        //!< ADCINT3 Interrupt
    ADC_INT_NUMBER4 = 3U        //!< ADCINT4 Interrupt
} ADC_IntNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e ppbNumber parameter for several
//! functions.
//
//*****************************************************************************
typedef enum
{
    ADC_PPB_NUMBER1 = 0U,        //!< Post-processing block 1
    ADC_PPB_NUMBER2 = 1U,        //!< Post-processing block 2
    ADC_PPB_NUMBER3 = 2U,        //!< Post-processing block 3
    ADC_PPB_NUMBER4 = 3U        //!< Post-processing block 4
} ADC_PPBNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e socNumber parameter for several
//! functions. This value identifies the start-of-conversion (SOC) that a
//! function is configuring or accessing. Note that in some cases (for example,
//! ADC_setInterruptSource()) \e socNumber is used to refer to the
//! corresponding end-of-conversion (EOC).
//
//*****************************************************************************
typedef enum
{
    ADC_SOC_NUMBER0  = 0U,        //!< SOC/EOC number 0
    ADC_SOC_NUMBER1  = 1U,        //!< SOC/EOC number 1
    ADC_SOC_NUMBER2  = 2U,        //!< SOC/EOC number 2
    ADC_SOC_NUMBER3  = 3U,        //!< SOC/EOC number 3
    ADC_SOC_NUMBER4  = 4U,        //!< SOC/EOC number 4
    ADC_SOC_NUMBER5  = 5U,        //!< SOC/EOC number 5
    ADC_SOC_NUMBER6  = 6U,        //!< SOC/EOC number 6
    ADC_SOC_NUMBER7  = 7U,        //!< SOC/EOC number 7
    ADC_SOC_NUMBER8  = 8U,        //!< SOC/EOC number 8
    ADC_SOC_NUMBER9  = 9U,        //!< SOC/EOC number 9
    ADC_SOC_NUMBER10 = 10U,       //!< SOC/EOC number 10
    ADC_SOC_NUMBER11 = 11U,       //!< SOC/EOC number 11
    ADC_SOC_NUMBER12 = 12U,       //!< SOC/EOC number 12
    ADC_SOC_NUMBER13 = 13U,       //!< SOC/EOC number 13
    ADC_SOC_NUMBER14 = 14U,       //!< SOC/EOC number 14
    ADC_SOC_NUMBER15 = 15U        //!< SOC/EOC number 15
} ADC_SOCNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e trigger parameter for the
//! ADC_setInterruptSOCTrigger() function.
//
//*****************************************************************************
typedef enum
{
    ADC_INT_SOC_TRIGGER_NONE = 0U,       //!< No ADCINT will trigger the SOC
    ADC_INT_SOC_TRIGGER_ADCINT1 = 1U,    //!< ADCINT1 will trigger the SOC
    ADC_INT_SOC_TRIGGER_ADCINT2 = 2U    //!< ADCINT2 will trigger the SOC
} ADC_IntSOCTrigger;

//*****************************************************************************
//
//! Values that can be passed to ADC_setSOCPriority() as the \e priMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_PRI_ALL_ROUND_ROBIN = 0U,    //!< Round robin mode is used for all
    ADC_PRI_SOC0_HIPRI      = 1U,    //!< SOC 0 hi pri, others in round robin
    ADC_PRI_THRU_SOC1_HIPRI = 2U,    //!< SOC 0-1 hi pri, others in round robin
    ADC_PRI_THRU_SOC2_HIPRI = 3U,    //!< SOC 0-2 hi pri, others in round robin
    ADC_PRI_THRU_SOC3_HIPRI = 4U,    //!< SOC 0-3 hi pri, others in round robin
    ADC_PRI_THRU_SOC4_HIPRI = 5U,    //!< SOC 0-4 hi pri, others in round robin
    ADC_PRI_THRU_SOC5_HIPRI = 6U,    //!< SOC 0-5 hi pri, others in round robin
    ADC_PRI_THRU_SOC6_HIPRI = 7U,    //!< SOC 0-6 hi pri, others in round robin
    ADC_PRI_THRU_SOC7_HIPRI = 8U,    //!< SOC 0-7 hi pri, others in round robin
    ADC_PRI_THRU_SOC8_HIPRI = 9U,    //!< SOC 0-8 hi pri, others in round robin
    ADC_PRI_THRU_SOC9_HIPRI = 10U,   //!< SOC 0-9 hi pri, others in round robin
    ADC_PRI_THRU_SOC10_HIPRI = 11U,  //!< SOC 0-10 hi pri, others in round robin
    ADC_PRI_THRU_SOC11_HIPRI = 12U,  //!< SOC 0-11 hi pri, others in round robin
    ADC_PRI_THRU_SOC12_HIPRI = 13U,  //!< SOC 0-12 hi pri, others in round robin
    ADC_PRI_THRU_SOC13_HIPRI = 14U,  //!< SOC 0-13 hi pri, others in round robin
    ADC_PRI_THRU_SOC14_HIPRI = 15U,  //!< SOC 0-14 hi pri, SOC15 in round robin
    ADC_PRI_ALL_HIPRI = 16U          //!< All priorities based on SOC number
} ADC_PriorityMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_getTemperatureC(), ADC_getTemperatureK(),
//! ADC_setVREF() and ADC_setOffsetTrimAll() as the \e refMode parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_REFERENCE_INTERNAL = 0U,
    ADC_REFERENCE_EXTERNAL = 1U
} ADC_ReferenceMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_setVREF() and ADC_setOffsetTrimAll() as the
//! \e refVoltage parameter.
//!
//
//*****************************************************************************
typedef enum
{
    ADC_REFERENCE_3_3V = 0U,
    ADC_REFERENCE_2_5V = 1U
} ADC_ReferenceVoltage;

enum ADC_MODULE
{
    ADC_ADCA_MODULE = 0,
    ADC_ADCC_MODULE,
    ADC_MAX_MODULE,
};

//*****************************************************************************
//
//! Values that can be passed to ADC_configOSDetectMode() as the \e modeVal
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_OSDETECT_MODE_DISABLED            = 0x0U,//!< Open/Shorts detection cir-
                                                 //!< cuit(O/S DC) is disabled
    ADC_OSDETECT_MODE_VSSA                = 0x1U,//!< O/S DC is enabled at zero
                                                 //!< scale
    ADC_OSDETECT_MODE_VDDA                = 0x2U,//!< O/S DC is enabled at full
                                                 //!< scale
    ADC_OSDETECT_MODE_5BY12_VDDA          = 0x3U,//!< O/S DC is enabled at 5/12
                                                 //!< scale
    ADC_OSDETECT_MODE_7BY12_VDDA          = 0x4U,//!< O/S DC is enabled at 7/12
                                                 //!< scale
    ADC_OSDETECT_MODE_5K_PULLDOWN_TO_VSSA = 0x5U,//!< O/S DC is enabled at 5K
                                                 //!< pulldown to VSSA
    ADC_OSDETECT_MODE_5K_PULLUP_TO_VDDA   = 0x6U,//!< O/S DC is enabled at 5K
                                                 //!< pullup to VDDA
    ADC_OSDETECT_MODE_7K_PULLDOWN_TO_VSSA = 0x7U //!< O/S DC is enabled at 7K
                                                 //!< pulldown to VSSA
} ADC_OSDetectMode;
// read result
#define BSW_MCAL_GetAdcResult(ADCxNum)        ADCxNum

enum ADCINT_SRC{
	ADCINT_EOC0  	= 0,
	ADCINT_EOC1,
	ADCINT_EOC2	,
	ADCINT_EOC3,
	ADCINT_EOC4,
	ADCINT_EOC5,
	ADCINT_EOC6,
	ADCINT_EOC7,
	ADCINT_EOC8,
	ADCINT_EOC9,
	ADCINT_EOC10,
	ADCINT_EOC11,
	ADCINT_EOC12,
	ADCINT_EOC13,
	ADCINT_EOC14,
	ADCINT_EOC15,
	ADCINT_DISABLE,
};

typedef struct
{
    enum ADC_MODULE         emAdcModule;
    ADC_ReferenceMode           emAdcRefMode;
    ADC_ReferenceVoltage       emAdcRefVolt;
    float                  					   f32AdcClkFreq;
    enum ADCINT_SRC          emADCINT1_SRC;
    enum ADCINT_SRC          emADCINT2_SRC;
    enum ADCINT_SRC          emADCINT3_SRC;
    enum ADCINT_SRC          emADCINT4_SRC;
    UINT16                  			   u16IntSrc;
}ADC_MODULE_CFG;



/*---emAdcModule--------------------emAdcRefMode-------------------------emAdcRefVolt--------------------------f32AdcClkFreq(MHz)---------- emADCINT1_SRC---------- emADCINT2_SRC----- emADCINT3_SRC----- emADCINT4_SRC*/
#define  REG_ADC_MODULE_CFG_TAB  \
{\
    {ADC_ADCA_MODULE,  			ADC_REFERENCE_INTERNAL,  			ADC_REFERENCE_3_3V,    			20.0,   								ADCINT_EOC3,   				ADCINT_DISABLE,				ADCINT_DISABLE,			ADCINT_DISABLE,},\
    {ADC_ADCC_MODULE,  			ADC_REFERENCE_INTERNAL,  			ADC_REFERENCE_3_3V,    			20.0,  			 					ADCINT_DISABLE,   			ADCINT_DISABLE,				ADCINT_DISABLE,			ADCINT_DISABLE,},\
}

/*--ADCx_MODULE-------------------------------ADC_SOCNumber---------------------ADC_Trigger--------------------------------ADC_Channel-----------------------------------u16AqcPs*/
struct ADCx_CFG_SOC{
    enum ADC_MODULE 	emAdcx_modele;
    ADC_SOCNumber   			emAdcx_socNum;
    ADC_Trigger     					emAdcx_trigSel;
    ADC_Channel    				 emAdcx_chSel;
    Uint16          						u16AqcPs;
};

#if (OVERSAMPLED == 0)
#define ADC_CFG_SOC_TAB  \
{\
    {ADC_ADCA_MODULE, 						ADC_SOC_NUMBER0, 				 ADC_TRIGGER_EPWM1_SOCA,   				ADCA_PFC_I_SENSE_L,     							20},\
    {ADC_ADCA_MODULE, 						ADC_SOC_NUMBER1, 				 ADC_TRIGGER_EPWM1_SOCA,   				ADCA_IIN_L	,      											    20},\
    {ADC_ADCA_MODULE, 						ADC_SOC_NUMBER2, 				 ADC_TRIGGER_EPWM1_SOCA,   				ADCA_VIN_L,      											20},\
    {ADC_ADCA_MODULE, 						ADC_SOC_NUMBER3, 				 ADC_TRIGGER_EPWM1_SOCA,   				ADCA_VPFC_BUS,      									20},\
    {ADC_ADCC_MODULE, 						ADC_SOC_NUMBER0, 				 ADC_TRIGGER_EPWM1_SOCA,   				ADCC_PFC_I_SENSE_H,      						    20},\
    {ADC_ADCC_MODULE, 						ADC_SOC_NUMBER1, 				 ADC_TRIGGER_EPWM1_SOCA,   				ADCC_IIN_H,    										        20},\
    {ADC_ADCC_MODULE, 						ADC_SOC_NUMBER2, 				 ADC_TRIGGER_EPWM1_SOCA,   				ADCC_VIN_N,     											20},\
    {ADC_ADCC_MODULE, 						ADC_SOC_NUMBER3, 				 ADC_TRIGGER_EPWM1_SOCA,   				ADCC_PRI_TEMP,     										20},\
}
#else
#define ADC_CFG_SOC_TAB  \
{\
}
#endif

extern void bsw_mcal_adc_init(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================
