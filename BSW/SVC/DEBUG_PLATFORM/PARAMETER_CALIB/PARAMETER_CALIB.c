#include "DEBUG_PLATFORM/DBG_BASIC.h"
#include "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB.H"
#include "DP_STACK/DPStackBasic.h"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DP_STACK/APL/APL_STACK.H"
#include "STORAGE/BSW_SVC_STORAGE.H"
#include "PUBLIC_INC/MEM_HANDLE.H"
#include "TASK/BSW_TASK_SERVICE.H"
#include "string.h"

#define GEN_PARAM_CALIB_ITEM_ENTITY
    #include "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB_CFG.h"
#undef GEN_PARAM_CALIB_ITEM_ENTITY

PARAME_CALIB_DATA_T g_stCalibData;

F32_CALIB_LIMIT_DATA_OBJ_T  g_stF32CalibLimitData;
I16_CALIB_LIMIT_DATA_OBJ_T  g_stI16CalibLimitData;

UINT16      g_u16CalibStoreFlg = 0;
void parame_calib_wr_data_cmd(void *p_vAplDm){
	APL_DOMAIN *p_stAplDm = (APL_DOMAIN *)p_vAplDm;
	FRAME_PROTOCOL_FORMAT st_CalibDataRespFrame = {0};  
	UINT16 u16IsCalibDataOk = 0;
	F32_CALIB_ITEM_T *p_stF32CalibItem = (F32_CALIB_ITEM_T *)&g_stCalibData.stF32;
	I16_CALIB_ITEM_T *p_stI16CalibItem = (I16_CALIB_ITEM_T *)&g_stCalibData.stI16;
	F32_CALIB_LIMIT_ITEM_T *p_stF32CalibLimitItem = (F32_CALIB_LIMIT_ITEM_T *)&g_stF32CalibLimitData;
	I16_CALIB_LIMIT_ITEM_T *p_stI16CalibLimitItem   = (I16_CALIB_LIMIT_ITEM_T *)&g_stI16CalibLimitData;
   	F32_CALIB_ITEM_T stF32CalibItem = {0};
	I16_CALIB_ITEM_T stI16CalibItem = {0};
	UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));
    UINT16 *p_u16DataTemp;
    UINT16  u16DataTemp;
	UINT16 u16ParamNum = 0,  i = 0;
	u16DataTemp = *p_u16Data++;
	if((u16DataTemp & 0x00FF)  == eu_fp32){
		u16ParamNum = u16DataTemp >> 8;
		p_stF32CalibItem += u16ParamNum;  //The calibration item
		p_stF32CalibLimitItem += u16ParamNum;
		p_u16DataTemp = (UINT16 *)&stF32CalibItem;
		for(i = 0; i < sizeof(F32_CALIB_ITEM_T)/sizeof(UINT16); i++)
		   *p_u16DataTemp++ = *p_u16Data++;
	    if((stF32CalibItem.f32K <= p_stF32CalibLimitItem->f32Kmax)&&(stF32CalibItem.f32K >= p_stF32CalibLimitItem->f32Kmin)\
		  &&(stF32CalibItem.f32Offset <= p_stF32CalibLimitItem->f32Bmax)&&(stF32CalibItem.f32Offset >= p_stF32CalibLimitItem->f32Bmin)){
			 p_stF32CalibItem->f32K      = stF32CalibItem.f32K;
			 p_stF32CalibItem->f32Offset = stF32CalibItem.f32Offset;
			 u16IsCalibDataOk = 1;
	    }
		
	}else{
        u16ParamNum      = u16DataTemp >> 8;
		p_stI16CalibItem  += u16ParamNum;
		p_u16DataTemp   = (UINT16 *)&stI16CalibItem;
		for(i = 0; i < sizeof(I16_CALIB_ITEM_T)/sizeof(UINT16); i++)
		  *p_u16DataTemp++ = *p_u16Data++;
	    if((stI16CalibItem.i16Q8K <= p_stI16CalibLimitItem->i16Q8Kmax)&&(stI16CalibItem.i16Q8K >= p_stI16CalibLimitItem->i16Q8Kmin)\
		  &&(stI16CalibItem.i16Q8Offset <= p_stI16CalibLimitItem->i16Q8Bmax)&&(stI16CalibItem.i16Q8Offset >= p_stI16CalibLimitItem->i16Q8Bmin)){
			 p_stI16CalibItem->i16Q8K      = stI16CalibItem.i16Q8K;
			 p_stI16CalibItem->i16Q8Offset = stI16CalibItem.i16Q8Offset;
			 u16IsCalibDataOk = 1;
	    }
	}
	st_CalibDataRespFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr  = PC_NODE_ADDR;   						
	st_CalibDataRespFrame.stAplDm.unAplCmd.bits.ul8CmdSet           = PARAM_CALIB_CMD_SET;
	st_CalibDataRespFrame.stAplDm.unAplCmd.bits.uh8CmdId            = PARAM_CALIB_WR_DATA_CMD_ID;
	st_CalibDataRespFrame.stAplDm.u16AplDLC                                 = 2;
	st_CalibDataRespFrame.p_u16AppData                                           = (UINT16 *)&u16IsCalibDataOk;
	Tpl_Single_Frame_Send(&st_CalibDataRespFrame);
}

