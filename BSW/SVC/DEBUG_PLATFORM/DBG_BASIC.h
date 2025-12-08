/*
 * dbg_basic.h
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */
#ifndef _DBG_BASIC_H_
#define _DBG_BASIC_H_

enum VAR_TYPE
{
    eu_int8     = 0x10,
    eu_uint8    = 0x11,
    eu_int16    = 0x12,
    eu_uint16   = 0x13,
    eu_int32    = 0x14,
    eu_uint32   = 0x15,
    eu_fp32     = 0x16,
};

#define  ENABLE_PARAM_CFG               					(1)
#define  DATA_REC_MAX_CNT               					12
#define  VAR_NAME_CHAR_MAX_LEN_BYTE     					32
#define  SCOPE_VAR_MAX_ITEM_CNT         					6

#if(SCOPE_VAR_MAX_ITEM_CNT > 6)
#error"The SCOPE_VAR_MAX_ITEM_CNT must below 7"
#endif

#if(DATA_REC_MAX_CNT > 12)
#error the maximum counter of data record variable must be less than 13
#endif

#if(VAR_NAME_CHAR_MAX_LEN_BYTE > 32)
#error the maximum length of variable name char must be less than 33
#endif

#endif

