/*
 * CommTest.c
 *
 *  Created on: 2022.10.22
 *      Author:  Hongbo.Jiang
 */
#include "BSW_SVC_BASIC.h"
#include "DEBUG_PLATFORM/DBG_BASIC.H"
#include "DEBUG_PLATFORM/COMM_TEST/COMM_TEST.H"
#include "DP_STACK/DP_STACK_BASIC.H"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DP_STACK/APL/APL_STACK.H"
#include "PUBLIC_INC/MEM_HANDLE.H"
#include "TASK/BSW_TASK_SERVICE.h"

static COMM_TEST_RX_INFO gs_stCommTestRxInfoObj;
static COMM_TEST_TX_INFO gs_stCommTestTxInfoObj;

void comm_test_init(void)
{
	memclr_user((UINT16 *)&gs_stCommTestRxInfoObj,sizeof(COMM_TEST_RX_INFO)/sizeof(UINT16));
	memclr_user((UINT16 *)&gs_stCommTestTxInfoObj,sizeof(COMM_TEST_TX_INFO)/sizeof(UINT16));
	gs_stCommTestRxInfoObj.u8CommTestCmd = COMM_TEST_STOP_CMD;
}

void comm_test_task(void)
{
	FRAME_PROTOCOL_FORMAT st_CommTestFrame = {0};
	UINT16 u16CommTestAplBuff[64] = {0};
    static UINT16 s_u16RxTestPeriodCnt = 0;
    static UINT32 s_u32TxMsgCnt = 0;
    static UINT16 s_u16TxTestFeedbackPeriodCnt = 0;
	if((gs_stCommTestRxInfoObj.u8CommTestCmd == COMM_TEST_RUN_CMD)&&\
	  (gs_stCommTestRxInfoObj.u16AplDLC <= 128))
	{
		s_u16RxTestPeriodCnt += COMM_TEST_TASK_PERIOD;
		if(s_u16RxTestPeriodCnt > gs_stCommTestRxInfoObj.u16Intv)
		{
			s_u16RxTestPeriodCnt = 0;
			st_CommTestFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;
			st_CommTestFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = COMM_TEST_CMD_SET;
			st_CommTestFrame.stAplDm.unAplCmd.bits.uh8CmdId         = RX_TEST_DATA_CMD_ID;
			st_CommTestFrame.stAplDm.u16AplDLC                  = ((gs_stCommTestRxInfoObj.u16AplDLC + 1)&0xfffe);
			st_CommTestFrame.p_u16AppData                       = u16CommTestAplBuff;
			u16CommTestAplBuff[0]                               = (UINT16)s_u32TxMsgCnt;
			u16CommTestAplBuff[1]                               = (UINT16)(s_u32TxMsgCnt >> 16);
			if(Tpl_Single_Frame_Send(&st_CommTestFrame) == 1)
			  s_u32TxMsgCnt++;
		}
	}else{
		s_u32TxMsgCnt = 0;
	}

	if(gs_stCommTestTxInfoObj.u8CommTestCmd == COMM_TEST_RUN_CMD)
	{
		s_u16TxTestFeedbackPeriodCnt+= COMM_TEST_TASK_PERIOD;
		if(s_u16TxTestFeedbackPeriodCnt >= 10*gs_stCommTestTxInfoObj.u16Intv)
		{
			s_u16TxTestFeedbackPeriodCnt = 0;
			st_CommTestFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;
			st_CommTestFrame.stAplDm.unAplCmd.bits.ul8CmdSet    = COMM_TEST_CMD_SET;
			st_CommTestFrame.stAplDm.unAplCmd.bits.uh8CmdId     = TX_TEST_FEEDBACK_NUM_CMD_ID;
			st_CommTestFrame.stAplDm.u16AplDLC                  = 2;
			st_CommTestFrame.p_u16AppData                       = u16CommTestAplBuff;
			u16CommTestAplBuff[0]                               = (UINT16)gs_stCommTestTxInfoObj.u32SuccRxCnt;
			u16CommTestAplBuff[1]                               = (UINT16)(gs_stCommTestTxInfoObj.u32SuccRxCnt >> 16);
			Tpl_Single_Frame_Send(&st_CommTestFrame);
		}
	}else{
		s_u16TxTestFeedbackPeriodCnt 	    = 0;
		gs_stCommTestTxInfoObj.u32SuccRxCnt = 0;
	}

}

void GetCommRxCmdInfo(APL_DOMAIN *p_stAplDm)
{
    UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));
    gs_stCommTestRxInfoObj.u8CommTestCmd = *p_u16Data++;
    gs_stCommTestRxInfoObj.u16AplDLC = *p_u16Data++;
    gs_stCommTestRxInfoObj.u16Intv   = *p_u16Data;
}

void GetCommTxCmdInfo(APL_DOMAIN *p_stAplDm)
{
    UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));
    gs_stCommTestTxInfoObj.u8CommTestCmd = *p_u16Data++;
    gs_stCommTestTxInfoObj.u16Intv       = *p_u16Data;
}

void GetCommTxData(void)
{
	gs_stCommTestTxInfoObj.u32SuccRxCnt++;
}

void CommTestCmdSetLink(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    UINT8 u8CmdId;
    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;
    switch(u8CmdId){
    	case RX_TEST_RUN_CMD_ID:
    	{
    	   GetCommRxCmdInfo(p_stAplDm);
    	}break;
    	case TX_TEST_RUN_CMD_ID:
    	{
    	   GetCommTxCmdInfo(p_stAplDm);
    	}break;
    	case TX_TEST_DATA_CMD_ID:
    	{
    	   GetCommTxData();
    	}break;
        default:break;
    }
}


