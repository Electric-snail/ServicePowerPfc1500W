/*
 * BSW_MACL_XBAR.h
 *
 *  Created on: 2022/8/9
 *      Author: rjgslg
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_XBAR_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_XBAR_H_

#include <BSW/MCAL/MCAL_INC/BSW_MCAL_GPIO_DEF.h>
#include <BSW/MCAL/BSW_MCAL_BASIC.h>
#include <BSW/ENV_CFG/HARDWARE_ENV_CFG.h>

#define XBAR_MUX00                     0 //!< Mask for X-BAR mux 0
#define XBAR_MUX01                     1 //!< Mask for X-BAR mux 1
#define XBAR_MUX02                     2 //!< Mask for X-BAR mux 2
#define XBAR_MUX03                     3 //!< Mask for X-BAR mux 3
#define XBAR_MUX04                     4 //!< Mask for X-BAR mux 4
#define XBAR_MUX05                     5 //!< Mask for X-BAR mux 5
#define XBAR_MUX06                     6 //!< Mask for X-BAR mux 6
#define XBAR_MUX07                     7 //!< Mask for X-BAR mux 7
#define XBAR_MUX08                     8 //!< Mask for X-BAR mux 8
#define XBAR_MUX09                     9 //!< Mask for X-BAR mux 9
#define XBAR_MUX10                     10 //!< Mask for X-BAR mux 10
#define XBAR_MUX11                     11 //!< Mask for X-BAR mux 11
#define XBAR_MUX12                     12 //!< Mask for X-BAR mux 12
#define XBAR_MUX13                     13 //!< Mask for X-BAR mux 13
#define XBAR_MUX14                     14 //!< Mask for X-BAR mux 14
#define XBAR_MUX15                     15 //!< Mask for X-BAR mux 15
#define XBAR_MUX16                     16 //!< Mask for X-BAR mux 16
#define XBAR_MUX17                     17 //!< Mask for X-BAR mux 17
#define XBAR_MUX18                     18 //!< Mask for X-BAR mux 18
#define XBAR_MUX19                     19 //!< Mask for X-BAR mux 19
#define XBAR_MUX20                     20 //!< Mask for X-BAR mux 20
#define XBAR_MUX21                     21 //!< Mask for X-BAR mux 21
#define XBAR_MUX22                     22 //!< Mask for X-BAR mux 22
#define XBAR_MUX23                     23 //!< Mask for X-BAR mux 23
#define XBAR_MUX24                     24 //!< Mask for X-BAR mux 24
#define XBAR_MUX25                     25 //!< Mask for X-BAR mux 25
#define XBAR_MUX26                     26 //!< Mask for X-BAR mux 26
#define XBAR_MUX27                     27 //!< Mask for X-BAR mux 27
#define XBAR_MUX28                     28 //!< Mask for X-BAR mux 28
#define XBAR_MUX29                     29 //!< Mask for X-BAR mux 29
#define XBAR_MUX30                     30 //!< Mask for X-BAR mux 30
#define XBAR_MUX31                     31 //!< Mask for X-BAR mux 31

#define ADCAEVT1                       2
#define INPUTXBAR1                     1
#define INPUTXBAR4_XBAR_MUX7           1
#define CMP3_CTRIP_H_OR_L_XBAR_MUX4    1

#define  TRIPX_INV_H_ACTIVE            0x00
#define  TRIP4_INV                     0x01   //low  active
#define  TRIP5_INV                     0x02
#define  TRIP7_INV                     0x04
#define  TRIP8_INV                     0x08
#define  TRIP9_INV                     0x10
#define  TRIP10_INV                    0x20
#define  TRIP11_INV                    0x40
#define  TRIP12_INV                    0x80

#define  XINT_DISABLED                 0
#define  XINT_ENABLED                  1

#define  XINT_POLARITY_DEF_NEGATIVE    0
#define  XINT_POLARITY_POSITIVE        1
#define  XINT_POLARITY_NEGATIVE        2
#define  XINT_POLARITY_ALL             3
typedef enum
{
    XBAR_INPUT1,            //!< ePWM[TZ1], ePWM[TRIP1], X-BARs, eCAPs
    XBAR_INPUT2,            //!< ePWM[TZ2], ePWM[TRIP2], X-BARs, eCAPs
    XBAR_INPUT3,            //!< ePWM[TZ3], ePWM[TRIP3], X-BARs, eCAPs
    XBAR_INPUT4,            //!< ADC wrappers, X-BARs, XINT1, eCAPs
    XBAR_INPUT5,            //!< EXTSYNCIN1, X-BARs, XINT2, eCAPs
    XBAR_INPUT6,            //!< EXTSYNCIN2, ePWM[TRIP6], X-BARs, XINT3, eCAPs
    XBAR_INPUT7,            //!< X-BARs, eCAPs
    XBAR_INPUT8,            //!< X-BARs, eCAPs
    XBAR_INPUT9,            //!< X-BARs, eCAPs
    XBAR_INPUT10,           //!< X-BARs, eCAPs
    XBAR_INPUT11,           //!< X-BARs, eCAPs
    XBAR_INPUT12,           //!< X-BARs, eCAPs
    XBAR_INPUT13,           //!< XINT4, X-BARs, eCAPs
    XBAR_INPUT14,           //!< XINT5, X-BARs, eCAPs
    XBAR_INPUT15,           //!< eCAPs
    XBAR_INPUT16            //!< eCAPs
} XBAR_InputNum;

typedef enum
{
    XBAR_TRIP4  = 0,        //!< TRIP4 of the ePWM X-BAR
    XBAR_TRIP5  = 4,        //!< TRIP5 of the ePWM X-BAR
    XBAR_TRIP7  = 8,        //!< TRIP7 of the ePWM X-BAR
    XBAR_TRIP8  = 12,        //!< TRIP8 of the ePWM X-BAR
    XBAR_TRIP9  = 16,        //!< TRIP9 of the ePWM X-BAR
    XBAR_TRIP10 = 20,       //!< TRIP10 of the ePWM X-BAR
    XBAR_TRIP11 = 24,       //!< TRIP11 of the ePWM X-BAR
    XBAR_TRIP12 = 28        //!< TRIP12 of the ePWM X-BAR
} XBAR_TripNum;

typedef enum
{
    XINT1  = 0,        //!< INPUT4
    XINT2  = 1,        //!< INPUT5
    XINT3  = 2,        //!< INPUT6
    XINT4  = 3,        //!< INPUT13
    XINT5  = 4,        //!< INPUT4
} XINTx_Num;

struct XBAR_INPUTNUM_CFG_PARAM{
    XBAR_InputNum         emInputSelect;
    enum GPIO_NUM         emGpioNum;
};

struct XBAR_EPWM_CFG_PARAM{
    XBAR_TripNum         emTripNum;
    UINT16               MUXES_NUM_VAL   :5;
    UINT16               MUXES_VAL       :2;
    UINT16               MUX_ENABLE_VAL  :1;
    UINT16               TRIPOUTINV_VAL  :8;
};

struct XINTx_CFG_PARAM{
    XINTx_Num         emXintSelect;
    UINT16            CR_ENABLE_VAL   :1;
    UINT16            CR_POLARITY_VAL :2;
    UINT16            reserve         :13;
};

/*--emInputSelect-----emGpioNum--*/
#define INPUT_XBAR_CFG_TAB  \
{\
   /* {XBAR_INPUT4, GPIO_HW_Protect_Lock},*/\
}
/*--emTripNum----MUXES_NUM_VAL--MUXES_VAL-----------------MUX_ENABLE_VAL--TRIPOUTINV_VAL-*/
#define EPWM_XBAR_CFG_TAB  \
{\
    {XBAR_TRIP4, XBAR_MUX07,   INPUTXBAR4_XBAR_MUX7,         1,            TRIPX_INV_H_ACTIVE},\
    {XBAR_TRIP4, XBAR_MUX04,   CMP3_CTRIP_H_OR_L_XBAR_MUX4,  1,            TRIPX_INV_H_ACTIVE},\
}

/*--XINTx_Num----CR_ENABLE_VAL-----CR_POLARITY_VAL--------reserve-*/
#define XINTX_CFG_TAB  \
{\
    {XINT1,      XINT_ENABLED,  XINT_POLARITY_POSITIVE,       0}\
}

extern void BSW_MCAL_xBarInit(void);

#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_XBAR_H_ */
