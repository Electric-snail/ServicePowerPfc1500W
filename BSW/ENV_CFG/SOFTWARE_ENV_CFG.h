/*
 * SOFTWARE_ENV_CFG.h
 *
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 */

#ifndef BSW_BASIC_IDE_BASIC_ENV_H_
#define BSW_BASIC_IDE_BASIC_ENV_H_

#include "stdint.h"

#define 	INLINE 		__inline

#define 	STATIC

#ifndef NULL
#define NULL    ((void *)0x0)
#endif

#ifndef NOP
#define NOP    __asm(" NOP")
#endif

#ifndef MNOP
#define MNOP    __asm(" MNOP")
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif

/* Define variable type */

typedef short               INT8;
typedef unsigned short      UINT8;

typedef short               INT16;
typedef unsigned short      UINT16;
typedef long                INT32;
typedef unsigned long       UINT32;
typedef unsigned long long  UINT64;
typedef signed long long    INT64;
typedef float               FLOAT32;

typedef void*               HANDLE;
typedef unsigned short      BOOLEAN;

typedef enum
{
    bFalse,
    bTrue,
}BOOL;

#if defined(__TMS320C28XX_CLA__)
    #define HWREG(x)                                                          \
            (*((volatile uint32_t *)((uintptr_t)(x))))
    #define HWREGH(x)                                                         \
            (*((volatile uint16_t *)((uintptr_t)(x))))
#else
    #define HWREG(x)                                                          \
            (*((volatile uint32_t *)(x)))
    #define HWREGH(x)                                                         \
            (*((volatile uint16_t *)(x)))
#endif

#define HWREG_BP(x)                                                           \
        __byte_peripheral_32((uint32_t *)(x))
#define HWREGB(x)                                                             \
        __byte((int16_t *)(x),0)

#define     LITTLE_END                      		0
#define     BIG_END                         			1

#define     TYPE_8_BYTE_SIZE                2
#define     MCU_MEM_STORE_MODE              LITTLE_END
#define     ENABLE_PARAM_CFG                (1)
#define     STACK_LEN                       (1024)

#define bsw_mcal_enable_global_int()            		 EINT
#define bsw_mcal_disable_global_int()                  DINT

//Unit --> us
//120000/(2*65) = 923
#define    PFC_PWM_TBPRD      			923UL
#define     CTR_FRQ                         		65000.0f
#define     CTR_PERIOD                        (1.0f/CTR_FRQ)


//Communication macro software definition
#define 	  SCIA_MODULE          			1
#define 	  SCIB_MODULE          			2
#define 	  CANA_MODULE          	    3
#define 	  CANB_MODULE          		4
#define     MCAN_MODULE                5
#define     FSIA_MODULE                   6
#define     I2CA_MODULE                   7
#define     PMBUS_MODULE              8

//Whether to enable the CLA function in system.
#define     CLA_ENABLE                      0

#define DB_TOOL_ENABLE          TRUE
#define SFRA_ENABLED            FALSE
#define SFRA_ENABLED_TI         FALSE

#if(DB_TOOL_ENABLE == TRUE)
#define     ISR_CPU_LOAD_TEST               0
#define     TASK_CPU_LOAD_TEST              0
#define     NESTING_ISR_CPU_LOAD_TEST       0
#define     MEASURE_TIME_TEST               0

#if((ISR_CPU_LOAD_TEST == 1)&&(TASK_CPU_LOAD_TEST == 1))
#error "Only one function can be done"
#elif((ISR_CPU_LOAD_TEST == 1)&&(NESTING_ISR_CPU_LOAD_TEST == 1))
#error "Only one function can be done"
#elif((ISR_CPU_LOAD_TEST == 1)&&(MEASURE_TIME_TEST == 1))
#error "Only one function can be done"
#elif((TASK_CPU_LOAD_TEST == 1)&&(NESTING_ISR_CPU_LOAD_TEST == 1))
#error "Only one function can be done"
#elif((TASK_CPU_LOAD_TEST == 1)&&(MEASURE_TIME_TEST == 1))
#error "Only one function can be done"
#elif((NESTING_ISR_CPU_LOAD_TEST == 1)&&(MEASURE_TIME_TEST == 1))
#error "Only one function can be done"
#endif
#endif


#if(CLA_ENABLE == 1)
#define CTR_FUNC     __interrupt
#else
#define CTR_FUNC
#endif

#endif /* BSW_BASIC_IDE_BASIC_ENV_H_ */
