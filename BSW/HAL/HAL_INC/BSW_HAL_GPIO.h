/*
 * BSW_HAL_GPIO.h
 *
 *  Created on: 2022/8/11/
 *      Author: nj7vgg
 */

#ifndef BSW_HAL_GPIO_H_
#define BSW_HAL_GPIO_H_
#ifndef DLLX64
#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL/MCAL_INC/BSW_MCAL_GPIO_DEF.h"
#endif
#include "ENV_CFG/HARDWARE_ENV_CFG.h"

#ifndef DLLX64
//LAUNCHXL BOARD
#define BSW_HAL_YELLOW_ON()                     GpioSet(A, 20)
#define BSW_HAL_YELLOW_OFF()                    GpioClear(A, 20)

//#define BSW_HAL_GREEN_ON()                   GpioSet(B, 49)
//#define BSW_HAL_GREEN_OFF()                  GpioClear(B, 49)

//OUTPUT
//feed watchdog signal
#define BSW_HAL_DSP_FEED_WD_H()
#define BSW_HAL_DSP_FEED_WD_L()

//CAN transceiver Standby mode control
#define BSW_HAL_CAN_STB_MODE_DIS()           GpioSet(B,49)
#define BSW_HAL_CAN_STB_MODE_EN()            GpioClear(B,49)

//Auxiliary source secondary 15V enable
#define BSW_HAL_DSP_SecAux15V_EN()              GpioSet(A,17)    //
#define BSW_HAL_DSP_SecAux15V_DIS()             GpioClear(A,17)

//Auxiliary source secondary 5V enable
#define BSW_HAL_DSP_SecAux5V_EN()              GpioSet(A,29)    //
#define BSW_HAL_DSP_SecAux5V_DIS()             GpioClear(A,29)

//Hardware protected reset
#define BSW_HAL_HwProtect_Reset_EN()         GpioSet(A,25)    //
#define BSW_HAL_HwProtect_Reset_DIS()        GpioClear(A,25)

//Fault wake-up of external BMU
#define BSW_HAL_Fault_WakeUp_BMU_EN()        GpioSet(A,26)    //
#define BSW_HAL_Fault_WakeUp_BMU_DIS()       GpioClear(A,26)

//Low voltage battery sampling enable
#define BSW_HAL_LVDC_VBAT_SAMP_EN()          GpioSet(A,27)    //
#define BSW_HAL_LVDC_VBAT_SAMP_DIS()         GpioClear(A,27)

//Auxiliary power supply enable unlock
#define BSW_HAL_DSP_AUX_CLOSE_EN()          GpioSet(B,42)    //
#define BSW_HAL_DSP_AUX_CLOSE_DIS()         GpioClear(B,42)

//Low voltage B2B MOS enable control
#define BSW_HAL_LVDC_B2B_MOS_EN()            GpioSet(A,8)    //
#define BSW_HAL_LVDC_B2B_MOS_DIS()           GpioClear(A,8)

//High voltage input voltage sampling enable
#define BSW_HVDC_VIN_SAMP_EN()               GpioSet(H,224)    //
#define BSW_HVDC_VIN_SAMP_DIS()              GpioClear(H,224)

#define CAN_STANDBY_MODE()                   BSW_HAL_CAN_STB_MODE_EN()
#define CAN_NORMAL_MODE()                    BSW_HAL_CAN_STB_MODE_DIS()

#define GPIO_ReadPin_HWP_LOCK_TZ()           GpioDataRegs.GPADAT.bit.GPIO6
#define GPIO_ReadPin_HW_VOUT_OVP()           GpioDataRegs.GPADAT.bit.GPIO14
#define GPIO_ReadPin_HW_VOUT_UVP()           GpioDataRegs.GPADAT.bit.GPIO15
#define GPIO_ReadPin_HW_IOUT_OCP()           GpioDataRegs.GPBDAT.bit.GPIO34
#define GPIO_ReadPin_HVIN_OCP_SGNL()         GpioDataRegs.GPADAT.bit.GPIO23
#define GPIO_ReadPin_EX_HW_ONOFF_CMD()       GpioDataRegs.GPADAT.bit.GPIO22

#else

typedef struct {
	unsigned short Num00;
	unsigned short Num01;
	unsigned short Num02;
	unsigned short Num03;
	unsigned short Num04;
	unsigned short Num05;
	unsigned short Num06;
	unsigned short Num07;
	unsigned short Num08;
	unsigned short Num09;
	unsigned short Num10;
	unsigned short Num11;
	unsigned short Num12;
	unsigned short Num13;
	unsigned short Num14;
	unsigned short Num15;
	unsigned short Num16;
	unsigned short Num17;
	unsigned short Num18;
	unsigned short Num19;
	unsigned short Num20;
	unsigned short Num21;
	unsigned short Num22;
	unsigned short Num23;
	unsigned short Num24;
	unsigned short Num25;
	unsigned short Num26;
	unsigned short Num27;
	unsigned short Num28;
	unsigned short Num29;
	unsigned short Num30;
	unsigned short Num31;
}SIM_GPIOA_T;

typedef struct {
	unsigned short Num32;
	unsigned short Num33;
	unsigned short Num34;
	unsigned short Num35;
	unsigned short Num36;
	unsigned short Num37;
	unsigned short Num38;
	unsigned short Num39;
	unsigned short Num40;
	unsigned short Num41;
	unsigned short Num42;
	unsigned short Num43;
	unsigned short Num44;
	unsigned short Num45;
	unsigned short Num46;
	unsigned short Num47;
	unsigned short Num48;
	unsigned short Num49;
	unsigned short Num50;
	unsigned short Num51;
	unsigned short Num52;
	unsigned short Num53;
	unsigned short Num54;
	unsigned short Num55;
	unsigned short Num56;
	unsigned short Num57;
	unsigned short Num58;
	unsigned short Num59;
	unsigned short Num60;
	unsigned short Num61;
	unsigned short Num62;
	unsigned short Num63;
}SIM_GPIOB_T;

typedef struct {
	unsigned short Num224;
	unsigned short Num225;
	unsigned short Num226;
	unsigned short Num227;
	unsigned short Num228;
	unsigned short Num229;
	unsigned short Num230;
	unsigned short Num231;
	unsigned short Num232;
	unsigned short Num233;
	unsigned short Num234;
	unsigned short Num235;
	unsigned short Num236;
	unsigned short Num237;
	unsigned short Num238;
	unsigned short Num239;
	unsigned short Num240;
	unsigned short Num241;
	unsigned short Num242;
	unsigned short Num243;
	unsigned short Num244;
	unsigned short Num245;
	unsigned short Num246;
	unsigned short Num247;
	unsigned short Num248;
	unsigned short Num249;
	unsigned short Num250;
	unsigned short Num251;
	unsigned short Num252;
	unsigned short Num253;
	unsigned short Num254;
	unsigned short Num255;
}SIM_GPIOH_T;

extern SIM_GPIOA_T g_stGpioA;
extern SIM_GPIOB_T g_stGpioB;
extern SIM_GPIOH_T g_stGpioH;
 //LAUNCHXL BOARD
#define BSW_HAL_YELLOW_ON()                      g_stGpioB.Num20 = 1
#define BSW_HAL_YELLOW_OFF()                     g_stGpioB.Num20 = 0


#endif

#endif /*BSW_HAL_GPIO_H_ */
