/*
 * POWER_CALC.C
 *
 *  Created on: 2025.9.30
 *      Author: Administrator
 */
#include "PUBLIC_INC/POWER_CALC.H"
#include "ENV_CFG/SOFTWARE_ENV_CFG.H"

#pragma CODE_SECTION(RmsCal, ".TI.ramfunc");

#define  	AC_MIN_FRQ_CNT             (CTR_FRQ/(2*5.0f))
#define   AC_MAX_FRQ_CNT			 (CTR_FRQ/(2*100.0f))

void RmsCal(RMS_CALC_OBJ_T *p_stRmsObj){
    float f32Temp;
    if(p_stRmsObj->stIn.i16Pol != p_stRmsObj->stInner.i16LastPol){ //换相了；
        if(p_stRmsObj->stInner.u16N >= AC_MAX_FRQ_CNT){  //小于1/4个周期，舍去
            p_stRmsObj->stOut.f32Rms = __sqrtf(p_stRmsObj->stInner.f32SqartSum/p_stRmsObj->stInner.u16N);
        }
        p_stRmsObj->stInner.u16N             = 0;
        p_stRmsObj->stInner.i16LastPol      = p_stRmsObj->stIn.i16Pol;
        p_stRmsObj->stInner.f32SqartSum   = 0.0f;
    }else{
        f32Temp = p_stRmsObj->stIn.f32Var * p_stRmsObj->stIn.f32Var;
        p_stRmsObj->stInner.f32SqartSum += f32Temp;
        p_stRmsObj->stInner.u16N++;
        if(p_stRmsObj->stInner.u16N > AC_MIN_FRQ_CNT){  //It is the DC type
        	p_stRmsObj->stOut.f32Rms 				= __sqrtf(p_stRmsObj->stInner.f32SqartSum/p_stRmsObj->stInner.u16N);
            p_stRmsObj->stInner.u16N             		= 0;
            p_stRmsObj->stInner.f32SqartSum   	= 0.0f;
        }
    }
}

#pragma CODE_SECTION(PolFrqCalc, ".TI.ramfunc");
void PolFrqCalc(POL_FRQ_CALC_OBJ_T 	*p_stPolFrqObj){
        if(p_stPolFrqObj ->stIn.f32VarTrans  > 0){
        	p_stPolFrqObj->stInner.u16PosN ++;
        	p_stPolFrqObj->stOut.u16Pol = 1;
        	if(p_stPolFrqObj->stInner.u16NegN  <= AC_MAX_FRQ_CNT){   //it is the noise signal
        		p_stPolFrqObj->stInner.u16NegN = 0;
        	}else if(p_stPolFrqObj->stInner.u16PosN > 5){
        		p_stPolFrqObj->stOut.f32Frq        = (float)CTR_FRQ/(2 * p_stPolFrqObj->stInner.u16NegN);
        		p_stPolFrqObj->stOut.u16InType  = AC_TYPE;
        		p_stPolFrqObj->stInner.u16NegN = 0;
        	}
        }else{
        	p_stPolFrqObj->stInner.u16NegN++;
        	p_stPolFrqObj->stOut.u16Pol = 0;
        	if(p_stPolFrqObj->stInner.u16PosN <= AC_MAX_FRQ_CNT){//it is the noise signal
        		p_stPolFrqObj->stInner.u16PosN = 0;
        	}else if(p_stPolFrqObj->stInner.u16NegN > 5){
        		p_stPolFrqObj->stOut.f32Frq        = (float)CTR_FRQ/(2 * p_stPolFrqObj->stInner.u16PosN);
        		p_stPolFrqObj->stInner.u16PosN = 0;
        	}
        }
        if((p_stPolFrqObj->stInner.u16NegN > AC_MIN_FRQ_CNT)	||	(p_stPolFrqObj->stInner.u16PosN > AC_MIN_FRQ_CNT)){
        	p_stPolFrqObj->stOut.u16InType = DC_TYPE;
        }
}