void parame_calib_rd_data_cmd(void *p_vAplDm){
	APL_DOMAIN *p_stAplDm = (APL_DOMAIN *)p_vAplDm;
	FRAME_PROTOCOL_FORMAT st_CalibDataRespFrame = {0};  
	UINT16 ua16CalibRdDataBuff[5] = {0};
	UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));
    UINT16 *p_u16DataTemp;
	UINT16  u16ParamNum = 0,  i = 0;
    UINT16  u16DataTemp;
    u16DataTemp = *p_u16Data++;
	if((u16DataTemp & 0x00FF) == eu_fp32){
		u16ParamNum = u16DataTemp >> 8;
		p_u16DataTemp = (UINT16 *)&g_stCalibData.stF32 + u16ParamNum * (sizeof(F32_CALIB_ITEM_T)/sizeof(UINT16));
		ua16CalibRdDataBuff[0] = eu_fp32 + (u16ParamNum << 8);
		for(i = 0; i < sizeof(F32_CALIB_ITEM_T)/sizeof(UINT16); i++)
		    ua16CalibRdDataBuff[i+1] = *p_u16DataTemp++;
		    st_CalibDataRespFrame.stAplDm.u16AplDLC                   = sizeof(F32_CALIB_ITEM_T) * TYPE_8_BYTE_SIZE + 2;
	}else{
        u16ParamNum = u16DataTemp >> 8;
	    p_u16DataTemp = (UINT16 *)&g_stCalibData.stI16 + u16ParamNum * sizeof(I16_CALIB_ITEM_T)/sizeof(UINT16);
        ua16CalibRdDataBuff[0] = eu_int16 + (u16ParamNum << 8);
		for(i = 0; i < sizeof(I16_CALIB_ITEM_T)/sizeof(UINT16); i++)
		  	ua16CalibRdDataBuff[i+1] = *p_u16DataTemp++;
		st_CalibDataRespFrame.stAplDm.u16AplDLC                             = sizeof(I16_CALIB_ITEM_T)*TYPE_8_BYTE_SIZE + 2;
	}
	st_CalibDataRespFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr   = PC_NODE_ADDR;
	st_CalibDataRespFrame.stAplDm.unAplCmd.bits.ul8CmdSet           = PARAM_CALIB_CMD_SET;
	st_CalibDataRespFrame.stAplDm.unAplCmd.bits.uh8CmdId            = PARAM_CALIB_RD_DATA_CMD_ID;
   
	st_CalibDataRespFrame.p_u16AppData                         = (UINT16 *)&ua16CalibRdDataBuff;
	Tpl_Single_Frame_Send(&st_CalibDataRespFrame);
}

