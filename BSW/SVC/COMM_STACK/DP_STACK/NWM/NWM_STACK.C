/*
 * NWM_Stack.c
 *
 *  Created on: 2022.8.17
 *      Author: xj8r1j
 */
#include "DP_STACK/DLL/DLL_SCI.H"
#include "PUBLIC_INC/LINE_BUFF.H"
#include "DP_STACK/DP_STACK_CFG.H"
#include "DP_STACK/NWM/NWM_STACK.h"


//The route address relative with the link id.
static ADDR_LINK_ITEM const gc_stRegRoutItemTab[] = REG_ADDR_LINK_ITEM_TAB;

static LINK_HAL_ITEM const gc_stLinkItemTab[]     = REG_LINK_HAL_TAB;

static UINT16  g_au16NwmRouteBuff[sizeof(gc_stLinkItemTab)/sizeof(LINK_HAL_ITEM)][DP_NWM_SIG_FRAME_TX_MAX_BYTE_LEN >> 1]       = {0};

static PIPE_CTRL_INFO gs_stRouteManage[sizeof(gc_stLinkItemTab)/sizeof(LINK_HAL_ITEM)];

//The NWM Frame receive object, including frame receive buff pointer; device write function pointer, device read function pointer.

static RX_FRAME_CALL_BACK_FUNC    p_fnFrameRxCallback = NULL;

UINT16 g_u16NwmRouteErrCnt = 0;
void Nwm_Frame_Rx_Callback_Init(void *p_vData){
    p_fnFrameRxCallback = (RX_FRAME_CALL_BACK_FUNC)p_vData;
}


UINT8 Find_LinkId_BaseOn_Addr(UINT8 u8Addr){
    UINT16 i = 0;
    const ADDR_LINK_ITEM *p_stAddrLink;
    for(i = 0; i < (sizeof(gc_stRegRoutItemTab)/sizeof(ADDR_LINK_ITEM)); i++){
        p_stAddrLink = &gc_stRegRoutItemTab[i];
        if(u8Addr == p_stAddrLink->u8Addr){
            return p_stAddrLink->u8LinkId;
        }
    }
    return LINK_INVALID_ID;
}

const LINK_HAL_ITEM *Find_LinkItem_BaseOn_LinkId(u8LinkId){
    UINT16 i = 0;
    const LINK_HAL_ITEM *p_stLinkItem;
    for(i = 0; i < sizeof(gc_stLinkItemTab)/sizeof(LINK_HAL_ITEM); i++){
          p_stLinkItem = &gc_stLinkItemTab[i];
          if(u8LinkId == p_stLinkItem->enLinkId){
              return p_stLinkItem;
          }
    }
    return NULL;
}

INT8 Nwm_Frame_Tx(FRAME_PROTOCOL_FORMAT *p_stFrameFormat){
    INT8 i8LinkId = 0;
    const LINK_HAL_ITEM *p_stLinkHalItem = NULL;
    p_stFrameFormat->stNwmDm.unNwmAddr.bits.uh8SrcAddr          = ITSELF_NODE_ADDR;
    p_stFrameFormat->stNwmDm.unNwmCtrl.bits.ul8RouteType        = ROUTE_ADDR_TYPE;
    i8LinkId                                                    = Find_LinkId_BaseOn_Addr(p_stFrameFormat->stNwmDm.unNwmAddr.bits.ul8DestAddr);
    p_stFrameFormat->stNwmDm.unNwmLink.bits.uh8TxLinkId         = (UINT8)i8LinkId;
    p_stFrameFormat->stNwmDm.unNwmCtrl.bits.uh8NwmAck           = 0;
    p_stFrameFormat->stNwmDm.u16NwmDLC                          = p_stFrameFormat->stTplDm.u16TplDLC + sizeof(TPL_DOMAIN) * TYPE_8_BYTE_SIZE;
    p_stLinkHalItem                                             = Find_LinkItem_BaseOn_LinkId(i8LinkId);
    if (p_stLinkHalItem != NULL)
    {
        if (p_stLinkHalItem->p_fnDevWrite != NULL)
        {
            if (p_stLinkHalItem->p_fnDevWrite(p_stFrameFormat) == 1)
                return NWM_TX_FRAME_SUCCESS;
        }
    }
    
    return NWM_TX_FRAME_FAIL;

}

NWM_ROUTE_STATUS Nwm_Route_Frame_Tx(FRAME_PROTOCOL_FORMAT *p_stFrameFormat){
    INT8  i8LinkId = 0;
    UINT8 u8DestAddr = 0;
    UINT8 u8RouteTemp = 0;
    const LINK_HAL_ITEM *p_stLinkHalItem = NULL;

    u8RouteTemp = p_stFrameFormat->stNwmDm.unNwmCtrl.bits.ul8RouteType;
    if(u8RouteTemp  == ROUTE_ADDR_TYPE){
        u8DestAddr  = p_stFrameFormat->stNwmDm.unNwmAddr.bits.ul8DestAddr;
        i8LinkId    = Find_LinkId_BaseOn_Addr(u8DestAddr);
        if(i8LinkId <= 0)
            return ROUTE_NO_REG_ADDR;
        p_stLinkHalItem = Find_LinkItem_BaseOn_LinkId(i8LinkId);
        if(p_stLinkHalItem == NULL)  //Cannot find the register route address infomation
            return ROUTE_NO_REG_LINK;
        if(p_stLinkHalItem->p_fnDevWrite(p_stFrameFormat) != 1){
            return ROUTE_WRITE_FAIL;
        }
    }
/*    else{
        g_u16RouteCnt = 0;
    }
    g_u16RouteCnt++;*/
    return ROUTE_SUCESS;
}

