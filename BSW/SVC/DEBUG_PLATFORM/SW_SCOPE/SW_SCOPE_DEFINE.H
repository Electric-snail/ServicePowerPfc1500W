/*
 * SW_Scope_Define.h
 *
 *  Created on: 2022.9.15
 *      Author: hongbo.jiang
 */
#ifdef GEN_SW_SCOPE_VAR_ENTITY
    #undef 	SW_SCOPE_START
    #undef 	SW_SCOPE_ITEM
    #undef 	SW_SCOPE_END
	#pragma DATA_SECTION(g_ua16ScopeBuff, ".SCOPE_BUFF_SECTION");
	#define SW_SCOPE_START(name,startup_mode,cache_size)      UINT16 g_ua16ScopeBuff[cache_size] = {0};	\
                                                 SW_SCOPE_CTRL_OBJ     		g_stScopeCtrlInfo;    			\
												 SW_SCOPE_GUI_CFG_ITEM 	g_stGuiCfgSwScope;
	#define SW_SCOPE_ITEM(var)
    #define SW_SCOPE_END()
#endif

#ifdef GEN_SW_SCOPE_VAR_DECLARE
    #undef 	SW_SCOPE_START
    #undef 	SW_SCOPE_ITEM
    #undef 	SW_SCOPE_END
	#define SW_SCOPE_START(name,startup_mode,cache_size)      extern UINT16 g_ua16ScopeBuff[cache_size];	\
                                                              extern SW_SCOPE_CTRL_OBJ     	g_stScopeCtrlInfo;    			\
												              extern SW_SCOPE_GUI_CFG_ITEM 	g_stGuiCfgSwScope;
	#define SW_SCOPE_ITEM(var)
    #define SW_SCOPE_END()
#endif

#ifdef GEN_SW_SCOPE_ITEM_ENTITY
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define  SW_SCOPE_START(name,startup_mode,cache_size)\
												  void sw_scope_##name##_item(void){                     						\
	                                              float     f32Temp;                                                            \
                                                  UINT16    *p_u16Temp = NULL;                                                  \
                                                  UINT16  	ua16RecBuf[150]	=	{0};        	\
                                                  FRAME_PROTOCOL_FORMAT st_ScopeItemFrame = {0};  								\
                                                  UINT16 *p_ua16RecBuffTemp = ua16RecBuf;										\
                                                  SCOPE_ITEM_INFO  *p_cfg_item  = NULL;   		    							\
                                                  SCOPE_VAR_NAME   *p_VarName  = NULL;                   					    \
                                                  UINT8 i 					   = 0;                                            	\
                                                  UINT8 max_var_item 		   = 0;                                 			\
                                                  UINT8 rec_w_index  		   = 0;     										\
                                                  UINT8 u8CharNum    		   = 0;												\
                                                  const char *p_u8PackName     = #name;                            				\
                                                  if(g_stScopeCtrlInfo.u8DataMsgTxFlg == 1)  return;                            \
                                                  st_ScopeItemFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;   		\
                                                  st_ScopeItemFrame.stAplDm.unAplCmd.bits.ul8CmdSet    = SW_SCOPE_CMD_SET;  	\
                                                  st_ScopeItemFrame.stAplDm.unAplCmd.bits.uh8CmdId     = SW_SCOPE_ITEM_CMD_ID;  					  \
                                                  st_ScopeItemFrame.p_u16AppData                       = ua16RecBuf;								  \
                                                  *p_ua16RecBuffTemp++                                 = startup_mode;   		  					  \
                                                  rec_w_index++;																			   		  \
                                                  *p_ua16RecBuffTemp++                                 = (ACQ_MODE + (ACQ_INTERVAL << 8));   		  \
                                                  rec_w_index++;																			   		  \
                                                  f32Temp                                              = CTR_PERIOD;                                  \
                                                  p_u16Temp = (unsigned short *)&f32Temp;                                                             \
                                                  *p_ua16RecBuffTemp++ = *p_u16Temp++;                                                                \
                                                  *p_ua16RecBuffTemp++ = *p_u16Temp++;                                                                \
                                                  f32Temp                                              = SW_SCOPE_TASK_PERIOD;                        \
                                                  p_u16Temp = (unsigned short *)&f32Temp;                                                             \
                                                  *p_ua16RecBuffTemp++ = *p_u16Temp++;                                                                \
                                                  *p_ua16RecBuffTemp++ = *p_u16Temp++;                                                                \
                                                  rec_w_index += 4;		                     														  \
                                                  p_cfg_item 										   = (SCOPE_ITEM_INFO *)p_ua16RecBuffTemp;        \
                                                  u8CharNum											   = strlen(p_u8PackName);				          \
                                                  if((rec_w_index + ((u8CharNum + 1 + 4) >> 1)) >= 150) return;   \
                                                  p_cfg_item->bits.uh8NameLen     = u8CharNum; 								\
                                                  rec_w_index++;															\
                                                  for(i = 0; i < u8CharNum;i+= 2){							       			\
                                                	  ua16RecBuf[rec_w_index] = *p_u8PackName++;						    \
                                                      ua16RecBuf[rec_w_index++] |= ((UINT16)(*p_u8PackName++) << 8);	    \
                                                  }
     #define SW_SCOPE_ITEM(var)              p_u8PackName  = #var;														\
		                                          u8CharNum									    = strlen(p_u8PackName);	    \
		                                          if((rec_w_index + ((u8CharNum + 1 + 4) >> 1)) >= 150)    return;      \
											      p_VarName = (SCOPE_VAR_NAME  *)(ua16RecBuf + rec_w_index);				\
												  p_VarName->bits.uh8NameLen   = u8CharNum;     							\
												  p_VarName->bits.ul8Index     = max_var_item;          	                \
												  rec_w_index ++;															\
												  for(i = 0; i < u8CharNum;i+= 2){							       			\
                                                	  ua16RecBuf[rec_w_index] = *p_u8PackName++;						    \
                                                      ua16RecBuf[rec_w_index++] |= ((UINT16)(*p_u8PackName++) << 8);	    \
                                                  }																			\
												  max_var_item ++;
    #define SW_SCOPE_END() 						  p_cfg_item->bits.ul8VarCnt      	   			   	  = max_var_item;       \
												  st_ScopeItemFrame.stAplDm.u16AplDLC                 = rec_w_index << 1;	\
                                                  Tpl_Single_Frame_Send(&st_ScopeItemFrame);  								\
                                                 }
