/*
 * DERATING.c
 *
 * Created on: 2024/6/13
 * Author:
 */
#include "PUBLIC_INC/mem_handle.h"
#include "PUBLIC_INC/DF_MATH.h"
#include "HAL/HAL_INC/BSW_HAL_PWM.h"
#include "HAL/HAL_INC/BSW_HAL_ADC.h"
#include "DERATING/DERATING.h"
#include "SVC/BSW_SVC_BASIC.h"
#include "SVC/TASK/BSW_TASK_SERVICE.h"
#include "ASW_BASIC.h"

float g_f32PowerDeratingActive;
float g_f32PowerLimitTest = 0.0f;

void derating_init(void)
{
    g_f32PowerDeratingActive = 300.0f;
}

static float TempDeratingProc(void)
{
    // 温度大于100°时从300W->100W
    // 温度小于95°时从100W->300W
    // 根据NTC - 314的温度，当NTC - 314的温度达到100°C时，MDCDC的最大功率有300W – > 100W
    // 当NTC - 314的温度恢复到95°C时，MDCDC的最大功率有100W – > 300W
}

static float VoltageDeratingProc(void)
{
}

void derating_task_20ms(void)
{
}


float GetPowerDeratingPower(void)
{
}


