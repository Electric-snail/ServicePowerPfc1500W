/*
 * SFRA_DEFINE.h
 *
 *  Created on: 2023.7.31
 *      Author: Hongbo.Jiang
 */
#ifdef   GEN_SFRA_VAR_ENTITY
#undef   SFRA_INJECT
#undef   SFRA_COLLECT
#define  SFRA_INJECT(f32InVar)                                             SFRA_DATA   g_stSfraData;
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)                           SFRA_OUT    g_stSfraOut##name;
#define  SFRA_END()
#endif

#ifdef   GEN_SFRA_VAR_DECLARE
         #undef SFRA_INJECT
         #undef SFRA_COLLECT
         #undef SFRA_END
#define  SFRA_INJECT(f32InjectVar)                                         extern SFRA_DATA   g_stSfraData;
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)                           extern SFRA_OUT    g_stSfraOut##name;
#define  SFRA_END()
#endif

#ifdef   GEN_SFRA_VAR_INIT_ENTITY
         #undef SFRA_INJECT
         #undef SFRA_COLLECT
         #undef SFRA_END
#define  SFRA_INJECT(f32InjectVar)                                         void sfra_var_init(void){\
                                                                               memclr_user((UINT16 *)&g_stSfraData,sizeof(SFRA_DATA)/sizeof(UINT16));

#define  SFRA_COLLECT(name, f32InVar, f32OutVar)                               memclr_user((UINT16 *)&g_stSfraOut##name,sizeof(SFRA_OUT)/sizeof(UINT16));


#define  SFRA_END()                                                        }
#endif

#ifdef   GEN_SFRA_VAR_INIT_CALL
         #undef SFRA_INJECT
         #undef SFRA_COLLECT
         #undef SFRA_END
#define  SFRA_INJECT(f32InjectVar)                                         sfra_var_init();
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)
#define  SFRA_END()
#endif

#ifdef GEN_SFRA_ITEM_ENTITY
         #undef   SFRA_INJECT
         #undef   SFRA_COLLECT
         #undef   SFRA_END
         #define  SFRA_INJECT(f32InjectVar)                  void SfraGetItem(void){\
                                                                  float     f32Temp;                                                            \
                                                                  UINT16    u16RecWrIndex = 0;                                                  \
                                                                  UINT16    u16ItemCnt    = 0;                                                  \
                                                                  UINT16    *p_u16Temp = NULL;                                                  \
                                                                  UINT16    ua16RecBuf[32]={0};                                                 \
                                                                  UINT16    i = 0;                                                              \
                                                                  UINT16    u8CharNum = 0;                                                      \
                                                                  FRAME_PROTOCOL_FORMAT stSfraItemFrame = {0};                                  \
                                                                  SFRA_ITEM_NAME *p_stSfraItemName = NULL;                                      \
                                                                  SFRA_ITEM_NAME *p_stSfraName     = NULL;                                      \
                                                                  const char *p_u8PackName     = #f32InjectVar;                                 \
                                                                  stSfraItemFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr   = PC_NODE_ADDR;          \
                                                                  stSfraItemFrame.stAplDm.unAplCmd.bits.ul8CmdSet      = SFRA_CMD_SET;          \
                                                                  stSfraItemFrame.stAplDm.unAplCmd.bits.uh8CmdId       = SFRA_GET_ITEM_ID;      \
                                                                  stSfraItemFrame.p_u16AppData                         = ua16RecBuf;            \
                                                                  f32Temp                                              = CTR_PERIOD;            \
                                                                  p_u16Temp = (unsigned short *)&f32Temp;                                       \
                                                                  ua16RecBuf[u16RecWrIndex++] = *p_u16Temp++;                                   \
                                                                  ua16RecBuf[u16RecWrIndex++] = *p_u16Temp++;                                   \
                                                                  p_stSfraName = (SFRA_ITEM_NAME *)(&ua16RecBuf[u16RecWrIndex++]);              \
                                                                  u8CharNum                                            = strlen(p_u8PackName);  \
                                                                  p_stSfraName->bits.uh8NameLen = u8CharNum;                                    \
                                                                  for(i = 0; i < u8CharNum;i+= 2){                                              \
                                                                      ua16RecBuf[u16RecWrIndex] = *p_u8PackName++;                              \
                                                                      ua16RecBuf[u16RecWrIndex++] |= ((UINT16)(*p_u8PackName++) << 8);          \
                                                                   }
         #define  SFRA_COLLECT(name, f32InVar, f32OutVar)          if(u16ItemCnt >= 3) return;\
                                                                   p_u8PackName       = #name;                                                  \
                                                                   u8CharNum          = strlen(p_u8PackName);                                   \
                                                                   p_stSfraItemName   = (SFRA_ITEM_NAME *)(&ua16RecBuf[u16RecWrIndex++]);       \
                                                                   p_stSfraItemName->bits.ul8Index   = u16ItemCnt++;                            \
                                                                   p_stSfraItemName->bits.uh8NameLen = u8CharNum;                               \
                                                                   for(i = 0; i < u8CharNum;i+= 2){                                             \
                                                                        ua16RecBuf[u16RecWrIndex] = *p_u8PackName++;                            \
                                                                        ua16RecBuf[u16RecWrIndex++] |= ((UINT16)(*p_u8PackName++) << 8);        \
                                                                   }

        #define  SFRA_END()                                        p_stSfraName->bits.ul8Index                          = u16ItemCnt;           \
                                                                   stSfraItemFrame.stAplDm.u16AplDLC                    = u16RecWrIndex << 1;   \
                                                                   Tpl_Single_Frame_Send(&stSfraItemFrame);                                     \
                                                               }
