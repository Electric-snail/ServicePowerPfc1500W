#ifndef _SOGI_H
#define _SOGI_H

typedef struct {
	float         f32SigIn;
}SOGI_INPUT_T;

typedef struct {
	unsigned char 		u8Ena2nd;
	float         				f32Kp;
	float         				f32Ts;
	float         				f32Wn;
}SOGI_COFF_T;

typedef struct {
	float         f32SigOut;
	float         f32SigOutQ;
	float         f32SigOut2nd;
	float         f32SigOut2ndQ;
}SOGI_OUTPUT_T;

typedef struct {
	float f32IntegInN_1;
	float f32IntegInQN_1;
	float f32IntegOut;
	float f32IntegOutN_1;
	float f32IntegOutQ;
	float f32IntegOutQN_1;
	float f32IntegIn2ndN_1;
	float f32IntegIn2ndQN_1;
	float f32IntegOut2nd;
	float f32IntegOut2ndN_1;
	float f32IntegOut2ndQ;
	float f32IntegOut2ndQN_1;
}SOGI_INTER_T;

typedef struct {
	SOGI_INPUT_T  		stIn;
	SOGI_COFF_T      	stCoff;
	SOGI_OUTPUT_T 	stOut;
	SOGI_INTER_T  		stInter;
}SOGI_OBJ_T;

typedef struct {
	float         f32SigIn;
}ORTH_INPUT_T;

typedef struct {
	float						f32CosOmegT;
	float						f32SinOmegT;
	float         				f32Kp;
	float                       f32OutMax;
}ORTH_COFF_T;

typedef struct {
	float         f32SigAlpha;
	float         f32SigBeta;

}ORTH_OUTPUT_T;

typedef struct {

}ORTH_INTER_T;

typedef struct {
	ORTH_INPUT_T  		stIn;
	ORTH_COFF_T      	stCoff;
	ORTH_OUTPUT_T 	stOut;
}ORTH_PLL_OBJ_T;

void sogi_set_freq_1p(SOGI_OBJ_T *pst_Sogi, float f32Freq);
extern void sogi_proc_1p(SOGI_OBJ_T *pst_Sogi);

extern void orth_pll_proc_1p(ORTH_PLL_OBJ_T 	*pst_OrthPll);

#endif

