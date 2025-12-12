/*
 * TPL_Stack.h
 *
 *  Created on: 2022.8.18
 *      Author: xj8r1j
 */

#ifndef BSW_SVC_COMMSTACK_DPSTACK_TPL_TPL_STACK_H_
#define BSW_SVC_COMMSTACK_DPSTACK_TPL_TPL_STACK_H_
#include "PUBLIC_INC/LINE_BUFF.H"
#include "PUBLIC_INC/RING_ARRAY.H"
#include "PUBLIC_INC/MEM_HANDLE.H"
#include "DP_STACK/NWM/NWM_STACK.H"

#if( (DP_SCIB_ENABLE == 1) || (DP_SCIA_ENABLE))
#define TPL_MUX_INTERVAL_TIME       100
#elif(( DP_CANA_ENABLE == 1)||( DP_CANB_ENABLE == 1)||(DP_MCAN_ENABLE == 1))
#else
#define TPL_MUX_INTERVAL_TIME       100
#endif
typedef void (*RX_MSG_APL_CALL_BACK_FUNC)(FRAME_PROTOCOL_FORMAT *p_stProtlFormat);

enum TPL_MUX_STATUS
{
    TPL_MUX_IDLE         = 0,
    TPL_MUX_REQUEST_TX   = 1,
};

typedef struct
{
    enum TPL_MUX_STATUS         enStatus;
    UINT16                      u16TplMuxTxTimer;
    UINT8                       u8RpsByte;
    FRAME_PROTOCOL_FORMAT       stFrameProtocolFormat;
    BUFF_CTRL_OBJ               stMulFrameBuffCtrlObj;
}TPL_MUX_MSG_CTRL_INFO;

#define  SINGLE_FRAME                       0
#define  MUL_FRAME                          1

#define  TPL_NO_ACK                         0
#define  TPL_REQUEST_ACK                    1
#define  TPL_ANSWER_ACK                     2

extern void  TPL_Init(void);
extern void  TPL_Handle(void);
extern void  Tpl_RxMsgCallbackInit(void *);
extern UINT8 Tpl_Single_Frame_Send(FRAME_PROTOCOL_FORMAT *);
extern UINT8 Tpl_Msg_Send(BUFF_CTRL_OBJ *p_stBuffCtrlInfo,FRAME_PROTOCOL_FORMAT *p_stTplFrameInfo);
#endif /* BSW_SVC_COMMSTACK_DPSTACK_TPL_TPL_STACK_H_ */
