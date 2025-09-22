#ifndef _USER_MATH_H
#define _USER_MATH_H

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
    float f32Cos1OmegT;
    float f32Sin1OmegT;
    float f32Width;
    float f32Deep;
}NOTCH_REG_COF_ST;

#define Notch_filter(f32In, prt, cof, f32Out)\
    prt.f32OutPredict0thX = prt.f32Out0thX;\
    prt.f32OutPredict0thY = prt.f32Out0thY;\
    prt.f32OutPredict1thX = cof.f32Cos1OmegT * prt.f32Out1thX - cof.f32Sin1OmegT * prt.f32Out1thY;\
    prt.f32OutPredict1thY = cof.f32Sin1OmegT * prt.f32Out1thX + cof.f32Cos1OmegT * prt.f32Out1thY;\
    prt.f32Err = f32In - prt.f32OutPredict0thX - prt.f32OutPredict1thX;\
    prt.f32Out0thX = prt.f32OutPredict0thX + cof.f32Deep * prt.f32Err;\
    prt.f32Out0thY = prt.f32OutPredict0thY;\
    prt.f32Out1thX = prt.f32OutPredict1thX + cof.f32Width * prt.f32Err;\
    prt.f32Out1thY = prt.f32OutPredict1thY;\
    f32Out = f32In - prt.f32Out1thX;

typedef struct
{
    float f32Out0thX;
    float f32Out0thY;
    float f32Out1thX;
    float f32Out1thY;
    float f32OutPredict1thX;
    float f32OutPredict1thY;
    float f32OutPredict0thX;
    float f32OutPredict0thY;
    float f32Err;
}NOTCH_REG_PRT_ST;

#endif
