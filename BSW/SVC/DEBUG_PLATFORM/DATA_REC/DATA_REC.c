/*
 * DataRec.c
 *
 *  Created on: 2022.10.27.
 *      Author: Hongbo.Jiang
 */
#include "PUBLIC_INC/ASSERT.H"
#include "BSW_SVC_BASIC.H"
#include "DEBUG_PLATFORM/DBG_BASIC.H"
#include "DEBUG_PLATFORM/DATA_REC/DATA_REC.h"
#include "TASK/BSW_TASK_SERVICE.H"
#include "DP_STACK/DPStackBasic.h"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DP_STACK/APL/APL_STACK.H"
#include "string.h"

unsigned short  g_u16DataRecRun = 0;

#define GEN_DATA_REC_DATA_ENTITY
	#include "DEBUG_PLATFORM/DATA_REC/DATA_REC_CFG.h"
#undef GEN_DATA_REC_DATA_ENTITY


#define GEN_DATA_REC_CFG_ENTITY
	#include "DEBUG_PLATFORM/DATA_REC/DATA_REC_CFG.h"
#undef GEN_DATA_REC_CFG_ENTITY

#if(DATA_REC_AUTO_TX_ENABLE == 1)
#define GEN_DATA_REC_REG_TASK
	#include "DEBUG_PLATFORM/DATA_REC/DATA_REC_CFG.h"
#undef GEN_DATA_REC_REG_TASK
#endif

void DataLogCmdSetLink(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    UINT8 u8CmdId;
    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;
    if(u8CmdId == DATA_LOG_GET_CFG_CMD_ID){
		#define GEN_DATA_REC_CFG_CALL
			#include "DEBUG_PLATFORM/DATA_REC/DATA_REC_CFG.h"
		#undef GEN_DATA_REC_CFG_CALL
    }else if(u8CmdId == DATA_LOG_GET_DATA_CMD_ID){
		#if(DATA_REC_AUTO_TX_ENABLE == 0)
				#define GEN_DATA_REC_DATA_CALL
					#include "DEBUG_PLATFORM/DATA_REC/DATA_REC_CFG.h"
				#undef GEN_DATA_REC_DATA_CALL
		#endif
	}else if(u8CmdId == DATA_LOG_STOP_CMD_ID){
		 g_u16DataRecRun = 0;
	}
}
