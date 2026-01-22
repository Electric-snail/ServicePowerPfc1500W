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
    float            			f32Frq;
    float                    f32SinOmegT;
    float                    f32CosOmegT;
    float                    f32Sin2OmegT;
    float                    f32Cos2OmegT;
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
   AVE_CALC_IN_T               stIn;
   AVE_CALC_INNER_T       stInner;
   AVE_CALC_OUT_T           stOut;
}AVE_CALC_OBJ_T;

typedef struct {
    float            f32VinAbsTrans;
}VIN_DROP_DIG_IN_T;

typedef struct {
    float           		  f32DropTransThrd;
    unsigned short u16DropWarnCntThrd;
    unsigned short u16DropFaultCntThrd;
    unsigned short u16DropRecvCntThrd;
}VIN_DROP_DIG_COFF_T;

typedef struct {
    unsigned short     u16DropN;
    unsigned short     u16RecvN;
}VIN_DROP_DIG_INNER_T;

typedef struct {
   unsigned short u16VinDropWarnFlag;
   unsigned short u16VinDropFaultFlag;
}VIN_DROP_DIG_OUT_T;

typedef struct {
	VIN_DROP_DIG_IN_T             stIn;
	VIN_DROP_DIG_COFF_T       stCoff;
	VIN_DROP_DIG_INNER_T     stInner;
	VIN_DROP_DIG_OUT_T         stOut;
}VIN_DROP_DIG_OBJ_T;

#define              INVALID_TYPE                                                0xFF
#define               AC_TYPE                                                         0
#define               DC_TYPE                                                         1

extern void 	rms_calc(RMS_CALC_OBJ_T 							*p_stRmsObj);
extern void 	average_calc(AVE_CALC_OBJ_T					*p_stAveObj);
extern void 	pol_freq_calc(POL_FRQ_CALC_OBJ_T 			*p_stPolFrqObj);
extern void 	vin_drop_diag(VIN_DROP_DIG_OBJ_T 			*p_stVinDropObj);

#endif /* PUBLIC_PUBLIC_INC_POWER_CALC_H_ */
