/*
 *   DC_MATH.H
 *
 *  Created on: 2024年8月28日
 *      Author: xj8r1j
 */

#ifndef PUBLIC_PUBLIC_INC_DC_MATH_H_
#define PUBLIC_PUBLIC_INC_DC_MATH_H_

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

#ifdef DLLX64
#include "math.h"
#define __divf32(f32A, f32B)       (float)((float)f32A/((float)f32B)) 
#define fabsf(f32Value)            (float)fabs(f32Value)
#endif

typedef struct
{
    FLOAT32 Kp;
    FLOAT32 Ki;
    FLOAT32 OldErr;
    FLOAT32 Out;
} PI_Ctrl_T;

typedef struct{
    FLOAT32     k;
    FLOAT32     b2;
    FLOAT32     b1;
    FLOAT32     b0;
    FLOAT32     a3;
    FLOAT32     a2;
    FLOAT32     a1;
} Loop2Z3P_COEFF;

typedef struct{
    FLOAT32                 x[3];                // Loop controller input data storage
    FLOAT32                 y[4];                // Loop controller output data storage
    FLOAT32                 Out;                // Loop controller output data storage
    Loop2Z3P_COEFF   loop2z3p_coeff; // Loop controller  coeffcient structure
}CTRL_2Z3P_VARS_T;

typedef struct {
    float f32Kp;
    float f32Ki;
    float f32Ts;
    float f32KiTs;        //调速早期可以分别用Ts, Ki 这两个独立变量，后期可以合并成一个
    float f32ErrN;
    float f32ErrN_1;
    float f32YN;
    float f32YN_1;
    float f32Ref;
    float f32Fb;
    float f32ErrMax;
    float f32ErrMin;
    float f32OutMax;
    float f32OutMin;
}PI_INC_CTRL_PARAM_T;

typedef struct{
    float f32Ref;
    float f32Fb;
}PI_POS_IN_T;

typedef struct{
    float f32Kp;
    float f32KiTs;
    float f32IntegrateMax;
     float f32IntegrateMin;
     float f32OutMax;
     float f32OutMin;
}PI_POS_COFF_T;

typedef struct{
    float f32Err;
    float f32Integrate;
}PI_POS_INNER_T;

typedef struct{
    float f32Out;
}PI_POS_OUT_T;


typedef struct {
	PI_POS_IN_T 				stIn;
	PI_POS_COFF_T			stCoff;
	PI_POS_INNER_T 		stInner;
	PI_POS_OUT_T           stOut;
}PI_POS_T;

typedef struct {
    float f32Ref;
    float f32Fb;
    float f32Gain;
}PI_POS_GAIN_IN_T;

typedef struct {
    PI_POS_GAIN_IN_T 		stIn;
    PI_POS_COFF_T			stCoff;
    PI_POS_INNER_T 		    stInner;
    PI_POS_OUT_T            stOut;
}PI_GAIN_POS_T;

#define RefTargeSoftStart(RefVal, Step, CurVal)\
{\
    if      ((CurVal + Step) < RefVal) CurVal = CurVal + Step;\
    else if (CurVal > (RefVal + Step)) CurVal = CurVal - Step;\
    else                               CurVal = RefVal;       \
}

#define Limit(In, min, max)         ((In > max) ? max : ((In > min) ? In : min))
#define Min(A, B)                   ((A > B) ? B : A)
#define Max(A, B)                   ((A < B) ? B : A)

//#define Limit(In, min, max)       __fsat(In, min, max)


FLOAT32 Loop_PiCtrl(PI_Ctrl_T* PI, FLOAT32 errVal);
void Ctrl2z3p(CTRL_2Z3P_VARS_T *loop2p2z_obj, FLOAT32 errVal);


typedef struct
{
    /* Coefficients */
    float coeffB0;
    float coeffB1;
    float coeffB2;
    float coeffA1;
    float coeffA2;
    float coeffOutMax;
    float coeffOutMin;
} Ctrl2Z2PCoeffs;

typedef struct
{
    float deltaOut;
    float out1;
    float out2;

    float err;
    float err1;
    float err2;
    /* Inputs*/
    float ref;
    float fdbk;
    float out;
} CTRL_2Z2P_VARS_T;

void Ctrl2z2p(CTRL_2Z2P_VARS_T * v, Ctrl2Z2PCoeffs* k);

#define  CTRL_2P2Z(Ctrl2P2ZVars, Ctrl2P2ZCoeffs)\
    Ctrl2P2ZVars.err = Ctrl2P2ZVars.ref - Ctrl2P2ZVars.fdbk;\
    Ctrl2P2ZVars.deltaOut = (Ctrl2P2ZCoeffs.coeffB2 * Ctrl2P2ZVars.err2) + (Ctrl2P2ZCoeffs.coeffB1 * Ctrl2P2ZVars.err1) + (Ctrl2P2ZCoeffs.coeffB0 * Ctrl2P2ZVars.err);\
    if (((Ctrl2P2ZVars.out >= Ctrl2P2ZCoeffs.coeffOutMax) && (Ctrl2P2ZVars.err > 0.0f)) || ((Ctrl2P2ZVars.out <= Ctrl2P2ZCoeffs.coeffOutMin) && (Ctrl2P2ZVars.err < 0.0f)))\
    {\
        Ctrl2P2ZVars.deltaOut = 0;\
    }\
    Ctrl2P2ZVars.out = (Ctrl2P2ZCoeffs.coeffA2 * Ctrl2P2ZVars.out2) + (Ctrl2P2ZCoeffs.coeffA1 * Ctrl2P2ZVars.out1) + Ctrl2P2ZVars.deltaOut;\
    Ctrl2P2ZVars.out = (Ctrl2P2ZVars.out < Ctrl2P2ZCoeffs.coeffOutMax) ? Ctrl2P2ZVars.out : Ctrl2P2ZCoeffs.coeffOutMax;\
    Ctrl2P2ZVars.out = (Ctrl2P2ZVars.out > Ctrl2P2ZCoeffs.coeffOutMin) ? Ctrl2P2ZVars.out : Ctrl2P2ZCoeffs.coeffOutMin;\
    Ctrl2P2ZVars.err2 = Ctrl2P2ZVars.err1;\
    Ctrl2P2ZVars.err1 = Ctrl2P2ZVars.err;\
    Ctrl2P2ZVars.out2 = Ctrl2P2ZVars.out1;\
    Ctrl2P2ZVars.out1 = Ctrl2P2ZVars.out;

extern void Loop_2p2zCtrlTest(void);
extern void ctrl_pi_position(PI_POS_T* p_stPI);
extern void set_pi_position_integrate(PI_POS_T* p_stPI, float f32Value);
#endif /* PUBLIC_PUBLIC_INC_DC_MATH_H_ */
