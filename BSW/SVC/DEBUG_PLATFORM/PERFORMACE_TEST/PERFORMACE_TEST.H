/*
 * PERFORMACE_TEST.h
 *
 *  Created on: 2022.11.06
 *      Author: Hongbo.Jiang
 */

#ifndef _PERFORMACE_TEST_H_
#define _PERFORMACE_TEST_H_

#include "SOFTWARE_ENV_CFG.h"
#include "HAL_INC/BSW_HAL_TIMER.H"
#include "PUBLIC_INC/AUTO_REGISTER.H"

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
                                 volatile ISR_TEST_ITEM  g_st##name##IsrTestEntity ={0xFFFFFFFF,  	0, 	0xFFFFFFFF};\
                                 REG_ISR_TEST_ITEM(name,(void *)&g_st##name##IsrTestEntity)

#define ISR_EXE_VAR_CALL(name)        \
                                 g_st##name##IsrTestEntity.u32RunTime = get_performace_test_timer();\
                                 g_st##name##IsrTestEntity.u32RunMinTime = (g_st##name##IsrTestEntity.u32RunTime > g_st##name##IsrTestEntity.u32RunMinTime)?g_st##name##IsrTestEntity.u32RunTime:g_st##name##IsrTestEntity.u32RunMinTime;\
                                 g_st##name##IsrTestEntity.u32RunMaxTime = (g_st##name##IsrTestEntity.u32RunTime < g_st##name##IsrTestEntity.u32RunMaxTime)?g_st##name##IsrTestEntity.u32RunTime:g_st##name##IsrTestEntity.u32RunMaxTime;

extern void PerformaceCmdSetLink(void *p_stAplDmTemp);

#if(TASK_CPU_LOAD_TEST == 1)
extern void stack_usage_calc_task(void);
extern void cpu_load_calc_task(void);
#else
#define       stack_usage_calc_task                 NULL
#define        cpu_load_calc_task                    NULL
#endif


#if(MEASURE_TIME_TEST == 1)
extern void measure_time_calc_task(void);
extern unsigned short g_u16TimerLockFlag;
extern unsigned long  g_u32TimerCnt;
#define ResetMeasureTimerLock()                    if(g_u16TimerLockFlag == 0){ reset_performace_test_timer();		g_u16TimerLockFlag = 1;}
#define GetMeasureTimerUnlock()                    if(g_u16TimerLockFlag == 1){ g_u32TimerCnt = 0xFFFFFFFFUL - CpuTimer1Regs.TIM.all;  g_u16TimerLockFlag = 0;}
#else
#define       measure_time_calc_task                 NULL
#define ResetMeasureTimerLock()
#define GetMeasureTimerUnlock()
#endif

#endif /* _PERFORMACE_TEST_H_ */
