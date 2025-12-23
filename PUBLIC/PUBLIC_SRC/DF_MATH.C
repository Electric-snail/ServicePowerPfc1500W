#include "PUBLIC_INC/DF_MATH.H"

#ifndef  DLLX64
//#pragma  CODE_SECTION(notch_filter_2th, 		".TI.ramfunc");
#pragma  CODE_SECTION(notch_filter, 		".TI.ramfunc");
#endif

#define PI2    6.283185307179586
//filter  y(n)=a*x+(1-a)*y(n-1)  a=Fc*2*pi*TS/(Fc*2*pi*TS+1)
#define LPF_COEFF(Fc, Ts)  ((PI2*(Fc)*(Ts))/(PI2*(Fc)*(Ts) + 1))

/**************************************************************************************************
  Function:      notch_filter_2th
  Description:    对基次谐波，和2次谐波进行滤波处理

  Called By:
  Input:
  Output:
  Return:
  Others:
**************************************************************************************************/

void notch_filter_2th(VOLATILE 	NOTCH_OBJ_2TH_T	 *p_stNotch){
	p_stNotch->stInner.f32OutPredict0thX 	= p_stNotch->stInner.f32Out0thX;
	p_stNotch->stInner.f32OutPredict0thY 	= p_stNotch->stInner.f32Out0thY;
	p_stNotch->stInner.f32OutPredict2thX 	= p_stNotch->stCoff.f32Cos2OmegT *p_stNotch->stInner.f32Out2thX - p_stNotch->stCoff.f32Sin2OmegT * p_stNotch->stInner.f32Out2thY;
	p_stNotch->stInner.f32OutPredict2thY 	= p_stNotch->stCoff.f32Sin2OmegT  * p_stNotch->stInner.f32Out2thX +p_stNotch->stCoff.f32Cos2OmegT * p_stNotch->stInner.f32Out2thY;
	p_stNotch->stInner.f32OutPredict1thX 	= p_stNotch->stCoff.f32Cos1OmegT *p_stNotch->stInner.f32Out1thX - p_stNotch->stCoff.f32Sin1OmegT * p_stNotch->stInner.f32Out1thY;
	p_stNotch->stInner.f32OutPredict1thY 	= p_stNotch->stCoff.f32Sin1OmegT  * p_stNotch->stInner.f32Out1thX + p_stNotch->stCoff.f32Cos1OmegT * p_stNotch->stInner.f32Out1thY;
	p_stNotch->stInner.f32Err 					  	= p_stNotch->stIn.f32In - p_stNotch->stInner.f32OutPredict0thX - p_stNotch->stInner.f32OutPredict2thX - p_stNotch->stInner.f32OutPredict1thX;
	p_stNotch->stInner.f32Out0thX 			  	= p_stNotch->stInner.f32OutPredict0thX + p_stNotch->stCoff.f32Width0 *p_stNotch->stInner.f32Err;
	p_stNotch->stInner.f32Out0thY 				= p_stNotch->stInner.f32OutPredict0thY;
	p_stNotch->stInner.f32Out1thX 				= p_stNotch->stInner.f32OutPredict1thX + p_stNotch->stCoff.f32Width1 * p_stNotch->stInner.f32Err;
	p_stNotch->stInner.f32Out1thY 				= p_stNotch->stInner.f32OutPredict1thY;
	p_stNotch->stInner.f32Out2thX 				= p_stNotch->stInner.f32OutPredict2thX + p_stNotch->stCoff.f32Width2 * p_stNotch->stInner.f32Err;
	p_stNotch->stInner.f32Out2thY 				= p_stNotch->stInner.f32OutPredict2thY;
	p_stNotch->stOut.f32Out 		   				= p_stNotch->stIn.f32In - p_stNotch->stInner.f32Out2thX -p_stNotch->stInner.f32Out1thX;
}

/**************************************************************************************************
  Function:      notch_filter
  Description:   p_stNotch->stInner.f32Out0thX 表示的是直流分量，  p_stNotch->stInner.f32Out1thX，表示基波，

  Called By:
  Input:
  Output:
  Return:
  Others:
**************************************************************************************************/

void notch_filter(VOLATILE		NOTCH_OBJ_T	 *p_stNotch){
	p_stNotch->stInner.f32OutPredict0thX = 	p_stNotch->stInner.f32Out0thX;
	p_stNotch->stInner.f32OutPredict0thY = 	p_stNotch->stInner.f32Out0thY;
	p_stNotch->stInner.f32OutPredict1thX = 	p_stNotch->stCoff.f32Cos1OmegT * p_stNotch->stInner.f32Out1thX - p_stNotch->stCoff.f32Sin1OmegT * p_stNotch->stInner.f32Out1thY;
	p_stNotch->stInner.f32OutPredict1thY =   p_stNotch->stCoff.f32Sin1OmegT *p_stNotch->stInner.f32Out1thX + p_stNotch->stCoff.f32Cos1OmegT * p_stNotch->stInner.f32Out1thY;
	p_stNotch->stInner.f32Err 					  = p_stNotch->stIn.f32In - p_stNotch->stInner.f32OutPredict0thX - p_stNotch->stInner.f32OutPredict1thX;
	p_stNotch->stInner.f32Out0thX 			= p_stNotch->stInner.f32OutPredict0thX + p_stNotch->stCoff.f32Width0 * p_stNotch->stInner.f32Err;
	p_stNotch->stInner.f32Out0thY 			= p_stNotch->stInner.f32OutPredict0thY;
	p_stNotch->stInner.f32Out1thX 			= p_stNotch->stInner.f32OutPredict1thX + p_stNotch->stCoff.f32Width1 * p_stNotch->stInner.f32Err;
	p_stNotch->stInner.f32Out1thY 			= p_stNotch->stInner.f32OutPredict1thY;
	p_stNotch->stOut.f32Out 		  			= p_stNotch->stIn.f32In - p_stNotch->stInner.f32Out1thX;
}
