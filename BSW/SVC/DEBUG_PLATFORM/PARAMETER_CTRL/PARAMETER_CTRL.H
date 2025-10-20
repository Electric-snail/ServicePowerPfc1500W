/*
 * Parameter_Cfg.h
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#ifndef _PARAMETER_CTRL_H_
#define _PARAMETER_CTRL_H_

#include "ENV_CFG/SOFTWARE_ENV_CFG.H"
#include "DEBUG_PLATFORM/DBG_BASIC.H"
#include "PUBLIC_INC/LIST.H"
#include "PUBLIC_INC/AUTO_REGISTER.H"

#define  CMD_ID_GET_PARAM_CNT           0x01
#define  CMD_ID_GET_PARAM_ITEM          0x02
#define  CMD_ID_WR_PARAM_ITEM           0x03
#define  CMD_ID_RD_PARAM_ITEM           0x04
#define  CMD_ID_RS_PARAM_ITEM           0x05
#define  CMD_ID_RS_ALL_PARAM_ITEM       0x06


#define MAX_ITEM_LEN                    100

#define PARAM_WR_ACK_DATA_MAX_LEN       2
#define PARAM_VAR_NAME_MAX_LEN          32

enum VAR_ATTR{
    VAR_WR      = 0,
    VAR_WE      = 1,
    VAR_RD      = 2,
};

typedef void (*pf_user_cb_func_t)(void);

typedef struct
{
    const char          *pchar_name;
    enum VAR_ATTR       emAttr;
    unsigned char       u8def_val;
    unsigned char       u8min_val;
    unsigned char       u8max_val;
    unsigned char       *p_u8Value;
    pf_user_cb_func_t   user_cb_func;
}param_item_cfg_u8_t;

typedef struct
{
    const char          *pchar_name;
    enum VAR_ATTR       emAttr;
    char                i8def_val;
    char                i8min_val;
    char                i8max_val;
    char                *p_i8Value;
    pf_user_cb_func_t   user_cb_func;
}param_item_cfg_i8_t;

typedef struct
{
    const char          *pchar_name;
    enum VAR_ATTR       emAttr;
    unsigned short      u16def_val;
    unsigned short      u16min_val;
    unsigned short      u16max_val;
    unsigned short      *p_u16Value;
    pf_user_cb_func_t   user_cb_func;
}param_item_cfg_u16_t;

typedef struct
{
    const char          *pchar_name;
    enum VAR_ATTR        emAttr;
    signed short         i16def_val;
    signed short         i16min_val;
    signed short         i16max_val;
    signed short         *p_i16Value;
    pf_user_cb_func_t   user_cb_func;
}param_item_cfg_i16_t;

typedef struct
{
    const char          *pchar_name;
    enum VAR_ATTR        emAttr;
    unsigned long        u32def_val;
    unsigned long        u32min_val;
    unsigned long        u32max_val;
    unsigned long        *p_u32Value;
    pf_user_cb_func_t   user_cb_func;
}param_item_cfg_u32_t;

typedef struct
{
    const char          *pchar_name;
    enum VAR_ATTR        emAttr;
    signed long          i32def_val;
    signed long          i32min_val;
    signed long          i32max_val;
    signed long          *p_i32Value;
    pf_user_cb_func_t    user_cb_func;
}param_item_cfg_i32_t;

typedef struct
{
    const char          *pchar_name;
    enum VAR_ATTR        emAttr;
    float                f32def_val;
    float                f32min_val;
    float                f32max_val;
    float                *p_f32Value;
    pf_user_cb_func_t   user_cb_func;
}param_item_cfg_f32_t;


typedef struct
{
    list_t param_head;
    UINT8  u8param_count;
}param_core_t;

typedef struct{
    UINT16   ul8status:         8;
    UINT16   uh8ItemNum:        8;
}PARAM_ITEM_CNT_ACK_BITS;

typedef union
{
    PARAM_ITEM_CNT_ACK_BITS     bits;
    UINT16                      u16all;
}PARAM_ITEM_CNT_ACK_OBJ;

typedef struct{
    UINT16   ul8status:          8;
    UINT16   uh8ItemIndex:       8;
}PARAM_ACK_BITS;

typedef union{
    UINT16                      u16all;
    PARAM_ACK_BITS              bits;
}PARAM_ACK_WORD;

typedef struct
{
    PARAM_ACK_WORD              unParamItemCtrl;
    UINT16                      ua16ValueBuff[PARAM_WR_ACK_DATA_MAX_LEN];
}PARAM_WR_ACK_OBJ;

typedef struct{
    UINT16   ul8VarAttr:          8;
    UINT16   uh8VarType:          8;
}PARAM_ATTR_BITS;

typedef union{
    UINT16                      u16all;
    PARAM_ATTR_BITS              bits;
}PARAM_ATTR_WORD;

typedef struct
{
    PARAM_ACK_WORD              unParamItemCtrl;
    PARAM_ATTR_WORD             unParamAttr;
    UINT16                      ua16DefValue[2];
    UINT16                      ua16MinValue[2];
    UINT16                      ua16MaxValue[2];
    UINT16                      ua16CurValue[2];
    UINT16                      ua16VarName[PARAM_VAR_NAME_MAX_LEN >> 1];
}PARAM_GET_ITEM_ACK_OBJ;

typedef struct
{
    const void       *p_item_cfg;
    enum VAR_TYPE    emType;
    unsigned short   u16VarSize;
    list_t 			 param_node;
}param_item_t;

//=================PARAM_CFG
#ifndef DLLX64
#define REG_CFG_ITEM_U8(var_name,var,attr,def,min,max) \
        const param_item_cfg_u8_t   param_cfg_##var_name= {#var_name,attr,def,min,max,&(var)};\
        param_item_t                param_##var_name = {(const void *)&param_cfg_##var_name,eu_uint8,sizeof(var),NULL};\
        AUTO_REG_ITEM(param_item_##var_name,AUTO_REG_PARAM_CFG,(void*)&param_##var_name)

#define REG_CFG_ITEM_I8(var_name,var,attr,def,min,max) \
        const param_item_cfg_i8_t   param_cfg_##var_name= {#var_name,attr,def,min,max,&(var)};\
        param_item_t                param_##var_name = {(const void *)&param_cfg_##var_name,eu_int8,sizeof(var),NULL};\
        AUTO_REG_ITEM(param_item_##var_name,AUTO_REG_PARAM_CFG,(void*)&param_##var_name)

#define REG_CFG_ITEM_U16(var_name,var,attr,def,min,max) \
        const param_item_cfg_u16_t  param_cfg_##var_name= {#var_name,attr,def,min,max,&(var)};\
        param_item_t                param_##var_name = {(const void *)&param_cfg_##var_name,eu_uint16,sizeof(var),NULL};\
        AUTO_REG_ITEM(param_item_##var_name,AUTO_REG_PARAM_CFG,(void*)&param_##var_name)

#define REG_CFG_ITEM_I16(var_name,var,attr,def,min,max) \
        const param_item_cfg_i16_t  param_cfg_##var_name= {#var_name,attr,def,min,max,&(var)};\
        param_item_t                param_##var_name = {(const void *)&param_cfg_##var_name,eu_int16,sizeof(var),NULL};\
        AUTO_REG_ITEM(param_item_##var_name,AUTO_REG_PARAM_CFG,(void*)&param_##var_name)

#define REG_CFG_ITEM_U32(var_name,var,attr,def,min,max) \
        const param_item_cfg_u32_t  param_cfg_##var_name= {#var_name,attr,def,min,max,&(var)};\
        param_item_t                param_##var_name = {(const void *)&param_cfg_##var_name, eu_uint32,sizeof(var), NULL};\
        AUTO_REG_ITEM(param_item_##var_name,AUTO_REG_PARAM_CFG,(void*)&param_##var_name)

#define REG_CFG_ITEM_I32(var_name,var,attr,def,min,max) \
        const param_item_cfg_i32_t  param_cfg_##var_name= {#var_name,attr,def,min,max,&(var)};\
        param_item_t                param_##var_name = {(const void *)&param_cfg_##var_name,eu_int32,sizeof(var),NULL};\
        AUTO_REG_ITEM(param_item_##var_name,AUTO_REG_PARAM_CFG,(void*)&param_##var_name)

#define REG_CFG_ITEM_F32(var_name,var,attr,def,min,max) \
        const param_item_cfg_f32_t  param_cfg_##var_name= {#var_name,attr,def,min,max,&(var)};\
        param_item_t                param_##var_name = {(const void *)&param_cfg_##var_name,eu_fp32,sizeof(var),NULL};\
        AUTO_REG_ITEM(param_item_##var_name,AUTO_REG_PARAM_CFG,(void*)&param_##var_name)

#define REG_CFG_ITEM_F64(var_name,var,attr,def,min,max) \
        const param_item_cfg_f64_t  param_cfg_##var_name= {#var_name,attr,def,min,max,&(var)};\
        param_item_t                param_##var_name = {(const void *)&param_cfg_##var_name,eu_fp64,NULL};\
        AUTO_REG_ITEM(param_item_##var_name,AUTO_REG_PARAM_CFG,(void*)&param_##var_name)
#else
#define REG_CFG_ITEM_U8(var_name,var,attr,def,min,max)

#define REG_CFG_ITEM_I8(var_name,var,attr,def,min,max)

#define REG_CFG_ITEM_U16(var_name,var,attr,def,min,max)

#define REG_CFG_ITEM_I16(var_name,var,attr,def,min,max)

#define REG_CFG_ITEM_U32(var_name,var,attr,def,min,max)

#define REG_CFG_ITEM_I32(var_name,var,attr,def,min,max)

#define REG_CFG_ITEM_F32(var_name,var,attr,def,min,max)

#define REG_CFG_ITEM_F64(var_name,var,attr,def,min,max)
#endif

extern void ParamCfgCmdSetLink(void *p_stAplDmTemp);
extern void param_core_init(void);

#endif /* BSW_DEBUGPLATFORM_PARAMETER_CFG_H_ */