void parame_calib_rs_data_cmd(void *p_vAplDm){
	APL_DOMAIN *p_stAplDm = (APL_DOMAIN *)p_vAplDm;
	FRAME_PROTOCOL_FORMAT st_CalibDataRespFrame = {0};  
	F32_CALIB_ITEM_T *p_stF32CalibItem = (F32_CALIB_ITEM_T *)&g_stCalibData.stF32;
	I16_CALIB_ITEM_T *p_stI16CalibItem = (I16_CALIB_ITEM_T *)&g_stCalibData.stI16;
	UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));
	UINT16  u16ParamNum = 0;
    UINT16  u16DataTemp;
    u16DataTemp = *p_u16Data++;

	if((u16DataTemp & 0x00FF) == eu_fp32){
        u16ParamNum = u16DataTemp >> 8;
		p_stF32CalibItem += u16ParamNum;  //The calibration item
		p_stF32CalibItem->f32K      = 1.0f;
		p_stF32CalibItem->f32Offset = 0.0f;
		
	}else{
        u16ParamNum = u16DataTemp >> 8;
		p_stI16CalibItem  += u16ParamNum;
	    p_stI16CalibItem->i16Q8K      = 256;
		p_stI16CalibItem->i16Q8Offset = 0;
	}
	st_CalibDataRespFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr  = PC_NODE_ADDR;   						
	st_CalibDataRespFrame.stAplDm.unAplCmd.bits.ul8CmdSet           = PARAM_CALIB_CMD_SET;
	st_CalibDataRespFrame.stAplDm.unAplCmd.bits.uh8CmdId            = PARAM_CALIB_RS_DATA_CMD_ID;
	st_CalibDataRespFrame.stAplDm.u16AplDLC                                 = 0;
	Tpl_Single_Frame_Send(&st_CalibDataRespFrame);
}


void  parame_calib_store_cmd(void *p_vAplDm){
    unsigned short *p_u16SrcAddr =  (UINT16 *)&g_stCalibData;
    unsigned short *p_u16DestAddr = (UINT16 *)get_calib_store_addr();
    unsigned short i = 0;
    FRAME_PROTOCOL_FORMAT st_CalibStoreRespFrame = {0};
    for(i = 0; i < sizeof(PARAME_CALIB_DATA_T)/sizeof(UINT16); i++){
        *p_u16DestAddr++ = *p_u16SrcAddr++;
    }
    set_store_flag();
	st_CalibStoreRespFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr  = PC_NODE_ADDR;   						
	st_CalibStoreRespFrame.stAplDm.unAplCmd.bits.ul8CmdSet          = PARAM_CALIB_CMD_SET;
	st_CalibStoreRespFrame.stAplDm.unAplCmd.bits.uh8CmdId          = PARAM_CALIB_STORE_CMD_ID;
	st_CalibStoreRespFrame.stAplDm.u16AplDLC                              = 0;
	st_CalibStoreRespFrame.p_u16AppData                                        = NULL;
	Tpl_Single_Frame_Send(&st_CalibStoreRespFrame);
}


#define GEN_PARAM_CALIB_LIMIT_DATA_INIT_ENTITY
#include "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB_CFG.h"
#undef GEN_PARAM_CALIB_LIMIT_DATA_INIT_ENTITY

