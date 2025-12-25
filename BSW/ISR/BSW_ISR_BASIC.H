/*
 * BSW_ISR_BASIC.H
 *
 *  Created on: 2025骞�8鏈�21鏃�
 *      Author: jhb72
 */

#ifndef BSW_ISR_BSW_ISR_BASIC_H_
#define BSW_ISR_BSW_ISR_BASIC_H_

#include "SOFTWARE_ENV_CFG.h"

typedef void(*IsrInitType)(void);

typedef struct
{
	IsrInitType pf_isr_init;    // Task process entity pointer
	UINT8       enable;			  // Task enable word
}ISR_INIT_ITEM_T;

#ifndef DLLX64
#define ISR_INIT_TAB \
{\
  {adc_isr_init,			1},\
}
#else
#define ISR_INIT_TAB \
{\
  {adc_isr_init,			1},\
}
#endif

extern void bsw_isr_init(void);



#endif /* BSW_ISR_BSW_ISR_BASIC_H_ */
