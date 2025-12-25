/*
 * BSW_ISR_BASIC.C
 *
 *  Created on: 2025.8.21
 *      Author:  Hongbo.Jiang
 */
#include "ISR_INC/BSW_ISR_ADC.h"
#include "BSW_ISR_BASIC.H"

const ISR_INIT_ITEM_T gc_stIsrInitTab[] = ISR_INIT_TAB;

void bsw_isr_init(void) {
    unsigned char i = 0;
    const ISR_INIT_ITEM_T* p_isr_init_item = NULL;
    unsigned char u8IsrInitNum = (unsigned char)(sizeof(gc_stIsrInitTab) / sizeof(ISR_INIT_ITEM_T));
    for (i = 0; i < u8IsrInitNum; i++) {
        p_isr_init_item = &gc_stIsrInitTab[i];
        if ((p_isr_init_item->enable == 1) && (p_isr_init_item->pf_isr_init != 0x00000000)) {
            p_isr_init_item->pf_isr_init();
        }
    }
}
