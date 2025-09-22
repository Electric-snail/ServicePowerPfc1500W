/*
 * SFRA.c
 *
 *  Created on: 2023.7.28
 *      Author: Hongbo.Jiang
 */
#include <DP_STACK/NWM/NWM_STACK.H>
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#include "SVC/BSW_SVC_BASIC.h"
#include "DEBUG_PLATFORM/SFRA/SFRA.h"

#include "PUBLIC_INC/MEM_HANDLE.H"

#include "DEBUG_PLATFORM/DBG_BASIC.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DP_STACK/APL/APL_STACK.H"
#include "TASK/BSW_TASK_SERVICE.H"
#include "math.h"
#include "string.h"

#define     SFRA_INIT               0
#define     SFRA_IDEL               1
#define     SFRA_INJECT_INIT        2
#define     SFRA_WAIT_STABLE        3
#define     SFRA_COLLECT_DATA       4
#define     SFRA_TRANS_DATA         5
#define     SFRA_WAIT_RESPOND       6

#define     SFRA_STOP_CMD           0
#define     SFRA_START_CMD          1

#define     SFRA_TASK_PERIOD        2   //ms

SFRA_CFG    g_stSfraCfg;

unsigned short g_u16SfraRunCmd = 0, g_u16SfraCfgFlg = 0, g_u16SfraDataRespFlg = 0;

#define GEN_SFRA_VAR_ENTITY
#include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
#undef GEN_SFRA_VAR_ENTITY

#define GEN_SFRA_ITEM_ENTITY
    #include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
#undef GEN_SFRA_ITEM_ENTITY

#define GEN_SFRA_INJECT_ISR_ENTITY
    #include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
#undef GEN_SFRA_INJECT_ISR_ENTITY

#define GEN_SFRA_COLLECT_ISR_ENTITY
    #include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
#undef GEN_SFRA_COLLECT_ISR_ENTITY

#define GEN_SFRA_TX_DATA_ENTITY
    #include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
#undef GEN_SFRA_TX_DATA_ENTITY

#define GEN_SFRA_VAR_INIT_ENTITY
    #include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
#undef GEN_SFRA_VAR_INIT_ENTITY

void sfra_init(void){
        #define GEN_SFRA_VAR_INIT_CALL
            #include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
        #undef GEN_SFRA_VAR_INIT_CALL
}

/*void SfraCollectDataTx(void){
    FRAME_PROTOCOL_FORMAT   stSfraCollectFrame = {0};
    stSfraCollectFrame.stAplDm.u16AplDLC                       = sizeof(SFRA_OUT) * TYPE_8_BYTE_SIZE;
    stSfraCollectFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = SFRA_CMD_SET;
    stSfraCollectFrame.stAplDm.unAplCmd.bits.uh8CmdId          = SFRA_DATA_ID;
    stSfraCollectFrame.p_u16AppData                            = (UINT16 *)&g_stSfraOut;
    stSfraCollectFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;
    Tpl_Single_Frame_Send(&stSfraCollectFrame);
}*/

