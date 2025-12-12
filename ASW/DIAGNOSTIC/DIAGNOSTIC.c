/*
 * DIAGNOSTIC.c
 *
 *  Created on: 2022/11/7/
 *      Author:   Hongbo.Jiang
 */
#include "PUBLIC_INC/MEM_HANDLE.H"
#include "PUBLIC_INC/DC_MATH.H"
#include "HAL_INC/BSW_HAL_PWM.h"
#include "HAL_INC/BSW_HAL_GPIO.h"
#include "HAL_INC/BSW_HAL_CMPSS.h"
 //#include "STORAGE/BSW_STORAGE.h"
#include "TASK/BSW_TASK_SERVICE.h"
#include "ASW_BASIC.h"
#include "DIAGNOSTIC/DIAGNOSTIC.h"
#include "ISR_INC/BSW_ISR_ADC.h"
#include "MEASURE/MEASURE.h"
#include "SYS_FSM/SYS_FSM_INF.h"
#include "POWER_FSM/POWER_FSM.h"
/********* function declaration region *************************************/


/*********variable declaration region *************************************/



/************ Variable definition region *********************************/
DIAG_STATUS_T 	g_stDiagStatus;
DIAG_STATUS_T 	g_stDiagHisStatus;

UINT16 g_u16SwDiagCount[SW_DIAG_ID_MAX] = { 0 };

const SWDIAG_PARAM_CFG_T  gc_stSwdiagCfgParam[SW_DIAG_ID_MAX] = DIAG_PARAM_TAB; 

void diagnostic_init(void){
	g_stDiagStatus.unAutoRecvFault.u16All = 0x0000;
	g_stDiagStatus.unNoRecvFault.u16All    = 0x0000;
}
/*************************************************
*  Function:       fast_diagnostic_task
*  Description:
*  Called:
*  Input:
*
*  Quoted Variable:
*  Modified Variable: No
*  Return:
*  Others:
*
*************************************************/
#ifndef  DLLX64
#pragma  CODE_SECTION(diagnostic_fast_task, ".TI.ramfunc");
#endif

void diagnostic_fast_task(void) {
	float f32IlCbcFlg = (float)read_pfc_drv_dcaevt2_flag();
	clr_pfc_drv_deaevt2_flag();
	ASW_DiagSWFaultOverNoRecv(g_stDiagStatus.unNoRecvFault.bits.b1IlCbbp, f32IlCbcFlg, gc_stSwdiagCfgParam[IL_CBBP_ID].f32PrtctThreshold, g_u16SwDiagCount[IL_CBBP_ID], gc_stSwdiagCfgParam[IL_CBBP_ID].u16ErrCnt);

	if(read_vpfc_hw_ovp_flag() == 1){
	 	g_stDiagStatus.unNoRecvFault.bits.b1VfpcHwOvp = 1;
	}
    if ((g_stDiagStatus.unNoRecvFault.u16All != 0x0000)||(g_stDiagStatus.unAutoRecvFault.u16All != 0x0000)) {
		g_stDiagHisStatus.unAutoRecvFault.u16All = g_stDiagStatus.unAutoRecvFault.u16All;
		g_stDiagHisStatus.unNoRecvFault.u16All   = g_stDiagStatus.unNoRecvFault.u16All;
		g_u16FaultDetetFlag = 1;
    }
}

