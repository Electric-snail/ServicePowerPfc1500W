/*
 * SFRA.h
 *
 *  Created on: 2023Äê7ÔÂ28ÈÕ
 *      Author: xj8r1j
 */

#ifndef _SFRA_SFRA_H_
#define _SFRA_SFRA_H_

#define     SFRA_GET_ITEM_ID        0
#define     SFRA_GUI_CFG_ID         1
#define     SFRA_RUN_CMD_ID         2
#define     SFRA_DATA_ID            3

typedef struct{
    unsigned short   ul8Index:     8;
    unsigned short   uh8NameLen:   8;
}SFRA_ITEM_NAME_BITS;

typedef union{
    unsigned short                u16all;
    SFRA_ITEM_NAME_BITS           bits;
}SFRA_ITEM_NAME;


typedef struct{
    float f32InjectMag;
    float f32StartFreq;
    float f32EndFreq;
    float f32StepFreq;
}SFRA_CFG;

typedef struct{
  float f32Real;
  float f32Imag;
}FFT_DATA;

typedef struct{
    unsigned short u16InjectCmd;
    unsigned short u16CollectCmd;
    unsigned long  u32InjectN;
    unsigned long  u32InjectCount;
    unsigned long  u32CollectN;
    unsigned long  u32CollectCount;
    float          f32Wn;
    float          f32FreqCmd;
    float          f32PeriodActual;
    FFT_DATA       stFftIn;
    FFT_DATA       stFftOut;
}SFRA_DATA;

typedef struct{
    UINT32     u32N;
    float      f32Period;
    FFT_DATA   stFftIn;
    FFT_DATA   stFftOut;
}SFRA_OUT;

extern void SfraCmdSetLink(void *p_stAplDmTemp);
extern void sfra_fsm_task(void);
extern void sfra_init(void);
/*#define GEN_SFRA_VAR_ENTITY
    #include "../DebugPlatform/SFRA/SFRA_CFG.h"
#undef GEN_SFRA_VAR_ENTITY*/

#endif /* BSW_SVC_DEBUGPLATFORM_SFRA_SFRA_H_ */
