/*
 * DPCommStackCfg.h
 *
 *  Created on: 2022.8.17
 *      Author: Jiang,hongbo
 */

#ifndef BSW_SVC_DPCOMMSTACK_DPCOMMSTACKCFG_H_
#define BSW_SVC_DPCOMMSTACK_DPCOMMSTACKCFG_H_

#include "SOFTWARE_ENV_CFG.h"

/***-The total protocol of msg as follow:
DLL_DOMAIN + NWM_DOMAIN + TPL_DOMAIN + APL_DOMAIN
------------------------------------------------------------------------*/
//In order to compatible the byte addressing with word addressing, the union data is used.
typedef struct
{
    UINT16   ul8RxLinkId:        8;
    UINT16   uh8TxLinkId:        8;
}NWM_LINK_BITS0;

typedef union{
    UINT16                      u16all;
    NWM_LINK_BITS0              bits;
}NWM_LINK_WORD;



typedef struct{
    UINT16 ul8DestAddr:    8;
    UINT16 uh8SrcAddr:     8;
}NWM_ADDR_BITS;

typedef union{
    UINT16           u16all;
    NWM_ADDR_BITS     bits;
}NWM_ADDR_WORD;

typedef struct{
    UINT16   ul8RouteType:       8;
    UINT16   uh8NwmAck:          8;
}NWM_CTRL_BITS0;

typedef union{
    UINT16              u16all;
    NWM_CTRL_BITS0      bits;
}NWM_CTRL_WORD;

typedef struct{
    NWM_LINK_WORD      unNwmLink;
    NWM_ADDR_WORD      unNwmAddr;
    NWM_CTRL_WORD      unNwmCtrl;
    UINT16             u16NwmDLC;
}NWM_DOMAIN;

#define   NWM_DOMAIN_BYTES_LEN              (sizeof(NWM_DOMAIN)*TYPE_8_BYTE_SIZE)


typedef struct{
    UINT16   ul8FrameType:   8;
    UINT16   uh8FrameNum:    8;
}TPL_FRAME_BITS;

typedef union{
    UINT16              u16all;
    TPL_FRAME_BITS      bits;
}TPL_FRAM_WORD;

typedef struct{
    TPL_FRAM_WORD       unTplFrame;
    UINT16              u16TplDLC;
}TPL_DOMAIN;

#define   TPL_DOMAIN_BYTES_LEN              (sizeof(TPL_DOMAIN)*TYPE_8_BYTE_SIZE)

typedef struct{
    UINT16   ul8CmdSet:      8;
    UINT16   uh8CmdId:       8;
}APL_CMD_BITS;

typedef union{
    UINT16              u16all;
    APL_CMD_BITS        bits;
}APL_CMD_WORD;

typedef struct{
    APL_CMD_WORD        unAplCmd;
    UINT16              u16AplDLC;
}APL_DOMAIN;
#define   APL_DOMAIN_BYTES_LEN              (sizeof(APL_DOMAIN)*TYPE_8_BYTE_SIZE)

typedef struct{
    NWM_DOMAIN              stNwmDm;
    TPL_DOMAIN              stTplDm;
    APL_DOMAIN              stAplDm;
    UINT16                  *p_u16AppData;
}FRAME_PROTOCOL_FORMAT;

//unify the action status definition of in the DPSecStack
#define  BYTE_PACK_TO_WORD_IN_BUFF(BYTE_L,BYTE_H,WORD)    \
         WORD = ((unsigned int)BYTE_L | (BYTE_H << 8))


#define DLL_TX_FRAME_SUCCESS            0x01

#define DLL_RX_FRAME_SUCCESS            0x09
#define DLL_RX_NO_DATA                  0x0A
#define DLL_RX_NO_FRAME                 0x0B

#define NWM_TX_FRAME_SUCCESS            0x11
#define NWM_TX_FRAME_FAIL               0x12

#define NWM_RX_FRAME_SUCCESS            0x19

#define TPL_TX_MSG_SUCCESS              0x21
#define TPL_TX_MSG_NWM_FAIL             0x22
#define TPL_TX_MUX_FRAME_DOING          0x23
#define TPL_TX_MUX_NO_FRAME_REQUEST     0x24
#define TPL_TX_MUX_WAIT_ACK             0x25
#define TPL_TX_MUX_BUFF_DLC_ERR         0x26
#define TPL_TX_MUX_PIPE_LOCK            0x27

#define TPL_TX_SIG_DLC_ERR              0x28
#define TPL_RX_FRAME_SUCCESS            0x29
#define TPL_RX_MSG_SUCCESS              0x29



#define TX_APL_DATA_LENGTH_ERR          0x32

#endif /* BSW_SVC_DPCOMMSTACK_DPCOMMSTACKCFG_H_ */
