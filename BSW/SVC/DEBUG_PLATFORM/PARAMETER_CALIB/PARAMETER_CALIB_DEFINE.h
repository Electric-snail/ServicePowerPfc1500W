/*
 * PARAME_CALIB_Define.h
 *
 *  Created on: 2022.9.15
 *      Author: hongbo.jiang
 */
                      
#ifdef GEN_PARAM_CALIB_VAR_F32_TYPE_ENTITY
    #undef 	PARAME_CALIB_START
    #undef 	PARAME_CALIB_ITEM_F32
	#undef 	PARAME_CALIB_RVS_ITEM_F32
	#undef 	PARAME_CALIB_ITEM_I16
	#undef 	PARAME_CALIB_RVS_ITEM_I16
    #undef 	PARAME_CALIB_END

	#define PARAME_CALIB_START()                       							typedef struct{
    #define PARAME_CALIB_RVS_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)                 	F32_CALIB_ITEM_T   st##name;
	#define PARAME_CALIB_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)                     	    F32_CALIB_ITEM_T   st##name;
	#define PARAME_CALIB_RVS_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)              
	#define PARAME_CALIB_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)                    
	#define PARAME_CALIB_END()                         							}F32_CALIB_DATA_OBJ_T;
#endif

#ifdef GEN_PARAM_CALIB_LIMIT_VAR_F32_TYPE_ENTITY
    #undef 	PARAME_CALIB_START
    #undef 	PARAME_CALIB_ITEM_F32
	#undef 	PARAME_CALIB_RVS_ITEM_F32
	#undef 	PARAME_CALIB_ITEM_I16
	#undef 	PARAME_CALIB_RVS_ITEM_I16
    #undef 	PARAME_CALIB_END

	#define PARAME_CALIB_START()                       						typedef struct{
    #define PARAME_CALIB_RVS_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)          F32_CALIB_LIMIT_ITEM_T   st##name;
	#define PARAME_CALIB_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)                  F32_CALIB_LIMIT_ITEM_T   st##name;
	#define PARAME_CALIB_RVS_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)              
	#define PARAME_CALIB_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)                    
	#define PARAME_CALIB_END()                         						}F32_CALIB_LIMIT_DATA_OBJ_T;
#endif

#ifdef GEN_PARAM_CALIB_VAR_I16_TYPE_ENTITY
    #undef 	PARAME_CALIB_START
    #undef 	PARAME_CALIB_ITEM_F32
	#undef 	PARAME_CALIB_RVS_ITEM_F32
	#undef 	PARAME_CALIB_ITEM_I16
	#undef 	PARAME_CALIB_RVS_ITEM_I16
    #undef 	PARAME_CALIB_END

	#define PARAME_CALIB_START()                       						typedef struct{
    #define PARAME_CALIB_RVS_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)               
	#define PARAME_CALIB_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)
	#define PARAME_CALIB_RVS_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)              I16_CALIB_ITEM_T   st##name;
	#define PARAME_CALIB_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)                      I16_CALIB_ITEM_T   st##name;
	#define PARAME_CALIB_END()                         						}I16_CALIB_DATA_OBJ_T;
#endif

#ifdef GEN_PARAM_CALIB_LIMIT_VAR_I16_TYPE_ENTITY
    #undef 	PARAME_CALIB_START
    #undef 	PARAME_CALIB_ITEM_F32
	#undef 	PARAME_CALIB_RVS_ITEM_F32
	#undef 	PARAME_CALIB_ITEM_I16
	#undef 	PARAME_CALIB_RVS_ITEM_I16
    #undef 	PARAME_CALIB_END

	#define PARAME_CALIB_START()                       						typedef struct{
    #define PARAME_CALIB_RVS_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)          
	#define PARAME_CALIB_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)              
	#define PARAME_CALIB_RVS_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)          I16_CALIB_LIMIT_ITEM_T   st##name;     
	#define PARAME_CALIB_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)                  I16_CALIB_LIMIT_ITEM_T   st##name;
	#define PARAME_CALIB_END()                         						}I16_CALIB_LIMIT_DATA_OBJ_T;
#endif
	
