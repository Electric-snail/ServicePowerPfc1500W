/*
 * DLL.h
 *
 *  Created on: 2022/8/21
 *      Author: xj8r1j
 */

#ifndef BSW_SVC_COMMSTACK_DLL_H_
#define BSW_SVC_COMMSTACK_DLL_H_

#include "SOFTWARE_ENV_CFG.h"
#include "DP_STACK/DP_STACK_CFG.H"

enum LINK_ID{
	LINK_INVALID_ID = 0,
    SCIA_LINK_ID,
    SCIB_LINK_ID,
    CANA_LINK_ID,
    CANB_LINK_ID,
    MCAN_LINK_ID,
    FSI_LINK_ID,
    I2CA_LINK_ID,
	PMBUS_LINK_ID,
};

enum DLL_RX_FMS{
    HEAD_BYTE0_FMS = 0,
    HEAD_BYTE1_FMS,
    HEAD_BYTE2_FMS,
    HEAD_BYTE3_FMS,
    DLC_BYTE0_FMS,
    DLC_BYTE1_FMS,
    DATA_BYTE_FMS,
    DATA1_BYTE_FMS,
};

//The head word0 bits defined,
typedef struct{
    UINT16 ul8HeadByte0:   8;
    UINT16 uh8HeadByte1:   8;
}DLL_HEAD_BITS0;

typedef union{
    UINT16                u16all;
    DLL_HEAD_BITS0        bits;
}DLL_HEAD_WORD0;

typedef struct{
    UINT16 ul8HeadByte2:   8;
    UINT16 uh8HeadByte3:   8;
}DLL_HEAD_BITS1;

typedef union{
    UINT16                u16all;
    DLL_HEAD_BITS1        bits;
}DLL_HEAD_WORD1;


//DLL Layer Header
typedef struct{
    DLL_HEAD_WORD0        unHeadWord0;
    DLL_HEAD_WORD1        unHeadWord1;
    UINT16                u16DllDLC;
}DLL_HEAD_DOMAIN;

typedef struct{
    UINT16   ul8CrcByte:    8;
    UINT16   uh8Rsv:        8;
}DLL_CRC_BITS;

typedef union{
    UINT16                 u16all;
    DLL_CRC_BITS           bits;
}DLL_CRC_WORD;

//DLL Layer Rail
typedef struct{
    DLL_CRC_WORD            unCrc;
}DLL_RAIL_DOMAIN;

#define 	DLL_TX_RING_LEN      			   DLL_TX_RING_BYTE_LEN
#define 	DLL_RX_RING_LEN					   256

#if(DLL_TX_RING_LEN < 512)
#error "the DLL_TX_RING_BYTE_LEN is configure too small."
#endif

#define   DP_DLL_HEAD_DOMAIN_BYTES_LEN         (sizeof(DLL_HEAD_DOMAIN)*TYPE_8_BYTE_SIZE)
#define   DP_DLL_RAIL_DOMAIN_BYTES_LEN         (sizeof(DLL_RAIL_DOMAIN)*TYPE_8_BYTE_SIZE)

typedef INT16 (*DEV_FRAME_READ)(UINT16 *);
typedef INT16 (*DEV_FRAME_WRITE)(void *);
extern void DLL_Handle(void);

#endif /* BSW_SVC_COMMSTACK_DLL_H_ */