#endif

#ifdef   GEN_SFRA_ITEM_CALL
         #undef SFRA_INJECT
         #undef SFRA_COLLECT
         #undef SFRA_END
#define  SFRA_INJECT(f32InjectVar)                              SfraGetItem();
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)
#define  SFRA_END()
#endif

#ifdef GEN_SFRA_TX_DATA_ENTITY
         #undef   SFRA_INJECT
         #undef   SFRA_COLLECT
         #undef   SFRA_END
         #define  SFRA_INJECT(f32InjectVar)                  void sfra_tx_data(void){\
                                                                FRAME_PROTOCOL_FORMAT   stSfraCollectFrame = {0};\
                                                                unsigned short u16DataIndex = 0, i = 0;\
                                                                unsigned short *p_u16Temp   = NULL;\
                                                                unsigned short ua16DataBuff[3*sizeof(SFRA_OUT)]            = {0};\
                                                                stSfraCollectFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = SFRA_CMD_SET;\
                                                                stSfraCollectFrame.stAplDm.unAplCmd.bits.uh8CmdId          = SFRA_DATA_ID;\
                                                                stSfraCollectFrame.p_u16AppData                            = ua16DataBuff;\
                                                                stSfraCollectFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;

         #define  SFRA_COLLECT(name, f32InVar, f32OutVar)       p_u16Temp = (unsigned short *)&g_stSfraOut##name;\
                                                                for(i = 0; i < sizeof(SFRA_OUT); i++){\
                                                                    ua16DataBuff[u16DataIndex++] = *p_u16Temp++;\
                                                                }

         #define  SFRA_END()                                    stSfraCollectFrame.stAplDm.u16AplDLC                       = u16DataIndex * TYPE_8_BYTE_SIZE;\
                                                                Tpl_Single_Frame_Send(&stSfraCollectFrame);\
                                                             }
#endif

#ifdef   GEN_SFRA_TX_DATA_CALL
         #undef SFRA_INJECT
         #undef SFRA_COLLECT
         #undef SFRA_END
#define  SFRA_INJECT(f32InjectVar)                              sfra_tx_data();
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)
#define  SFRA_END()
#endif

#ifdef   GEN_SFRA_INJECT_ISR_ENTITY
         #undef SFRA_INJECT
         #undef SFRA_COLLECT
         #undef SFRA_END
         #pragma CODE_SECTION(sfra_inject_isr, ".TI.ramfunc");
#define  SFRA_INJECT(f32InjectVar)                                         void sfra_inject_isr(float *p_f32SfraInject){\
                                                                             float f32Temp,f32CosTemp;\
                                                                              if(g_stSfraData.u16InjectCmd == 0) return;\
                                                                              f32Temp  = g_stSfraData.f32Wn*g_stSfraData.u32InjectCount;\
                                                                              f32CosTemp = cosf(f32Temp);\
                                                                              (*p_f32SfraInject)  += g_stSfraCfg.f32InjectMag*f32CosTemp;\
                                                                              g_stSfraData.u32InjectCount++;\
                                                                              if(g_stSfraData.u32InjectCount >= g_stSfraData.u32InjectN)  g_stSfraData.u32InjectCount = 0;
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)
#define  SFRA_END()                                                       }
#endif

