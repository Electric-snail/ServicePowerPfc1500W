/*
 * asw_sci_comm.h
 *
 *  Created on: 2022/8/30
 *      Author: rjgslg
 */

#ifndef _PFC_LLC_COMM_H_
#define _PFC_LLC_COMM_H_

#include "SOFTWARE_ENV_CFG.h"

#define  			CMD_ID_DATA_ITEM            0x10

extern UINT16 g_SciCommTimeOutCnt;

#define COMM_TIMEOUT_T      10
#define set_SciCommTimeOutCnt_Val()   g_SciCommTimeOutCnt = COMM_TIMEOUT_T

extern void pfc_llc_comm_rx_hander(void *p_stAplDmTemp);
extern void pfc_send_msg_task_50ms(void);

#endif /* _PFC_LLC_COMM_H_ */