#endif

#ifdef GEN_SW_SCOPE_ITEM_DECLARE
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define SW_SCOPE_START(name,startup_mode,cache_size)       extern void sw_scope_##name##_item(void);
    #define SW_SCOPE_ITEM(var)
    #define SW_SCOPE_END()

#endif


#ifdef GEN_SW_SCOPE_ITEM_CALL
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define SW_SCOPE_START(name,startup_mode,cache_size)       sw_scope_##name##_item();
    #define SW_SCOPE_ITEM(var)
    #define SW_SCOPE_END()
#endif


#ifdef GEN_SW_SCOPE_INIT_ENTITY
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define  SW_SCOPE_START(name,startup_mode,cache_size)    						        							\
                                                void sw_scope_init(void)											    \
												{              															\
													UINT8 u8VarNum = 0;												    \
													memclr_user((UINT16 *)&g_stScopeCtrlInfo,sizeof(SW_SCOPE_CTRL_OBJ)/sizeof(UINT16));           \
													memclr_user((UINT16 *)&g_stGuiCfgSwScope,sizeof(SW_SCOPE_GUI_CFG_ITEM)/sizeof(UINT16));       \
													g_stScopeRingCtrl.p_u16HeadAddr 	= g_ua16ScopeBuff;					\
													g_stScopeRingCtrl.p_u16Input    	= g_ua16ScopeBuff;					\
													g_stScopeRingCtrl.p_u16Output   	= g_ua16ScopeBuff;					\
													g_stScopeRingCtrl.i16IdelSize   	= sizeof(g_ua16ScopeBuff);			\
													g_stScopeRingCtrl.i16TotalSize  	= sizeof(g_ua16ScopeBuff);			\
													g_stScopeRingCtrl.enRingStaus   	= RING_EMPTY;						\
													g_stScopeRingCtrl.enRingCmd     	= RING_IDLE;						\
													memcpy((void *)&g_stScopeCopyRingCtrl,(void *)&g_stScopeRingCtrl,sizeof(RING_ITEM));\
													g_stScopeCtrlInfo.u8RunStopCmd      = SCOPE_STOP_CMD;					\
													g_stScopeCtrlInfo.f32PreData        = 0;								\
													g_stScopeCtrlInfo.f32PreLastData    = 0;								\
													g_stGuiCfgSwScope.emAcqMode         = INVALID_ACQ_MODE;					\
													g_stGuiCfgSwScope.u8TrigIndex       = 0;								\
													if(startup_mode == STARTUP_ITSELF){										\
														g_stGuiCfgSwScope.u8TrigIndex 	 = TRIGG_INDEX;						\
														g_stGuiCfgSwScope.emTrigMethod   = TRIGG_METHOD;					\
														g_stGuiCfgSwScope.emTrigPoint    = TRIGG_POINT;						\
														g_stGuiCfgSwScope.emAcqMode      = ACQ_MODE;						\
														g_stGuiCfgSwScope.u16AcqInterval = ACQ_INTERVAL;						\
														g_stGuiCfgSwScope.f32ThrdValue   = F32_THRD_VALUE;					\
														g_stScopeCtrlInfo.u8RunStopCmd   = SCOPE_RUN_CMD;					\
														g_stScopeRingCtrl.enRingCmd      = RING_REQUEST_WRITE;				\
                                                        if((g_stGuiCfgSwScope.emTrigMethod == FALLING_EDGE)||(g_stGuiCfgSwScope.emTrigMethod == ABOVE_LEVEL)){\
                                                       	 g_stScopeCtrlInfo.f32PreData = g_stGuiCfgSwScope.f32ThrdValue - 10.0f;			\
                                                            g_stScopeCtrlInfo.f32PreLastData = g_stScopeCtrlInfo.f32PreData; 				\
                                              	   	   	 }else{																				\
                                              	   	   	   	 g_stScopeCtrlInfo.f32PreData = g_stGuiCfgSwScope.f32ThrdValue + 10.0f;	    \
                                              	   	   	   	 g_stScopeCtrlInfo.f32PreLastData = g_stScopeCtrlInfo.f32PreData; 			    \
                                              	   	   	 }																					\
													}
 #define SW_SCOPE_ITEM(var) 				   	 u8VarNum++;  
 #define SW_SCOPE_END()                          g_stScopeCtrlInfo.u8Enable = 0;\
													if((u8VarNum <=  SCOPE_VAR_MAX_ITEM_CNT)||(u8VarNum > 0)){\
														g_stScopeCtrlInfo.u8VarChannelNum = u8VarNum;\
														if(g_stGuiCfgSwScope.u8TrigIndex < g_stScopeCtrlInfo.u8VarChannelNum)\
															g_stScopeCtrlInfo.u8Enable = 1;\
                                                    }\
												}