#ifdef GEN_SFRA_INJECT_ISR_DECLARE
          #undef SFRA_INJECT
          #undef SFRA_COLLECT
          #undef SFRA_END
#define  SFRA_INJECT(f32InjectVar)                                        extern void sfra_inject_isr(float *);
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)
#define  SFRA_END()
#endif

#ifdef GEN_SFRA_INJECT_ISR_CALL
          #undef SFRA_INJECT
          #undef SFRA_COLLECT
          #undef SFRA_END
#define  SFRA_INJECT(f32InjectVar)                                        sfra_inject_isr(&(f32InjectVar));
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)
#define  SFRA_END()
#endif

#ifdef   GEN_SFRA_COLLECT_ISR_ENTITY
         #undef SFRA_INJECT
         #undef SFRA_COLLECT
         #undef SFRA_END
         #pragma CODE_SECTION(sfra_collect_isr, ".TI.ramfunc");
#define  SFRA_INJECT(f32InjectVar)                                         void sfra_collect_isr(void){\
                                                                             float f32Temp,f32CosTemp,f32SinTemp;\
                                                                             if(g_stSfraData.u16CollectCmd == 0) return;

#define  SFRA_COLLECT(name, f32InVar, f32OutVar)                             static FFT_DATA   s_stFftInCollect##name  = {0.0f, 0.0f};\
                                                                             static FFT_DATA   s_stFftOutCollect##name = {0.0f, 0.0f};\
                                                                             if(g_stSfraData.u32CollectCount >= g_stSfraData.u32CollectN){\
                                                                                g_stSfraOut##name.u32N                 =  g_stSfraData.u32CollectN;\
                                                                                g_stSfraOut##name.stFftIn.f32Real      =  s_stFftInCollect##name.f32Real;\
                                                                                g_stSfraOut##name.stFftIn.f32Imag      =  s_stFftInCollect##name.f32Imag;\
                                                                                g_stSfraOut##name.stFftOut.f32Real     =  s_stFftOutCollect##name.f32Real;\
                                                                                g_stSfraOut##name.stFftOut.f32Imag     =  s_stFftOutCollect##name.f32Imag;\
                                                                                g_stSfraOut##name.f32Period            =  g_stSfraData.f32PeriodActual;\
                                                                                s_stFftInCollect##name.f32Real         =  0;\
                                                                                s_stFftInCollect##name.f32Imag         =  0;\
                                                                                s_stFftOutCollect##name.f32Real        =  0;\
                                                                                s_stFftOutCollect##name.f32Imag        =  0;\
                                                                            }else{\
                                                                               f32Temp                           = g_stSfraData.f32Wn*g_stSfraData.u32CollectCount;\
                                                                               f32CosTemp                        = cosf(f32Temp);\
                                                                               f32SinTemp                        = sinf(f32Temp);\
                                                                               s_stFftInCollect##name.f32Real         += (f32InVar)*f32CosTemp;\
                                                                               s_stFftInCollect##name.f32Imag         -= (f32InVar)*f32SinTemp;\
                                                                               s_stFftOutCollect##name.f32Real        +=  (f32OutVar)*f32CosTemp;\
                                                                               s_stFftOutCollect##name.f32Imag        -=  (f32OutVar)*f32SinTemp;\
                                                                            }
#define  SFRA_END()                                                         if(g_stSfraData.u32CollectCount >= g_stSfraData.u32CollectN){\
                                                                                g_stSfraData.u16CollectCmd       =  0;\
                                                                                g_stSfraData.u32CollectCount     =  0;\
                                                                            }else{\
                                                                                g_stSfraData.u32CollectCount++;\
                                                                            }\
                                                                          }
#endif

#ifdef GEN_SFRA_COLLECT_ISR_DECLARE
          #undef SFRA_INJECT
          #undef SFRA_COLLECT
          #undef SFRA_END
#define  SFRA_INJECT(f32InjectVar)                                        extern void sfra_collect_isr(void);
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)
#define  SFRA_END()
#endif

#ifdef GEN_SFRA_COLLECT_ISR_CALL
          #undef SFRA_INJECT
          #undef SFRA_COLLECT
          #undef SFRA_END
#define  SFRA_INJECT(f32InjectVar)                                        sfra_collect_isr();
#define  SFRA_COLLECT(name, f32InVar, f32OutVar)
#define  SFRA_END()
#endif
