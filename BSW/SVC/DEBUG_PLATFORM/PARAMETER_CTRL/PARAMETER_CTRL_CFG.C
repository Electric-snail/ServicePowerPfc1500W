/*
 * PARAMETER_CTRL_CFG.C
 *
 *  Created on: 2025��10��16��
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
extern float g_f32VpfcPiKpLv;
extern float g_f32VpfcPiKiTsLv;
extern float g_f32VpfcPiGainLv;
extern float g_f32VpfcPiKpMv;
extern float g_f32VpfcPiKiTsMv;
extern float g_f32VpfcPiGainMv;
extern float g_f32VpfcPiKpHv;
extern float g_f32VpfcPiKiTsHv;
extern float g_f32VpfcPiGainHv;
extern float g_f32VpfcPiGain;
extern float g_f32VpfcPiKiTsDcSlow;
extern float g_f32VpfcPiKpDcSlow;

extern    float			    gs_f32FeedCoff;
extern    float             g_f32PowerOpenSet;
extern    float             g_f32VpfcTestTarget;
extern    float             g_f32IacRmsRef;
extern    float             g_f32IacKpDc;
extern    float             g_f32IacKiTsDc;
extern    float             g_f32IacFeedCoffDc;
extern    float             g_f32IacKpDcLv;
extern    float             g_f32IacKiTsDcLv;
extern    float             g_f32IacFeedCoffDcLv;
extern    unsigned short    g_u16IacCtrlTuneEnable;
extern    float             g_f32IacKpAc;
extern    float             g_f32IacKiTsAc;
extern    float             g_f32IacFeedCoffAc;
extern    float             g_stIacPiGainCtrlGuiKpHv;
extern    float             g_stIacPiGainCtrlGuiKiTsHv;
extern    float             g_f32FeedCoffGuiHv;
//-----------------------------------------var_name,					var,																		attr,					  def,				  										 min,															max
REG_CFG_ITEM_U16(FAULT_FLAG,					g_u16FaultDetetFlag,						    		VAR_RD,		     		0,						  										0,																1);
REG_CFG_ITEM_U16(PFC_CTR_CMD,                   g_stPwrFsmOut.u16CtrCmd,                                VAR_RD,                 0,                                                              0,                                                              1);

REG_CFG_ITEM_F32(IAC_REF_RMS,					g_f32IacRmsRef,						    				VAR_RD,		      		0,						  										0,																0.0f);
REG_CFG_ITEM_F32(OPEN_DUTY,					    g_f32OpenDuty,						    				VAR_WR,		      		0,						  										0,																1.0f);
//REG_CFG_ITEM_F32(POWER_SET,					g_f32PowerOpenSet,						    			VAR_WR,		      	    0,						  								    	0,																2000.0f);
//REG_CFG_ITEM_F32(VPFC_SET,					    g_f32VpfcTestTarget,						    		VAR_WR,		      		0,						  										0,																450.0f);
REG_CFG_ITEM_F32(VPFC_FILT_DC,			   		gs_stVpfcNotchFilt.stCoff.f32Width0,					VAR_WR,		      		0.001f,			      									        0.00001f,						 							    0.1f);
REG_CFG_ITEM_F32(VPFC_FILT_AC,			   		gs_stVpfcNotchFilt.stCoff.f32Width1,					VAR_WR,		      		0.0083f,			      								        0.000083f,						 						        0.83f);

REG_CFG_ITEM_U16(HISTORY_AUTO_FAULT, 		    g_stDiagHisStatus.unAutoRecvFault.u16All,               VAR_WR,                  0,    								                            0,    				                                            0xFFFF);
REG_CFG_ITEM_U16(HISTORY_NO_FAULT,   			g_stDiagHisStatus.unNoRecvFault.u16All,      	        VAR_WR,                  0,     							 0,    				0xFFFF);
REG_CFG_ITEM_U16(CURRENT_AUTO_FAULT, 		    g_stDiagStatus.unAutoRecvFault.u16All,       		    VAR_RD,                  0,     							 0,    				0xFFFF);
REG_CFG_ITEM_U16(CURRENT_NO_FAULT,   			g_stDiagStatus.unNoRecvFault.u16All,         		    VAR_RD,                  0,     							 0,    				0xFFFF);
REG_CFG_ITEM_U16(CURRENT_WARN,                  g_stDiagStatus.unWarn.u16All,                           VAR_WR,                  0,                                                             0,                                                              0xFFFF);


REG_CFG_ITEM_U16(PWR_FSM,	   				 fsm_obj_POWER_FSM.u8CurStateId,						    VAR_RD,			  0,						  										0,																4);

REG_CFG_ITEM_F32(VPFC_KP_LV,				 g_f32VpfcPiKpLv,						    				VAR_WR,		      5.0f,				 														1,												2000.0f);
REG_CFG_ITEM_F32(VPFC_KI_LV,			     g_f32VpfcPiKiTsLv,						    				VAR_WR,		     0.0025f,																	(0.01f / 65000.0f	),					(5000.0f / 65000.0f));
REG_CFG_ITEM_F32(VPFC_KG_LV,				 g_f32VpfcPiGainLv,						    			    VAR_WR,		     0.1f,																	    0,												10.0f);

REG_CFG_ITEM_F32(VPFC_KP_MV,				 g_f32VpfcPiKpMv,						    				VAR_WR,		      5.0f,				 														1,												2000.0f);
REG_CFG_ITEM_F32(VPFC_KI_MV,				 g_f32VpfcPiKiTsMv,						    				VAR_WR,		      0.002f,																	(0.01f / 65000.0f	),					(5000.0f / 65000.0f));
REG_CFG_ITEM_F32(VPFC_KG_MV,				 g_f32VpfcPiGainMv,						    			    VAR_WR,		     0.1f,																	    0,												10.0f);

REG_CFG_ITEM_F32(VPFC_KP_HV,				 g_f32VpfcPiKpHv,						    				VAR_WR,		      5.0f,				 														1,												2000.0f);
REG_CFG_ITEM_F32(VPFC_KI_HV,				 g_f32VpfcPiKiTsHv,						    				VAR_WR,		      0.001f,																	(0.01f / 65000.0f	),					(5000.0f / 65000.0f));
REG_CFG_ITEM_F32(VPFC_KG_HV,				 g_f32VpfcPiGainHv,						    			    VAR_WR,		     0.1f,																	    0,												10.0f);

REG_CFG_ITEM_F32(VPFC_KG,			         g_f32VpfcPiGain,						    			    VAR_RD,		     	0.1f,																		0,												10.0f);
REG_CFG_ITEM_F32(VPFC_KP,				     gs_stVpfcPiCtrl.stCoff.f32Kp,						        VAR_RD,		     	0.0f,														        0,												0);
REG_CFG_ITEM_F32(VPFC_KI,				     gs_stVpfcPiCtrl.stCoff.f32KiTs,						    VAR_RD,		     	0.0f,														        0,												0);

REG_CFG_ITEM_F32(VPFC_KP_DC,			     g_f32VpfcPiKpDcSlow,						    			VAR_WR,		     	5.0f,															0,									100.0f);
REG_CFG_ITEM_F32(VPFC_KI_DC,				 g_f32VpfcPiKiTsDcSlow,						                VAR_WR,		     	0.0025f,												    0,									1.0);

REG_CFG_ITEM_F32(PLL_KP,					 gs_stOrthPll.stCoff.f32Kp,						    		VAR_WR,		        0.01f,				 										0.001,														0.1f);

REG_CFG_ITEM_F32(IL_KP,					   	 gs_stIacPiGainCtrl.stCoff.f32Kp,						    VAR_RD,		        10.0f,				 										0.01,														500.0f);
REG_CFG_ITEM_F32(IL_KI,					     gs_stIacPiGainCtrl.stCoff.f32KiTs,						    VAR_RD,		        (10.0f * 2000.0f/ 65000.0f),			      (10.0f * 10.0f/ 65000.0f),						 (10.0f * 100000.0f/ 65000.0f));
REG_CFG_ITEM_F32(IL_FEED,					 gs_f32FeedCoff,						    				VAR_RD,		        0.8,			      										  0,						 										 1.0f);

REG_CFG_ITEM_U16(IL_AC_TUNE_EN,              g_u16IacCtrlTuneEnable,                                      VAR_WR,             0,                                                          0,                                                          1);
REG_CFG_ITEM_F32(IL_KP_AC,                   g_f32IacKpAc,                                                VAR_WR,             3.0f,                                                       0.01f,                                                      500.0f);
REG_CFG_ITEM_F32(IL_KI_AC,                   g_f32IacKiTsAc,                                              VAR_WR,             0.3f,                                                       0.0f,                                                       30.0f);
REG_CFG_ITEM_F32(IL_FEED_AC,                 g_f32IacFeedCoffAc,                                          VAR_WR,             0.65f,                                                      0.0f,                                                       1.0f);

REG_CFG_ITEM_F32(IL_KP_DC,                   g_f32IacKpDc,                                              VAR_WR,             4.8f,                                                      0.03,                                                       300.0f);
REG_CFG_ITEM_F32(IL_KI_DC,                   g_f32IacKiTsDc,                                            VAR_WR,             0.00002f,                                                  0.0f,                                                     30.0f);
REG_CFG_ITEM_F32(IL_FEED_DC,                 g_f32IacFeedCoffDc,                                        VAR_WR,             0.15f,                                                     0,                                                          1.0f);
REG_CFG_ITEM_F32(IL_KP_DC_LV,                g_f32IacKpDcLv,                                            VAR_WR,             4.8f,                                                      0.03,                                                       300.0f);
REG_CFG_ITEM_F32(IL_KI_DC_LV,                g_f32IacKiTsDcLv,                                          VAR_WR,             0.0001f,                                                   0.0f,                                                       30.0f);
REG_CFG_ITEM_F32(IL_FEED_DC_LV,              g_f32IacFeedCoffDcLv,                                      VAR_WR,             0.15f,                                                     0.0f,                                                       1.0f);

REG_CFG_ITEM_F32(IL_KP_HV,                   g_stIacPiGainCtrlGuiKpHv,                                  VAR_WR,             10.0f,                                                     0.01,                                                       500.0f);
REG_CFG_ITEM_F32(IL_KI_HV,                   g_stIacPiGainCtrlGuiKiTsHv,                                VAR_WR,             1.0f,                                                      (10.0f * 10.0f/ 65000.0f),                                (10.0f * 100000.0f/ 65000.0f));
REG_CFG_ITEM_F32(IL_FEED_HV,                 g_f32FeedCoffGuiHv,                                        VAR_WR,             0.8f,                                                      0,                                                          1.0f);

REG_CFG_ITEM_F32(VIN_FRQ,			         g_stMeasureOut. stVinPolFrqObj.stOut.f32Frq,			    VAR_RD,		      	0,			      										 -10000.0f,						 								10000.0f);
REG_CFG_ITEM_U16(VIN_TYPE,			         g_stMeasureOut. stVinPolFrqObj.stOut.u16Type,			    VAR_RD,		        0xFF,			      										        0,						 							0xFF);

REG_CFG_ITEM_F32(VIN_RMS,			         g_stMeasureOut.stVinRmsObj.stOut.f32Rms,			        VAR_RD,		        0,			      										  -10000.0f,						 							10000.0f);

REG_CFG_ITEM_F32(VIN_RMS_FLT,			     g_stMeasureOut.f32VinRmsLpf,			        	        VAR_RD,		        0,			      										 -10000.0f,						 								10000.0f);

REG_CFG_ITEM_F32(PIN_AVE,					 g_stMeasureOut.f32PinLpf,			        			    VAR_RD,		        0,			      										 -10000.0f,						 								10000.0f);

REG_CFG_ITEM_F32(IIN_RMS,				     g_stMeasureOut.f32IinRmsLpf,			        		    VAR_RD,		        0,			      										 -10000.0f,					 								 	10000.0f);

REG_CFG_ITEM_F32(PFC_MOS_TEMP,				 g_stMeasureOut.f32Temperature,			        			VAR_RD,		        0,			      										 -10000.0f,					 								 	10000.0f);

#if(MEASURE_TIME_TEST == 1)
extern float g_f32MeasureTime;
REG_CFG_ITEM_F32(MEASURE_TIME, g_f32MeasureTime, VAR_RD, 0, 0, 1000000);
#endif
