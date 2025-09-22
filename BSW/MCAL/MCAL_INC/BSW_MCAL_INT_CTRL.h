/*********************************************************************
File name:       BSW_MCAL_INT_CTRL.h

 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/

#ifndef BSW_MCAL_INT_H
#define BSW_MCAL_INT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "CHIP_PACK/common/include/F28x_Project.h"
#include "MCAL/BSW_MCAL_BASIC.h"


enum INT_VECT_X{
    INT_X1 = 1,
    INT_X2 = 2,
    INT_X3 = 3,
    INT_X4 = 4,
    INT_X5 = 5,
    INT_X6 = 6,
    INT_X7 = 7,
    INT_X8 = 8,
    INT_X9 = 9,
    INT_X10 = 10,
    INT_X11 = 11,
    INT_X12 = 12,
    INT_X13 = 13,
    INT_X14 = 14,
    INT_X15 = 15,
    INT_X16 = 16,
    INT_X_MAX
};

enum INT_VECT_Y{
    INT_Y_INVALID = 0,
    INT_Y1 = 1,
    INT_Y2 = 2,
    INT_Y3 = 3,
    INT_Y4 = 4,
    INT_Y5 = 5,
    INT_Y6 = 6,
    INT_Y7 = 7,
    INT_Y8 = 8,
    INT_Y9 = 9,
    INT_Y10 = 10,
    INT_Y11 = 11,
    INT_Y12 = 12,
    INT_Y13 = 13,
    INT_Y14 = 14,
    INT_Y15 = 15,
    INT_Y16 = 16,
    INT_Y_MAX,
};

typedef struct{
    PINT                fp_isr;
    enum INT_VECT_X     emINTx;
    enum INT_VECT_Y     emINTy;
}INT_PARAM_CFG;

//fp_isr:it means the isr function,    INTx,y;u16INTy: the interrupt group
//u16INTy:If it is the peripheral interrupt, it is the sub interrupt index.
//The PIE Channel mapping and CPU Interrupt vectors in datasheet can be checked.
/*----fp_isr-----------emINTx----------emINTy----------*/
#define REG_INT_PARAM_CFG_TAB                               \
{\
    {&IsrCpuTimer2,     INT_X14,      INT_Y_INVALID},     	\
  /*  {&adcA1ISR,              INT_X1,         INT_Y1},*/            \
}

extern void bsw_mcal_pie_ctrl_init(void);

#define bsw_mcal_enable_global_int()            		 EINT
#define bsw_mcal_disable_global_int()                 DINT

#ifdef __cplusplus
}
#endif // extern "C"

#endif
//===========================================================================
// End of file.
//===========================================================================
