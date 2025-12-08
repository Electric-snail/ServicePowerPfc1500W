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
#include "DIAGNOSTIC/DIAGNOSTIC.H"
#include "MEASURE/MEASURE.H"
#include "ASW/ASW_BASIC.h"


 PFC_LLC_COMM_OUT    g_stPfcLlcCommOut;
 unsigned short g_u16VpfcRef             = 400;
 unsigned short g_u16PfcStopCmd      = 1;

void pfc_llc_comm_init(void)
{
	g_stPfcLlcCommOut.u16VpfcRef 		= 400;
	g_stPfcLlcCommOut.u8PfcStopCmd 	= 1;
}


void pfc_send_msg_task_50ms(void)
{
	unsigned short ua16AppTxBuff[7] = {0};
	unsigned short u16Temp;
    FRAME_PROTOCOL_FORMAT stAwrAckFrame;
    stAwrAckFrame.stAplDm.unAplCmd.bits.ul8CmdSet            = PRI_SEC_DATA_CMD_SET;
    stAwrAckFrame.stAplDm.unAplCmd.bits.uh8CmdId             = PFC_TO_LLC_DATA_ITEM_CMD_ID;
    stAwrAckFrame.stAplDm.u16AplDLC                                   = 14;
    stAwrAckFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr   = LLC_NODE_ADDR;
    u16Temp																					= (unsigned short)(f32_get_vin_rms() * 10.0f);
    ua16AppTxBuff[0]																	=    u16Temp;
    u16Temp																					= (unsigned short)(f32_get_iin_rms() * 100.0f);
    ua16AppTxBuff[1]																	=    u16Temp;

    u16Temp																					= (unsigned short)(f32_get_pin_ave() * 10.0f);
    ua16AppTxBuff[2]																	=    u16Temp;

    u16Temp																					= (unsigned short)(f32_get_vpfc_lpf() * 10.0f);
    ua16AppTxBuff[3]																	=   u16Temp;
    u16Temp																					= (unsigned short)(f32_get_vin_freq()  * 100.0f);
    ua16AppTxBuff[4]																	=  u16Temp;

    ua16AppTxBuff[5]                                                                 =  u16_get_auto_recv_diag();

    ua16AppTxBuff[6]                                                                 =  u16_get_no_recv_diag();

    stAwrAckFrame.p_u16AppData                                              = ua16AppTxBuff;

    Tpl_Single_Frame_Send(&stAwrAckFrame);
}

void RxCommSlowDataDpStack(APL_DOMAIN* p_stAplDm)
{
    static unsigned short s_u16Cnt = 0;
    unsigned short u16Temp;
    UINT16   *p_u16AplData   = NULL;
    if(p_stAplDm -> u16AplDLC != 4) 		return;

    p_u16AplData   = (unsigned short *)p_stAplDm + sizeof(APL_DOMAIN);
    u16Temp = *p_u16AplData++;
    if(u16Temp > 380){
    	g_stPfcLlcCommOut.u16VpfcRef = u16Temp;
    }
    g_stPfcLlcCommOut.u8PfcStopCmd = *p_u16AplData & 0x00ff;

    s_u16Cnt++;
}

unsigned short g_u16PfcRxFrameCnt = 0;
void pfc_llc_comm_rx_hander(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    UINT8 u8CmdId;
    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;

    switch(u8CmdId){
        case LLC_TO_PFC_DATA_ITEM_CMD_ID :
            g_u16PfcRxFrameCnt++;
            RxCommSlowDataDpStack(p_stAplDm);
        break;
        default:break;
    }
}