#endif


#ifdef GEN_SW_SCOPE_INIT_DECLARE
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define SW_SCOPE_START(name,startup_mode,cache_size)        extern void sw_scope_init(void);
    #define SW_SCOPE_ITEM(var)
    #define SW_SCOPE_END()

#endif


#ifdef GEN_SW_SCOPE_DATA_ENTITY
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END
    #pragma CODE_SECTION(sw_scope_data, ".TI.ramfunc");
    #define  SW_SCOPE_START(name,startup_mode,cache_size)   void sw_scope_data(void){\
																static UINT16 s_u16AcqIntervalCnt 	         = 0;\
    															UINT16 *p_u16DataTemp                        = NULL;\
																float  f32TempData                           = 0.0f;\
																UINT8  u8VarChannelNum             		     = 0;\
																if(g_stScopeRingCtrl.enRingCmd != RING_REQUEST_WRITE) return;\
																s_u16AcqIntervalCnt ++;\
																if(s_u16AcqIntervalCnt < g_stGuiCfgSwScope.u16AcqInterval) return;\
																s_u16AcqIntervalCnt = 0;\
																if((g_stScopeCtrlInfo.u8TrigFlg == 0)&&(g_stScopeCtrlInfo.u8RunStopCmd == SCOPE_RUN_CMD)){\
																	if(g_stGuiCfgSwScope.emTrigMethod == SW_TRIGG){\
																			 g_stScopeCtrlInfo.u8TrigFlg     = 1;\
																	}else if(g_stGuiCfgSwScope.emTrigMethod == RISING_EDGE){\
																			if((g_stScopeCtrlInfo.f32PreData >= g_stGuiCfgSwScope.f32ThrdValue)&&(g_stScopeCtrlInfo.f32PreLastData <= g_stGuiCfgSwScope.f32ThrdValue))\
																				g_stScopeCtrlInfo.u8TrigFlg = 1;\
																	}else if(g_stGuiCfgSwScope.emTrigMethod == FALLING_EDGE){\
																		if((g_stScopeCtrlInfo.f32PreData <= g_stGuiCfgSwScope.f32ThrdValue)&&(g_stScopeCtrlInfo.f32PreLastData >= g_stGuiCfgSwScope.f32ThrdValue))\
																			g_stScopeCtrlInfo.u8TrigFlg = 1;\
																	}else if(g_stGuiCfgSwScope.emTrigMethod == EQUAL){\
                                                                         if(g_stScopeCtrlInfo.f32PreData == g_stGuiCfgSwScope.f32ThrdValue) \
																		    g_stScopeCtrlInfo.u8TrigFlg = 1;\
																    }else if(g_stGuiCfgSwScope.emTrigMethod == ABOVE_LEVEL){\
																		 if(g_stScopeCtrlInfo.f32PreData >= g_stGuiCfgSwScope.f32ThrdValue)\
																		    g_stScopeCtrlInfo.u8TrigFlg = 1;\
																	}else if(g_stGuiCfgSwScope.emTrigMethod == BELOW_LEVEL){\
																		 if(g_stScopeCtrlInfo.f32PreData <= g_stGuiCfgSwScope.f32ThrdValue) \
																		    g_stScopeCtrlInfo.u8TrigFlg = 1;\
																	}\
                                                                    if(g_stScopeCtrlInfo.u8TrigFlg == 1){\
                                                                        g_stScopeCtrlInfo.i16RecCnt = 0;\
                                                                        if(g_stGuiCfgSwScope.emTrigMethod == SW_TRIGG){\
                                                                            g_stScopeCtrlInfo.i16RecRefCnt = g_stScopeRingCtrl.i16TotalSize;\
                                                                        }else {\
                                                                            if(g_stScopeRingCtrl.i16IdelSize > (SW_SCOPE_CASH_SIZE >> 1))\
                                                                                g_stScopeCtrlInfo.i16RecRefCnt = g_stScopeRingCtrl.i16TotalSize - g_stScopeRingCtrl.i16IdelSize;\
                                                                            else\
                                                                                g_stScopeCtrlInfo.i16RecRefCnt = (SW_SCOPE_CASH_SIZE >> 1);\
                                                                        }\
                                                                    }\
																}
