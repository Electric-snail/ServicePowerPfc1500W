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
#define           LLC_TO_PFC_MSG_LEN                                 6

extern UINT16 g_SciCommTimeOutCnt;

#define 			COMM_TIMEOUT_T      				10

typedef struct{
	  unsigned short  u16VpfcRef;
	  unsigned char   u8PfcStopCmd;
}PFC_LLC_COMM_OUT;

extern 	PFC_LLC_COMM_OUT    		g_stPfcLlcCommOut;
extern		unsigned short 		g_u16VpfcRef;
extern		unsigned short 		g_u16PfcStopCmd;

extern UINT16  g_ua16RxData[LLC_TO_PFC_MSG_LEN >> 1];
extern UINT16  g_u16AppRxFlag;
//#define 	u16_get_vpfc_set()				 		  g_stPfcLlcCommOut.	u16VpfcRef
//#define 	u8_get_pfc_stop_cmd()				  g_stPfcLlcCommOut.	u8PfcStopCmd

#define 	u16_get_vpfc_set()					g_u16VpfcRef
#define 	u8_get_pfc_stop_cmd()			g_u16PfcStopCmd
#define    u16_set_app_rx_flag()           g_u16AppRxFlag = 1
#define    u16_get_app_buff_pointer()   g_ua16RxData

extern void pfc_llc_msg_50ms_task(void);
extern void pfc_llc_comm_init(void);

#endif /* _PFC_LLC_COMM_H_ */
