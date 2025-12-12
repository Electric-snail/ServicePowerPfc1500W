/*
 * SysFsm.c
 *
 *  Created on: 2022.9.19
 */
#include "ISR_INC/BSW_ISR_ADC.h"
#include "HAL_INC/BSW_HAL_PWM.h"
#include "HAL/HAL_INC/BSW_HAL_ADC.h"
#include "HAL/HAL_INC/BSW_HAL_GPIO.h"
#include "SVC/BSW_SVC_BASIC.h"
#include "SVC/FSM/BSW_FSM_CORE.h"
#include "SYS_FSM/SYS_FSM.h"
#include "POWER_FSM/POWER_FSM.h"
#include "PFC_LLC_COMM/PFC_LLC_COMM.H"
#include "DIAGNOSTIC/DIAGNOSTIC.h"
#include "MEASURE/MEASURE.h"
#include "SYS_FSM/SYS_FSM_INF.h"
#include "VPFC_MGT/VPFC_MGT.H"

void  power_standby_in(void);
void  power_standby_exe(void);
UINT8 power_standby_cond(UINT16 u16TrigEven);

void  power_relay_dither_exe(void);
UINT8 power_relay_dither_cond(UINT16 u16TrigEven);

void  power_softstart_in(void);
void  power_softstart_exe(void);
UINT8 power_softstart_cond(UINT16 u16TrigEven);

void  power_run_in(void);
void  power_run_exe(void);
UINT8 power_run_cond(UINT16 u16TrigEven);

void  power_fault_in(void);
void  power_fault_exe(void);
UINT8 power_fault_cond(UINT16 u16TrigEven);

POWER_FSM_OUT_T		g_stPwrFsmOut;
//----------FSM name-----initial status id---------------------
REG_FSM_OBJ(POWER_FSM, PWR_STATUS_STANDBY, \
	//---fsm status id------------------------------fsm_in_func-----------------fsm_exe_func-----------fsm_out_func---------fsm_cond_func;
{PWR_STATUS_STANDBY, 						power_standby_in, 			power_standby_exe, 				NULL, 				power_standby_cond}, \
{PWR_STATUS_RELAY_DITHER, 			NULL,									power_relay_dither_exe, 		NULL, 				power_relay_dither_cond}, \
{PWR_STATUS_SOFTSTART, 					power_softstart_in, 			power_softstart_exe, 			NULL, 				power_softstart_cond}, \
{PWR_STATUS_RUN, 								power_run_in, 					power_run_exe, 					NULL, 				power_run_cond}, \
{PWR_STATUS_FAULT, 								power_fault_in, 					power_fault_exe, 					NULL, 				power_fault_cond}, \
)



unsigned short g_u16PwrFsmTimerCnt = 0;

void power_fsm_init(void) {
	FSM_INIT_CALL(POWER_FSM)
}
void power_fsm_1ms_task(void){
    FSM_OBJ_CALL(POWER_FSM)
}



void  power_standby_in(void){
	g_u16PwrFsmTimerCnt		= 0;
	g_stPwrFsmOut.u16CtrCmd = 0;
	BSW_HAL_BUCK_NOT_OK();
	BSW_HAL_ALERT_CLR();
}

void  power_standby_exe(void){
	static unsigned short s_u16PolLast = 0;
	unsigned short u16PolRvsFlag = 0;
	float f32VpfcPrechargeThrd;
	float f32VpfcLpf;

/*	if(u8_get_pfc_stop_cmd() == 1)
		return;*/
	if (u16_get_vin_type() == DC_TYPE) {
		u16PolRvsFlag = 1;  //DC type 下默认输入极性出现跳变，控制继电器的吸合在过零点出.
	}
	else {
		if (s_u16PolLast != u16_get_vin_pol()) {
			s_u16PolLast  = u16_get_vin_pol();
			u16PolRvsFlag = 1;
		}
	}
	f32VpfcPrechargeThrd	= 0.9f * 1.414f * f32_get_vin_rms_flt();
	f32VpfcLpf						= f32_get_vpfc_lpf();
	g_u16PwrFsmTimerCnt++;

	if ((g_u16PwrFsmTimerCnt > 800)&&(1 == u16PolRvsFlag)&&(f32VpfcLpf > f32VpfcPrechargeThrd)&&(0x0000 == u16_get_auto_recv_diag())){
			BSW_HAL_RELAY_ON();
			g_u16PwrFsmTimerCnt  = 0;
			EMIT_FSM(POWER_FSM, PWR_PRE_CHG_CMP);
	}
}

