/*
 * SW_Scope.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#include "BSW_SVC_BASIC.H"
#include "DEBUG_PLATFORM/DBG_BASIC.H"
#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE.H"
#include "DP_STACK/DP_STACK_BASIC.H"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DP_STACK/APL/APL_STACK.H"
#include "PUBLIC_INC/MEM_HANDLE.H"
#include "string.h"

RING_ITEM g_stScopeRingCtrl = {0};
RING_ITEM g_stScopeCopyRingCtrl = {0};

#define GEN_SW_SCOPE_VAR_ENTITY
	#include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
#undef GEN_SW_SCOPE_VAR_ENTITY

#define GEN_SW_SCOPE_INIT_ENTITY
        #include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
#undef GEN_SW_SCOPE_INIT_ENTITY

#define GEN_SW_SCOPE_ITEM_ENTITY
       #include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
#undef GEN_SW_SCOPE_ITEM_ENTITY

/*#define GEN_SW_SCOPE_GUI_SET_ACTION_ENTITY
        #include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
#undef GEN_SW_SCOPE_GUI_SET_ACTION_ENTITY*/

#define GEN_SW_SCOPE_DATA_ENTITY
      #include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
#undef GEN_SW_SCOPE_DATA_ENTITY

#define GEN_SW_SCOPE_RUN_CMD_ENTITY
      #include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
#undef GEN_SW_SCOPE_RUN_CMD_ENTITY

void sw_scope_gui_set_action(APL_DOMAIN *p_stAplDm){
			UINT16 u16GuiIdStatus = 0;
			UINT16 *p_u16FloatTemp = NULL;
			FRAME_PROTOCOL_FORMAT st_ScopeGuiFrame = {0};
			UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));
			if((g_stScopeCtrlInfo.u8Enable == 0)||(g_stScopeCtrlInfo.u8DataMsgTxFlg == 1)||(g_stScopeCtrlInfo.u8RunStopCmd == SCOPE_RUN_CMD)) return;
	//		if(startup_mode == STARTUP_ITSELF) return;
			if(p_stAplDm->u16AplDLC == 10)
			{\
				if((g_stScopeRingCtrl.enRingCmd == RING_IDLE)||(g_stScopeRingCtrl.enRingCmd == RING_REQUEST_WRITE)){
					 g_stGuiCfgSwScope.emTrigMethod = (SW_SCOPE_TRIGG_METHOD_M)(*p_u16Data & 0x00FF);
					 g_stGuiCfgSwScope.emTrigPoint  = (SW_SCOPE_TRIGG_POINT_M)(*p_u16Data++ >> 8);
					 g_stGuiCfgSwScope.emAcqMode    = (SW_SCOPE_ACQ_MODE_M)(*p_u16Data & 0x00FF);
					 g_stGuiCfgSwScope.u8TrigIndex    = (UINT8)(*p_u16Data++ >> 8);
					 g_stGuiCfgSwScope.u16AcqInterval = (UINT8)(*p_u16Data++);
					 p_u16FloatTemp    = (UINT16 *)&g_stGuiCfgSwScope.f32ThrdValue;
					 *p_u16FloatTemp++ = *p_u16Data++;
					 *p_u16FloatTemp++ = *p_u16Data++;
					 g_stScopeRingCtrl.p_u16HeadAddr  	= g_ua16ScopeBuff;
					 g_stScopeRingCtrl.p_u16Input     		= g_ua16ScopeBuff;
					 g_stScopeRingCtrl.p_u16Output    		= g_ua16ScopeBuff;
					 g_stScopeRingCtrl.i16IdelSize   			= sizeof(g_ua16ScopeBuff);
					 g_stScopeRingCtrl.i16TotalSize  		= sizeof(g_ua16ScopeBuff);
					 memclr_user((UINT16 *)&g_stScopeCopyRingCtrl,sizeof(RING_ITEM)/sizeof(UINT16));
					g_stScopeRingCtrl.enRingStaus   = RING_EMPTY;
					g_stScopeRingCtrl.enRingCmd     = RING_REQUEST_WRITE;
				   if((g_stGuiCfgSwScope.emTrigMethod == FALLING_EDGE)||(g_stGuiCfgSwScope.emTrigMethod == ABOVE_LEVEL))
					{
						 g_stScopeCtrlInfo.f32PreData 		= g_stGuiCfgSwScope.f32ThrdValue - 10.0f;
						 g_stScopeCtrlInfo.f32PreLastData   = g_stScopeCtrlInfo.f32PreData;
					}else{
						 g_stScopeCtrlInfo.f32PreData 		= g_stGuiCfgSwScope.f32ThrdValue + 10.0f;
						 g_stScopeCtrlInfo.f32PreLastData 	= g_stScopeCtrlInfo.f32PreData;
					}
					 u16GuiIdStatus                  	  = 1;
					 if(g_stGuiCfgSwScope.u8TrigIndex >= g_stScopeCtrlInfo.u8VarChannelNum){
						 g_stGuiCfgSwScope.emAcqMode         = INVALID_ACQ_MODE;
						 u16GuiIdStatus                      = 0;
					 }
				}
				st_ScopeGuiFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;
				st_ScopeGuiFrame.stAplDm.unAplCmd.bits.ul8CmdSet    = SW_SCOPE_CMD_SET;
				st_ScopeGuiFrame.stAplDm.unAplCmd.bits.uh8CmdId     = SW_SCOPE_GUI_CFG_ID;
				st_ScopeGuiFrame.stAplDm.u16AplDLC                  = 2;
				st_ScopeGuiFrame.p_u16AppData                        = (UINT16 *)&u16GuiIdStatus;
				Tpl_Single_Frame_Send(&st_ScopeGuiFrame);
			}
}


