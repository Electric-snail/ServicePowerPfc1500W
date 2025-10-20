
/*
 * BSW_SVC_BASIC.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */
#ifndef DLLX64
#include "BSW_MCAL_BASIC.H"
#include "DP_STACK/APL/APL_STACK.H"
#include "DEBUG_PLATFORM/PARAMETER_CTRL/PARAMETER_CTRL.H"
#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE.H"
#endif

#include "BSW_SVC_BASIC.h"
#include "ISR_INC/BSW_ISR_ADC.h"
#include "TASK/BSW_TASK_SERVICE.h"
#include "STORAGE/BSW_SVC_STORAGE.h"

const SVC_INIT_ITEM_T gc_stSvcInitTab[] = SVC_INIT_TAB;

void bsw_svc_init(void) {
	unsigned char i = 0;
	const SVC_INIT_ITEM_T *p_svc_init_item = NULL;
	unsigned char u8SvcInitNum = (unsigned char)(sizeof(gc_stSvcInitTab) / sizeof(SVC_INIT_ITEM_T));
	for (i = 0; i < u8SvcInitNum; i++) {
		p_svc_init_item = &gc_stSvcInitTab[i];
		if ((p_svc_init_item->enable == 1) && (p_svc_init_item->pf_svc_init != 0x00000000)) {
			p_svc_init_item->pf_svc_init();
		}
	}
}
