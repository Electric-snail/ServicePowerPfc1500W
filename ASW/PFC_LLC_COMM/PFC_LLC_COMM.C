/*
 * asw_sci_comm.c
 *
 *  Created on: 2022/8/30
 *      Author:   Hongbo.Jiang
 */
#include "TASK/BSW_TASK_SERVICE.h"
#include "BSW_SVC_BASIC.h"
#include "DP_STACK/DLL/DLL_SCI.H"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DP_STACK/APL/APL_STACK.H"
#include "DP_STACK/DP_STACK_BASIC.H"
#include "PFC_LLC_COMM/PFC_LLC_COMM.H"
#include "DIAGNOSTIC/DIAGNOSTIC.H"
#include "MEASURE/MEASURE.H"
#include "ASW/ASW_BASIC.h"


UINT16  g_ua16RxData[LLC_TO_PFC_MSG_LEN >> 1] ={0};
UINT16  g_u16AppRxFlag = 0;
 PFC_LLC_COMM_OUT    g_stPfcLlcCommOut;
 unsigned short g_u16VpfcRef             = 400;
 unsigned short g_u16PfcStopCmd      = 1;

void pfc_llc_comm_init(void)
{
	g_stPfcLlcCommOut.u16VpfcRef 		= 400;
	g_stPfcLlcCommOut.u8PfcStopCmd 	= 1;
}


void pfc_llc_msg_50ms_task(void)
{
	unsigned short ua16AppTxBuff[PFC_TO_LLC_MSG_LEN >> 1] 	= {0};
	unsigned short u16Temp;
    u16Temp																					= (unsigned short)(f32_get_vin_rms() * 10.0f);
    ua16AppTxBuff[0]																	=    u16Temp;
    u16Temp																					= (unsigned short)(f32_get_iin_rms() * 100.0f);
    ua16AppTxBuff[1]																	=    u16Temp;

    u16Temp																					= (unsigned short)(f32_get_pin_lpf() * 10.0f);
    ua16AppTxBuff[2]																	=    u16Temp;

    u16Temp																					= (unsigned short)(f32_get_vpfc_lpf_measure() * 10.0f);
    ua16AppTxBuff[3]																	=   u16Temp;
    u16Temp																					= (unsigned short)(f32_get_vin_freq()  * 100.0f);
    ua16AppTxBuff[4]																	=  u16Temp;

    ua16AppTxBuff[5]                                                                 =  u16_get_auto_recv_diag();
    ua16AppTxBuff[6]                                                                 =  u16_get_no_recv_diag();
    ua16AppTxBuff[7]                                                                 =  u16_get_warn_diag();

    dll_scib_frame_write1(ua16AppTxBuff,     (PFC_TO_LLC_MSG_LEN >> 1));

    if(1 == g_u16AppRxFlag){
  	  g_stPfcLlcCommOut.u16VpfcRef 			 = g_ua16RxData[0];
  	  g_stPfcLlcCommOut.u8PfcStopCmd      = g_ua16RxData[1];
  	  g_u16AppRxFlag = 0;
    }
}



