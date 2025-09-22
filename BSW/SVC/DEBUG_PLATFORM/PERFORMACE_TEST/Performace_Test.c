/*
 * PERFORMACE_TEST.c
 *
 *  Created on: 2022.12.16
 *      Author: xj8r1j
 */

/*
 * Parameter_Cfg.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */
#include "BSW_SVC_BASIC.h"
#include "DP_STACK/DPStackBasic.h"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DEBUG_PLATFORM/DBG_BASIC.H"
#include "DEBUG_PLATFORM/PERFORMACE_TEST/PERFORMACE_TEST.H"
#include "HAL_INC/BSW_HAL_TIMER.H"
#include "string.h"

#if(TASK_CPU_LOAD_TEST == 1)
#define   	CPU_LOAD_TASK_PERIOD             5
extern UINT32 TaskRegLoadStart;
extern TASK_SCHE_OBJ g_TaskScheVars;
extern UINT32 g_u32CpuLoadTotalTimer;
extern UINT16 g_u16CpuLoadCnt;
float g_f32CpuLoadAve = 0.0f;
static float gs_f32CpuLoadMax = 0.0f;
static float gs_f32CpuLoadMin = 1.0f;
static float gs_f32StackUsage = 0;

//--------------protocol-api interface
void TaskGetCntAction(APL_DOMAIN *p_stAplDm)
{
    FRAME_PROTOCOL_FORMAT   stFrame_info = {0};
    UINT16 ua16TaskCnt[2];
    stFrame_info.stAplDm.unAplCmd.u16all             = p_stAplDm->unAplCmd.u16all;
    stFrame_info.stNwmDm.unNwmAddr.bits.ul8DestAddr  = PC_NODE_ADDR;
    stFrame_info.stAplDm.u16AplDLC                   = 4;
    ua16TaskCnt[0]                                   = g_TaskScheVars.u8NumOfTasks;
    ua16TaskCnt[1]                                   = GetTaskTestTimeInv();
    stFrame_info.p_u16AppData                        = ua16TaskCnt;
    Tpl_Single_Frame_Send(&stFrame_info);
}


void TaskGetItemAction(APL_DOMAIN *p_stAplDm)
{
    AUTO_REG_OBJ *p_auto_reg = NULL;
    TASK_ITEM_OBJ *p_task_reg = NULL;
    FRAME_PROTOCOL_FORMAT     stTaskGetItemFrame = {0};
    UINT16 *p_u16TempData = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN));
    UINT16 ua16TaskItemBuff[((TASK_FUNC_NAME_MAX_LEN + 1)>> 1) + sizeof(TASK_ITEM_OBJ) + 4] = {0};
    UINT32 u32RunTimeTemp;
    UINT8  u8DataCnt;
    const char *p_u8char;
    if(p_stAplDm->u16AplDLC != 2)
        return;
    UINT16 i = *p_u16TempData;
    p_auto_reg = (AUTO_REG_OBJ *)&TaskRegLoadStart;//&SvcRegLoadStart
    p_u8char                        = p_auto_reg[i].name;
    for(u8DataCnt = 0; u8DataCnt < ((TASK_FUNC_NAME_MAX_LEN + 1)>> 1);u8DataCnt ++){
        ua16TaskItemBuff[u8DataCnt] = *p_u8char;
        if(*p_u8char == '\0'){
            break;
        }
        p_u8char++;
        ua16TaskItemBuff[u8DataCnt] |= ((UINT16)(*p_u8char) << 8);
        if(*p_u8char == '\0'){
            break;
        }
        p_u8char++;
    }
    if(*p_u8char != '\0')
    ua16TaskItemBuff[u8DataCnt] = '\0';
    u8DataCnt ++;
    p_task_reg = (TASK_ITEM_OBJ *)p_auto_reg[i].p_reg_data;
    ua16TaskItemBuff[u8DataCnt++] = p_task_reg->enable;
    ua16TaskItemBuff[u8DataCnt++] = p_task_reg->u16Period;
    ua16TaskItemBuff[u8DataCnt++] = p_task_reg->u16Offset;
    u32RunTimeTemp = 0xFFFFFFFF-g_TaskScheVars.ua32TaskRunMinCnt[i];
    ua16TaskItemBuff[u8DataCnt ++] = u32RunTimeTemp & 0x0000ffff;
    ua16TaskItemBuff[u8DataCnt ++] = u32RunTimeTemp >> 16;
    u32RunTimeTemp = (0xFFFFFFFF - g_TaskScheVars.ua32TaskRunMaxCnt[i]);
    ua16TaskItemBuff[u8DataCnt ++] = u32RunTimeTemp & 0x0000ffff;
    ua16TaskItemBuff[u8DataCnt ++] = u32RunTimeTemp >> 16;
    stTaskGetItemFrame.p_u16AppData                         = ua16TaskItemBuff;
    stTaskGetItemFrame.stAplDm.unAplCmd.u16all              = p_stAplDm->unAplCmd.u16all;
    stTaskGetItemFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr   = PC_NODE_ADDR;
    stTaskGetItemFrame.stAplDm.u16AplDLC = u8DataCnt << 1;  //Response the get item information.
    Tpl_Single_Frame_Send(&stTaskGetItemFrame);
}