void sw_scope_task(void)
{
    static unsigned char s_u8FsmStatus = 0;
    UINT8 u8TplTxStatus;
	FRAME_PROTOCOL_FORMAT st_ScopeDataFrame = {0};
	BUFF_CTRL_OBJ st_ScopeDataBuffCtrl;
	//如果没有配置示波器，emAcqMode == INVALID_ACQ_MODE,示波器任务，和中断的数据采集都不会运行。
	if(g_stGuiCfgSwScope.emAcqMode == INVALID_ACQ_MODE)  return;
	//如果已配置示波器，且示波器的环形对列为空闲状态，则转化成RING_REQUEST_WRITE状态，可以采集数据
	if(g_stGuiCfgSwScope.emAcqMode == TASK_FRE) 		sw_scope_data();
	
	if(g_stScopeCtrlInfo.u8DataMsgTxFlg == 1){
		st_ScopeDataFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;
		st_ScopeDataFrame.stAplDm.unAplCmd.bits.ul8CmdSet    		= SW_SCOPE_CMD_SET;
		st_ScopeDataFrame.stAplDm.unAplCmd.bits.uh8CmdId     		= SW_SCOPE_DATA_CMD_ID;
		st_ScopeDataFrame.stAplDm.u16AplDLC                  		= (g_stScopeRingCtrl.i16TotalSize - g_stScopeRingCtrl.i16IdelSize)*TYPE_8_BYTE_SIZE;
		st_ScopeDataFrame.p_u16AppData                       		= g_ua16ScopeBuff;
		st_ScopeDataBuffCtrl.enBuffType                      		= RING_BUFF_TYPE;
		st_ScopeDataBuffCtrl.p_BuffObj                       		= (void *)&g_stScopeRingCtrl;
		memcpy((void *)&g_stScopeCopyRingCtrl,(void *)&g_stScopeRingCtrl,sizeof(RING_ITEM));
        g_stScopeRingCtrl.enRingStaus                        		= RING_FULL;
        g_stScopeRingCtrl.enRingCmd                          		= RING_REQUEST_READ;

        if(g_stGuiCfgSwScope.u8StartMode == STARTUP_ITSELF){
        	  	if(g_stScopeCtrlInfo.u8GetDataFlag == 1){
        	  			u8TplTxStatus = Tpl_Msg_Send(&st_ScopeDataBuffCtrl,&st_ScopeDataFrame);
        	  			if((u8TplTxStatus == TPL_TX_MSG_SUCCESS) || (u8TplTxStatus == TPL_TX_MUX_FRAME_DOING)){
        	  				g_stScopeCtrlInfo.u8DataMsgTxFlg                    = 0;
        	  				g_stScopeCtrlInfo.u8GetDataFlag                        = 0;
        	  				s_u8FsmStatus = 1;
						}
        	  }else{
        		  g_stScopeCtrlInfo.u8DataMsgTxFlg   = 0;
        		  g_stScopeRingCtrl.enRingCmd 		  = RING_IDLE;
        		  g_stScopeRingCtrl.enRingStaus         = RING_EMPTY;
        		  s_u8FsmStatus = 1;
        	  }
        }else{
    		u8TplTxStatus = Tpl_Msg_Send(&st_ScopeDataBuffCtrl,&st_ScopeDataFrame);
    		if((u8TplTxStatus == TPL_TX_MSG_SUCCESS) || (u8TplTxStatus == TPL_TX_MUX_FRAME_DOING)){
    			g_stScopeCtrlInfo.u8DataMsgTxFlg                    = 0;
    			g_stScopeCtrlInfo.u8GetDataFlag                        = 0;
    			s_u8FsmStatus = 1;
    		}
        }

	}
	//s_u8FsmStatus = 1 表示示波器已经装了数据，并成功，g_stScopeRingCtrl.enRingCmd = RING_IDLE 表示示波器的数据已经发送完毕。
	if((s_u8FsmStatus == 1)&&(g_stScopeRingCtrl.enRingCmd == RING_IDLE)){
	        s_u8FsmStatus                   = 0;
            g_stScopeCtrlInfo.u8RunStopCmd  = SCOPE_STOP_CMD;
			g_stScopeCtrlInfo.u8TrigFlg     		= 0;
	//	    g_stScopeRingCtrl.enRingCmd     	= RING_REQUEST_WRITE;  //导致get data的功能无法正常使用
	}
}

