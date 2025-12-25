/*
 * POWER_CALC.C
 *
 *  Created on: 2025.9.30
 *      Author: Administrator
 */
#include    "PUBLIC_INC/POWER_CALC.H"
#include    "SOFTWARE_ENV_CFG.H"
#define  	AC_MIN_FRQ_CNT             (CTR_FRQ/(2*5.0f))
#define     AC_MAX_FRQ_CNT			   (CTR_FRQ/(2*100.0f))

#ifndef  DLLX64
#pragma  CODE_SECTION(rms_calc, 		".TI.ramfunc");
#endif

void rms_calc(RMS_CALC_OBJ_T *p_stRmsObj){
    float f32Temp;
    if(p_stRmsObj->stIn.i16Pol != p_stRmsObj->stInner.i16LastPol){ //换相了；
        if(p_stRmsObj->stInner.u16N >= AC_MAX_FRQ_CNT){  //小于1/4个周期，舍去
            p_stRmsObj->stOut.f32Rms = SQRTF(p_stRmsObj->stInner.f32SqartSum / p_stRmsObj->stInner.u16N);
        }
        p_stRmsObj->stInner.u16N             = 0;
        p_stRmsObj->stInner.i16LastPol      = p_stRmsObj->stIn.i16Pol;
        p_stRmsObj->stInner.f32SqartSum   = 0.0f;
    }else{
        f32Temp = p_stRmsObj->stIn.f32Var * p_stRmsObj->stIn.f32Var;
        p_stRmsObj->stInner.f32SqartSum += f32Temp;
        p_stRmsObj->stInner.u16N++;
        if(p_stRmsObj->stInner.u16N > AC_MIN_FRQ_CNT){  //It is the DC type
            p_stRmsObj->stOut.f32Rms = SQRTF(p_stRmsObj->stInner.f32SqartSum / p_stRmsObj->stInner.u16N);
            p_stRmsObj->stInner.u16N             		= 0;
            p_stRmsObj->stInner.f32SqartSum   	= 0.0f;
        }
    }
}

#ifndef  DLLX64
#pragma  CODE_SECTION(average_calc, 		".TI.ramfunc");
#endif

void average_calc(AVE_CALC_OBJ_T* p_stAveObj) {
    if (p_stAveObj->stIn.i16Pol != p_stAveObj->stInner.i16LastPol) { //换相了；
        if (p_stAveObj->stInner.u16N >= AC_MAX_FRQ_CNT) {  //小于1/4个周期，舍去
            p_stAveObj->stOut.f32Ave = p_stAveObj->stInner.f32Sum / p_stAveObj->stInner.u16N;
        }
        p_stAveObj->stInner.u16N        = 0;
        p_stAveObj->stInner.i16LastPol  = p_stAveObj->stIn.i16Pol;
        p_stAveObj->stInner.f32Sum      = 0.0f;
    }
    else {
        p_stAveObj->stInner.f32Sum += p_stAveObj->stIn.f32Var;
        p_stAveObj->stInner.u16N++;
        if (p_stAveObj->stInner.u16N > AC_MIN_FRQ_CNT) {  //It is the DC type
            p_stAveObj->stOut.f32Ave    = p_stAveObj->stInner.f32Sum / p_stAveObj->stInner.u16N;
            p_stAveObj->stInner.u16N    = 0;
            p_stAveObj->stInner.f32Sum  = 0.0f;
        }
    }
}

#ifndef  DLLX64
#pragma  CODE_SECTION(pol_freq_calc, 		".TI.ramfunc");
#endif