void sfra_fsm_task(void){
   static UINT16 s_u16SfraFsmStatus = SFRA_INIT;
   static UINT32 s_u32TimerCnt = 0;
   UINT32 u32Temp;
   float  f32Temp;
   switch(s_u16SfraFsmStatus){
       case SFRA_INIT:{
            #define GEN_SFRA_VAR_INIT_CALL
                #include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
            #undef GEN_SFRA_VAR_INIT_CALL
            s_u16SfraFsmStatus  = SFRA_IDEL;
       }break;
       case SFRA_IDEL:{
           if(g_u16SfraRunCmd == SFRA_START_CMD){
               g_stSfraData.f32FreqCmd = g_stSfraCfg.f32StartFreq;
               s_u16SfraFsmStatus      = SFRA_INJECT_INIT;
           }
       }break;
      case SFRA_INJECT_INIT:{
           if(g_stSfraData.f32FreqCmd > g_stSfraCfg.f32EndFreq){
               g_u16SfraRunCmd      = SFRA_STOP_CMD;
               s_u16SfraFsmStatus   = SFRA_INIT;
           }else{
               g_stSfraData.u32InjectN   = (unsigned long)(1.0f/(g_stSfraData.f32FreqCmd*CTR_PERIOD*0.000001f));
               g_stSfraData.f32PeriodActual = g_stSfraData.u32InjectN*CTR_PERIOD*0.000001f;
               g_stSfraData.f32Wn           = 2.0f*3.1415926f/g_stSfraData.u32InjectN;
               g_stSfraData.u16InjectCmd    = 1;
               s_u32TimerCnt                = 0;
               s_u16SfraFsmStatus           = SFRA_WAIT_STABLE;
           }
           if(g_stSfraData.f32FreqCmd > 2000.0f)
             f32Temp = 0.01f*g_stSfraData.f32FreqCmd;
           else
             f32Temp = 0.005f*g_stSfraData.f32FreqCmd;
           if(f32Temp > g_stSfraCfg.f32StepFreq)
               g_stSfraData.f32FreqCmd += f32Temp;
           else
               g_stSfraData.f32FreqCmd += g_stSfraCfg.f32StepFreq;
           g_stSfraData.f32FreqCmd      += g_stSfraCfg.f32StepFreq;
       }break;
       case SFRA_WAIT_STABLE:{
           s_u32TimerCnt += (UINT32)(SFRA_TASK_PERIOD*1000/CTR_PERIOD);
           u32Temp = (s_u32TimerCnt >> 4);
           if(u32Temp > g_stSfraData.u32InjectN){
               if(g_stSfraData.u32InjectN > 1024){
                  g_stSfraData.u32CollectN   = g_stSfraData.u32InjectN;//收集的点，不超过1024个
               }
               else
               {
                   if (g_stSfraData.u32InjectN != 0U)
                   {
                       u32Temp = (unsigned long)(1024 / g_stSfraData.u32InjectN); //如果收集点一个周期内，低于1024个，取小于1024的整数倍
                   }
                   else
                   {
                       u32Temp = 0U; //如果收集点一个周期内，低于1024个，取小于1024的整数倍
                   }
                       
                   g_stSfraData.u32CollectN  = (unsigned long)(g_stSfraData.u32InjectN*u32Temp);
               }
               g_stSfraData.u16CollectCmd = 1;
               s_u16SfraFsmStatus        = SFRA_COLLECT_DATA;
           }
       }break;
       case SFRA_COLLECT_DATA:{
           if(g_stSfraData.u16CollectCmd == 0){
               s_u16SfraFsmStatus        = SFRA_TRANS_DATA;
           }
           if(g_u16SfraRunCmd == SFRA_STOP_CMD){
               s_u16SfraFsmStatus        = SFRA_INIT;
           }
       }break;
       case SFRA_TRANS_DATA:{
            #define GEN_SFRA_TX_DATA_CALL
                #include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
            #undef GEN_SFRA_TX_DATA_CALL
           s_u32TimerCnt                 = 0;
           s_u16SfraFsmStatus            = SFRA_WAIT_RESPOND;
       }break;
       case SFRA_WAIT_RESPOND:{
           s_u32TimerCnt++;
           if(s_u32TimerCnt > 50)
               s_u16SfraFsmStatus            = SFRA_INJECT_INIT;
           if(g_u16SfraRunCmd == SFRA_STOP_CMD){
               s_u16SfraFsmStatus        = SFRA_INIT;
           }
       }break;
       default:break;
   }
}

