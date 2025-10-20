/*
 * SW_Scope_Cfg.h
 *
 *  Created on: 2022.9.15
 *      Author: xj8r1j
 */
#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_DEFINE.H"
#ifndef SCOPE_EXTERN_VAR_DECLAR
#define SCOPE_EXTERN_VAR_DECLAR
#include "ISR_INC/BSW_ISR_ADC.H"
extern 	volatile ANA_PHY_VALUE_T 			g_stAnaPhyRaw;
#endif

//蹇呴』涓�4锛� 8锛� 12锛�16锛�20锛�24鏈�灏忓叕鍊嶆暟銆�
#define SW_SCOPE_CASH_SIZE           (1680*2)

#if(SW_SCOPE_CASH_SIZE%1680 != 0)
#error"the SW_SCOPE_CACHE_SIZE must be times of 1680"
#elif(SW_SCOPE_CASH_SIZE > 5120)
#endif

#ifndef SCOPE_CFG_DEFINE
#define SCOPE_CFG_DEFINE

#define STARTUP_ITSELF              0
#define STARTUP_GUI                 1
//Unit --> ms
#define SW_SCOPE_TASK_PERIOD        1

#define STARTUP_MODE     			STARTUP_GUI
#define F32_THRD_VALUE              100.0f
#define TRIGG_INDEX                 0
#define ACQ_MODE                    CTR_FRE
#define ACQ_INTERVAL                10
#define TRIGG_POINT                 TRIGG_POINT_MID
#define TRIGG_METHOD                FALLING_EDGE
#endif

//-------------name------------------------------startup_mode------------cache_size
SW_SCOPE_START(PFC_SCOPE,		 STARTUP_GUI,  SW_SCOPE_CASH_SIZE)
SW_SCOPE_ITEM( gs_stOrthPll.stOut.f32SigAlpha)
SW_SCOPE_ITEM(gs_stOrthPll.stOut.f32SigBeta)
SW_SCOPE_ITEM(gs_stVpfcNotchFilt.stOut.f32Out)
//SW_SCOPE_ITEM(g_stAnaPhyRaw.f32VinN)
//SW_SCOPE_ITEM(g_stAnaPhyRaw.f32IinL)
//SW_SCOPE_ITEM(g_stAnaPhyRaw.f32IlAveL)
//SW_SCOPE_ITEM(gs_stIacPiGainCtrl.stIn.f32Fb)
SW_SCOPE_END()

