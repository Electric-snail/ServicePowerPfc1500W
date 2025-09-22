/*
 * HARDWARE_ENV_CFG.h
 *
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 */

#ifndef BSW_BASIC_HARDWARE_BASIC_ENV_H_
#define BSW_BASIC_HARDWARE_BASIC_ENV_H_

#define   LAUNCHPAD
#define   VREFHIX_EX_EN                1

/*******GPIO hardware configuration *************/
/*AGPIO - EPWM*/
#define GPIO_EPWM3_A                   AGPIO227_NUM
#define GPIO_EPWM3_B                   AGPIO230_NUM

/*AGPIO - ADC*/
#define GPIO_ADC_HW_VER                GPIO28_NUM
#define GPIO_ADC_1V24                  GPIO12_NUM
#define GPIO_ADC_HW_WAKEUP             AGPIO242_NUM

/*AGPIO - CMPSS*/
#define GPIO_CMP3_OUT_V_R              AGPIO226_NUM
#define GPIO_CMP1_OUT_I                AGPIO228_NUM

#define GPIO_LED_YELLOW              GpioNum(20)
/* GPIOx_NUM or AIOx_Num, x it means the number of GPIO,notes: for x = 1, it must write as GPIO01 ***/


/*******ADC relative hardware configuration *********/
#define ADCA_HW_VER                    ADC_CH_ADCIN16
#define ADCA_OUT_V                     ADC_CH_ADCIN14   //LVDC2
#define ADCA_BAT_V                     ADC_CH_ADCIN1
#define ADCA_CASE_T                    ADC_CH_ADCIN12
#define ADCA_LVSEC_T                   ADC_CH_ADCIN8
#define ADCA_HW_WAKEUP                 ADC_CH_ADCIN3

#define ADCC_OUT_I                     ADC_CH_ADCIN0
#define ADCC_OUT_V_R                   ADC_CH_ADCIN2     //LVDC1
#define ADCC_HVIN_V                    ADC_CH_ADCIN15
#define ADCC_HVPRI_T                   ADC_CH_ADCIN3
#define ADCC_1V24_V                    ADC_CH_ADCIN20


/*c*/


//Protection latch GPIO hardware connect definition


/********Communication hardware configuration ***********/
#define GPIO_SCIB_TX                   		GPIO12_NUM
#define GPIO_MUX_SCIB_TX                GpioMux(12,  SCIB_TX)

#define GPIO_SCIB_RX                   		GPIO13_NUM
#define GPIO_MUX_SCIB_RX                GpioMux(13,  SCIB_RX)


#define     HW_VERSION                  0xB3

#endif /* BSW_BASIC_HARDWARE_BASIC_ENV_H_ */
