/*
 * VPFC_MGT.H
 *
 *  Created on: 2025Äê10ÔÂ20ÈÕ
 *      Author: Administrator
 */

#ifndef ASW_VPFC_MGT_VPFC_MGT_H_
#define ASW_VPFC_MGT_VPFC_MGT_H_

#define    VPFC_TARGET_DEFAULT						385

extern 	float g_f32VpfcSetTarget;

#define 		f32_get_vpfc_set_target()        					g_f32VpfcSetTarget

extern 	void 	vpfc_mgt_init(void);


#endif /* ASW_VPFC_MGT_VPFC_MGT_H_ */
