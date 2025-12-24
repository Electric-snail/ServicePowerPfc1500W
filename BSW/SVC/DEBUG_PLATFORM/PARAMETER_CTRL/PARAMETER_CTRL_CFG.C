/*
 * PARAMETER_CTRL_CFG.C
 *
 *  Created on: 2025Äê10ÔÂ16ÈÕ
 *      Author: Administrator
 */
#include "SOFTWARE_ENV_CFG.H"
#include "DEBUG_PLATFORM/PARAMETER_CTRL/PARAMETER_CTRL.H"
#include "ISR_INC/BSW_ISR_ADC.H"
#include "DIAGNOSTIC/DIAGNOSTIC.H"
#include "POWER_FSM/POWER_FSM.H"
#include "PFC_LLC_COMM/PFC_LLC_COMM.H"
#include "PUBLIC_INC/DC_MATH.H"
#include "PFC_CTR/PFC_CTR.H"
#include "MEASURE/MEASURE.H"

extern 	STATIC 		PI_POS_T				    gs_stVpfcPiCtrl;
extern 	STATIC 		PI_GAIN_POS_T		gs_stIacPiGainCtrl;
extern    float				g_f32VpfcPiKpSlow;
extern    float				g_f32VpfcPiKiTsSlow;
extern 	float			    gs_f32FeedCoff;
extern     float 			g_f32VpfcSetTarget;
extern     float           g_f32PowerOpenSet;

//-----------------------------------------var_name,					var,																		attr,					  def,				  										 min,															max
REG_CFG_ITEM_U16(FAULT_FLAG,					g_u16FaultDetetFlag,						    						VAR_WR,		     		0,						  										0,																1);
REG_CFG_ITEM_F32(OPEN_DUTY,					g_f32OpenDuty,						    								VAR_WR,		      		0,						  										0,																1.0f);
//REG_CFG_ITEM_F32(POWER_SET,					g_f32PowerOpenSet,						    						VAR_WR,		      		0,						  										0,																2000.0f);
REG_CFG_ITEM_F32(VPFC_TARGET,			   g_f32VpfcSetTarget,						    							VAR_WR,		      		380.0,			      										350.0f,						 							    430.0f);
REG_CFG_ITEM_F32(VPFC_FILT_DC,			   gs_stVpfcNotchFilt.stCoff.f32Width0,						    VAR_WR,		      		0.001,			      										0.00001,						 							0.1);
REG_CFG_ITEM_F32(VPFC_FILT_AC,			   gs_stVpfcNotchFilt.stCoff.f32Width1,						    VAR_WR,		      		0.0083,			      								    0.000083f,						 						0.83);

REG_CFG_ITEM_U16(LLC_HISTORY_AUTO_FAULT, 		g_stDiagHisStatus.unAutoRecvFault.u16All,     VAR_WR,     0,    								 0,    				0xFFFF);
REG_CFG_ITEM_U16(LLC_HISTORY_NO_FAULT,   			g_stDiagHisStatus.unNoRecvFault.u16All,      	VAR_WR,     0,     							 0,    				0xFFFF);
REG_CFG_ITEM_U16(LLC_CURRENT_AUTO_FAULT, 		g_stDiagStatus.unAutoRecvFault.u16All,       		VAR_RD,     0,     							 0,    				0xFFFF);
REG_CFG_ITEM_U16(LLC_CURRENT_NO_FAULT,   			g_stDiagStatus.unNoRecvFault.u16All,         		VAR_RD,     0,     							 0,    				0xFFFF);

REG_CFG_ITEM_U16(PWR_FSM,	   					fsm_obj_POWER_FSM.u8CurStateId,						VAR_RD,			  0,						  										0,																4);

REG_CFG_ITEM_F32(VPFC_KP,					   g_f32VpfcPiKpSlow,						    							VAR_WR,		      50.0f,				 														1,												2000.0f);
REG_CFG_ITEM_F32(VPFC_KI,					       g_f32VpfcPiKiTsSlow,						    						VAR_WR,		      (1 * 2 * 3.1415926f * 5 * CTR_PERIOD	),			(0.1f / 65000.0f	),					(5000.0f / 65000.0f)	);

REG_CFG_ITEM_F32(IL_KP,					   		   gs_stIacPiGainCtrl.stCoff.f32Kp,						    		VAR_WR,		      10.0f,				 										0.01,														500.0f);
REG_CFG_ITEM_F32(IL_KI,					       	   gs_stIacPiGainCtrl.stCoff.f32KiTs,						    	VAR_WR,		      (10.0f * 2000.0f/ 65000.0f),			      (10.0f * 10.0f/ 65000.0f),						 (10.0f * 10000.0f/ 65000.0f));
REG_CFG_ITEM_F32(IL_FEED,					       gs_f32FeedCoff,						    									VAR_WR,		      0.8,			      										  0,						 										 1.0f);

REG_CFG_ITEM_F32(VIN_FRQ,			             g_stMeasureOut. stVinPolFrqObj.stOut.f32Frq,			VAR_RD,		      0,			      										  		0.0f,						 								 	0.0f);
REG_CFG_ITEM_U16(VIN_TYPE,			         g_stMeasureOut. stVinPolFrqObj.stOut.u16Type,			VAR_RD,		      0,			      										        0,						 								   		0);

REG_CFG_ITEM_F32(VIN_RMS,			        g_stMeasureOut.stVinRmsObj.stOut.f32Rms,			    VAR_RD,		      0,			      										  		0.0f,						 								 	0.0f);

REG_CFG_ITEM_F32(VIN_RMS_FLT,			g_stMeasureOut.f32VinRmsLpf,			        					VAR_RD,		      0,			      										  		0.0f,						 								 	0.0f);

REG_CFG_ITEM_F32(PIN_AVE,						g_stMeasureOut.f32PinLpf,			        							VAR_RD,		      0,			      										  		0.0f,						 								 	0.0f);

REG_CFG_ITEM_F32(IIN_RMS,						g_stMeasureOut.f32IinRmsLpf,			        					VAR_RD,		      0,			      										  		0.0f,						 								 	0.0f);
