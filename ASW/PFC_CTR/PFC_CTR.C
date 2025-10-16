/*
 * PFC_CTR.C
 *
 *  Created on: 2025.9.30
 *      Author:   Hongbo.Jiang
 */
#include "PUBLIC_INC/DIGITAL_PLL.H"
#include "PFC_CTR/PFC_CTR.H"
#include "ISR_INC/BSW_ISR_ADC.H"
#include "SOFTWARE_ENV_CFG.H"
#include "ASW_BASIC.H"
#include "DF_MATH.H"

SOGI_OBJ_T   				g_stSogi;
NOTCH_OBJ_T			g_stVpfcNotchFilt;

ORTH_PLL_OBJ_T  	g_stOrthPll;

void 	pfc_controller_init(void){
		g_stSogi.stCoff.f32Kp                			= 1.414f;
		g_stSogi.stCoff.u8Ena2nd             		= 0;   //¶þ½×½ûÖ¹
		g_stSogi.stCoff.f32Ts                			= CTR_PERIOD;
		g_stSogi.stInter.f32IntegOut       			= 0.0f;
		g_stSogi.stInter.f32IntegOutQ      		= 0.0f;
		g_stSogi.stInter.f32IntegOut2nd   	 	= 0.0f;
		g_stSogi.stInter.f32IntegOut2ndQ   		= 0.0f;
		sogi_set_freq_1p(&g_stSogi, 		50.0f);

	    g_stVpfcNotchFilt.stOut.f32Out 							= 0;
	    g_stVpfcNotchFilt.stCoff.f32Sin1OmegT  			= 0.00966628823119899249250527769323f;   		//Sin(2*pi*100/fs)
	    g_stVpfcNotchFilt.stCoff.f32Cos1OmegT	 		= 0.99995328034455258936414796865385f;   		//Cos(2*pi*100/fs)
	    g_stVpfcNotchFilt.stCoff.f32Width1    				= 0.0083;
	    g_stVpfcNotchFilt.stCoff.f32Width0    				= 0.001;
	    g_stVpfcNotchFilt.stInner.f32Out0thX       		= 0.0f;
	    g_stVpfcNotchFilt.stInner.f32Out0thY       		= 0.0f;
	    g_stVpfcNotchFilt.stInner.f32Out1thX       		= 0.0f;
	    g_stVpfcNotchFilt.stInner.f32Out1thY       		= 0.0f;
	    g_stVpfcNotchFilt.stInner.f32OutPredict0thX 	= 0.0f;
	    g_stVpfcNotchFilt.stInner.f32OutPredict0thY 	= 0.0f;
	    g_stVpfcNotchFilt.stInner.f32OutPredict1thX 	= 0.0f;
	    g_stVpfcNotchFilt.stInner.f32OutPredict1thY 	= 0.0f;
	    g_stVpfcNotchFilt.stInner.f32Err               			= 0.0f;
}

 REG_ASW_INIT(pfc_controller,			pfc_controller_init);

void 	pfc_controller(void){
	    float f32VinTrans;
		#if(NOTICH_FILT_ENABLE == 1)
			g_stVpfcNotchFilt.stIn.f32In = f32_get_vpfc_volt_raw();
			notch_filter(&g_stVpfcNotchFilt);
		#endif
		f32VinTrans = f32_get_vin_volt_raw();

		g_stOrthPll.stIn.f32SigIn = f32VinTrans;
		orth_pll_proc_1p(&g_stOrthPll);

}