#ifdef GEN_PARAM_CALIB_LIMIT_DATA_INIT_ENTITY
    #undef 	PARAME_CALIB_START
    #undef 	PARAME_CALIB_ITEM_F32
	#undef 	PARAME_CALIB_RVS_ITEM_F32
	#undef 	PARAME_CALIB_ITEM_I16
	#undef 	PARAME_CALIB_RVS_ITEM_I16
    #undef 	PARAME_CALIB_END
    #define PARAME_CALIB_START()                  void parame_calib_limit_init(void){
    #define PARAME_CALIB_RVS_ITEM_F32(name, K_MAX, K_MIN, B_MAX, B_MIN)\
												  g_stF32CalibLimitData.st##name.f32Kmax = K_MAX;\
		                                          g_stF32CalibLimitData.st##name.f32Kmin = K_MIN;\
		                                          g_stF32CalibLimitData.st##name.f32Bmax = B_MAX;\
		                                          g_stF32CalibLimitData.st##name.f32Bmin = B_MIN;
		
   #define PARAME_CALIB_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)\
												  g_stF32CalibLimitData.st##name.f32Kmax = K_MAX;\
		                                          g_stF32CalibLimitData.st##name.f32Kmin = K_MIN;\
		                                          g_stF32CalibLimitData.st##name.f32Bmax = B_MAX;\
		                                          g_stF32CalibLimitData.st##name.f32Bmin = B_MIN;
   #define PARAME_CALIB_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)\
												  g_stI16CalibLimitData.st##name.i16Q8Kmax = (signed short)(K_MAX);\
		                                          g_stI16CalibLimitData.st##name.i16Q8Kmin = (signed short)(K_MIN);\
		                                          g_stI16CalibLimitData.st##name.i16Q8Bmax = (signed short)(B_MAX);\
		                                          g_stI16CalibLimitData.st##name.i16Q8Bmin = (signed short)(B_MIN);
		
   #define PARAME_CALIB_RVS_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)\
												  g_stI16CalibLimitData.st##name.i16Q8Kmax = (signed short)(K_MAX);\
		                                          g_stI16CalibLimitData.st##name.i16Q8Kmin = (signed short)(K_MIN);\
		                                          g_stI16CalibLimitData.st##name.i16Q8Bmax = (signed short)(B_MAX);\
		                                          g_stI16CalibLimitData.st##name.i16Q8Bmin = (signed short)(B_MIN);

   #define PARAME_CALIB_END()   				}
	
#endif

#ifdef GEN_PARAM_CALIB_LIMIT_DATA_INIT_DECLARE
    #undef 	PARAME_CALIB_START
    #undef 	PARAME_CALIB_ITEM_F32
	#undef 	PARAME_CALIB_RVS_ITEM_F32
	#undef 	PARAME_CALIB_ITEM_I16
	#undef 	PARAME_CALIB_RVS_ITEM_I16
    #undef 	PARAME_CALIB_END
    #define PARAME_CALIB_START()              
    #define PARAME_CALIB_RVS_ITEM_F32(name, K_MAX, K_MIN, B_MAX, B_MIN)
    #define PARAME_CALIB_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)
    #define PARAME_CALIB_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)	
    #define PARAME_CALIB_RVS_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)
    #define PARAME_CALIB_END()   				extern void parame_calib_limit_init(void);
	
#endif

#ifdef GEN_PARAM_CALIB_LIMIT_DATA_INIT_CALL
    #undef 	PARAME_CALIB_START
    #undef 	PARAME_CALIB_ITEM_F32
	#undef 	PARAME_CALIB_RVS_ITEM_F32
	#undef 	PARAME_CALIB_ITEM_I16
	#undef 	PARAME_CALIB_RVS_ITEM_I16
    #undef 	PARAME_CALIB_END
    #define PARAME_CALIB_START()              
    #define PARAME_CALIB_RVS_ITEM_F32(name, K_MAX, K_MIN, B_MAX, B_MIN)
    #define PARAME_CALIB_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)
    #define PARAME_CALIB_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)	
    #define PARAME_CALIB_RVS_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)
    #define PARAME_CALIB_END()   				parame_calib_limit_init();
	
#endif