void TaskGetCpuLoadAction(APL_DOMAIN *p_stAplDm)
{
    FRAME_PROTOCOL_FORMAT   stFrame_info = {0};
    UINT16 ua16CpuLoad[6];
    UINT16 *p_u16TempData;

    stFrame_info.stAplDm.unAplCmd.u16all             = p_stAplDm->unAplCmd.u16all;
    stFrame_info.stNwmDm.unNwmAddr.bits.ul8DestAddr  = PC_NODE_ADDR;
    stFrame_info.stAplDm.u16AplDLC                   = 12;
    p_u16TempData                                    = (UINT16 *)&gs_f32CpuLoadMax;
    ua16CpuLoad[0]                                   = *p_u16TempData++;
    ua16CpuLoad[1]                                   = *p_u16TempData;
    p_u16TempData                                    = (UINT16 *)&g_f32CpuLoadAve;
    ua16CpuLoad[2]                                   = *p_u16TempData++;
    ua16CpuLoad[3]                                   = *p_u16TempData;
    p_u16TempData                                    = (UINT16 *)&gs_f32StackUsage;
    ua16CpuLoad[4]                                   = *p_u16TempData++;
    ua16CpuLoad[5]                                   = *p_u16TempData;

    stFrame_info.p_u16AppData                        = ua16CpuLoad;
    Tpl_Single_Frame_Send(&stFrame_info);
}

void CpuLoadCalculate(void){
    static UINT8 s_u8FirstRunFlg = 1;
    if(s_u8FirstRunFlg == 1){
       s_u8FirstRunFlg = 0;
    }else{
       g_f32CpuLoadAve = 1.0f - ((float)GetCpuTimer1Inv()*g_u32CpuLoadTotalTimer/(1000000.0f*g_u16CpuLoadCnt));
       if(g_f32CpuLoadAve >= 1.0f)  g_f32CpuLoadAve = 1.0f;
       if(g_f32CpuLoadAve <= 0.0f)  g_f32CpuLoadAve = 0.0f;
       gs_f32CpuLoadMax       = (gs_f32CpuLoadMax > g_f32CpuLoadAve)?gs_f32CpuLoadMax:g_f32CpuLoadAve;
       gs_f32CpuLoadMin       = (gs_f32CpuLoadMin < g_f32CpuLoadAve)?gs_f32CpuLoadMin:g_f32CpuLoadAve;
    }
    g_u32CpuLoadTotalTimer = 0;
    g_u16CpuLoadCnt        = 0;
}

REG_TASK(CpuLoadCalculate,1,  CPU_LOAD_TASK_PERIOD,CPU_LOAD_TASK_PERIOD)

extern unsigned int HWI_STKBOTTOM;
extern unsigned int HWI_STKTOP;
extern unsigned int HWI_STKSIZE;
void StackUsageCalculate(void){
    unsigned short *p_u16Temp    = (unsigned short *)&HWI_STKTOP;
    unsigned short *p_u16TempRef = (unsigned short *)&HWI_STKBOTTOM;
    unsigned long u32StackSize  = (unsigned long)&HWI_STKSIZE;
    unsigned short u16TempData;
    while(p_u16Temp > p_u16TempRef){
        u16TempData = *p_u16Temp--;
        if(u16TempData != 0xAA55) break;
    }
    u16TempData = p_u16Temp - p_u16TempRef;
    gs_f32StackUsage  = (float)u16TempData/(float)u32StackSize;
}
REG_TASK(StackUsageCalculate,1,  300, 177)

#elif((ISR_CPU_LOAD_TEST == 1)||(NESTING_ISR_CPU_LOAD_TEST == 1))
extern UINT16 IsrTestRegLoadSize;
extern UINT32 IsrTestRegLoadStart;
//-------------
void IsrTestGetCntAction(APL_DOMAIN *p_stAplDm)
{
    FRAME_PROTOCOL_FORMAT   stFrame_info = {0};
    UINT16 ua16TaskCnt[2];
    unsigned int u16IsrTestNum = (UINT16)((UINT32)&IsrTestRegLoadSize/sizeof(AUTO_REG_OBJ));
    stFrame_info.stAplDm.unAplCmd.u16all             = p_stAplDm->unAplCmd.u16all;
    stFrame_info.stNwmDm.unNwmAddr.bits.ul8DestAddr  = PC_NODE_ADDR;
    stFrame_info.stAplDm.u16AplDLC                   = 4;
    ua16TaskCnt[0]                                   = u16IsrTestNum;
    ua16TaskCnt[1]                                   = GetTaskTestTimeInv();
    stFrame_info.p_u16AppData                        = ua16TaskCnt;
    Tpl_Single_Frame_Send(&stFrame_info);
}

