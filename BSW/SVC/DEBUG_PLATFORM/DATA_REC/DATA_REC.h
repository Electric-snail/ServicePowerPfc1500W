/*
 * Data_Record.h
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#ifndef _DATA_RECORD_H_
#define _DATA_RECORD_H_
#include "PUBLIC_INC/LIST.H"

#define DATA_LOG_GET_DATA_CMD_ID     			0x00
#define DATA_LOG_GET_CFG_CMD_ID         		0x01
#define DATA_LOG_STOP_CMD_ID                    0x02

#define DATA_LOG_RESPONSE_DATA_CMD_ID   0x10
#define DATA_LOG_RESPONSE_CFG_CMD_ID    0x11

typedef struct{
    UINT16   ul8Index:        	  8;
    UINT16   uh8NameLen:          8;
}REC_NAME_BITS;

typedef union{
	UINT16             u16all;
	REC_NAME_BITS      bits;
}REC_NAME_WORD;

typedef struct
{
	REC_NAME_WORD       unRecItemNameCtrl;
}REC_ITEM_CFG;

typedef struct{
    UINT16   ul8Index:        	  8;
    UINT16   uh8VarCnt:           8;
}REC_DATA_BITS;

typedef union{
	UINT16             u16all;
	REC_DATA_BITS      bits;
}REC_DATA_WORD;


typedef struct{
    UINT16   ul8VarType:    8;
    UINT16   uh8VarSize:    8;
}REC_VAR_ATTR_BITS;

typedef union{
	UINT16                 u16all;
	REC_VAR_ATTR_BITS      bits;
}REC_VAR_ATTR;


typedef struct{
	REC_VAR_ATTR   unRecVarAttr;
	REC_NAME_WORD  unRecVarNameCtrl;
}REC_VAR_CFG;

typedef void (*pf_void_rec_func)(void);

typedef struct
{
    list_t                rec_init_node;
    pf_void_rec_func      rec_cfg_func;
}REC_NODE_OBJ;

extern   UINT32 g_u32SysTimerMs;
#define  REC_TIME_STAMP   			g_u32SysTimerMs

extern void DataLogCmdSetLink(void *p_stAplDmTemp);

#endif /* BSW_DEBUGPLATFORM_DATA_RECORD_H_ */
