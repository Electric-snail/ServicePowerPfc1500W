/*
 * SW_Scope_Cfg.h
 *
 *  Created on: 2022.9.15
 *      Author: hongbo
 */
#include "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB_DEFINE.h"


//X = RVS 表示以软件设定的值为基准，校准的系统输出的物理值；
//例如 采用PWM或者DAC, 设定参考电压的设定值；设定为12V, 实际输出为11.5V; 则校准后，目的是使得实际输出值与软件设定值一样；
//X = ; 表示以实际输出值为基准，校准软件上报的值；使得软件的值，和上报值一样；
//Y表示 校准的数据类型，如果是浮点型用F32, 如果是有符号整型，用I16, 不支持其他类型
//PARAME_CALIB_X_ITEM_Y     (name,              K_MAX,      K_MIN,       B_MAX,     B_MIN)
PARAME_CALIB_START()
PARAME_CALIB_ITEM_F32(VOUT_CALIB,         1.2f,           0.8f,             5.0f,             -5.0f)
PARAME_CALIB_ITEM_I16(IOUT_CALIB,            307,           204,             1280,             -1280)
PARAME_CALIB_RVS_ITEM_F32(VREF_CALIB, 	1.2f, 	        0.8f,             5.0f,  	        -5.0f)
PARAME_CALIB_RVS_ITEM_I16(IREF_CALIB,     307,           204,             1280,             -1280)
PARAME_CALIB_END()

