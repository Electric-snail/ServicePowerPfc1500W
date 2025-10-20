#ifndef _USER_MATH_H
#define _USER_MATH_H

#include "SOFTWARE_ENV_CFG.H"

#define pi                                    (3.1415926f)
#define LPF_COFF(Fc, Ts)                      (2*pi*(Fc)*(Ts)/(2*pi*(Fc)*(Ts)+1))
#define LPF(Output, Input, Fc, Ts)   													 \
        Output = LPF_COFF(Fc,Ts)*(Input) + (1-LPF_COFF(Fc,Ts))*(Output);

#define AVG(Output,Input,Sum, PreOutput,Cnt,Filter_Cnt)             \
        (Sum) += (Input);											\
				(Cnt)++;											\
				if((Cnt) >= (Filter_Cnt)){							\
					(Output)    = (Sum)/(Filter_Cnt);				\
					(Sum)       = 0;								\
				  (Cnt)       = 0;									\
					(PreOutput) = (Output);							\
				}else{												\
					(Output)    = (PreOutput);						\
				}
					
#define SLIDE_AVG(Output,Input,Sum,PreOutput,Filter_Cnt)       		\
				(Sum) +  		= (Input);							\
				(Sum) -  		= (PreOutput);						\
				(Output) 		= (Sum)/(Filter_Cnt);				\
				(PreOutput) = (Output);																					



typedef struct
{
    float f32In;
}NOTCH_IN_T;

typedef struct
{
    float f32Out0thX;
    float  f32Out0thY;
    float f32Out1thX;
    float f32Out1thY;
    float f32Out2thX;
    float f32Out2thY;
    float f32OutPredict0thX;
    float  f32OutPredict0thY;
    float f32OutPredict1thX;
    float  f32OutPredict1thY;
    float f32OutPredict2thX;
    float f32OutPredict2thY;
    float  f32Err;
}NOTCH_INNER_2TH_T;

typedef struct
{
    float  f32Cos2OmegT;
    float  f32Sin2OmegT;
    float f32Cos1OmegT;
    float f32Sin1OmegT;
    float  f32Width2;
    float f32Width1;
    float  f32Width0;
}NOTCH_COFF_2TH_T;

typedef struct
{
    float f32Out0thX;
    float  f32Out0thY;
    float f32Out1thX;
    float f32Out1thY;
    float f32OutPredict0thX;
    float  f32OutPredict0thY;
    float f32OutPredict1thX;
    float  f32OutPredict1thY;
    float  f32Err;
}NOTCH_INNER_T;

typedef struct
{
    float f32Cos1OmegT;
    float f32Sin1OmegT;
    float  f32Width0;
    float f32Width1;
}NOTCH_COFF_T;

typedef struct
{
    float f32Out;
}NOTCH_OUT_T;

typedef struct{
	NOTCH_IN_T        					stIn;
	NOTCH_COFF_2TH_T  			    stCoff;
	NOTCH_INNER_2TH_T 		        stInner;
	NOTCH_OUT_T    					stOut;
}NOTCH_OBJ_2TH_T;

typedef struct{
	NOTCH_IN_T        					stIn;
	NOTCH_COFF_T  					stCoff;
	NOTCH_INNER_T 					stInner;
	NOTCH_OUT_T    					stOut;
}NOTCH_OBJ_T;

extern void notch_filter(VOLATILE			NOTCH_OBJ_T	 *p_stNotch);
extern void notch_filter_2th(VOLATILE	NOTCH_OBJ_2TH_T	 	*p_stNotch);

#endif