/*#pragma CODE_SECTION(SfraInjectIsr, ".TI.ramfunc");

void SfraInjectIsr(float *p_f32SfraInject){
      float f32Temp,f32CosTemp;
      if(g_stSfraData.u16InjectCmd == 0) return;
      f32Temp  = g_stSfraData.f32Wn*g_stSfraData.u32InjectCount;
      f32CosTemp = cosf(f32Temp);
      (*p_f32SfraInject)  += g_stSfraCfg.f32InjectMag*f32CosTemp;
      g_stSfraData.u32InjectCount++;
      if(g_stSfraData.u32InjectCount >= g_stSfraData.u32InjectN)  g_stSfraData.u32InjectCount = 0;
}


#pragma CODE_SECTION(SfraCollectIsr, ".TI.ramfunc");
void SfraCollectIsr(float f32SfraInObj, float f32SfraOutObj){
    static FFT_DATA   s_stFftInCollect  = {0};
    static FFT_DATA   s_stFftOutCollect = {0};
    float f32Temp,f32CosTemp,f32SinTemp;
    if(g_stSfraData.u16CollectCmd == 0) return;
    if(g_stSfraData.u32CollectCount >= g_stSfraData.u32CollectN){
        g_stSfraOutLPF.u32N                 =  g_stSfraData.u32CollectN;
        g_stSfraOutLPF.stFftIn.f32Real      =  s_stFftInCollect.f32Real;
        g_stSfraOutLPF.stFftIn.f32Imag      =  s_stFftInCollect.f32Imag;
        g_stSfraOutLPF.stFftOut.f32Real     =  s_stFftOutCollect.f32Real;
        g_stSfraOutLPF.stFftOut.f32Imag     =  s_stFftOutCollect.f32Imag;
        g_stSfraOutLPF.f32Period            =  g_stSfraData.f32PeriodActual;
        s_stFftInCollect.f32Real         =  0;
        s_stFftInCollect.f32Imag         =  0;
        s_stFftOutCollect.f32Real        =  0;
        s_stFftOutCollect.f32Imag        =  0;
        g_stSfraData.u16CollectCmd       =  0;
        g_stSfraData.u32CollectCount     =  0;
    }else{
       f32Temp                           = g_stSfraData.f32Wn*g_stSfraData.u32CollectCount;
       f32CosTemp                        = cosf(f32Temp);
       f32SinTemp                        = sinf(f32Temp);
       s_stFftInCollect.f32Real         += f32SfraInObj*f32CosTemp;
       s_stFftInCollect.f32Imag         -= f32SfraInObj*f32SinTemp;
       s_stFftOutCollect.f32Real        += f32SfraOutObj*f32CosTemp;
       s_stFftOutCollect.f32Imag        -= f32SfraOutObj*f32SinTemp;
       g_stSfraData.u32CollectCount++;
    }
}
*/

void SfraGuiCfg(APL_DOMAIN *p_stAplDm){
    UINT16 i = 0;
    UINT16 *p_u16Temp = NULL;
    FRAME_PROTOCOL_FORMAT st_SfraGuiFrame = {0};
    UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));
    if(p_stAplDm->u16AplDLC == 16)
    {
        p_u16Temp    = (UINT16 *)&g_stSfraCfg;
        for(i = 0; i < sizeof(SFRA_CFG); i++)
           *p_u16Temp++ = *p_u16Data++;
        g_u16SfraCfgFlg                                    = 1;
        st_SfraGuiFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;
        st_SfraGuiFrame.stAplDm.unAplCmd.bits.ul8CmdSet    = SFRA_CMD_SET;
        st_SfraGuiFrame.stAplDm.unAplCmd.bits.uh8CmdId     = SFRA_GUI_CFG_ID;
        st_SfraGuiFrame.stAplDm.u16AplDLC                  = 0;
        st_SfraGuiFrame.p_u16AppData                       = NULL;
        Tpl_Single_Frame_Send(&st_SfraGuiFrame);
   }
}

void SfraRun(APL_DOMAIN *p_stAplDm){
    UINT16 u16Temp;
    FRAME_PROTOCOL_FORMAT st_SfraRunFrame = {0};
    UINT16 *p_u16Data = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT16));
    if(p_stAplDm->u16AplDLC == 2){
        u16Temp =  *p_u16Data;
        if(u16Temp != SFRA_START_CMD){
            g_u16SfraRunCmd = SFRA_STOP_CMD;
        }
        else if(g_u16SfraCfgFlg == 1){
            g_u16SfraRunCmd = SFRA_START_CMD;
        }
        st_SfraRunFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr = PC_NODE_ADDR;
        st_SfraRunFrame.stAplDm.unAplCmd.bits.ul8CmdSet    = SFRA_CMD_SET;
        st_SfraRunFrame.stAplDm.unAplCmd.bits.uh8CmdId     = SFRA_RUN_CMD_ID;
        st_SfraRunFrame.stAplDm.u16AplDLC                  = 2;
        st_SfraRunFrame.p_u16AppData                       = &g_u16SfraRunCmd;
        Tpl_Single_Frame_Send(&st_SfraRunFrame);
   }
}


void SfraCmdSetLink(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    UINT8 u8CmdId;

    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;
    switch(u8CmdId){
        case SFRA_GET_ITEM_ID:{
            #define GEN_SFRA_ITEM_CALL
                #include "DEBUG_PLATFORM/SFRA/SFRA_CFG.h"
            #undef GEN_SFRA_ITEM_CALL
        }break;
        case SFRA_GUI_CFG_ID:{
            SfraGuiCfg(p_stAplDm);
        }break;
        case SFRA_RUN_CMD_ID:{
            SfraRun(p_stAplDm);
        }break;
        default:break;
    }
}
