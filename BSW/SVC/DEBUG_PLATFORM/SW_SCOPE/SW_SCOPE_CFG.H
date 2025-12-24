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
#include "MEASURE/MEASURE.H"
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
SW_SCOPE_ITEM(g_stAnaPhyRaw.f32Vin)
SW_SCOPE_ITEM(g_stMeasureOut.stVinPolFrqObj.stInner.u16PosN)
SW_SCOPE_ITEM(g_stMeasureOut.stVinPolFrqObj.stInner.u16NegN)
SW_SCOPE_END()