UINT8 power_standby_cond(UINT16 u16TrigEven){
	if (u16TrigEven == PWR_PRE_CHG_CMP)    return  PWR_STATUS_RELAY_DITHER;
	return PWR_STATUS_STANDBY;
}

void  power_relay_dither_exe(void){
	    g_u16PwrFsmTimerCnt ++;
        if(g_u16PwrFsmTimerCnt > 20 ){
			EMIT_FSM(POWER_FSM, 	PWR_RELAY_DITHER_CMP);
        }
}

UINT8 power_relay_dither_cond(UINT16 u16TrigEven){
	if (u16TrigEven == PWR_RELAY_DITHER_CMP)    return  PWR_STATUS_SOFTSTART;
	return PWR_STATUS_STANDBY;
}

void  power_softstart_in(void) {
	g_stPwrFsmOut.u16CtrCmd = 1;
	g_u16PwrFsmTimerCnt = 0;
	g_stPwrFsmOut.f32VpfcSet = f32_get_vpfc_raw();
}

void  power_softstart_exe(void) {
	float f32VpfcSetTarget = f32_get_vpfc_set_target();
	g_stPwrFsmOut.f32VpfcSet += 0.2f;
	if (g_stPwrFsmOut.f32VpfcSet > f32VpfcSetTarget) {
		g_stPwrFsmOut.f32VpfcSet = f32VpfcSetTarget;
		if (f32_get_vpfc_raw() > (f32VpfcSetTarget - 10.0f)) {
			g_u16PwrFsmTimerCnt++;
			if (g_u16PwrFsmTimerCnt > 3) {
				BSW_HAL_BUCK_OK();
				EMIT_FSM(POWER_FSM, PWR_SOFTSTART_CMP);
			}
		}
	}
}

UINT8 power_softstart_cond(UINT16 u16TrigEven) {
	if (u16TrigEven == PWR_SOFTSTART_CMP)		return PWR_STATUS_RUN;
	return PWR_STATUS_SOFTSTART;
}

void  power_run_in(void) {
	
}

void  power_run_exe(void) {
	float f32VpfcSetTarget = f32_get_vpfc_set_target();
	if (g_stPwrFsmOut.f32VpfcSet < f32VpfcSetTarget) {
		EMIT_FSM(POWER_FSM, PWR_SOFTSTART_REQ_EVEN);
	}
	else {
		g_stPwrFsmOut.f32VpfcSet = f32VpfcSetTarget;
	}
	if (IsFastFaultDetect() == TRUE) {
		EMIT_FSM(POWER_FSM, PWR_FAULT_EVEN);
	}
}

UINT8 power_run_cond(UINT16 u16TrigEven) {
	if (u16TrigEven == PWR_SOFTSTART_REQ_EVEN)		return PWR_STATUS_SOFTSTART;
	if (u16TrigEven == PWR_FAULT_EVEN)			    return PWR_STATUS_FAULT;
	return PWR_STATUS_RUN;
}

void  power_fault_in(void) {
	g_u16PwrFsmTimerCnt = 0;
}

void  power_fault_exe(void) {
	static unsigned short s_u16NoRecvRepeatStartFlag = 0;
	if (u16_get_no_recv_diag() != 0) {
		g_u16PwrFsmTimerCnt++;
		if (g_u16PwrFsmTimerCnt > 3000) {
			s_u16NoRecvRepeatStartFlag = 1;
		}
	}
	else {
		s_u16NoRecvRepeatStartFlag = 1;
	}
/*	if ((u16_get_auto_recv_diag() == 0)&&(s_u16NoRecvRepeatStartFlag == 1)) {
		ClrFastFaultDetectFlag();
		s_u16NoRecvRepeatStartFlag = 0;
		EMIT_FSM(POWER_FSM, PWR_FAULT_CLR_EVEN);
	}*/
}

UINT8 power_fault_cond(UINT16 u16TrigEven) {

	return PWR_STATUS_FAULT;
}




