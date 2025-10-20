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
    g_f32PowerDeratingActive = 2000.0f;
}

void derating_task_20ms(void)
{
}