void param_calib_init(void){
	UINT8 i = 0;
	PARAME_CALIB_DATA_T  *p_stCalibData;
	F32_CALIB_ITEM_T *p_stF32CalibItemSrc;
	F32_CALIB_ITEM_T *p_stF32CalibItemDst;
	I16_CALIB_ITEM_T *p_stI16CalibItemSrc;
	I16_CALIB_ITEM_T *p_stI16CalibItemDst;
	F32_CALIB_LIMIT_ITEM_T *p_stF32CalibLimitItem = (F32_CALIB_LIMIT_ITEM_T *)&g_stF32CalibLimitData;
	I16_CALIB_LIMIT_ITEM_T *p_stI16CalibLimitItem = (I16_CALIB_LIMIT_ITEM_T *)&g_stI16CalibLimitData;
    #define GEN_PARAM_CALIB_LIMIT_DATA_INIT_CALL
	#include "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB_CFG.h"
	#undef GEN_PARAM_CALIB_LIMIT_DATA_INIT_CALL
	p_stCalibData           =  (PARAME_CALIB_DATA_T  *)get_calib_store_addr();
	p_stF32CalibItemSrc =  (F32_CALIB_ITEM_T *)&(p_stCalibData->stF32);
	p_stF32CalibItemDst =  (F32_CALIB_ITEM_T *)&g_stCalibData.stF32;
	p_stI16CalibItemSrc  =  (I16_CALIB_ITEM_T *)&(p_stCalibData->stI16);
	p_stI16CalibItemDst  =  (I16_CALIB_ITEM_T *)&(g_stCalibData.stI16);
	if(p_stCalibData != NULL){
		for(i = 0; i < (sizeof(F32_CALIB_DATA_OBJ_T)/sizeof(F32_CALIB_ITEM_T)); i++){
		   if((p_stF32CalibItemSrc->f32K <= p_stF32CalibLimitItem->f32Kmax)&&(p_stF32CalibItemSrc->f32K >= p_stF32CalibLimitItem->f32Kmin)\
		       &&(p_stF32CalibItemSrc->f32Offset <= p_stF32CalibLimitItem->f32Bmax)&&(p_stF32CalibItemSrc->f32Offset >= p_stF32CalibLimitItem->f32Bmin)){
			   p_stF32CalibItemDst->f32K      = p_stF32CalibItemSrc->f32K;
			   p_stF32CalibItemDst->f32Offset = p_stF32CalibItemSrc->f32Offset;
	       }else{
			   p_stF32CalibItemDst->f32K      = 1.0f;
			   p_stF32CalibItemDst->f32Offset = 0;
		   }
		   p_stF32CalibItemDst++;
		   p_stF32CalibItemSrc++;
		}
		for(i = 0; i < (sizeof(I16_CALIB_DATA_OBJ_T)/sizeof(I16_CALIB_ITEM_T)); i++){
		   if((p_stI16CalibItemSrc->i16Q8K <= p_stI16CalibLimitItem->i16Q8Kmax)&&(p_stI16CalibItemSrc->i16Q8K >= p_stI16CalibLimitItem->i16Q8Kmin)\
		       &&(p_stI16CalibItemSrc->i16Q8Offset <= p_stI16CalibLimitItem->i16Q8Bmax)&&(p_stI16CalibItemSrc->i16Q8Offset >= p_stI16CalibLimitItem->i16Q8Bmin)){
			   p_stI16CalibItemDst->i16Q8K      = p_stI16CalibItemSrc->i16Q8K;
			   p_stI16CalibItemDst->i16Q8Offset = p_stI16CalibItemSrc->i16Q8Offset;
	       }else{
			   p_stI16CalibItemDst->i16Q8K      = 256;
			   p_stI16CalibItemDst->i16Q8Offset = 0;
		   }
		   p_stI16CalibItemDst++;
		   p_stI16CalibItemSrc++;
		}
	}else{
		for(i = 0; i < (sizeof(F32_CALIB_DATA_OBJ_T)/sizeof(F32_CALIB_ITEM_T)); i++){
		   p_stF32CalibItemDst->f32K      = 1.0f;
		   p_stF32CalibItemDst->f32Offset = 0;
		   p_stF32CalibItemDst++;
		}
		for(i = 0; i < (sizeof(I16_CALIB_DATA_OBJ_T)/sizeof(I16_CALIB_ITEM_T)); i++){
		   p_stI16CalibItemDst->i16Q8K      = 256;
		   p_stI16CalibItemDst->i16Q8Offset = 0;
		   p_stI16CalibItemDst++;
		}
	}
}

void ParamCalibCmdSetLink(void *p_vAplDm){
    UINT8 u8CmdId;
	APL_DOMAIN *p_stAplDm = (APL_DOMAIN *)p_vAplDm;
    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;
    switch(u8CmdId){
        case PARAM_CALIB_ITEM_CMD_ID:
			#define GEN_PARAM_CALIB_ITEM_CALL
			#include "DEBUG_PLATFORM/PARAMETER_CALIB/Parameter_Calib_Cfg.h"
			#undef GEN_PARAM_CALIB_ITEM_CALL
        break;
        case PARAM_CALIB_WR_DATA_CMD_ID:
           parame_calib_wr_data_cmd(p_vAplDm);
        break;
        case PARAM_CALIB_RD_DATA_CMD_ID:
           parame_calib_rd_data_cmd(p_vAplDm);
        break;
        case PARAM_CALIB_RS_DATA_CMD_ID:
           parame_calib_rs_data_cmd(p_vAplDm);
        break;		
		case PARAM_CALIB_STORE_CMD_ID:
			parame_calib_store_cmd(p_vAplDm);
		break;
        default:break;
    }
}
