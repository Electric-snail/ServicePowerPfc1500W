#include  "PUBLIC_INC/DIGITAL_PLL.H"

#ifndef  DLLX64
#pragma  CODE_SECTION( sogi_fall_proc_1p, 	".TI.ramfunc");
#endif

/**************************************************************************************************
  Function:       	sogi_fall_proc_1p
  Description:    	based on input signal, to general the orth(正交信号) signal, which is on the fall of original singal
  Called By:
  Input:
  Output:
  Return:
  Others:
**************************************************************************************************/
void sogi_fall_proc_1p(VOLATILE	SOGI_OBJ_T *pst_Sogi)
{
    float f32Dx1, f32Dx2;
    f32Dx1 = pst_Sogi->stCoff.f32Wn * (pst_Sogi->stCoff.f32Kp * (pst_Sogi->stIn.f32SigIn - pst_Sogi->stOut.f32Alfa) - pst_Sogi->stOut.f32Beta);

    pst_Sogi->stInter.f32IntegOutN +=
        + pst_Sogi->stCoff.f32Ts * (f32Dx1 + pst_Sogi->stInter.f32IntegInN_1) * 0.5f;

    pst_Sogi->stInter.f32IntegInN_1 = f32Dx1;
    f32Dx2 = pst_Sogi->stCoff.f32Wn * pst_Sogi->stOut.f32Alfa;

    pst_Sogi->stInter.f32IntegOutQN += pst_Sogi->stCoff.f32Ts * (f32Dx2 + pst_Sogi->stInter.f32IntegInQN_1) * 0.5f;
    pst_Sogi->stInter.f32IntegInQN_1 = f32Dx2;
    pst_Sogi->stOut.f32Alfa = pst_Sogi->stInter.f32IntegOutN;
    pst_Sogi->stOut.f32Beta = pst_Sogi->stInter.f32IntegOutQN;
}

/**************************************************************************************************
  Function:       	sogi_front_proc_1p
  Description:    	based on input signal, to general the orth(正交信号) signal, which is on the fall of original singal
  Called By:
  Input:
  Output:
  Return:
  Others:
**************************************************************************************************/
void sogi_front_proc_1p(VOLATILE	SOGI_OBJ_T* pst_Sogi)
{
    float f32Dx1, f32Dx2;
    f32Dx1 = pst_Sogi->stCoff.f32Wn * (pst_Sogi->stCoff.f32Kp * (pst_Sogi->stIn.f32SigIn - pst_Sogi->stOut.f32Alfa) - pst_Sogi->stInter.f32IntegOutQN);

    pst_Sogi->stInter.f32IntegOutN +=
        +pst_Sogi->stCoff.f32Ts * (f32Dx1 + pst_Sogi->stInter.f32IntegInN_1) * 0.5f;

    pst_Sogi->stInter.f32IntegInN_1 = f32Dx1;
    f32Dx2 = pst_Sogi->stCoff.f32Wn * pst_Sogi->stOut.f32Alfa;

    pst_Sogi->stInter.f32IntegOutQN += pst_Sogi->stCoff.f32Ts * (f32Dx2 + pst_Sogi->stInter.f32IntegInQN_1) * 0.5f;
    pst_Sogi->stInter.f32IntegInQN_1 = f32Dx2;
    pst_Sogi->stOut.f32Alfa = pst_Sogi->stInter.f32IntegOutN;
    pst_Sogi->stOut.f32Beta = -pst_Sogi->stInter.f32IntegOutQN;
}
/**************************************************************************************************
  Function:       sogi_init
  Description:    对sogi相关变量进行初始化

  Called By:
  Input:
  Output:
  Return:
  Others:
**************************************************************************************************/
/*void sogi_init(SOGI_OBJ_T *pst_sogi, float f32Ts)
{
    pst_sogi->stCoff.f32Kp                		= 1.414f;
    pst_sogi->stCoff.u8Ena2nd             		= 0;   //二阶禁止
    pst_sogi->stCoff.f32Ts                			= f32Ts;
    pst_sogi->stInter.f32IntegOut       		= 0.0f;
    pst_sogi->stInter.f32IntegOutQ      		= 0.0f;
    pst_sogi->stInter.f32IntegOut2nd   	 	= 0.0f;
    pst_sogi->stInter.f32IntegOut2ndQ   	= 0.0f;

    sogi_set_central_freq(pst_sogi, 50.0f);
}*/


