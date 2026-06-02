/*
 * CLARK_PARK.H
 *
 *  Created on: 2026Äê3ÔÂ30ÈÕ
 *      Author: Administrator
 */

#ifndef PUBLIC_PUBLIC_INC_CLARK_PARK_H_
#define PUBLIC_PUBLIC_INC_CLARK_PARK_H_

typedef struct
{
float phase_a;
float phase_b;
float phase_c;

float f32Alpha;
float f32Beta;

float f32D;
float f32Q;

float f32SinOmeg;
float f32CosOmeg;
}CLARK_PARK_T;

extern void park_conv(CLARK_PARK_T *p_stClarkPart);
extern void ipark_conv(CLARK_PARK_T *p_stClarkPart);

extern void clarke_conv(CLARK_PARK_T *p_stClarkPart);
extern void iclarke_conv(CLARK_PARK_T *p_stClarkPart);

#define ipark_conv_macro(stClarkPart)	\
		stClarkPart.f32Alpha =stClarkPart.f32CosOmeg *  stClarkPart.f32D -  stClarkPart.f32SinOmeg*stClarkPart.f32Q;	\
		stClarkPart.f32Beta   =stClarkPart.f32SinOmeg  *  stClarkPart.f32D + stClarkPart.f32CosOmeg*stClarkPart.f32CosOmeg;

#define park_conv_macro(stClarkPart)	\
		stClarkPart.f32D   = stClarkPart.f32CosOmeg  *  stClarkPart.f32Alpha +  stClarkPart.f32SinOmeg*stClarkPart.f32Beta;	\
	    stClarkPart.f32Q   = -stClarkPart.f32SinOmeg  *  stClarkPart.f32Alpha + stClarkPart.f32CosOmeg*stClarkPart.f32Beta;

#endif /* PUBLIC_PUBLIC_INC_CLARK_PARK_H_ */
