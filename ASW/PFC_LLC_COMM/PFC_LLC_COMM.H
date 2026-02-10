/*
 * asw_sci_comm.h
 *
 *  Created on: 2022/8/30
 *      Author: rjgslg
 */

#ifndef _PFC_LLC_COMM_H_
#define _PFC_LLC_COMM_H_

#include "SOFTWARE_ENV_CFG.h"

#define  			PFC_TO_LLC_DATA_ITEM_CMD_ID            0x10
#define  			LLC_TO_PFC_DATA_ITEM_CMD_ID            0x11
#define            CALIB_DATA_ITEM_CMD_ID        				0x12
#define           PFC_TO_LLC_MSG_LEN                                 16
#define           LLC_TO_PFC_MSG_LEN                                 4

extern UINT16 g_SciCommTimeOutCnt;

#define 			COMM_TIMEOUT_T      				10

typedef struct{
	  float                   f32VpfcRef;
	  unsigned short   u16BootReq;
}PFC_LLC_COMM_OUT;

extern 	PFC_LLC_COMM_OUT    		g_stPfcLlcCommOut;

extern UINT16  g_ua16RxData[LLC_TO_PFC_MSG_LEN >> 1];

#define 	f32_get_vpfc_set_target()			g_stPfcLlcCommOut.f32VpfcRef
#define    u16_get_app_buff_pointer()   	g_ua16RxData

extern void pfc_llc_msg_50ms_task(void);
extern void pfc_llc_comm_init(void);
extern void app_rx_msg_handle(void);
#endif /* _PFC_LLC_COMM_H_ */