/**************************************************************************************************
  Function:       sogi_pll_proc_1p
  Description:    sogi  单相锁相算法，实现对输入信号的跟踪，在调用之前，需调用sogi_init函数
  Called By:      
  Input:          
  Output:         
  Return:         
  Others:         
**************************************************************************************************/
void sogi_pll_proc_1p(VOLATILE	SOGI_PLL_OBJ_T *pst_SogiPll)
{
    float kp_out_tmp;
    float err_tmp;
    float f32Temp;
    //-----------------------------???SOGI-----------------------------//
    err_tmp 		= pst_SogiPll->stIn.f32SigIn - pst_SogiPll->stOut.f32SigOut;
    kp_out_tmp = pst_SogiPll->stCoff.f32Kp * err_tmp;

   // pst_sogi->inter.integral_output.in.input = pst_sogi->stInter.f32Wn * (kp_out_tmp - pst_sogi->stOut.f32SignalQ);
    f32Temp = pst_SogiPll->stCoff.f32Wn * (kp_out_tmp - pst_SogiPll->stOut.f32SigOutQ);

    //Tustin integration
    pst_SogiPll->stInter.f32IntegOut = pst_SogiPll->stInter.f32IntegOutN_1
        + pst_SogiPll->stCoff.f32Ts * (f32Temp + pst_SogiPll->stInter.f32IntegInN_1) * 0.5f;

    pst_SogiPll->stInter.f32IntegOutN_1 = pst_SogiPll->stInter.f32IntegOut;
    pst_SogiPll->stInter.f32IntegInN_1   = f32Temp;

    pst_SogiPll->stOut.f32SigOut = pst_SogiPll->stInter.f32IntegOut;

    f32Temp = pst_SogiPll->stCoff.f32Wn * pst_SogiPll->stOut.f32SigOut;

    pst_SogiPll->stInter.f32IntegOutQ = pst_SogiPll->stInter.f32IntegOutQN_1
        + pst_SogiPll->stCoff.f32Ts * (f32Temp + pst_SogiPll->stInter.f32IntegInQN_1) * 0.5f;

    pst_SogiPll->stInter.f32IntegOutQN_1 = pst_SogiPll->stInter.f32IntegOutQ;
    pst_SogiPll->stInter.f32IntegInQN_1    = f32Temp;

    pst_SogiPll->stOut.f32SigOutQ 				= pst_SogiPll->stInter.f32IntegOutQ;
    //---------------------------------------------------------------------//

    if (1 == pst_SogiPll->stCoff.u8Ena2nd)
    {
        //-----------------------------SOGI-----------------------------//
        err_tmp = pst_SogiPll->stOut.f32SigOut - pst_SogiPll->stOut.f32SigOut2nd;
        kp_out_tmp = pst_SogiPll->stCoff.f32Kp * err_tmp;
        //Tustin integration
        f32Temp = pst_SogiPll->stCoff.f32Wn * (kp_out_tmp - pst_SogiPll->stOut.f32SigOut2ndQ);
        pst_SogiPll->stInter.f32IntegOut2nd = pst_SogiPll->stInter.f32IntegOut2ndN_1
            + pst_SogiPll->stCoff.f32Ts * (f32Temp + pst_SogiPll->stInter.f32IntegIn2ndN_1) * 0.5f;
        pst_SogiPll->stInter.f32IntegOut2ndN_1 = pst_SogiPll->stInter.f32IntegOut2nd;
        pst_SogiPll->stInter.f32IntegIn2ndN_1    = f32Temp;
        pst_SogiPll->stOut.f32SigOut2nd 			  = pst_SogiPll->stInter.f32IntegOut2nd;
        //Tustin integration
        f32Temp = pst_SogiPll->stCoff.f32Wn * pst_SogiPll->stOut.f32SigOut2nd;
        pst_SogiPll->stInter.f32IntegOut2ndQ = pst_SogiPll->stInter.f32IntegOut2ndQN_1
            + pst_SogiPll->stCoff.f32Ts * (f32Temp + pst_SogiPll->stInter.f32IntegIn2ndQN_1) * 0.5f;

        pst_SogiPll->stInter.f32IntegOut2ndQN_1 = pst_SogiPll->stInter.f32IntegOut2ndQ;
        pst_SogiPll->stInter.f32IntegIn2ndQN_1  	= f32Temp;
        pst_SogiPll->stOut.f32SigOut2ndQ 		    = pst_SogiPll->stInter.f32IntegOut2ndQ;
    }

}

#ifndef  DLLX64
#pragma  CODE_SECTION(orth_pll_proc_1p, 	".TI.ramfunc");
#endif

/**************************************************************************************************
  Function:       orth_pll_proc_1p
  Description:   Vin = Vm*Cos(ωt + θ)；  X = [α,  β];    α = Vm*Cos(ωt + θ)； β = Vm*Sin(ωt + θ)
  	  	  	  	  	  	  x[k+1] = Φ·x[k]，其中 Φ = e^(A·Ts)
  	  	  	  	  	  	  Φ = [cos(ωTs), -sin(ωTs);
									sin(ωTs),  cos(ωTs)]
  Called By:
  Input:
  Output:
  Return:
  Others:    如果用直流分量怎么办;
**************************************************************************************************/
void orth_pll_proc_1p(VOLATILE	ORTH_PLL_OBJ_T  *pst_OrthPll)
{
	float f32OutXTemp, f32OutYTemp, f32ErrTemp;
    f32OutXTemp 								= (pst_OrthPll->stCoff.f32CosOmegT * pst_OrthPll->stOut.f32SigAlpha - pst_OrthPll->stCoff.f32SinOmegT * pst_OrthPll->stOut.f32SigBeta);
    f32OutYTemp 								= (pst_OrthPll->stCoff.f32SinOmegT * pst_OrthPll->stOut.f32SigAlpha + pst_OrthPll->stCoff.f32CosOmegT * pst_OrthPll->stOut.f32SigBeta);
    f32ErrTemp 	 							= pst_OrthPll->stIn.f32SigIn - f32OutXTemp;
    pst_OrthPll->stOut.f32SigAlpha = f32OutXTemp + (pst_OrthPll->stCoff.f32Kp * f32ErrTemp);
    pst_OrthPll->stOut.f32SigBeta  	= f32OutYTemp;
    if(pst_OrthPll->stOut.f32SigAlpha > pst_OrthPll->stCoff.f32OutMax)
    	pst_OrthPll->stOut.f32SigAlpha =	pst_OrthPll->stCoff.f32OutMax;
    if(pst_OrthPll->stOut.f32SigAlpha < -pst_OrthPll->stCoff.f32OutMax)
    	pst_OrthPll->stOut.f32SigAlpha = -pst_OrthPll->stCoff.f32OutMax;

}