#ifdef GEN_PARAM_CALIB_ITEM_ENTITY
    #undef 	PARAME_CALIB_START
    #undef 	PARAME_CALIB_ITEM_F32
	#undef 	PARAME_CALIB_RVS_ITEM_F32
	#undef 	PARAME_CALIB_ITEM_I16
	#undef 	PARAME_CALIB_RVS_ITEM_I16
    #undef 	PARAME_CALIB_END

	#define PARAME_CALIB_START()                  void parame_calib_item(void){\
												  float f32Temp;\
												  UINT16     *p_u16Temp;\
                                                  UINT16  	 ua16RecBuf[DP_APL_SIG_FRAME_RX_MAX_BYTE_LEN >> 1]={0};     \
                                                  FRAME_PROTOCOL_FORMAT st_ParamCalibItemFrame = {0};  		  \
                                                  UINT16    i 					        =    0;                           \
                                                  UINT16  max_var_item 		    = 0;                              \
                                                  UINT16  rec_w_index  		    = 0;     					        \
                                                  UINT16  u16CharNum    		= 0;							    \
												  UINT16  u16TempData;                                              \
                                                  const char *p_u8PackName;\
                                                  st_ParamCalibItemFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR; \
                                                  st_ParamCalibItemFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = PARAM_CALIB_CMD_SET; \
                                                  st_ParamCalibItemFrame.stAplDm.unAplCmd.bits.uh8CmdId         = PARAM_CALIB_ITEM_CMD_ID;  \
                                                  st_ParamCalibItemFrame.p_u16AppData                                       = ua16RecBuf;	\
                                                  rec_w_index++;       //Reserve one word to store the number of calibration
   #define PARAME_CALIB_RVS_ITEM_F32(name, K_MAX, K_MIN, B_MAX, B_MIN)\
												  p_u8PackName                   = #name;       \
		                                          u16CharNum					    = strlen(p_u8PackName);	    \
                                                  if((rec_w_index + ((u16CharNum + 1) >> 1)) >= (DP_APL_SIG_FRAME_RX_MAX_BYTE_LEN >> 1)) return;   \
											      ua16RecBuf[rec_w_index++]      = CALIB_RVS_METHOD + ((UINT16)eu_fp32 << 8);\
												  ua16RecBuf[rec_w_index++]      = max_var_item + ((UINT16)u16CharNum<< 8);\
											      for(i = 0; i < u16CharNum;i+= 2){\
											          u16TempData = *p_u8PackName++;                                                                        \
												     ua16RecBuf[rec_w_index++] = u16TempData +  ((UINT16)*p_u8PackName++ << 8);\
                                                  }\
												  p_u16Temp                       = (UINT16 *)&f32Temp;\
												  f32Temp                           = (K_MAX);\
												  ua16RecBuf[rec_w_index++]       = p_u16Temp[0];\
												  ua16RecBuf[rec_w_index++]       = p_u16Temp[1];\
												  f32Temp = K_MIN;\
                                                  ua16RecBuf[rec_w_index++]       = p_u16Temp[0];\
                                                  ua16RecBuf[rec_w_index++]       = p_u16Temp[1];\
												  f32Temp = B_MAX;\
                                                  ua16RecBuf[rec_w_index++]       = p_u16Temp[0];\
                                                  ua16RecBuf[rec_w_index++]       = p_u16Temp[1];\
												  f32Temp = B_MIN;\
                                                  ua16RecBuf[rec_w_index++]       = p_u16Temp[0];\
                                                  ua16RecBuf[rec_w_index++]       = p_u16Temp[1];\
												  max_var_item ++;
   #define PARAME_CALIB_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)\
                                                  p_u8PackName  = #name;\
                                                  u16CharNum					     = strlen(p_u8PackName);\
                                                  if((rec_w_index + ((u16CharNum + 1) >> 1)) >=( DP_APL_SIG_FRAME_RX_MAX_BYTE_LEN >> 1)) return; \
                                                  ua16RecBuf[rec_w_index++]      = CALIB_FWD_METHOD + ((UINT16)eu_fp32 << 8);\
                                                  ua16RecBuf[rec_w_index++]      = max_var_item + ((UINT16)u16CharNum<< 8);\
                                                  for(i = 0; i < u16CharNum;i+= 2){\
                                                      u16TempData                       = *p_u8PackName++;                                                  \
                                                     ua16RecBuf[rec_w_index++]  = u16TempData +  ((UINT16)*p_u8PackName++ << 8);\
                                                  }\
                                                    p_u16Temp                         = (UINT16 *)&f32Temp;\
                                                    f32Temp                             = (K_MAX);\
                                                    ua16RecBuf[rec_w_index++]       = p_u16Temp[0];\
                                                    ua16RecBuf[rec_w_index++]       = p_u16Temp[1];\
                                                    f32Temp                             = K_MIN;\
                                                    ua16RecBuf[rec_w_index++]       = p_u16Temp[0];\
                                                    ua16RecBuf[rec_w_index++]       = p_u16Temp[1];\
                                                    f32Temp                             = B_MAX;\
                                                    ua16RecBuf[rec_w_index++]       = p_u16Temp[0];\
                                                    ua16RecBuf[rec_w_index++]       = p_u16Temp[1];\
                                                    f32Temp                             = B_MIN;\
                                                    ua16RecBuf[rec_w_index++]       = p_u16Temp[0];\
                                                    ua16RecBuf[rec_w_index++]       = p_u16Temp[1];\
                                                    max_var_item ++;

    #define PARAME_CALIB_RVS_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)\
                                               p_u8PackName  = #name;                                                        \
                                               u16CharNum                    = strlen(p_u8PackName);      \
                                               if((rec_w_index + ((u16CharNum + 1) >> 1)) >=( DP_APL_SIG_FRAME_RX_MAX_BYTE_LEN >> 1)) return; \
                                               ua16RecBuf[rec_w_index++]      = CALIB_RVS_METHOD + ((UINT16)eu_int16 << 8);\
                                              ua16RecBuf[rec_w_index++]      = max_var_item + ((UINT16)u16CharNum<< 8);\
                                              for(i = 0; i < u16CharNum;i+= 2){\
                                                  u16TempData = *p_u8PackName++;                                                                        \
                                                 ua16RecBuf[rec_w_index++] = u16TempData +  ((UINT16)*p_u8PackName++ << 8);\
                                              }\
                                               ua16RecBuf[rec_w_index++]       = (UINT16)((signed short)K_MAX);\
                                               ua16RecBuf[rec_w_index++]       = (UINT16)((signed short)K_MIN);\
                                               ua16RecBuf[rec_w_index++]       = (UINT16)((signed short)B_MAX);\
                                               ua16RecBuf[rec_w_index++]       = (UINT16)((signed short)B_MIN);\
                                               max_var_item ++;

   #define PARAME_CALIB_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)\
                                                p_u8PackName  = #name;                                                        \
                                                u16CharNum                    = strlen(p_u8PackName);      \
                                                if((rec_w_index + ((u16CharNum + 1) >> 1)) >=( DP_APL_SIG_FRAME_RX_MAX_BYTE_LEN >> 1)) return; \
                                                ua16RecBuf[rec_w_index++]      = CALIB_FWD_METHOD + ((UINT16)eu_int16 << 8);\
                                               ua16RecBuf[rec_w_index++]      = max_var_item + ((UINT16)u16CharNum<< 8);\
                                               for(i = 0; i < u16CharNum;i+= 2){\
                                                   u16TempData = *p_u8PackName++;                                                                       \
                                                  ua16RecBuf[rec_w_index++] = u16TempData +  ((UINT16)*p_u8PackName++ << 8);\
                                               }\
                                                ua16RecBuf[rec_w_index++]       = (UINT16)((signed short)K_MAX);\
                                                ua16RecBuf[rec_w_index++]       = (UINT16)((signed short)K_MIN);\
                                                ua16RecBuf[rec_w_index++]       = (UINT16)((signed short)B_MAX);\
                                                ua16RecBuf[rec_w_index++]       = (UINT16)((signed short)B_MIN);\
                                                max_var_item ++;
												  
   #define PARAME_CALIB_END()   				 \
                                                 ua16RecBuf[0]  = max_var_item;       \
												 st_ParamCalibItemFrame.stAplDm.u16AplDLC                 = rec_w_index << 1;	       \
                                                 Tpl_Single_Frame_Send(&st_ParamCalibItemFrame);  								\
                                     }
#endif

#ifdef GEN_PARAM_CALIB_ITEM_CALL
    #undef 	PARAME_CALIB_START
    #undef 	PARAME_CALIB_ITEM_F32
	#undef 	PARAME_CALIB_RVS_ITEM_F32
	#undef 	PARAME_CALIB_ITEM_I16
	#undef 	PARAME_CALIB_RVS_ITEM_I16
    #undef 	PARAME_CALIB_END

	#define PARAME_CALIB_START()                  
    #define PARAME_CALIB_RVS_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)
    #define PARAME_CALIB_ITEM_F32(name,K_MAX, K_MIN, B_MAX, B_MIN)
    #define PARAME_CALIB_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)
    #define PARAME_CALIB_RVS_ITEM_I16(name,K_MAX, K_MIN, B_MAX, B_MIN)						  
    #define PARAME_CALIB_END()					  parame_calib_item();
#endif