//REG_TASK(sw_scope_task,1,1,0);

void scope_get_data_cmd_action(void){
    FRAME_PROTOCOL_FORMAT st_ScopeDataFrame = {0};
 //   BUFF_CTRL_OBJ st_ScopeDataBuffCtrl;
    st_ScopeDataFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;
    st_ScopeDataFrame.stAplDm.unAplCmd.bits.ul8CmdSet    	= SW_SCOPE_CMD_SET;
    if(g_stScopeCopyRingCtrl.enRingCmd == RING_IDLE){   //Not ready data
        st_ScopeDataFrame.stAplDm.unAplCmd.bits.uh8CmdId     = SW_SCOPE_DATA_NOT_READY_ID;
        st_ScopeDataFrame.stAplDm.u16AplDLC                  = 0;
        st_ScopeDataFrame.p_u16AppData                       = (void *)0x00000000;
        Tpl_Single_Frame_Send(&st_ScopeDataFrame);
    }else if(g_stScopeCtrlInfo.u8RunStopCmd  == SCOPE_RUN_CMD){  //The scope is running now
        st_ScopeDataFrame.stAplDm.unAplCmd.bits.uh8CmdId     = SW_SCOPE_IS_RUNNING_ID;
        st_ScopeDataFrame.stAplDm.u16AplDLC                  = 0;
        st_ScopeDataFrame.p_u16AppData                       = (void *)0x00000000;
        Tpl_Single_Frame_Send(&st_ScopeDataFrame);
    }else if(g_stScopeRingCtrl.enRingStaus == RING_EMPTY){
        memcpy((void *)&g_stScopeRingCtrl,(void *)&g_stScopeCopyRingCtrl,sizeof(RING_ITEM));
        g_stScopeCtrlInfo.u8DataMsgTxFlg = 1;
        g_stScopeCtrlInfo.u8GetDataFlag     = 1;
    }
}



void SwScopeCmdSetLink(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    UINT8 u8CmdId;
    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;
    switch(u8CmdId){
        case SW_SCOPE_ITEM_CMD_ID:
				#define GEN_SW_SCOPE_ITEM_CALL
                        #include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
				#undef GEN_SW_SCOPE_ITEM_CALL
        break;
        case SW_SCOPE_GUI_CFG_ID:
 /*               #define GEN_SW_SCOPE_GUI_SET_ACTION_CALL
                        #include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
                #undef GEN_SW_SCOPE_GUI_SET_ACTION_CALL*/
        	sw_scope_gui_set_action(p_stAplDm);
        break;
        case SW_SCOPE_RUN_COMM_ID:{
                #define GEN_SW_SCOPE_RUN_CMD_CALL
                        #include "DEBUG_PLATFORM/SW_SCOPE/SW_SCOPE_CFG.H"
                #undef GEN_SW_SCOPE_RUN_CMD_CALL
      }
        break;
        case SW_SCOPE_GET_DATA_ID:{
            scope_get_data_cmd_action();
        }break;
        default:break;
    }
}







