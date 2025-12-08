/*
 * VPFC_MGT.C
 *
 *  Created on: 2025Äê10ÔÂ20ÈÕ
 *      Author: Administrator
 */
#include "VPFC_MGT/VPFC_MGT.H"

float g_f32VpfcSetTarget = 0;


void vpfc_mgt_init(void){
	g_f32VpfcSetTarget = VPFC_TARGET_DEFAULT;
}