void Nwm_Rx_Frame(void){
    FRAME_PROTOCOL_FORMAT *p_NwmFrameInfo = NULL;
    UINT16 *p_u16Data;
    INT16 i16FrameRxStatus;
    UINT8 i;
//jackey    UINT16 u16DataLen = 0;
    const LINK_HAL_ITEM *p_stLinkHalItem = NULL;
    for(i = 0; i < (sizeof(gc_stLinkItemTab)/sizeof(LINK_HAL_ITEM)); i++){
        p_stLinkHalItem = &gc_stLinkItemTab[i];
        if(p_stLinkHalItem->p_fnDevRead == NULL)
            continue;

        p_u16Data           = p_stLinkHalItem->p_u16BuffAddr;
        i16FrameRxStatus    = p_stLinkHalItem->p_fnDevRead(p_u16Data);

        if(DLL_RX_FRAME_SUCCESS != i16FrameRxStatus)
            continue;

        p_NwmFrameInfo =  (FRAME_PROTOCOL_FORMAT *)p_u16Data;
        if(p_NwmFrameInfo->stNwmDm.unNwmAddr.bits.ul8DestAddr == ITSELF_NODE_ADDR){ //The dest address is not itself, so check if the route is enable
            if(p_fnFrameRxCallback != NULL){
                p_fnFrameRxCallback(p_NwmFrameInfo); //use the call back function to handle the frame in tpl and apl layer.
            }
        }
        #if(NODE_ROUTE_ENABLE == 1)
        else{
           if(gs_stRouteManage[i].u16Lock != PIPE_WRITE_LOCK)//route is lock in this link. continue check next link.
           {
               gs_stRouteManage[i].u16Lock = PIPE_WRITE_LOCK;
               //Change the link id to itself to route sent, if the link route is enable.
               p_NwmFrameInfo->stNwmDm.unNwmLink.bits.ul8RxLinkId = p_stLinkHalItem->enLinkId; //From which link to get these data
               memcpy((UINT16 *)&gs_stRouteManage[i].stRouteFrame, (UINT16 *)p_u16Data,(sizeof(FRAME_PROTOCOL_FORMAT) - sizeof(UINT16 *))/sizeof(UINT16));
               p_u16Data += ((sizeof(FRAME_PROTOCOL_FORMAT) - sizeof(UINT16 *))/sizeof(UINT16));
               u16DataLen = (p_NwmFrameInfo->stAplDm.u16AplDLC >> 1);
               memcpy((UINT16 *)gs_stRouteManage[i].stRouteFrame.p_u16AppData, (UINT16 *)p_u16Data, u16DataLen);
           }
        }
       #endif
    }
}

void NWM_Init(void){
    UINT16 i = 0;
    //Initial the route management table, the link id should be the same with gc_stLinkItemTab.
    for(i = 0; i < sizeof(gs_stRouteManage)/sizeof(PIPE_CTRL_INFO); i++){
        gs_stRouteManage[i].enLinkId                    = gc_stLinkItemTab[i].enLinkId;
        gs_stRouteManage[i].stRouteFrame.p_u16AppData   = g_au16NwmRouteBuff[i];
        gs_stRouteManage[i].u16Lock                     = PIPE_READ_LOCK;
    }
}

void NWM_Handle(void){

    UINT16 i = 0;
    PIPE_CTRL_INFO  *p_stRoutePipeItem;
    NWM_ROUTE_STATUS emRouteStatus;
    //Check whether the route frame need to be resent.
    for(i = 0; i < sizeof(gs_stRouteManage)/sizeof(PIPE_CTRL_INFO); i++){
        p_stRoutePipeItem = &gs_stRouteManage[i];
        if(p_stRoutePipeItem->u16Lock == PIPE_READ_LOCK)  //if there is no data need to be route, continue check other route pipe
            continue;
        emRouteStatus = Nwm_Route_Frame_Tx(&(p_stRoutePipeItem->stRouteFrame));
        if(emRouteStatus == ROUTE_SUCESS){
           p_stRoutePipeItem->u16Lock = PIPE_READ_LOCK;
        }
        else{
            g_u16NwmRouteErrCnt ++;
            if((emRouteStatus == ROUTE_NO_REG_ADDR)||(emRouteStatus == ROUTE_NO_REG_LINK))
                p_stRoutePipeItem->u16Lock = PIPE_READ_LOCK; // unlock it to route the next message.
        }
    }
    Nwm_Rx_Frame();

}