#define  SW_SCOPE_ITEM(var)				    		    		f32TempData = (float)var;\
																p_u16DataTemp                        = (UINT16 *)&f32TempData;\
																if(u8VarChannelNum == g_stGuiCfgSwScope.u8TrigIndex){\
																		g_stScopeCtrlInfo.f32PreLastData = g_stScopeCtrlInfo.f32PreData;\
																		g_stScopeCtrlInfo.f32PreData     = f32TempData;\
																}\
																*g_stScopeRingCtrl.p_u16Input++            = *p_u16DataTemp++;\
																*g_stScopeRingCtrl.p_u16Input++            = *p_u16DataTemp;\
																u8VarChannelNum ++;

      #define  SW_SCOPE_END()                                       g_stScopeCtrlInfo.i16RecCnt += (u8VarChannelNum << 1);\
																if(g_stScopeRingCtrl.i16IdelSize > 0)\
                                                                    g_stScopeRingCtrl.i16IdelSize -= (u8VarChannelNum << 1);\
                                                                if(g_stScopeRingCtrl.p_u16Input >= (g_stScopeRingCtrl.p_u16HeadAddr + g_stScopeRingCtrl.i16TotalSize))\
                                                                    g_stScopeRingCtrl.p_u16Input = g_stScopeRingCtrl.p_u16HeadAddr;\
															    if(g_stScopeRingCtrl.i16IdelSize <= 0)\
                                                                    g_stScopeRingCtrl.p_u16Output = g_stScopeRingCtrl.p_u16Input;\
																if(g_stScopeCtrlInfo.u8TrigFlg == 1){\
																    if(g_stScopeCtrlInfo.i16RecCnt >= g_stScopeCtrlInfo.i16RecRefCnt){\
																		 g_stScopeRingCtrl.enRingCmd      = RING_LOCK_WRITE;\
																		 g_stScopeCtrlInfo.u8DataMsgTxFlg = 1;\
																	}\
																}\
															}
