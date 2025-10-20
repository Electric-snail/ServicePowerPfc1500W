/*
 * ASW_BASIC.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#ifndef DLLX64
#include "DEBUG_PLATFORM/PARAMETER_CTRL/PARAMETER_CTRL.H"
#endif

#include "ASW_BASIC.h"
#include "HAL/HAL_INC/BSW_HAL_GPIO.h"
#include "DIAGNOSTIC/DIAGNOSTIC.h"
#include "MEASURE/MEASURE.h"
#include "DERATING/DERATING.h"
#include "SYS_FSM/SYS_FSM.h"
#include "POWER_FSM/POWER_FSM.h"
#include "PFC_CTR/PFC_CTR.H"
#include "VPFC_MGT/VPFC_MGT.H"


const ASW_INIT_ITEM_T gc_stAswInitTab[] = ASW_INIT_ITEM_TAB;

void asw_init(void) {
	unsigned char i = 0;
	const ASW_INIT_ITEM_T *p_asw_init_item = NULL;
	unsigned char u8AswInitNum = (unsigned char)(sizeof(gc_stAswInitTab) / sizeof(ASW_INIT_ITEM_T));
	for (i = 0; i < u8AswInitNum; i++) {
		p_asw_init_item = &gc_stAswInitTab[i];
		if ((p_asw_init_item->enable == 1) && (p_asw_init_item->pf_asw_init != 0x00000000)) {
			p_asw_init_item->pf_asw_init();
		}
	}
}

void asw_1msTask(void)
{
#if(SFRA_ENABLED == TRUE)
//    SFRA_RUN_BACKGROUND(&sfra);
//    SFRA_GUI_RUN_COMMS(&sfra);

//   TiSfraCollectDataTx();
#endif
}
