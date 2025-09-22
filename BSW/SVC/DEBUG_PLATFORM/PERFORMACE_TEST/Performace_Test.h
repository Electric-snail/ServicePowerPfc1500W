/*
 * PERFORMACE_TEST.h
 *
 *  Created on: 2022骞�12鏈�16鏃�
 *      Author: xj8r1j
 */

#ifndef _PERFORMACE_TEST_H_
#define _PERFORMACE_TEST_H_

#include "SOFTWARE_ENV_CFG.h"
//#include "../PUBLIC/PUBLIC_INC/list.h"
//#include "../PUBLIC/PUBLIC_INC/auto_register.h"
//#include "../DPStack/APL/APL_Stack.h"

#define  CMD_ID_GET_TASK_CNT           0x01
#define  CMD_ID_GET_TASK_ITEM          0x02
#define  CMD_ID_GET_CPU_LOAD           0x03
#define  CMD_ID_GET_ISR_TEST_CNT       0x04
#define  CMD_ID_GET_ISR_TEST_ITEM      0x05

#define  TASK_FUNC_NAME_MAX_LEN        36

typedef struct{
    UINT32     u32RunMaxTime;
    UINT32     u32RunMinTime;
    UINT32     u32RunTime;
}ISR_TEST_ITEM;

#define REG_ISR_TEST_SECTION  __attribute__ ((used,section(".ISR_TEST_REG_SECTION")))

#define REG_ISR_TEST_ITEM(name,p_user_data)  const AUTO_REG_OBJ _auto_reg_##name REG_ISR_TEST_SECTION = {#name,AUTO_REG_ISR_TEST,p_user_data};

#define ISR_EXE_VAR_ENTITY(name)      \
                                 volatile ISR_TEST_ITEM  g_st##name##IsrTestEntity ={0xFFFFFFFF, 0, 0xFFFFFFFF};\
                                 REG_ISR_TEST_ITEM(name,(void *)&g_st##name##IsrTestEntity)

#define ISR_EXE_VAR_CALL(name)        \
                                 g_st##name##IsrTestEntity.u32RunTime = GetTaskTestTimer();\
                                 /*g_st##name##IsrTestEntity.u32RunMinTime = (g_st##name##IsrTestEntity.u32RunTime > g_st##name##IsrTestEntity.u32RunMinTime)?g_st##name##IsrTestEntity.u32RunTime:g_st##name##IsrTestEntity.u32RunMinTime;*/\
                                 g_st##name##IsrTestEntity.u32RunMaxTime = (g_st##name##IsrTestEntity.u32RunTime < g_st##name##IsrTestEntity.u32RunMaxTime)?g_st##name##IsrTestEntity.u32RunTime:g_st##name##IsrTestEntity.u32RunMaxTime;

extern void PerformaceCmdSetLink(void *p_stAplDmTemp);



#endif /* _PERFORMACE_TEST_H_ */
