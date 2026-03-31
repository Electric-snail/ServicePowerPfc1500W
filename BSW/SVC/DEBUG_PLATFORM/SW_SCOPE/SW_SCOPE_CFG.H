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
#include "PUBLIC_INC/DC_MATH.H"
#include "PUBLIC_INC/DF_MATH.H"
#include "PFC_CTR/PFC_CTR.H"
#include "MEASURE/MEASURE.H"
#include "POWER_FSM/POWER_FSM.H"
#include "DIAGNOSTIC/DIAGNOSTIC.H"
#include "PUBLIC_INC/POWER_CALC.H"

extern 	volatile ANA_PHY_VALUE_T 			g_stAnaPhyRaw;
extern 	PI_POS_T				    						gs_stVpfcPiCtrl;
extern    PI_GAIN_POS_T									gs_stIacPiGainCtrl;
extern    volatile float 										g_f32VpfcIsrLpf;
extern    VIN_DROP_DIG_OBJ_T       				g_stVinDropDiag;
#endif

//蹇呴』涓�4锛� 8锛� 12锛�16锛�20锛�24鏈�灏忓叕鍊嶆暟銆�
#define SW_SCOPE_CASH_SIZE           (120*34)

#if(SW_SCOPE_CASH_SIZE%120 != 0)
#error"the SW_SCOPE_CACHE_SIZE must be times of 120"
#elif(SW_SCOPE_CASH_SIZE > 5120)
#endif

#ifndef SCOPE_CFG_DEFINE
#define SCOPE_CFG_DEFINE

#define STARTUP_ITSELF              				0
#define STARTUP_GUI                 					1
//Unit --> ms
#define SW_SCOPE_TASK_PERIOD        	1

#define STARTUP_MODE     			STARTUP_GUI
#define F32_THRD_VALUE              360.0f
#define TRIGG_INDEX                     1
#define ACQ_MODE                          CTR_FRE
#define ACQ_INTERVAL                   10
#define TRIGG_METHOD                RISING_EDGE
#endif

//-------------name------------------------------startup_mode------------cache_size
SW_SCOPE_START(PFC_SCOPE,		 STARTUP_MODE,  SW_SCOPE_CASH_SIZE)
SW_SCOPE_ITEM(gs_stVpfcPiCtrl.stIn.f32Ref)
SW_SCOPE_ITEM(gs_stVpfcPiCtrl.stIn.f32Fb)
SW_SCOPE_ITEM(g_f32VpfcIsrLpf)
SW_SCOPE_END()

