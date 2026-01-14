/*
 * measure.c
 *
 *  Created on: 2022/11/24
 *      Author: hongbo.jiang
 */
#include "PUBLIC_INC/DF_MATH.h"
#include "MEASURE/MEASURE.h"
#include "PFC_CTR/PFC_CTR.H"
#include "ISR_INC/BSW_ISR_ADC.h"

MEASURE_OUT_T           		g_stMeasureOut;
/********* function declaration region *************************************/


/*********variable declaration region *************************************/


/************ Variable definition region *********************************/


/********  function definition region **************************************/

/*************************************************
*  Function:       measure_init
*  Description:    
*  Called:         asw_init();
*  Input:          None
*
*  Quoted Variable:   None
*  Modified Variable: g_stMeasureAve: the output interface parameters
*  Return:
*  Others:
*
*************************************************/
void measure_init(void)
{
	g_stMeasureOut.stVinRmsObj.stInner.f32SqartSum  = 0.0f;
	g_stMeasureOut.stVinRmsObj.stInner.i16LastPol     = 0;
	g_stMeasureOut.stVinRmsObj.stInner.u16N              = 0;
	g_stMeasureOut.stVinRmsObj.stOut.f32Rms            = 0.0f;

	g_stMeasureOut.stIinRmsObj.stInner.f32SqartSum   = 0.0f;
	g_stMeasureOut.stIinRmsObj.stInner.i16LastPol  		= 0;
	g_stMeasureOut.stIinRmsObj.stInner.u16N        		= 0;
	g_stMeasureOut.stIinRmsObj.stOut.f32Rms				= 0.0f;

	g_stMeasureOut.stVinPolFrqObj.stInner.u16NegN   = 0;
	g_stMeasureOut.stVinPolFrqObj.stInner.u16PosN   = 0;
	g_stMeasureOut.stVinPolFrqObj.stOut.u16Type      = INVALID_TYPE;

	g_stMeasureOut.f32PinLpf										  = 0.0f;

	g_stMeasureOut.f32VpfcLpf                                      = 0.0f;
	g_stMeasureOut.f32Temperature                        		  = 0.0f;
}

/*************************************************
*  Function:       measure_fast_task
*  Description:
*  Called:        isrAdc
*  Call:          
*                 
*                 
*                
*  Input:
*
*  Quoted Variable:  None.
*  Modified Variable: No
*  Return:
*
*************************************************/

#ifndef  DLLX64
#pragma  CODE_SECTION(measure_fast_task, ".TI.ramfunc");
#endif

void measure_fast_task(void)
{
	g_stMeasureOut.stVinPolFrqObj.stIn.f32VarTrans = f32_get_vin_raw();
    pol_freq_calc(&g_stMeasureOut.stVinPolFrqObj);

    g_stMeasureOut.stVinRmsObj.stIn.f32Var = f32_get_vin_raw();
    g_stMeasureOut.stVinRmsObj.stIn.i16Pol = g_stMeasureOut.stVinPolFrqObj.stOut.u16Pol;
    rms_calc(&g_stMeasureOut.stVinRmsObj);

    g_stMeasureOut.stIinRmsObj.stIn.f32Var      = f32_get_iin_low_raw();
  //  LPF(g_stMeasureOut.stIinRmsObj.stInner.f32SqartSum, (g_stMeasureOut.stIinRmsObj.stIn.f32Var * g_stMeasureOut.stIinRmsObj.stIn.f32Var), 0.3f, (CTR_PERIOD));
  //  g_stMeasureOut.stIinRmsObj.stOut.f32Rms          = SQRTF(g_stMeasureOut.stIinRmsObj.stInner.f32SqartSum);
    g_stMeasureOut.stIinRmsObj.stIn.i16Pol      = g_stMeasureOut.stVinPolFrqObj.stOut.u16Pol;
    rms_calc(&g_stMeasureOut.stIinRmsObj);

//    g_stMeasureOut.stPinAveObj.stIn.f32Var = g_stMeasureOut.stIinRmsObj.stIn.f32Var * g_stMeasureOut.stVinRmsObj.stIn.f32Var;
//    LPF(g_stMeasureOut.stPinAveObj.stOut.f32Ave, g_stMeasureOut.stPinAveObj.stIn.f32Var,  0.3f,   (CTR_PERIOD));
  //  g_stPinAveObj.stIn.i16Pol = g_stVinPolFrqObj.stOut.u16Pol;
  //  AveCal(&g_stPinAveObj);
}

