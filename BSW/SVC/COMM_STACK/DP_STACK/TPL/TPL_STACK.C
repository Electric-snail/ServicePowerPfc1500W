/*
 * TPL_Stack.c
 *
 *  Created on: 2022.8.18
 *      Author: xj8r1j
 */

#include "PUBLIC_INC/MEM_HANDLE.H"
#include "DP_STACK/DP_STACK_BASIC.H"
#include "DP_STACK/DP_STACK_CFG.H"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"

//It use to ring buff data Tx.
UINT16 gs_au16TplTxDataBuff[(DP_TPL_SIG_FRAME_TX_MAX_BYTE_LEN + 1) >> 1] = {0};

TPL_MUX_MSG_CTRL_INFO g_stTplMuxCtrlInfo;

static RX_MSG_APL_CALL_BACK_FUNC   p_fnMsgRxAplCallback = NULL;
static UINT16 gs_u16MuxHandPeriod = 0;
extern void Tpl_Frame_Recv(FRAME_PROTOCOL_FORMAT *p_stProtlFormat);

void Tpl_Mux_Tx_Init(void){
    g_stTplMuxCtrlInfo.enStatus             =  TPL_MUX_IDLE;
    g_stTplMuxCtrlInfo.u16TplMuxTxTimer     = 0;
    memclr_user((UINT16 *)&g_stTplMuxCtrlInfo.stFrameProtocolFormat, sizeof(FRAME_PROTOCOL_FORMAT)/sizeof(UINT16));
    memclr_user((UINT16 *)&g_stTplMuxCtrlInfo.stMulFrameBuffCtrlObj, sizeof(BUFF_CTRL_OBJ)/sizeof(UINT16));
}

void Tpl_RxMsgCallbackInit(void *p_vData){
	p_fnMsgRxAplCallback = (RX_MSG_APL_CALL_BACK_FUNC)p_vData;
}

void TPL_Init(void){
    Tpl_Mux_Tx_Init();

    Nwm_Frame_Rx_Callback_Init((void *)Tpl_Frame_Recv);
}


void Tpl_Frame_Recv(FRAME_PROTOCOL_FORMAT *p_stProtlFormat){
    if(p_stProtlFormat == NULL)
        return;
    if(p_stProtlFormat->stTplDm.unTplFrame.bits.ul8FrameType == SINGLE_FRAME){
    	if(p_fnMsgRxAplCallback != NULL)
    	   p_fnMsgRxAplCallback(p_stProtlFormat);
    }

}

UINT8 Tpl_Single_Frame_Send(FRAME_PROTOCOL_FORMAT *p_stTplFrameInfo)
{
    unsigned int u16DataSize;
    UINT8        u8NwmFrameTxStatus;
    u16DataSize = p_stTplFrameInfo->stAplDm.u16AplDLC;
    if(u16DataSize > DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN)
        return TPL_TX_SIG_DLC_ERR;
    p_stTplFrameInfo->stTplDm.unTplFrame.bits.ul8FrameType  = SINGLE_FRAME;
    p_stTplFrameInfo->stTplDm.unTplFrame.bits.uh8FrameNum   = 0;
    p_stTplFrameInfo->stTplDm.u16TplDLC                     = p_stTplFrameInfo->stAplDm.u16AplDLC + sizeof(APL_DOMAIN)*TYPE_8_BYTE_SIZE;
    u8NwmFrameTxStatus = Nwm_Frame_Tx(p_stTplFrameInfo);
    if(u8NwmFrameTxStatus == NWM_TX_FRAME_SUCCESS)
    	return TPL_TX_MSG_SUCCESS;
    else
    	return TPL_TX_MSG_NWM_FAIL;
}

