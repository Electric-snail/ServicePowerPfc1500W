/*
 * SW_Scope_Cfg.h
 *
 *  Created on: 2022.9.15
 *      Author: xj8r1j
 */
#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_DEFINE.H"
#ifndef SCOPE_EXTERN_VAR_DECLAR
#define SCOPE_EXTERN_VAR_DECLAR
extern float f32VoltRaw;
extern float g_f32VoltLpf;
#endif

//必须为4， 8， 12，16，20，24最小公倍数。
#define SW_SCOPE_CASH_SIZE           1680

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

//-------------name------startup_mode----cache_size
SW_SCOPE_START(LLC_SCOPE, STARTUP_GUI,  SW_SCOPE_CASH_SIZE)
SW_SCOPE_ITEM(f32VoltRaw)
SW_SCOPE_ITEM(g_f32VoltLpf)
SW_SCOPE_END()