void IsrTestGetItemAction(APL_DOMAIN *p_stAplDm)
{
    AUTO_REG_OBJ  *p_auto_reg = NULL;
    ISR_TEST_ITEM *p_isr_test_reg = NULL;
    FRAME_PROTOCOL_FORMAT     stIsrTestGetItemFrame = {0};
    UINT16 *p_u16TempData = ((UINT16 *)p_stAplDm + sizeof(APL_DOMAIN));
    UINT16 ua16IsrTestItemBuff[((TASK_FUNC_NAME_MAX_LEN + 1)>> 1) + sizeof(ISR_TEST_ITEM) + 4] = {0};
    UINT8  u8DataCnt = 0;
    UINT32 u32RunTimeTemp = 0;
    const char *p_u8char;
    if(p_stAplDm->u16AplDLC != 2)
        return;
    UINT16 i = *p_u16TempData;
    p_auto_reg = (AUTO_REG_OBJ *)&IsrTestRegLoadStart;//
    p_u8char                        = p_auto_reg[i].name;
    for(u8DataCnt = 0; u8DataCnt < ((TASK_FUNC_NAME_MAX_LEN + 1)>> 1);u8DataCnt ++){
        ua16IsrTestItemBuff[u8DataCnt] = *p_u8char;
        if(*p_u8char == '\0'){
            break;
        }
        p_u8char++;
        ua16IsrTestItemBuff[u8DataCnt] |= ((UINT16)(*p_u8char) << 8);
        if(*p_u8char == '\0'){
            break;
        }
        p_u8char++;
    }
    if(*p_u8char != '\0')
       ua16IsrTestItemBuff[u8DataCnt] = '\0';
    u8DataCnt ++;
    p_isr_test_reg = (ISR_TEST_ITEM *)p_auto_reg[i].p_reg_data;
    u32RunTimeTemp = (0xFFFFFFFF - p_isr_test_reg->u32RunTime);
    ua16IsrTestItemBuff[u8DataCnt++] = (u32RunTimeTemp) & 0x0000FFFF;
    ua16IsrTestItemBuff[u8DataCnt++] = (u32RunTimeTemp >> 16);
    u32RunTimeTemp = 0;//(0xFFFFFFFF - p_isr_test_reg->u32RunMinTime);
    ua16IsrTestItemBuff[u8DataCnt++] = (u32RunTimeTemp & 0x0000FFFF);
    ua16IsrTestItemBuff[u8DataCnt++] = (u32RunTimeTemp >> 16);
    u32RunTimeTemp = (0xFFFFFFFF - p_isr_test_reg->u32RunMaxTime);
    ua16IsrTestItemBuff[u8DataCnt++] = (u32RunTimeTemp & 0x0000FFFF);
    ua16IsrTestItemBuff[u8DataCnt++] = (u32RunTimeTemp >> 16);

    stIsrTestGetItemFrame.p_u16AppData                         = ua16IsrTestItemBuff;
    stIsrTestGetItemFrame.stAplDm.unAplCmd.u16all              = p_stAplDm->unAplCmd.u16all;
    stIsrTestGetItemFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr  = PC_NODE_ADDR;
    stIsrTestGetItemFrame.stAplDm.u16AplDLC = u8DataCnt << 1;  //Response the get item information.
    Tpl_Single_Frame_Send(&stIsrTestGetItemFrame);
}
#elif(MEASURE_TIME_TEST == 1)
float g_f32MeasureTime = 0.0f;
extern unsigned long g_u32TimerCnt;
void MeasureTimeCalc(void){
    g_f32MeasureTime = (float)g_u32TimerCnt * GetCpuTimer1Inv()/1000000.0f;
}

REG_TASK(MeasureTimeCalc,	1,  200, 	111)
REG_CFG_ITEM_F32(MEASURE_TIME, g_f32MeasureTime, VAR_RD, 0, 0, 1000000);
#endif


void PerformaceCmdSetLink(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    UINT8 u8CmdId;
    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;
    switch(u8CmdId){
#if(TASK_CPU_LOAD_TEST == 1)
        case CMD_ID_GET_TASK_CNT:
            TaskGetCntAction(p_stAplDm);
        break;
        case CMD_ID_GET_TASK_ITEM:
            TaskGetItemAction(p_stAplDm);
        break;
        case CMD_ID_GET_CPU_LOAD:
            TaskGetCpuLoadAction(p_stAplDm);
        break;



#elif((ISR_CPU_LOAD_TEST == 1)||(NESTING_ISR_CPU_LOAD_TEST == 1))
        case CMD_ID_GET_ISR_TEST_CNT:
            IsrTestGetCntAction(p_stAplDm);
        break;
        case CMD_ID_GET_ISR_TEST_ITEM:
            IsrTestGetItemAction(p_stAplDm);
        break;
#endif
        default:break;
    }
}


