/*********************************************************************
File name:       BSW_MCAL_GPIO.h
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/

#ifndef BSW_MCAL_GPIO_H
#define BSW_MCAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../MCAL/BSW_MCAL_BASIC.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_GPIO_DEF.h"
#include "../CHIP_PACK/common/include/F28x_Project.h"
enum GPIO_OUTPUT_DATA
{
    GPIO_LOW  = 0,
    GPIO_HIGH = 1
};

enum GPIO_DIR
{
    GPIO_IN = 0,                   //!< Pin is a GPIO input
    GPIO_OUT,                      //!< Pin is a GPIO output
};

//*****************************************************************************
//
//! Values that can be passed to GPIO_setInterruptType() as the \e intType
//! parameter and returned from GPIO_getInterruptType().
//
//*****************************************************************************
enum GPIO_INT_Type
{
    GPIO_INT_FALLING_EDGE = 0x00,   //!< Interrupt on falling edge
    GPIO_INT_RISING_EDGE  = 0x04,   //!< Interrupt on rising edge
    GPIO_INT_BOTH_EDGES   = 0x0C,   //!< Interrupt on both edges
    GPIO_INT_INVALID      = 0xFF
};

//*****************************************************************************
//
//! Values that can be passed to GPIO_setQualificationMode() as the
//! \e qualification parameter and returned by GPIO_getQualificationMode().
//
//*****************************************************************************
typedef enum
{
    GPIO_QUAL_SYNC,                     //!< Synchronization to SYSCLK
    GPIO_QUAL_3SAMPLE,                  //!< Qualified with 3 samples
    GPIO_QUAL_6SAMPLE,                  //!< Qualified with 6 samples
    GPIO_QUAL_ASYNC                     //!< No synchronization
} GPIO_QualificationMode;

//*****************************************************************************
//
//! Values that can be passed to GPIO_setMasterCore() as the \e core parameter.
//
//*****************************************************************************
enum GPIO_CORE
{
    GPIO_CORE_CPU1,             //!< CPU1 selected as master core
    GPIO_CORE_CPU1_CLA1         //!< CPU1's CLA1 selected as master core
};

//*****************************************************************************
//
//! Values that can be passed to GPIO_readPortData(), GPIO_setPortPins(),
//! GPIO_clearPortPins(), and GPIO_togglePortPins() as the \e port parameter.
//
//*****************************************************************************
typedef enum
{
    GPIO_PORT_A = 0,                    //!< GPIO port A
    GPIO_PORT_B = 1,                    //!< GPIO port B
    GPIO_PORT_H = 7                     //!< GPIO port H
} GPIO_Port;

//*****************************************************************************
//
//! Values that can be passed to GPIO_setInterruptPin(),
//! GPIO_setInterruptType(), GPIO_getInterruptType(), GPIO_enableInterrupt(),
//! GPIO_disableInterrupt(), as the \e extIntNum parameter.
//
//*****************************************************************************
typedef enum
{
    GPIO_INT_XINT1,                     //!< External Interrupt 1
    GPIO_INT_XINT2,                     //!< External Interrupt 2
    GPIO_INT_XINT3,                     //!< External Interrupt 3
    GPIO_INT_XINT4,                     //!< External Interrupt 4
    GPIO_INT_XINT5                      //!< External Interrupt 5
} GPIO_ExternalIntNum;

struct GPIO_CFG_PARAM{
    enum GPIO_NUM         emGpioNum;
    enum GPIO_CORE        emGpioCore;
    enum GPIO_DIR         emGpioDirect;
    UINT16                u16CtrlValue;
    UINT16                flag;
    UINT16                u16GpioMux;
    UINT16                u16IntEnable;
    UINT16                u16AnalogEnable;
    enum GPIO_INT_Type    emIntType;
    enum GPIO_OUTPUT_DATA emOutputDataType;
};
#if defined (MCAN)
#define GPIO_0_MODE
#else

#endif


/*--GPIO_NUM--------------GPIO_CORE---------GPIO_DIR--u16OutValue-------flag------------------GPIO_MUX---u16IntEna--u16AnalogEnable--emIntType---emOutputDataType*/
#define GPIO_CFG_PARAM_TAB                \
{\
	 {GPIO_SCIB_RX,                  GPIO_CORE_CPU1,     GPIO_IN,                0,         GPIO_PUSHPULL|GPIO_PULLUP,     GPIO_MUX_SCIB_RX,                  0,             0,          GPIO_INT_INVALID,       GPIO_LOW},\
	 {GPIO_SCIB_TX,                  GPIO_CORE_CPU1,     GPIO_OUT,            0,         GPIO_PUSHPULL|GPIO_PULLUP,      GPIO_MUX_SCIB_TX,                  0,             0,           GPIO_INT_INVALID,       GPIO_LOW},\
	 {GPIO_LED_YELLOW,         GPIO_CORE_CPU1,     GPIO_OUT,            0,          GPIO_PUSHPULL|GPIO_PULLUP,     GPIO_IO,                                      0,             0,          GPIO_INT_INVALID,       GPIO_HIGH},\
}

#define PIN_AIO_224           224
#define AIO_DI_TYPE           0
#define AIO_AI_TYPE           1

#define AIO_SYN_SAMPLE        0
#define AIO_3_SAMPLE_POINTS   1
#define AIO_6_SAMPLE_POINTS   2
#define AI0_ASYN_SAMPLE       3

extern void bsw_mcal_gpio_init(void);

static inline void BSW_MCAL_GPIOSetHigh(enum GPIO_NUM emGpioNum)
{
    if(emGpioNum >= GPIO_MAX_NUM)
      return;

    GPIO_WritePin(emGpioNum, GPIO_HIGH);
}

static inline void BSW_MCAL_GPIOSetLow(enum GPIO_NUM emGpioNum)
{
    if(emGpioNum >= GPIO_MAX_NUM)
         return;

    GPIO_WritePin(emGpioNum, GPIO_LOW);
}

#define BSW_MCAL_GPIORead(emGpioNum)    GPIO_ReadPin((UINT16)emGpioNum)

#ifdef __cplusplus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================
