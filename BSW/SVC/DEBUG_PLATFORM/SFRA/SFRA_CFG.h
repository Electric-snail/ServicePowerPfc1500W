/*
 * SFRA_CFG.h
 *
 *  Created on: 2023Äê7ÔÂ28ÈÕ
 *      Author: xj8r1j
 */

#ifndef _SFRA_SFRA_CFG_H_
#define _SFRA_SFRA_CFG_H_
#include "../SFRA/SFRA_DEFINE.h"

#ifndef SFRA_VAR_DECLAR
#define SFRA_VAR_DECLAR
extern float            g_f32Vout1;
extern float            g_f32Vout2;
#endif

SFRA_INJECT(g_f32Vout1)
SFRA_COLLECT(LPF, g_f32Vout1, g_f32Vout2)
SFRA_COLLECT(HPF, g_f32Vout1, g_f32Vout2)
#endif /* BSW_SVC_DEBUGPLATFORM_SFRA_SFRA_CFG_H_ */