UINT8 Tpl_Msg_Send(BUFF_CTRL_OBJ *p_stBuffCtrlInfo,FRAME_PROTOCOL_FORMAT *p_stTplFrameInfo)
{
    LINE_BUF_OBJ *p_stLineBufObj;
    RING_ITEM     *p_stRingItem;
    INT16        i16DataWordSize = 0;
    UINT16       u16DataByteCnt  = 0;
    UINT16       i = 0;
    UINT16       *p_u16Output = NULL;
    UINT8        u8NwmFrameTxStatus;
    if(p_stBuffCtrlInfo->enBuffType == LINE_BUFF_TYPE){
        p_stLineBufObj 		= (LINE_BUF_OBJ *)p_stBuffCtrlInfo->p_BuffObj;
        i16DataWordSize    	= p_stLineBufObj->i16TotalSize - p_stLineBufObj->i16IdSize;
    }else{
    	p_stRingItem    		= (RING_ITEM *)p_stBuffCtrlInfo->p_BuffObj;
        i16DataWordSize         = (p_stRingItem->i16TotalSize - p_stRingItem->i16IdelSize);
    }
    u16DataByteCnt =  (UINT16)(i16DataWordSize << 1);
    //Single Frame Send
    if(u16DataByteCnt <=  DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN){  			//Only single frame send
        if(p_stTplFrameInfo->stAplDm.u16AplDLC != u16DataByteCnt)  //Check the data length in p_stBuffCtrlInfo with the apl data length in p_stTplFrameInfo
           return TX_APL_DATA_LENGTH_ERR;
        p_stTplFrameInfo->stTplDm.unTplFrame.bits.ul8FrameType  = SINGLE_FRAME;
        p_stTplFrameInfo->stTplDm.unTplFrame.bits.uh8FrameNum   = 0;
        p_stTplFrameInfo->stTplDm.u16TplDLC                     = p_stTplFrameInfo->stAplDm.u16AplDLC + sizeof(APL_DOMAIN)*TYPE_8_BYTE_SIZE;
        if(p_stBuffCtrlInfo->enBuffType == LINE_BUFF_TYPE){
        	p_stTplFrameInfo->p_u16AppData = p_stLineBufObj->p_u16HeadBuf;
        	u8NwmFrameTxStatus = Nwm_Frame_Tx(p_stTplFrameInfo);
        	if(u8NwmFrameTxStatus == 1)
        		return TPL_TX_MSG_SUCCESS;
        	else
        		return TPL_TX_MSG_NWM_FAIL;
        }else{
        	p_u16Output = p_stRingItem->p_u16Output;
            for(i = 0; i < i16DataWordSize; i ++){
               gs_au16TplTxDataBuff[i] = *p_u16Output++;
               if(p_u16Output >= \
                              (p_stRingItem->p_u16HeadAddr + p_stRingItem->i16TotalSize))
            	   p_u16Output = p_stRingItem->p_u16HeadAddr;
            }
            p_stRingItem->enRingCmd   = RING_IDLE;
            p_stRingItem->enRingStaus = RING_EMPTY;
            p_stTplFrameInfo->p_u16AppData = gs_au16TplTxDataBuff; //gs_au16TplTxDataBuff will not be used in the same time.
            u8NwmFrameTxStatus = Nwm_Frame_Tx(p_stTplFrameInfo);
            if(u8NwmFrameTxStatus == NWM_TX_FRAME_SUCCESS)
               return TPL_TX_MSG_SUCCESS;
            else
               return TPL_TX_MSG_NWM_FAIL;
        }
    }

    //Mult frame send, at this function, only copy information to tpl mux frame control obj.
    if(u16DataByteCnt > DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN){
        if(g_stTplMuxCtrlInfo.enStatus != TPL_MUX_IDLE) //Check if TPL MUX is lock write. if one mul msg have not been sent, the TPL MUL is locked write.
            return TPL_TX_MUX_PIPE_LOCK;

        g_stTplMuxCtrlInfo.enStatus                             = TPL_MUX_REQUEST_TX;
        g_stTplMuxCtrlInfo.u8RpsByte                            = TPL_NO_ACK;

        //Configure the TPL domain data.
        p_stTplFrameInfo->stTplDm.unTplFrame.bits.ul8FrameType  = MUL_FRAME;
        p_stTplFrameInfo->stTplDm.unTplFrame.bits.uh8FrameNum   = 0;
        p_stTplFrameInfo->stTplDm.u16TplDLC                     = DP_APL_SIG_FRAME_TX_MAX_BYTE_LEN;

        //Store the multi frame protocol format.
        memcpy((UINT16 *)&g_stTplMuxCtrlInfo.stFrameProtocolFormat,(UINT16 *)p_stTplFrameInfo,sizeof(FRAME_PROTOCOL_FORMAT));

        //Store the app data buff object to used in TPL_Handler.
        memcpy((UINT16 *)&g_stTplMuxCtrlInfo.stMulFrameBuffCtrlObj,(UINT16 *)p_stBuffCtrlInfo,sizeof(BUFF_CTRL_OBJ));

        gs_u16MuxHandPeriod = 0;
        return TPL_TX_MSG_SUCCESS;
    }else{
        //if the i16DataSize is the negative, the tpl mux should be init.
        Tpl_Mux_Tx_Init();
        return TPL_TX_MUX_BUFF_DLC_ERR;
    }
}

