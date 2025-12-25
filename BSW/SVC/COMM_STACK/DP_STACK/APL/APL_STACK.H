/*
 * ApiProtocolStack.h
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#ifndef BSW_SVC_APIPROTOCOLSTACK_APIPROTOCOLSTACK_H_
#define BSW_SVC_APIPROTOCOLSTACK_APIPROTOCOLSTACK_H_

#define MAX_PROTCOL_PRIO                2  //Support 2 max kinds of protocol
#define MAX_SEND_PACK_LEN               1024

typedef void (*pf_action_func)(void *p_stAplDm);

//RVS default command set 0x00
#define  PARAM_CFG_CMD_SET                  	0x01
#define  SW_SCOPE_CMD_SET                    	0x02
#define  DATA_LOG_CMD_SET                    	0x03
#define  RVS0_CMD_SET             				0x04
#define  RVS1_CMD_SET                           0x05
#define  BOOTLOAD_CMD_SET                  		0x06
#define  COMM_TEST_CMD_SET                		0x07
#define  PERFOR_TEST_CMD_SET             		0x08
#define  SFRA_CMD_SET                           0x09
#define  PARAM_CALIB_CMD_SET          	 		0x0a

#define  MPPT_MASTER_DATA_CMD_SET     			0x10
#define  LLC_MASTER_DATA_CMD_SET        		0x11
#define  BMS_MASTER_DATA_CMD_SET       			0x12
#define  PRI_SEC_DATA_CMD_SET                	0x13
#define  MASTER_DCDC_DATA_CMD_SET               0x14

typedef struct
{
    unsigned char           u8CmdSet;
    pf_action_func  action_func;
}CMD_LINK_ACTION_ITEM;

#define APL_NO_ACK               0
#define APL_REQUEST_ACK          1
#define APL_ANSWER_ACK           2

#define REG_CMD_LINK_ACTION_TAB  \
{\
    {PRI_SEC_DATA_CMD_SET,  pfc_llc_comm_rx_hander},   \
    {PARAM_CFG_CMD_SET,  	ParamCfgCmdSetLink},    	\
    {DATA_LOG_CMD_SET,  	DataLogCmdSetLink},    	    \
	{SW_SCOPE_CMD_SET,   	SwScopeCmdSetLink}, 		\
/*	{BOOTLOAD_CMD_SET,      bootload_cmd_set_link},   */  \
/*    {PERFOR_TEST_CMD_SET,   PerformaceCmdSetLink}, */     \
/*    {COMM_TEST_CMD_SET,     CommTestCmdSetLink},  */      \
/*    {SFRA_CMD_SET,          SfraCmdSetLink},    */        \
	{PARAM_CALIB_CMD_SET,   ParamCalibCmdSetLink},\
}

extern void apl_init(void);
extern void apl_main(void);

#endif /* BSW_SVC_APIPROTOCOLSTACK_APIPROTOCOLSTACK_H_ */
