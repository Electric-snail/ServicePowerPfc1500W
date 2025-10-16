/*
 * DIAGNOSTIC_INF.H
 *
 *  Created on: 2024.9.20
 *      Author: hongbo.jiang
 */
#ifndef  _DIAGNOSTIC_INF_H
#define  _DIAGNOSTIC_INF_H

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

typedef struct {
    unsigned short  b1VinOvp:      1;
    unsigned short  b1VinUvp:      1;
	unsigned short  b1VbatOvp:     1;
    unsigned short  b1VbatUvp:     1;
	unsigned short  b1MosOtp:      1;
    unsigned short  b1EnvOtp:      1;
    unsigned short  b10Rvs :       10;
}AUTO_RECV_FAULT_BITS;

typedef struct {
    unsigned short  b1VoutSlowOvp:     1;
	unsigned short  b1VoutFastOvp:     1;
    unsigned short  b1VoutUvp:         1;
	unsigned short  b1VoutShort:       1;
    unsigned short  b1IoutOcp:         1;
	unsigned short  b1IoutShort:       1;
    unsigned short  b1IlSwOcp:         1;
    unsigned short  b1IinOcp:          1;
	unsigned short  b1IlHwOcp:         1;
	unsigned short  b1BrakeOcp:        1;
    unsigned short  b6Rvs :            7;
}NO_RECV_FAULT_BITS;

typedef union {
    unsigned short 			u16All;
    AUTO_RECV_FAULT_BITS    bits;
}AUTO_RECV_FAULT_WORD_U;

typedef union {
    unsigned short 			u16All;
    NO_RECV_FAULT_BITS      bits;
}NO_RECV_FAULT_WORD_U;



typedef struct {
    AUTO_RECV_FAULT_WORD_U  unAutoRecvFault;
	NO_RECV_FAULT_WORD_U    unNoRecvFault;
}DIAG_STATUS_T;

extern DIAG_STATUS_T g_stDiagStatus;

#define u16_get_auto_recv_diag()       g_stDiagStatus.unAutoRecvFault.u16All
#define u16_get_no_recv_diag()          g_stDiagStatus.unNoRecvFault.u16All

extern void fast_diagnostic_task(void);
extern void diag_1ms_task(void);
extern void diag_10ms_task(void);
extern void diag_100ms_task(void);
extern void diag_cfg_param_init(void);
#endif
