/*
 * Parameter_Calib.h
 *
 *  Created on: 2023-10-28
 *      Author: Hongbo.jiang
 */

#ifndef _PARAMETER_CALIB_H_
#define _PARAMETER_CALIB_H_

typedef struct{
    float f32K;
    float f32Offset;
}F32_CALIB_ITEM_T;

typedef struct{
    float f32Kmax;
	float f32Kmin;
    float f32Bmax;
	float f32Bmin;
}F32_CALIB_LIMIT_ITEM_T;

typedef struct{
    signed short i16Q8K;
    signed short i16Q8Offset;
}I16_CALIB_ITEM_T;

typedef struct{
    signed short i16Q8Kmax;
    signed short i16Q8Kmin;
    signed short i16Q8Bmax;
    signed short i16Q8Bmin;
}I16_CALIB_LIMIT_ITEM_T;

#define GEN_PARAM_CALIB_VAR_F32_TYPE_ENTITY
    #include "../DEBUG_PLATFORM/PARAMETER_CALIB/Parameter_Calib_Cfg.h"
#undef GEN_PARAM_CALIB_VAR_F32_TYPE_ENTITY

#define GEN_PARAM_CALIB_VAR_I16_TYPE_ENTITY
    #include "../DEBUG_PLATFORM/PARAMETER_CALIB/Parameter_Calib_Cfg.h"
#undef GEN_PARAM_CALIB_VAR_I16_TYPE_ENTITY

//F32_CALIB_DATA_OBJ_T 包含了所用定义的浮点型定义的校准数组
//I16_CALIB_DATA_OBJ_T 包含了所用定义的有符号16位校准数组
typedef struct{
	F32_CALIB_DATA_OBJ_T  stF32;
    I16_CALIB_DATA_OBJ_T  stI16;
}PARAME_CALIB_DATA_T;

#define GEN_PARAM_CALIB_LIMIT_VAR_F32_TYPE_ENTITY
    #include "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB_CFG.h"
#undef GEN_PARAM_CALIB_LIMIT_VAR_F32_TYPE_ENTITY

#define GEN_PARAM_CALIB_LIMIT_VAR_I16_TYPE_ENTITY
    #include "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB_CFG.h"
#undef GEN_PARAM_CALIB_LIMIT_VAR_I16_TYPE_ENTITY

#define   PARAM_CALIB_ITEM_CMD_ID            0x00
#define   PARAM_CALIB_WR_DATA_CMD_ID         0x01
#define   PARAM_CALIB_RD_DATA_CMD_ID         0x02
#define   PARAM_CALIB_RS_DATA_CMD_ID         0x03
#define   PARAM_CALIB_STORE_CMD_ID           0x04

#define   CALIB_FWD_METHOD                   0
#define   CALIB_RVS_METHOD                   1

 
#define f32_get_param_calib_k(name)            g_stCalibData.stF32.st##name.f32K
#define f32_get_param_calib_offset(name)	   g_stCalibData.stF32.st##name.f32Offset
#define i16_get_param_calib_k(name)            g_stCalibData.stI16.st##name.i16Q8K
#define i16_get_param_calib_offset(name)	   g_stCalibData.stI16.st##name.i16Q8Offset

#define u8_get_calib_store_flag()              g_u8CalibStoreFlg
#define u8_clc_calib_store_flag()              g_u8CalibStoreFlg = 0
#define p_u8_get_calib_data_addr()             ((unsigned char *)&g_stCalibData)
#define u16_get_calib_data_num()               sizeof(g_stCalibData)
extern unsigned char       g_u8CalibStoreFlg;
extern PARAME_CALIB_DATA_T g_stCalibData;
extern void ParamCalibCmdSetLink(void *p_vAplDm);
extern void param_calib_init(void);

#endif
