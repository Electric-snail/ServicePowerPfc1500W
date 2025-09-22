/*
 * SW_Scope_Define.h
 *
 *  Created on: 2022.9.15
 *      Author:  hongbo.jiang
 */
#ifdef GEN_DATA_REC_CFG_ENTITY
    #undef DATA_REC_START
    #undef DATA_REC_ITEM
    #undef DATA_REC_END
    #define  DATA_REC_START(name,index)        			      void DataRecCfg_##name(void)\
													  	  	  {     UINT16  	ua16RecBuf[(DATA_REC_MAX_CNT*VAR_NAME_CHAR_MAX_LEN_BYTE + 1) >> 1]={0};\
																	FRAME_PROTOCOL_FORMAT st_RecCfgFrame = {0};\
																	REC_ITEM_CFG *p_cfg_item  =(REC_ITEM_CFG*)(ua16RecBuf);\
																	REC_VAR_CFG  *p_var_cfg	=	NULL;\
																	UINT8 i = 0;\
																	UINT8 max_var_item = 0;\
																	UINT8 rec_w_index  = 0;\
																	UINT8 u8CharNum    = 0;\
																	const char *p_u8PackName = #name;\
																	UINT16 *p_u16VarCnt      = NULL;\
																	st_RecCfgFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;\
																	st_RecCfgFrame.stAplDm.unAplCmd.bits.ul8CmdSet    = DATA_LOG_CMD_SET;\
																	st_RecCfgFrame.stAplDm.unAplCmd.bits.uh8CmdId     = DATA_LOG_RESPONSE_CFG_CMD_ID;\
																	st_RecCfgFrame.p_u16AppData                       = ua16RecBuf;\
																	u8CharNum										  = strlen(p_u8PackName);\
																	u8CharNum 										  = ((u8CharNum + 1) & 0xFE);\
																	if(((u8CharNum + 1 + 4) >> 1) >= ((DATA_REC_MAX_CNT*VAR_NAME_CHAR_MAX_LEN_BYTE + 1) >> 1)) return;\
																	p_cfg_item->unRecItemNameCtrl.bits.uh8NameLen     = u8CharNum;\
																	p_cfg_item->unRecItemNameCtrl.bits.ul8Index       = index;\
																	rec_w_index++;\
																	for(i = 0; i < u8CharNum;i+= 2){\
																		ua16RecBuf[rec_w_index] = *p_u8PackName ++;\
																		ua16RecBuf[rec_w_index] |= ((UINT16)(*p_u8PackName ++) << 8);\
																		rec_w_index++;\
																	}\
																	p_u16VarCnt  =   ua16RecBuf + rec_w_index; \
																	rec_w_index ++;
	#define  DATA_REC_ITEM(type,var)								p_u8PackName  = #var;\
																	u8CharNum									    = strlen(p_u8PackName);\
																	u8CharNum 										= ((u8CharNum + 1) & 0xFE); \
																	if((rec_w_index + ((u8CharNum + 1 + 4) >> 1))   >= ((DATA_REC_MAX_CNT*VAR_NAME_CHAR_MAX_LEN_BYTE + 1) >> 1)) return;\
																	p_var_cfg = (REC_VAR_CFG  *)(ua16RecBuf + rec_w_index);\
																	p_var_cfg->unRecVarAttr.bits.ul8VarType       	= type;\
																	p_var_cfg->unRecVarAttr.bits.uh8VarSize       	= sizeof(var)*TYPE_8_BYTE_SIZE;\
																	p_var_cfg->unRecVarNameCtrl.bits.uh8NameLen   	= u8CharNum;\
																	p_var_cfg->unRecVarNameCtrl.bits.ul8Index     	= max_var_item;\
																	rec_w_index += 2;\
																	for(i = 0; i < u8CharNum;i+= 2){\
																		ua16RecBuf[rec_w_index] = *p_u8PackName ++;\
																		ua16RecBuf[rec_w_index] |= ((UINT16)(*p_u8PackName ++) << 8);\
																		rec_w_index++;\
																	}\
																	max_var_item ++;
	#define  DATA_REC_END()                       	  			  	*p_u16VarCnt      	   				   		  = max_var_item;       \
																  	 st_RecCfgFrame.stAplDm.u16AplDLC             = rec_w_index << 1;	\
																  	 g_u16DataRecRun                              = 1;	    \
																  	 Tpl_Single_Frame_Send(&st_RecCfgFrame);	 							\
													        }
#endif

#ifdef GEN_DATA_REC_CFG_DECLARE
    #undef DATA_REC_START
    #undef DATA_REC_ITEM
    #undef DATA_REC_END

    #define DATA_REC_START(name,index)       				extern void DataRecCfg_##name(void);
    #define DATA_REC_ITEM(type,var)
    #define DATA_REC_END()