#endif
		
#ifdef GEN_SW_SCOPE_DATA_DECLARE
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define SW_SCOPE_START(name,startup_mode,cache_size)       extern void sw_scope_data(void);
    #define SW_SCOPE_ITEM(var)
    #define SW_SCOPE_END()
#endif


#ifdef GEN_SW_SCOPE_DATA_CALL
	#undef  SW_SCOPE_START
	#undef  SW_SCOPE_ITEM
	#undef  SW_SCOPE_END

    #define SW_SCOPE_START(name,startup_mode,cache_size)           			sw_scope_data();
    #define SW_SCOPE_ITEM(var)
    #define SW_SCOPE_END()
#endif

#ifdef GEN_SW_SCOPE_GUI_SET_ACTION_ENTITY
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define  SW_SCOPE_START(name,startup_mode,cache_size)    void sw_scope_gui_set_action_##name(APL_DOMAIN *p_stAplDm){\
                                                                    UINT16 u16GuiIdStatus = 0;                                                      \
                                                                    UINT16 *p_u16FloatTemp = NULL;                                                  \
                                                                    FRAME_PROTOCOL_FORMAT st_ScopeGuiFrame = {0};                                   \
                                                                    UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));  \
                                                                    if((g_stScopeCtrlInfo.u8Enable == 0)||(g_stScopeCtrlInfo.u8DataMsgTxFlg == 1)||(g_stScopeCtrlInfo.u8RunStopCmd == SCOPE_RUN_CMD)) return;\
     	    														if(startup_mode == STARTUP_ITSELF) return;	\
				                                                    if(p_stAplDm->u16AplDLC == 10)   	\
				                                                    {\
                                                        				if((g_stScopeRingCtrl.enRingCmd == RING_IDLE)||(g_stScopeRingCtrl.enRingCmd == RING_REQUEST_WRITE)){\
                                                                             g_stGuiCfgSwScope.emTrigMethod = (SW_SCOPE_TRIGG_METHOD_M)(*p_u16Data & 0x00FF);             \
                                                                             g_stGuiCfgSwScope.emTrigPoint  = (SW_SCOPE_TRIGG_POINT_M)(*p_u16Data++ >> 8);                \
                                                                             g_stGuiCfgSwScope.emAcqMode    = (SW_SCOPE_ACQ_MODE_M)(*p_u16Data & 0x00FF);                 \
                                                                             g_stGuiCfgSwScope.u8TrigIndex    = (UINT8)(*p_u16Data++ >> 8);                               \
                                                                             g_stGuiCfgSwScope.u16AcqInterval = (UINT8)(*p_u16Data++);                                    \
                                                                             p_u16FloatTemp    = (UINT16 *)&g_stGuiCfgSwScope.f32ThrdValue;                                 \
                                                                             *p_u16FloatTemp++ = *p_u16Data++;                                                              \
                                                                             *p_u16FloatTemp++ = *p_u16Data++;                                                              \
																		     g_stScopeRingCtrl.p_u16HeadAddr  	= g_ua16ScopeBuff;				\
																			 g_stScopeRingCtrl.p_u16Input     		= g_ua16ScopeBuff;				\
																			 g_stScopeRingCtrl.p_u16Output    		= g_ua16ScopeBuff;				\
																			 g_stScopeRingCtrl.i16IdelSize   			= sizeof(g_ua16ScopeBuff);	\
																			 g_stScopeRingCtrl.i16TotalSize  		= sizeof(g_ua16ScopeBuff);	\
																			 memclr_user((UINT16 *)&g_stScopeCopyRingCtrl,sizeof(RING_ITEM)/sizeof(UINT16));           \
															g_stScopeRingCtrl.enRingStaus   = RING_EMPTY;					\
															g_stScopeRingCtrl.enRingCmd     = RING_REQUEST_WRITE;			\
                                                           if((g_stGuiCfgSwScope.emTrigMethod == FALLING_EDGE)||(g_stGuiCfgSwScope.emTrigMethod == ABOVE_LEVEL))\
														    {\
                                                            	 g_stScopeCtrlInfo.f32PreData 		= g_stGuiCfgSwScope.f32ThrdValue - 10.0f;		\
                                                               	 g_stScopeCtrlInfo.f32PreLastData   = g_stScopeCtrlInfo.f32PreData; 				\
                                                   	   	   	}else{																					\
                                                   	   	   	   	 g_stScopeCtrlInfo.f32PreData 		= g_stGuiCfgSwScope.f32ThrdValue + 10.0f;	    \
                                                   	   	   	   	 g_stScopeCtrlInfo.f32PreLastData 	= g_stScopeCtrlInfo.f32PreData; 			    \
                                                   	   	    }																						\
															 u16GuiIdStatus                  	  = 1;											    \
															 if(g_stGuiCfgSwScope.u8TrigIndex >= g_stScopeCtrlInfo.u8VarChannelNum){				\
																 g_stGuiCfgSwScope.emAcqMode         = INVALID_ACQ_MODE;							\
																 u16GuiIdStatus                      = 0;											\
															 }																						\
														}																							\
															st_ScopeGuiFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;   						\
															st_ScopeGuiFrame.stAplDm.unAplCmd.bits.ul8CmdSet    = SW_SCOPE_CMD_SET;  					\
															st_ScopeGuiFrame.stAplDm.unAplCmd.bits.uh8CmdId     = SW_SCOPE_GUI_CFG_ID;  				\
															st_ScopeGuiFrame.stAplDm.u16AplDLC                  = 2;    								\
															st_ScopeGuiFrame.p_u16AppData                        = (UINT16 *)&u16GuiIdStatus;	    		\
															Tpl_Single_Frame_Send(&st_ScopeGuiFrame);													\
												         }
    #define  SW_SCOPE_ITEM(var)
    #define  SW_SCOPE_END()                      }