UINT8 TPL_Mux_Frame_Handle(void){
    LINE_BUF_OBJ *p_stLineBufObj    = NULL;
    RING_ITEM     *p_stRingItem       = NULL;
    INT16        i16DataWordSize    = 0;
    INT16        i16DataByteSize    = 0;
    INT16        i16DataSizeTemp0   = 0;
    UINT16       u16TheLastFrame    = 0;
    UINT16       u16NwmFrameTxStatus = 0;
    UINT16       i =0;
    if(g_stTplMuxCtrlInfo.enStatus != TPL_MUX_REQUEST_TX)
        return TPL_TX_MUX_NO_FRAME_REQUEST;

    if(g_stTplMuxCtrlInfo.u8RpsByte == TPL_REQUEST_ACK)
        return TPL_TX_MUX_WAIT_ACK;

    if(g_stTplMuxCtrlInfo.stMulFrameBuffCtrlObj.enBuffType == LINE_BUFF_TYPE){
        p_stLineBufObj              = (LINE_BUF_OBJ *)g_stTplMuxCtrlInfo.stMulFrameBuffCtrlObj.p_BuffObj;
        i16DataWordSize 			= p_stLineBufObj->i16TotalSize - p_stLineBufObj->i16IdSize;
        i16DataSizeTemp0 		    = (i16DataWordSize > (DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN >> 1))?(DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN >> 1):i16DataWordSize;
        g_stTplMuxCtrlInfo.stFrameProtocolFormat.p_u16AppData = p_stLineBufObj->p_u16HeadBuf + p_stLineBufObj->u16R_Index;
    }else{
        p_stRingItem      = (RING_ITEM *)g_stTplMuxCtrlInfo.stMulFrameBuffCtrlObj.p_BuffObj;
        i16DataWordSize  = (p_stRingItem->i16TotalSize - p_stRingItem->i16IdelSize);
        i16DataSizeTemp0 = (i16DataWordSize > (DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN >> 1))?(DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN >> 1):i16DataWordSize;
        for(i = 0; i < i16DataSizeTemp0; i++){
        	gs_au16TplTxDataBuff[i] = *(p_stRingItem->p_u16Output);
        	p_stRingItem->p_u16Output ++;
        	if(p_stRingItem->p_u16Output >= (p_stRingItem->p_u16HeadAddr + p_stRingItem->i16TotalSize))
        		p_stRingItem->p_u16Output = p_stRingItem->p_u16HeadAddr;
        }
        p_stRingItem->i16IdelSize = p_stRingItem->i16IdelSize + i16DataSizeTemp0;
        g_stTplMuxCtrlInfo.stFrameProtocolFormat.p_u16AppData = gs_au16TplTxDataBuff;
    }
    //Judge whether is it the last frame, and the data length of buff is correct
    i16DataByteSize = i16DataWordSize << 1;
    if(i16DataByteSize <= DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN){  //The last frame will be sent.
        u16TheLastFrame = 1;
        g_stTplMuxCtrlInfo.stFrameProtocolFormat.stTplDm.unTplFrame.bits.uh8FrameNum    = 0xFF; //it means the end of frame.
    }
     //the i16DataSizeTemp0 is used, the i16DataSizeTemp1 cannot be used in follow.
     g_stTplMuxCtrlInfo.stFrameProtocolFormat.stAplDm.u16AplDLC                 = (i16DataSizeTemp0 << 1);
     g_stTplMuxCtrlInfo.stFrameProtocolFormat.stTplDm.u16TplDLC                 = (i16DataSizeTemp0 << 1) + sizeof(APL_DOMAIN)*TYPE_8_BYTE_SIZE;
     // Send the mux frame by NWM_Frame_Tx.
     g_stTplMuxCtrlInfo.u16TplMuxTxTimer ++;
     u16NwmFrameTxStatus = Nwm_Frame_Tx(&g_stTplMuxCtrlInfo.stFrameProtocolFormat);

     if(u16NwmFrameTxStatus == NWM_TX_FRAME_SUCCESS){
    	  g_stTplMuxCtrlInfo.stFrameProtocolFormat.stTplDm.unTplFrame.bits.uh8FrameNum++;
          if(1 == u16TheLastFrame){
             g_stTplMuxCtrlInfo.u16TplMuxTxTimer     = 0;
             g_stTplMuxCtrlInfo.enStatus             = TPL_MUX_IDLE;
             if(g_stTplMuxCtrlInfo.stMulFrameBuffCtrlObj.enBuffType == LINE_BUFF_TYPE){
                  p_stLineBufObj->i16IdSize          =  p_stLineBufObj->i16TotalSize;
                  p_stLineBufObj->u16R_Index         =  0;
                  p_stLineBufObj->u16W_Index         =  0;
                  p_stLineBufObj->enState            =  BUFF_EMPTY;
                  p_stLineBufObj->enCmd              =  BUFF_UNLOCK;
             }else if(g_stTplMuxCtrlInfo.stMulFrameBuffCtrlObj.enBuffType == RING_BUFF_TYPE){
            	 p_stRingItem->p_u16Input  = p_stRingItem->p_u16HeadAddr;
            	 p_stRingItem->p_u16Output = p_stRingItem->p_u16HeadAddr;
            	 p_stRingItem->i16IdelSize = p_stRingItem->i16TotalSize;
            	 p_stRingItem->enRingStaus = RING_EMPTY;
            	 p_stRingItem->enRingCmd   = RING_IDLE;
             }
             return TPL_TX_MSG_SUCCESS;
         }else{
             if(g_stTplMuxCtrlInfo.stMulFrameBuffCtrlObj.enBuffType == LINE_BUFF_TYPE){
                 p_stLineBufObj->u16R_Index += i16DataSizeTemp0;
                 p_stLineBufObj->i16IdSize  += i16DataSizeTemp0;
              }
             return TPL_TX_MUX_FRAME_DOING;
         }
     }else{
         if(g_stTplMuxCtrlInfo.stMulFrameBuffCtrlObj.enBuffType == RING_BUFF_TYPE){
             for(i = 0; i < i16DataSizeTemp0; i++){
            	 p_stRingItem->p_u16Output --;
             	if(p_stRingItem->p_u16Output < p_stRingItem->p_u16HeadAddr)
             		p_stRingItem->p_u16Output = (p_stRingItem->p_u16HeadAddr + p_stRingItem->i16TotalSize - 1);
             }
             p_stRingItem->i16IdelSize = p_stRingItem->i16IdelSize - i16DataSizeTemp0;
         }
    	 return TPL_TX_MUX_FRAME_DOING;
     }
}
void TPL_Handle(void)
{
 //If MUX MSG Send Channel lock?.
 //In generally only after one MUL MSG be sent, the MUX MSG channel will be unlock
    static UINT16 s_u16TplTimerCnt = 0;
    s_u16TplTimerCnt ++;
    UINT8 u8TplMuxFrameStatus = 0;
    //Check whether mult frame request to be send.
    if(s_u16TplTimerCnt > gs_u16MuxHandPeriod)
    {
       u8TplMuxFrameStatus  = TPL_Mux_Frame_Handle();
       s_u16TplTimerCnt     = 0;
       gs_u16MuxHandPeriod  = TPL_MUX_INTERVAL_TIME;

       if(u8TplMuxFrameStatus == TPL_TX_MUX_BUFF_DLC_ERR){
    	   Tpl_Mux_Tx_Init();
       }else if(g_stTplMuxCtrlInfo.u16TplMuxTxTimer >= 800){
    	   Tpl_Mux_Tx_Init();
       }
    }
}