#endif

#ifdef GEN_DATA_REC_CFG_CALL
    #undef DATA_REC_START
    #undef DATA_REC_ITEM
    #undef DATA_REC_END

    #define DATA_REC_START(name,index)       				DataRecCfg_##name();
    #define DATA_REC_ITEM(type,var)
    #define DATA_REC_END()
#endif

#ifdef GEN_DATA_REC_DATA_ENTITY
    #undef DATA_REC_START
    #undef DATA_REC_ITEM
    #undef DATA_REC_END
    #define  DATA_REC_START(name,index)        				void DataRecData_##name(void)\
															{ \
    														      static unsigned long s_u32TimerTargetCnt = DATA_LOG_MIN_INTERVAL;\
																  UINT16   ua16RecBuf[DATA_REC_MAX_CNT*2]={0};      	\
																  UINT16   rec_w_index = 0;                               			     	\
																  FRAME_PROTOCOL_FORMAT st_RecDataFrame = {0};  						 	\
																  REC_DATA_WORD *p_rec_data     = NULL;   									\
																  UINT8 max_var_item = 0;                                 					\
																  UINT8 u8VarSize    = 0;													\
																  UINT16 *p_u16Data  = NULL;												\
																  UINT32 u32Cur_ms   = REC_TIME_STAMP;										\
     															  if((TIME_OVER_U32(s_u32TimerTargetCnt,		u32Cur_ms))&&(g_u16DataRecRun == 1)){\
	    															  s_u32TimerTargetCnt = u32Cur_ms + DATA_LOG_MIN_INTERVAL;\
																	  st_RecDataFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;   		\
																	  st_RecDataFrame.stAplDm.unAplCmd.bits.ul8CmdSet    = DATA_LOG_CMD_SET;  	\
																	  st_RecDataFrame.stAplDm.unAplCmd.bits.uh8CmdId     = DATA_LOG_RESPONSE_DATA_CMD_ID;  	\
																	  st_RecDataFrame.p_u16AppData                        = (UINT16 *)ua16RecBuf;			\
																	  p_rec_data                                         = (REC_DATA_WORD *)(ua16RecBuf + rec_w_index);\
																	  p_rec_data->bits.ul8Index       					 = index;				\
																	  rec_w_index++;															\
																	  ua16RecBuf[rec_w_index++]                          = (UINT16)(u32Cur_ms & 0x0000ffff);\
																	  ua16RecBuf[rec_w_index++]                          = (UINT16)(u32Cur_ms >> 16);
	#define  DATA_REC_ITEM(type,var) 							  		u8VarSize = sizeof(var)*TYPE_8_BYTE_SIZE;													 \
																  	  if(max_var_item < DATA_REC_MAX_CNT){                                      \
																  		  p_u16Data = (UINT16 *)&var;											\
																  		  if(u8VarSize == 4){													\
																		  	  ua16RecBuf[rec_w_index++] = *p_u16Data++;							\
																		  	  ua16RecBuf[rec_w_index++] = *p_u16Data;							\
																		  }else{																\
																			  ua16RecBuf[rec_w_index++] = var;									\
																		  }																		\
																		 max_var_item++;														\
																  	  }
	#define  DATA_REC_END()                       	  		  	  		p_rec_data->bits.uh8VarCnt      	                 = max_var_item;        \
		                                               	   	      	  st_RecDataFrame.stAplDm.u16AplDLC                 = rec_w_index << 1;		\
		                                               	   	      	  Tpl_Single_Frame_Send(&st_RecDataFrame);	    							\
	   															  }\
															}
#endif

#ifdef GEN_DATA_REC_DATA_DECLARE
    #undef DATA_REC_START
    #undef DATA_REC_ITEM
    #undef DATA_REC_END

    #define DATA_REC_START(name,index)       				extern void DataRecData_##name(void);
    #define DATA_REC_ITEM(type,var)
    #define DATA_REC_END()
#endif


#ifdef GEN_DATA_REC_DATA_CALL
	#undef  DATA_REC_START
	#undef  DATA_REC_ITEM
	#undef  DATA_REC_END

    #define DATA_REC_START(name,index)           			DataRecData_##name();
    #define DATA_REC_ITEM(type,var)
    #define DATA_REC_END()
#endif

#ifdef GEN_DATA_REC_REG_TASK
	#undef  DATA_REC_START
	#undef  DATA_REC_ITEM
	#undef  DATA_REC_END

    #define DATA_REC_START(name,index)           			REG_TASK(DataRecData_##name,    1,   DATA_REC_AUTO_PERIOD,   79)
    #define DATA_REC_ITEM(type,var)
    #define DATA_REC_END()
#endif