/*************************************************
*  Function:       measure_1ms_task
*  Description:
*  Called:        BSW_SVC_ScheExcuTask
*  Call:          f32_vdc_out_calc()
*                 f32_vdc_out_rand_calc()
*                 f32_idc_out_calc()
*                 f32_hv_vin_calc()
*  Input:
*
*  Quoted Variable:  None.
*  Modified Variable: No
*  Return:
*
*************************************************/

void measure_1ms_task(void)
{
    float f32Temp = f32_get_vpfc_raw();

    LPF(g_stMeasureOut.f32VpfcLpf, f32Temp, 0.5f, 0.001f);

}


/*************************************************
*  Function:      measure_10ms_task
*  Description:
*  Called:        BSW_SVC_ScheExcuTask
*  Call:
*  Input:
*
*  Quoted Variable:  None.
*  Modified Variable: No
*  Return:
*
*************************************************/

void measure_10ms_task(void)
{
	static float s_f32VinRmsSum = 0;
	static float s_f32IinRmsSum = 0;
    float f32PinTemp;
	float f32Temp = s_f32VinRmsSum * 0.0625f;
	s_f32VinRmsSum += g_stMeasureOut.stVinRmsObj.stOut.f32Rms - f32Temp;
	g_stMeasureOut.f32VinRmsLpf = s_f32VinRmsSum * 0.0625f;

	f32Temp = s_f32IinRmsSum * 0.125f;
	s_f32IinRmsSum += g_stMeasureOut.stIinRmsObj.stOut.f32Rms - f32Temp;

	g_stMeasureOut.f32IinRmsLpf = s_f32IinRmsSum * 0.125f  + 0.2f;

	f32PinTemp = g_stMeasureOut.f32IinRmsLpf * g_stMeasureOut.f32VinRmsLpf;

	if(g_stMeasureOut.f32VinRmsLpf < 150.0f){
		if(f32PinTemp < 300.0f){
			g_stMeasureOut.f32PinLpf = f32PinTemp * (0.985f - (300.0f - f32PinTemp) * 0.001f) ;
		}else if(f32PinTemp < 500.0f){
			g_stMeasureOut.f32PinLpf = f32PinTemp * (0.995f - (500.0f - f32PinTemp) * 0.0005f);
		}else  if(f32PinTemp < 1000.0f){
			g_stMeasureOut.f32PinLpf =  f32PinTemp * (1.0f - (1000.0f - f32PinTemp) * 0.00001f);
		}else{
			g_stMeasureOut.f32PinLpf =  f32PinTemp;
		}
	}else{
		if(f32PinTemp < 300.0f){
			g_stMeasureOut.f32PinLpf = f32PinTemp * (0.970f - (300.0f - f32PinTemp) * 0.001f) ;
		}else if(f32PinTemp < 500.0f){
			g_stMeasureOut.f32PinLpf = f32PinTemp * (0.980f - (500.0f - f32PinTemp) * 0.0005f);
		}else  if(f32PinTemp < 1000.0f){
			g_stMeasureOut.f32PinLpf =  f32PinTemp * (0.985f - (1000.0f - f32PinTemp) * 0.00001f);
		}else  if(f32PinTemp < 1500.0f){
			g_stMeasureOut.f32PinLpf =  f32PinTemp * (0.990f - (1000.0f - f32PinTemp) * 0.00001f);
		}else {
			g_stMeasureOut.f32PinLpf =  f32PinTemp * 0.992f;
		}
	}
}

