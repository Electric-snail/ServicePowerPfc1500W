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
PFC_LLC_COMM_OUT    g_stPfcLlcCommOut;
float g_f32VpfcTestTarget = 0.0f;
void pfc_llc_comm_init(void)
{
	g_stPfcLlcCommOut.f32VpfcRef 		= 400;
	g_stPfcLlcCommOut.u16BootReq 	    = 0;
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

    u16Temp																					= (unsigned short)(f32_get_vpfc_slow_lpf() * 10.0f);
    ua16AppTxBuff[3]																	=   u16Temp;
    u16Temp																					= (unsigned short)(f32_get_vin_freq()  * 100.0f);
    ua16AppTxBuff[4]																	=  u16Temp;

    ua16AppTxBuff[5]                                                                 =  u16_get_auto_recv_diag();
    ua16AppTxBuff[6]                                                                 =  u16_get_no_recv_diag();
    ua16AppTxBuff[7]                                                                 =  u16_get_warn_diag();

    dll_scib_frame_write1(ua16AppTxBuff,     (PFC_TO_LLC_MSG_LEN >> 1));
}

void app_rx_msg_handle(void){
	 unsigned short u16Iout;
	 u16Iout		  = g_ua16RxData[0];
	 g_stPfcLlcCommOut.u16LlcIout = u16Iout;
	 if(u16Iout < 18){
		 g_stPfcLlcCommOut.f32VpfcRef = 400;
	 }else if((u16Iout >= 18)&&(u16Iout < 23)){
		 g_stPfcLlcCommOut.f32VpfcRef = 400.0f +2.0f*(u16Iout -18);
	 }else if((u16Iout >= 23)&&(u16Iout  < 90)){
		 g_stPfcLlcCommOut.f32VpfcRef = 410.0f;
	 }else if(u16Iout >= 108){
		 g_stPfcLlcCommOut.f32VpfcRef = 427.0f;
	 }else{
		 g_stPfcLlcCommOut.f32VpfcRef = 410.0f +0.94444f*(u16Iout -90);
	 }
	  g_stPfcLlcCommOut.u16BootReq      = g_ua16RxData[1];
}

float f32_get_vpfc_set_target_llc(void){
	float f32VpfcRef;
	float f32VrmsValue = f32_get_vin_rms();
	if(g_f32VpfcTestTarget > 300.0f){
		f32VpfcRef = g_f32VpfcTestTarget;
	}else{
		if(f32VrmsValue <= 270.0f){
			f32VpfcRef = 400.0f;
		}else if(f32VrmsValue <= 280.0f){
			f32VpfcRef = 400.0f + 2.0*(f32VrmsValue - 270.0f);
		}else{
			f32VpfcRef = 420.0f + 0.5f*(f32VrmsValue - 280.0f);
		}
		if(g_stPfcLlcCommOut.f32VpfcRef > f32VpfcRef)
			f32VpfcRef = g_stPfcLlcCommOut.f32VpfcRef;
	}
	if(f32VpfcRef > 435.0)   f32VpfcRef  = 435.0f;

	return f32VpfcRef;
}


