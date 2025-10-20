/*
 * POWER_CALC.H
 *
 *  Created on: 2025Äê9ÔÂ30ÈÕ
 *      Author: Administrator
 */

#ifndef PUBLIC_PUBLIC_INC_POWER_CALC_H_
#define PUBLIC_PUBLIC_INC_POWER_CALC_H_

typedef struct{
    float              f32Var;
    signed short       i16Pol;
}RMS_CALC_IN_T;

typedef struct{
    float              f32SqartSum;
    signed short       i16LastPol;
    unsigned short     u16N;
}RMS_CALC_INNER_T;

typedef struct{
    float                   f32Rms;
}RMS_CALC_OUT_T;

typedef struct{
    float                   f32VarTrans;
}POL_FRQ_CALC_IN_T;

typedef struct{
    unsigned short   u16PosN;
    unsigned short   u16NegN;
}POL_FRQ_INNER_T;

typedef struct{
    unsigned short   u16Pol;
    unsigned short   u16Type;
    float            f32Frq;
}POL_FRQ_OUT_T;

typedef struct{
	POL_FRQ_CALC_IN_T         	stIn;
	POL_FRQ_INNER_T           	stInner;
	POL_FRQ_OUT_T           	stOut;
}POL_FRQ_CALC_OBJ_T;

typedef struct{
    RMS_CALC_IN_T          stIn;
    RMS_CALC_INNER_T       stInner;
    RMS_CALC_OUT_T         stOut;
}RMS_CALC_OBJ_T;


typedef struct {
    float              f32Var;
    signed short       i16Pol;
}AVE_CALC_IN_T;

typedef struct {
    float              f32Sum;
    signed short       i16LastPol;
    unsigned short     u16N;
}AVE_CALC_INNER_T;

typedef struct {
    float                   f32Ave;
}AVE_CALC_OUT_T;

typedef struct {
   AVE_CALC_IN_T          stIn;
   AVE_CALC_INNER_T       stInner;
   AVE_CALC_OUT_T         stOut;
}AVE_CALC_OBJ_T;

#define               AC_TYPE                                                         0
#define               DC_TYPE                                                         1

extern void 	RmsCal(RMS_CALC_OBJ_T *p_stRmsObj);
extern void 	AveCal(AVE_CALC_OBJ_T* p_stAveObj);
extern void 	PolFrqCalc(POL_FRQ_CALC_OBJ_T *p_stPolFrqObj);

#endif /* PUBLIC_PUBLIC_INC_POWER_CALC_H_ */
