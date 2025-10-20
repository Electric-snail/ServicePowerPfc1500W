/*
 * PFC_CTR.H
 *
 *  Created on: 2025Äê9ÔÂ30ÈÕ
 *      Author: Administrator
 */

#ifndef ASW_PFC_CTR_PFC_CTR_H_
#define ASW_PFC_CTR_PFC_CTR_H_

typedef struct {
	float f32VinPll;
	float f32Duty;
}PFC_CTR_OUT;

extern PFC_CTR_OUT				g_stPfcOut;

#define             NOTICH_FILT_ENABLE				TRUE
#define				f32_get_pwm_duty()             g_stPfcOut.f32Duty
#define              f32_get_vin_pll_out()          g_stPfcOut.f32VinPll

extern		void 		pfc_controller(void);
extern		void 		pfc_controller_init(void);
#endif /* ASW_PFC_CTR_PFC_CTR_H_ */
