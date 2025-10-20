/*
 * NWM_Stack.h
 *
 *  Created on: 2022.8.17
 *      Author: xj8r1j
 */

#ifndef BSW_SVC_COMMSTACK_DPSTACK_NWM_NWM_STACK_H_
#define BSW_SVC_COMMSTACK_DPSTACK_NWM_NWM_STACK_H_

#include "DP_STACK/DLL/DLL_STACK.H"
#include "DP_STACK/DP_STACK_BASIC.H"
#include "DP_STACK/DP_STACK_CFG.H"

#define  PFC_NODE_ADDR                 01
#define  LLC_NODE_ADDR                 02
#define  MCB_NODE_ADDR                03
#define  PC_NODE_ADDR              		 04
#define  DCDC_NODE_ADDR              05
#define  ITSELF_NODE_ADDR            PFC_NODE_ADDR

#define  ROUTE_ADDR_TYPE            0
#define  ROUTE_LINK_TYPE            1

#define  NO_REG_ADDR                1
#define  NO_REG_LINK                2

#define  PIPE_READ_LOCK             0
#define  PIPE_WRITE_LOCK            1

typedef enum{
    ROUTE_SUCESS            = 0,
    ROUTE_NO_REG_ADDR       = 1,
    ROUTE_NO_REG_LINK       = 2,
    ROUTE_PIPE_READ_LOCK    = 3,
    ROUTE_PIPE_WRITE_LOCK   = 4,
    ROUTE_DISABLE           = 5,
    ROUTE_WRITE_FAIL        = 6,
}NWM_ROUTE_STATUS;

typedef struct{
    UINT8 u8Addr;
    UINT8 u8LinkId;
}ADDR_LINK_ITEM;

typedef struct{
    UINT8 u8SrcLinkId;
    UINT8 u8DestLinkId;
}ROUTE_LINK_ITEM;

typedef struct{
    enum LINK_ID        enLinkId;
    DEV_FRAME_READ      p_fnDevRead;
    DEV_FRAME_WRITE     p_fnDevWrite;
    UINT16              *p_u16BuffAddr;
}LINK_HAL_ITEM;

typedef struct{
    enum LINK_ID           					 enLinkId;
    UINT16                						 u16Lock;
    FRAME_PROTOCOL_FORMAT   stRouteFrame;
}PIPE_CTRL_INFO;

#define REG_ADDR_LINK_ITEM_TAB  \
{\
    {PC_NODE_ADDR,    SCIB_LINK_ID},\
    {LLC_NODE_ADDR,  SCIB_LINK_ID},\
/*     {DCDC_NODE_ADDR,   MCAN_LINK_ID}, */\
}

#define  REG_LINK_HAL_TAB   \
{\
   {SCIB_LINK_ID,   	dll_scib_frame_read, 		dll_scib_frame_write, 		g_au16DllScibRxMsgBuff}, \
/*   {FSI_LINK_ID,   DLL_Fsi_Frame_Read,  DLL_Fsi_Frame_Write,  g_au16DLLFsiRxMsgBuff},  \
   {MCAN_LINK_ID,  DLL_Mcan_Frame_Read, DLL_Mcan_Frame_Write, g_au16DLLMcanRxMsgBuff},*/\
}

typedef void (*RX_FRAME_CALL_BACK_FUNC)(FRAME_PROTOCOL_FORMAT *p_stProtlFormat);

extern INT8 Nwm_Frame_Tx(FRAME_PROTOCOL_FORMAT *);
extern void Nwm_Frame_Rx_Callback_Init(void *p_fn);
extern void NWM_Handle(void);
extern void NWM_Init(void);
#endif /* BSW_SVC_COMMSTACK_DPSTACK_NWM_NWM_STACK_H_ */
