/*
 * ApiProtocolStack.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */
#include <DEBUG_PLATFORM/PARAMETER_CTRL/PARAMETER_CTRL.H>
#include <DP_STACK/DLL/DLL_STACK.H>
#include "common/include/F28x_Project.h"
#include "BSW_SVC_BASIC.h"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DP_STACK/APL/APL_STACK.H"
#include "DP_STACK/DP_STACK_BASIC.H"
#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE.H"
#include "DEBUG_PLATFORM/DATA_REC/DATA_REC.H"
#include "DEBUG_PLATFORM/COMM_TEST/COMM_TEST.H"
#include "DEBUG_PLATFORM/BOOTLOAD/BOOTLOAD.H"
#include "DEBUG_PLATFORM/PERFORMACE_TEST/PERFORMACE_TEST.H"
#include "DEBUG_PLATFORM/DATA_REC/DATA_REC.h"
#include "DEBUG_PLATFORM/SFRA/SFRA.h"
#include "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB.h"

extern void Apl_Rx_Msg(FRAME_PROTOCOL_FORMAT *p_stProtlFormat);

static const CMD_LINK_ACTION_ITEM gc_stCmdLinkAction[] = REG_CMD_LINK_ACTION_TAB;

void apl_init(void){
    NWM_Init();
    TPL_Init();
    Tpl_RxMsgCallbackInit((void *)Apl_Rx_Msg);
}

pf_action_func Find_CmdSet_LinkAction(UINT8 u8CmdSet){
    unsigned int i = 0;

    const CMD_LINK_ACTION_ITEM *p_stCmdLinkAction = gc_stCmdLinkAction;

    for(i = 0; i < sizeof(gc_stCmdLinkAction)/sizeof(CMD_LINK_ACTION_ITEM); i++){
        if(p_stCmdLinkAction->u8CmdSet == u8CmdSet)
            return p_stCmdLinkAction->action_func;
        p_stCmdLinkAction ++;
    }
    return NULL;
}

void Apl_Auto_Send_Ack(FRAME_PROTOCOL_FORMAT *p_RqtAckFrame)
{
    FRAME_PROTOCOL_FORMAT stAwrAckFrame;
    UINT16 au16AwrAckBuff[6]     = {0};

    stAwrAckFrame.stAplDm.unAplCmd.u16all                   = p_RqtAckFrame->stAplDm.unAplCmd.u16all;
    stAwrAckFrame.stAplDm.u16AplDLC                         = 0;
    stAwrAckFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr        = p_RqtAckFrame->stNwmDm.unNwmAddr.bits.uh8SrcAddr;
    stAwrAckFrame.p_u16AppData                              = au16AwrAckBuff;

    Tpl_Single_Frame_Send(&stAwrAckFrame);
}

void Apl_Rx_Msg(FRAME_PROTOCOL_FORMAT *p_stProtlFormat){
    pf_action_func  p_fnAction = NULL;
    if(p_stProtlFormat == NULL)
        return;
    p_fnAction = Find_CmdSet_LinkAction(p_stProtlFormat->stAplDm.unAplCmd.bits.ul8CmdSet);
    if(p_fnAction != NULL){
          p_fnAction(&p_stProtlFormat->stAplDm);
    }

}

void apl_main(void)
{
    static UINT16 s_u16FreqDiv = 0;
    if(((s_u16FreqDiv++)&0x0001)== 0x0000)
        DLL_Handle();//every 3* 2ms = 6 ms
    TPL_Handle();   //Call the TPL layer handler function to handle error manager.
    NWM_Handle();   //Call the NWM layer handler function to call the frame receive and error management.
}



