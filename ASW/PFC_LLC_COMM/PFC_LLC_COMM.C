/*
 * asw_sci_comm.c
 *
 *  Created on: 2022/8/30
 *      Author:   Hongbo.Jiang
 */
#include "TASK/BSW_TASK_SERVICE.h"
#include "BSW_SVC_BASIC.h"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DP_STACK/APL/APL_STACK.H"
#include "DP_STACK/DP_STACK_BASIC.H"
#include "PFC_LLC_COMM/PFC_LLC_COMM.H"
#include "PFC_LLC_COMM/PFC_LLC_COMM_INF.h"
#include "ASW/ASW_BASIC.h"



void pfc_llc_comm_init(void)
{
}


void pfc_send_msg_task_50ms(void)
{
	unsigned short ua16AppTxBuff[10] = {0};
    FRAME_PROTOCOL_FORMAT stAwrAckFrame;
    stAwrAckFrame.stAplDm.unAplCmd.bits.ul8CmdSet            = PFC_LLC_DATA_CMD_SET;
    stAwrAckFrame.stAplDm.unAplCmd.bits.uh8CmdId             = CMD_ID_DATA_ITEM;
    stAwrAckFrame.stAplDm.u16AplDLC                                    = 10 * TYPE_8_BYTE_SIZE;
    stAwrAckFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr   = LLC_NODE_ADDR;
    stAwrAckFrame.p_u16AppData                                          = ua16AppTxBuff;

    Tpl_Single_Frame_Send(&stAwrAckFrame);
}

unsigned short g_u16PfcRxFrameCnt = 0;
void pfc_llc_comm_rx_hander(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    UINT8 u8CmdId;
    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;

    switch(u8CmdId){
        case CMD_ID_DATA_ITEM:
            g_u16PfcRxFrameCnt++;
       //     RxCommSlowDataDpStack(p_stAplDm);
        break;
        default:break;
    }
}


