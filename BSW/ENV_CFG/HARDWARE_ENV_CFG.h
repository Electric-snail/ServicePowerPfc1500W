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

#define GPIO_LED_YELLOW              GpioNum(20)


/********Communication hardware configuration ***********/
#define 		GPIO_SCIB_TX                   		 				GPIO12_NUM
#define 		GPIO_MUX_SCIB_TX               				GpioMux(12,  SCIB_TX)

#define 		GPIO_SCIB_RX                   						GPIO13_NUM
#define 		GPIO_MUX_SCIB_RX               				GpioMux(13,  SCIB_RX)

#define 		RELAY_IN_CTR                						GPIO05_NUM

#define 		RELAY_IN_LATCH 									GPIO06_NUM

#define 		P_BUCK_OK                             				GPIO16_NUM
#define 		P_ALERT									   			GPIO33_NUM

#define       ADCC_PRI_TEMP              					   ADC_CH_ADCIN16
#define       GPIO_ADC_PRI_TEMP                         GPIO28_NUM

#define 		ADCA_VIN_L                      						ADC_CH_ADCIN9
//#define 		ADCA_VIN_N                     						ADC_CH_ADCIN10
#define       GPIO_ADC_VIN_L                                  AGPIO227_NUM

//#define 		ADCC_VIN_L                      						ADC_CH_ADCIN8
#define 		ADCC_VIN_N                     						ADC_CH_ADCIN10
#define       GPIO_ADC_VIN_N                                 AGPIO230_NUM

#define       ADCA_VPFC_BUS             						ADC_CH_ADCIN1

#define       ADCA_PFC_I_SENSE_L  						ADC_CH_ADCIN3
//#define       ADCC_PFC_I_SENSE_L 						ADC_CH_ADCIN5
#define      GPIO_ADC_PFC_I_SENSE_L				AGPIO242_NUM

//#define      ADCA_ PFC_I_SENSE_H						ADC_CH_ADCIN2
#define      ADCC_PFC_I_SENSE_H					       ADC_CH_ADCIN9
#define      GPIO_ADC_PFC_I_SENSE_H			   AGPIO224_NUM

#define         ADCA_IIN_L									   		ADC_CH_ADCIN15
//#define       ADCC_IIN_L											ADC_CH_ADCIN7

//#define       ADCA_IIN_H											ADC_CH_ADCIN11
#define        ADCC_IIN_H											ADC_CH_ADCIN0

#define      IL_CBB_CMP_IO										CMP1L_P_AGPIO224
#define      VPFC_OVP_CMP_IO								CMP3L_P_AIO244

#define       GPIO_PWM_PFC_DRV           			    GPIO00_NUM
#define       GPIO_MUX_EPWM1_A                         GpioMux(00,  EPWM1_A)
#define 		PFC_PWM_CHANNEL              				ePWM1_CHANNEL


#define    HW_ADC_REF_VOLT										3.3f
#define 	 FULL_RANGE_VIN_L										535.182f
#define 	VIN_N_OFFSET                     								-0.7f

#define 	 FULL_RANGE_VIN_N										535.182f
#define 	VIN_L_OFFSET                     								-0.7f

#define 	 FULL_RANGE_VPFC										509.465f
#define 	 HW_OFFSET_VPFC                      						0.0f

#define 	 FULL_RANGE_CUR_INDUCTOR_L								35.455f
#define 	 HW_OFFSET_CUR_INDUCTOR_L								0.017f

#define 	 FULL_RANGE_CUR_INDUCTOR_H								70.91f
#define 	 HW_OFFSET_CUR_INDUCTOR_H								0.0085f

#define 	 FULL_RANGE_IIN_L										35.455f
#define 	 HW_OFFSET_IIN_L                						0.017f

#define 	 FULL_RANGE_IIN_H										70.91f
#define 	 HW_OFFSET_IIN_H                						0.0085f

#endif /* BSW_BASIC_HARDWARE_BASIC_ENV_H_ */
