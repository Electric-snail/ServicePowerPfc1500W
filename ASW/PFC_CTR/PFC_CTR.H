/*
 * PFC_CTR.H
 *
 *  Created on: 2025Äê9ÔÂ30ÈÕ
 *      Author: Administrator
 */

#ifndef ASW_PFC_CTR_PFC_CTR_H_
#define ASW_PFC_CTR_PFC_CTR_H_


#define               NOTICH_FILT_ENABLE				1
#define				f32_get_pwm_duty()                         0.5f


extern		void 		pfc_controller(void);
extern		void 		pfc_controller_init(void);
#endif /* ASW_PFC_CTR_PFC_CTR_H_ */