void pol_freq_calc(POL_FRQ_CALC_OBJ_T 	*p_stPolFrqObj){
	   float f32Temp0;
        if(p_stPolFrqObj ->stIn.f32VarTrans  > 0){
        	p_stPolFrqObj->stInner.u16PosN ++;
        	p_stPolFrqObj->stOut.u16Pol = 1;
        	if(p_stPolFrqObj->stInner.u16NegN  <= AC_MAX_FRQ_CNT){   //it is the noise signal
        		p_stPolFrqObj->stInner.u16NegN = 0;
        	}else if(p_stPolFrqObj->stInner.u16PosN > 5){
        		p_stPolFrqObj->stInner.u16NegN 			-= 6;
        		f32Temp0												= __divf32(1.0f,		p_stPolFrqObj->stInner.u16NegN);
        		p_stPolFrqObj->stOut.f32Sin2OmegT 	= __sinpuf32(f32Temp0);
        		p_stPolFrqObj->stOut.f32Cos2OmegT 	= __cospuf32(f32Temp0);
        		f32Temp0                                                = 0.5f * f32Temp0;
        		p_stPolFrqObj->stOut.f32Frq         		= CTR_FRQ * f32Temp0;
        		p_stPolFrqObj->stOut.f32SinOmegT  	=   __sinpuf32(f32Temp0);
        		p_stPolFrqObj->stOut.f32CosOmegT	 	=  __cospuf32(f32Temp0);
        		p_stPolFrqObj->stOut.u16Type  			= AC_TYPE;
        		p_stPolFrqObj->stInner.u16NegN 			= 0;
        	}
        }else{
        	p_stPolFrqObj->stInner.u16NegN++;
        	p_stPolFrqObj->stOut.u16Pol = 0;
        	if(p_stPolFrqObj->stInner.u16PosN <= AC_MAX_FRQ_CNT){//it is the noise signal
        		p_stPolFrqObj->stInner.u16PosN = 0;
        	}else if(p_stPolFrqObj->stInner.u16NegN > 5){
        		p_stPolFrqObj->stInner.u16PosN 			-= 6;
        		f32Temp0												= __divf32(1.0f,		p_stPolFrqObj->stInner.u16PosN);
        		p_stPolFrqObj->stOut.f32Sin2OmegT 	= __sinpuf32(f32Temp0);
        		p_stPolFrqObj->stOut.f32Cos2OmegT 	= __cospuf32(f32Temp0);
        		f32Temp0                                                = 0.5f * f32Temp0;
        		p_stPolFrqObj->stOut.f32Frq         		= CTR_FRQ * f32Temp0;
        		p_stPolFrqObj->stOut.f32SinOmegT  	=   __sinpuf32(f32Temp0);
        		p_stPolFrqObj->stOut.f32CosOmegT	 	=  __cospuf32(f32Temp0);
        		p_stPolFrqObj->stOut.u16Type  			=  AC_TYPE;
        		p_stPolFrqObj->stInner.u16PosN = 0;
        	}
        }
        if((p_stPolFrqObj->stInner.u16NegN > AC_MIN_FRQ_CNT)	||	(p_stPolFrqObj->stInner.u16PosN > AC_MIN_FRQ_CNT)){
        	p_stPolFrqObj->stOut.u16Type = DC_TYPE;
        }
}

#ifndef  DLLX64
#pragma  CODE_SECTION(vin_drop_diag, 		".TI.ramfunc");
#endif

void vin_drop_diag(VIN_DROP_DIG_OBJ_T *p_stVinDropObj){
        if(p_stVinDropObj->stIn.f32VinAbsTrans < p_stVinDropObj->stCoff.f32DropTransThrd){
        	p_stVinDropObj->stInner.u16DropN++;
        	if(p_stVinDropObj->stInner.u16DropN > p_stVinDropObj->stCoff.u16DropCntThrd){
        		p_stVinDropObj->stOut.u16VinDropFlag   = 1;
        		p_stVinDropObj->stInner.u16DropN 			= p_stVinDropObj->stCoff.u16DropCntThrd;
            	p_stVinDropObj->stInner.u16RecvN 			= 0;
        	}
        }else{
        	p_stVinDropObj->stInner.u16DropN = 0;
        }
}

void vin_drop_recv_diag(VIN_DROP_DIG_OBJ_T *p_stVinDropObj){
	   if(1 == p_stVinDropObj->stOut.u16VinDropFlag){
		     if(p_stVinDropObj->stIn.f32VinRms > p_stVinDropObj->stCoff.f32RecvRmsThrd){
		    	 	 p_stVinDropObj->stInner.u16RecvN++;
		    	 	 if(p_stVinDropObj->stInner.u16RecvN >= 2){
		    	 		p_stVinDropObj->stOut.u16VinDropFlag  = 0;
		    	 	 }
		     }else{
		    	 p_stVinDropObj->stInner.u16RecvN = 0;
		     }
	   }
}
