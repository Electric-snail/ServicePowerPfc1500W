/*
 * SOFTWARE_ENV_CFG.h
 *
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 */

#ifndef BSW_BASIC_IDE_BASIC_ENV_H_
#define BSW_BASIC_IDE_BASIC_ENV_H_

#include "stdint.h"
#ifndef      DLLX64
#define      SQRT(INT32_A)                          __builtin_sqrtf(INT32_A)
#define      SQRTF(float_A)                         __builtin_sqrtf(float_A)
#define      ABSF(float_A)                          __builtin_fabsf(float_A)
#define      ABS(INT32_A)                           __builtin_fabs(INT32_A)
#define      INTERRUPT                              __interrupt
#define        INLINE                               __inline
#define       STATIC
#define       VOLATILE                              volatile
#define     bsw_mcal_enable_global_int()     EINT
#define     bsw_mcal_disable_global_int()    DINT
#else
#include    "math.h"
#define     SQRTF(A)                        sqrtf(A)
#define     ABSF(A)                         fabs(A)
#define     INTERRUPT
#define       STATIC
#define       VOLATILE
#define     bsw_mcal_enable_global_int()
#define     bsw_mcal_disable_global_int()
#define     bsw_mcal_disable_watchdog()
#endif

#define INLINE __inline

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

typedef void* HANDLE;
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

#define     LITTLE_END                                                  0
#define     BIG_END                                                     1

#define     TYPE_8_BYTE_SIZE                                            (2)
#define     MCU_MEM_STORE_MODE                                          LITTLE_END

#define     FLASH_SECTOR_SIZE                                           1024
#define     STORAGE_WORD_SIZE                                           FLASH_SECTOR_SIZE
#define     APP_START_ADDR                                              (unsigned long)0x00084000
#define     APP_FLASH_WORD_SIZE                                         (unsigned long)0x0000C000
#define     FLASH_CHECK_FAIL                                            0
#define     FLASH_CHECK_PASS                                            1

#define     SCIA_MODULE                                                 1
#define     SCIB_MODULE                                                 2
#define     CANA_MODULE                                                 3
#define     CANB_MODULE                                                 4
#define     MCAN_MODULE                                                 5
#define     FSIA_MODULE                                                 6
#define     I2CA_MODULE                                                 7
#define     PMBUS_MODULE                                                8


#ifdef  CLA_ENABLE
#define CTR_FUNC     __interrupt
#else
#define CTR_FUNC
#endif

#endif /* BSW_BASIC_IDE_BASIC_ENV_H_ */
