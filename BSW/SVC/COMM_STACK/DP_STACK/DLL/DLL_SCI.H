/*
 * DLL_SCI.h
 *
 *  Created on: 2022.8.16
 *      Author: xj8r1j
 */

#ifndef     _DLL_STACK_DLL_SCI_H_
#define     _DLL_STACK_DLL_SCI_H_

#include "ENV_CFG/SOFTWARE_ENV_CFG.H"
#include "DP_STACK/DP_STACK_CFG.H"


#if(DP_SCIA_ENABLE == 1)
    extern UINT16  g_au16DllSciaRxMsgBuff[];
#endif

#if(DP_SCIB_ENABLE == 1)
    extern UINT16  g_au16DllScibRxMsgBuff[];
#endif

//DLL Layer Header
//The head word0 bits defined,
typedef struct{
    UINT16 ul8HeadByte0:   8;
    UINT16 uh8HeadByte1:   8;
}DLL_SCI_HEAD_BITS0;

typedef union{
    UINT16                u16all;
    DLL_SCI_HEAD_BITS0    bits;
}DLL_SCI_HEAD_WORD0;

typedef struct{
    UINT16 ul8HeadByte2:   8;
    UINT16 uh8HeadByte3:   8;
}DLL_SCI_HEAD_BITS1;

typedef union{
    UINT16                u16all;
    DLL_SCI_HEAD_BITS1        bits;
}DLL_SCI_HEAD_WORD1;


typedef struct{
    DLL_SCI_HEAD_WORD0    unHeadWord0;
    DLL_SCI_HEAD_WORD1    unHeadWord1;
    UINT16                u16DllDLC;
}DLL_SCI_HEAD_DOMAIN;

typedef struct{
    UINT16   ul8CrcByte:    8;
    UINT16   uh8Rsv:        8;
}DLL_SCI_CRC_BITS;

typedef union{
    UINT16                 u16all;
    DLL_SCI_CRC_BITS       bits;
}DLL_SCI_CRC_WORD;

//DLL Layer Rail
typedef struct{
	DLL_SCI_CRC_WORD        unCrc;
}DLL_SCI_RAIL_DOMAIN;

#define   DLL_HEAD_DOMAIN_BYTES_LEN         3
#define   DLL_RAIL_DOMAIN_BYTES_LEN         4

extern INT16 dll_scia_frame_write(void *);
extern INT16 dll_scia_frame_read(UINT16 *);
extern void scia_send_from_ring(void);

extern INT16 dll_scib_frame_write(void *);
extern INT16 dll_scib_frame_read(UINT16 *);
extern INT16 dll_scib_frame_read_fifo(UINT16 *);
extern void scib_send_from_ring(void);

#endif /* BSW_SVC_COMMPROTOCOLSTACK_DLLSTACK_DLL_SCI_H_ */