#endif


#ifdef GEN_SW_SCOPE_GUI_SET_ACTION_DECLARE
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END
	#define SW_SCOPE_START(name,startup_mode,cache_size)           extern void sw_scope_gui_set_action_##name(APL_DOMAIN *p_stAplDm);
	#define SW_SCOPE_ITEM(var)					               extern SW_SCOPE_GUI_CFG_ITEM g_stGuiCfgSwScope;
	#define SW_SCOPE_END()
#endif

#ifdef GEN_SW_SCOPE_GUI_SET_ACTION_CALL
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END
	#define SW_SCOPE_START(name,startup_mode,cache_size)           sw_scope_gui_set_action_##name(p_stAplDm);
	#define SW_SCOPE_ITEM(var)
	#define SW_SCOPE_END()
#endif

#ifdef GEN_SW_SCOPE_TASK_ENTITY
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define  SW_SCOPE_START(name,startup_mode,cache_size)      \
	                                                void sw_scope_task_##name(void){						  											\
														FRAME_PROTOCOL_FORMAT st_ScopeDataFrame = {0};\
														BUFF_CTRL_OBJ st_ScopeDataBuffCtrl;\
														if(g_stScopeCtrlInfo.u8RunStopCmd == SCOPE_STOP_CMD) return;\
														if(g_stGuiCfgSwScope.em_acq_mode == TASK_FRE) sw_scope_data();\
														if(g_stGuiCfgSwScope.em_trig_mode == INVALID_TRIG)  return;\
														if(g_stScopeCtrlInfo.u8DataMsgTxFlg == 1){\
															st_ScopeDataFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;\
															st_ScopeDataFrame.stAplDm.unAplCmd.bits.ul8CmdSet    = SW_SCOPE_CMD_SET;\
															st_ScopeDataFrame.stAplDm.unAplCmd.bits.uh8CmdId     = SW_SCOPE_DATA_CMD_ID;\
															st_ScopeDataFrame.stAplDm.u16AplDLC                  = (g_stScopeRingCtrl.i16TotalSize - g_stScopeRingCtrl.i16IdelSize) << 1;\
															st_ScopeDataFrame.p_u16AppData                       = g_ua16ScopeBuff;\
															st_ScopeDataBuffCtrl.enBuffType                      = RING_BUFF_TYPE;\
															st_ScopeDataBuffCtrl.p_BuffObj                       = (void *)&g_stScopeRingCtrl;\
															if(Tpl_Msg_Send(&st_ScopeDataBuffCtrl,&st_ScopeDataFrame) == TPL_TX_MSG_SUCCESS)\
															{\
																g_stScopeRingCtrl.enRingCmd                         = RING_IDLE;\
															    g_stScopeCtrlInfo.u8RunStopCmd                      = SCOPE_STOP_CMD;\
																g_stScopeCtrlInfo.u8TrigFlg   						= 0;\
																g_stScopeCtrlInfo.u8DataMsgTxFlg                    = 0;\
															}\
														}\
												}\
												REG_TASK(sw_scope_task_##name,	1,		1,		0);
    #define  SW_SCOPE_ITEM(var)
    #define  SW_SCOPE_END()
#endif

#ifdef GEN_SW_SCOPE_ISR_CALL
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define  SW_SCOPE_START(name,startup_mode,cache_size)     	   if(g_stGuiCfgSwScope.emAcqMode == CTR_FRE){sw_scope_data();}
    #define  SW_SCOPE_ITEM(var)
    #define  SW_SCOPE_END()

#endif

#ifdef GEN_SW_SCOPE_RUN_CMD_DECLARE
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define  SW_SCOPE_START(name,startup_mode,cache_size)			extern void sw_scope_run_cmd_##name(APL_DOMAIN *p_stAplDm);
    #define  SW_SCOPE_ITEM(var)
    #define  SW_SCOPE_END()
#endif

#ifdef GEN_SW_SCOPE_RUN_CMD_ENTITY
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END
    #define  SW_SCOPE_START(name,startup_mode,cache_size)       void sw_scope_run_cmd_##name(void *p_stAplDm){\
                                                                     UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));\
																	if(g_stScopeCtrlInfo.u8Enable == 0)             return;\
																	if(g_stScopeRingCtrl.enRingStaus == RING_FULL)  return;\
																	if(startup_mode != STARTUP_ITSELF){\
                                                                         if((*p_u16Data & 0x00FF) == SCOPE_RUN_CMD) {\
                                                                               if(g_stScopeCtrlInfo.u8RunStopCmd  == SCOPE_STOP_CMD){\
                                                                                     g_stScopeRingCtrl.enRingCmd         = RING_REQUEST_WRITE;\
																		             g_stScopeCtrlInfo.u8RunStopCmd 	= SCOPE_RUN_CMD; \
																		           if((g_stGuiCfgSwScope.emTrigMethod == FALLING_EDGE)||(g_stGuiCfgSwScope.emTrigMethod == ABOVE_LEVEL))\
																				  {\
																						 g_stScopeCtrlInfo.f32PreData = g_stGuiCfgSwScope.f32ThrdValue - 10.0f;			\
																						 g_stScopeCtrlInfo.f32PreLastData = g_stScopeCtrlInfo.f32PreData; 				\
																				  }else{																				\
																					g_stScopeCtrlInfo.f32PreData = g_stGuiCfgSwScope.f32ThrdValue + 10.0f;	        \
																					g_stScopeCtrlInfo.f32PreLastData = g_stScopeCtrlInfo.f32PreData; 			    \
																				}\
																		   }\
																		 }else{\
																			 g_stScopeCtrlInfo.u8RunStopCmd     = SCOPE_STOP_CMD; \
																		 }\
																	     g_stScopeCtrlInfo.u8TrigFlg          = 0;\
																	}
    #define  SW_SCOPE_ITEM(var)
    #define  SW_SCOPE_END()				}
#endif


#ifdef GEN_SW_SCOPE_RUN_CMD_CALL
    #undef SW_SCOPE_START
    #undef SW_SCOPE_ITEM
    #undef SW_SCOPE_END

    #define  SW_SCOPE_START(name,startup_mode,cache_size)			sw_scope_run_cmd_##name(p_stAplDm);
    #define  SW_SCOPE_ITEM(var)
    #define  SW_SCOPE_END()
#endif