/*************************************************
*  Function:       diag_1ms_task
*  Description:
*  Called:         clr_diag_fault_flag_handle
*  Input:
*
*  Quoted Variable:
*  Modified Variable: No
*  Return:
*  Others:
*
*************************************************/
void diag_1ms_task(void)
{
	float f32TempValue = f32_get_vpfc_raw();
	ASW_DiagSWFaultOverNoRecv(g_stDiagStatus.unNoRecvFault.bits.b1VpfcFastOvp, f32TempValue, gc_stSwdiagCfgParam[VPFC_FAST_OVP_ID].f32PrtctThreshold, \
		g_u16SwDiagCount[VPFC_FAST_OVP_ID], gc_stSwdiagCfgParam[VPFC_FAST_OVP_ID].u16ErrCnt);
	
	if (u16_get_pwr_status() == PWR_STATUS_RUN) {
		ASW_DiagSWFaultUnderNoRecv(g_stDiagStatus.unNoRecvFault.bits.b1VpfcFastUvp, f32TempValue, gc_stSwdiagCfgParam[VPFC_FAST_UVP_ID].f32PrtctThreshold, \
			g_u16SwDiagCount[VPFC_FAST_UVP_ID], gc_stSwdiagCfgParam[VPFC_FAST_UVP_ID].u16ErrCnt);
	}
}
/*************************************************
*  Function:       diag_10ms_task
*  Description:
*  Called:
*  Input:
*
*  Quoted Variable:
*  Modified Variable: No
*  Return:
*  Others:
*
*************************************************/
void diag_10ms_task(void)
{
	float f32TempValue  = f32_get_vin_rms();

	ASW_DiagSWFaultOverRecv(g_stDiagStatus.unAutoRecvFault.bits.b1VinRmsOvp, f32TempValue, gc_stSwdiagCfgParam[VIN_RMS_OVP_ID].f32PrtctThreshold, \
							gc_stSwdiagCfgParam[VIN_RMS_OVP_ID].f32RcvrThreshold, g_u16SwDiagCount[VIN_RMS_OVP_ID], gc_stSwdiagCfgParam[VIN_RMS_OVP_ID].u16ErrCnt, gc_stSwdiagCfgParam[VIN_RMS_OVP_ID].u16RcvrCnt);

	ASW_DiagSWFaultUnderRecv(g_stDiagStatus.unAutoRecvFault.bits.b1VinRmsUvp, f32TempValue, gc_stSwdiagCfgParam[VIN_RMS_UVP_ID].f32PrtctThreshold, \
		gc_stSwdiagCfgParam[VIN_RMS_UVP_ID].f32RcvrThreshold, g_u16SwDiagCount[VIN_RMS_UVP_ID], gc_stSwdiagCfgParam[VIN_RMS_UVP_ID].u16ErrCnt, gc_stSwdiagCfgParam[VIN_RMS_UVP_ID].u16RcvrCnt);

	f32TempValue = f32_get_vin_freq();

	if (u16_get_vin_type() == AC_TYPE) {
		ASW_DiagSWFaultOverRecv(g_stDiagStatus.unAutoRecvFault.bits.b1VinOfp, f32TempValue, gc_stSwdiagCfgParam[VIN_OFP_ID].f32PrtctThreshold, \
			gc_stSwdiagCfgParam[VIN_OFP_ID].f32RcvrThreshold, g_u16SwDiagCount[VIN_OFP_ID], gc_stSwdiagCfgParam[VIN_OFP_ID].u16ErrCnt, gc_stSwdiagCfgParam[VIN_OFP_ID].u16RcvrCnt);

		ASW_DiagSWFaultUnderRecv(g_stDiagStatus.unAutoRecvFault.bits.b1VinUfp, f32TempValue, gc_stSwdiagCfgParam[VIN_UFP_ID].f32PrtctThreshold, \
			gc_stSwdiagCfgParam[VIN_UFP_ID].f32RcvrThreshold, g_u16SwDiagCount[VIN_UFP_ID], gc_stSwdiagCfgParam[VIN_UFP_ID].u16ErrCnt, gc_stSwdiagCfgParam[VIN_UFP_ID].u16RcvrCnt);

	}

	f32TempValue = f32_get_vpfc_lpf();
	ASW_DiagSWFaultOverNoRecv(g_stDiagStatus.unNoRecvFault.bits.b1VpfcSlowOvp, f32TempValue, gc_stSwdiagCfgParam[VPFC_SLOW_OVP_ID].f32PrtctThreshold, \
		g_u16SwDiagCount[VPFC_SLOW_OVP_ID], gc_stSwdiagCfgParam[VPFC_SLOW_OVP_ID].u16ErrCnt);

	if (u16_get_pwr_status() == PWR_STATUS_RUN) {
		ASW_DiagSWFaultUnderNoRecv(g_stDiagStatus.unNoRecvFault.bits.b1VpfcSlowUvp, f32TempValue, gc_stSwdiagCfgParam[VPFC_SLOW_UVP_ID].f32PrtctThreshold, \
			g_u16SwDiagCount[VPFC_SLOW_UVP_ID], gc_stSwdiagCfgParam[VPFC_SLOW_UVP_ID].u16ErrCnt);
	}
}
/*************************************************
*  Function:       diag_100ms_task
*  Description:
*  Called:
*  Input:
*
*  Quoted Variable:
*  Modified Variable: No
*  Return:
*  Others:
*
*************************************************/
void diag_100ms_task(void)
{
}





