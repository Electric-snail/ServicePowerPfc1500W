/*
 * asw_sci_comm.h
 *
 *  Created on: 2022/8/30
 *      Author: rjgslg
 */

#ifndef _PFC_LLC_COMM_H_
#define _PFC_LLC_COMM_H_

#include "../ENV_CFG/SOFTWARE_ENV_CFG.h"

#define  CMD_ID_DATA_ITEM            0x10

extern UINT16 g_SciCommTimeOutCnt;

#define COMM_TIMEOUT_T      10
#define set_SciCommTimeOutCnt_Val()   g_SciCommTimeOutCnt = COMM_TIMEOUT_T

typedef struct{
	//BYTE0
    UINT16 rolling_counter            :8;   //0
    //BYTE1
    UINT16 b4WorkModeCmd              :4;
    UINT16 b4ModeStateCmd             :4;   //1
    //BYTE2
    UINT16 b2AcTypeSet				  :2;
	UINT16 b2AcFreqLevelSet           :1;
	UINT16 b2AcVoltLevelSet           :4;
	UINT16 b1FaultClrCmd              :1;   //2
    //BYTE3
	UINT16 b4InvPoutMaxLevel          :4;
	UINT16 b4Byte3Rvs                 :4;   //3
    //BYTE4
    UINT16 VbatL                      :8;   //4
    //BYTE5
    UINT16 VbatH                      :8;   //5
    //BYTE6
    UINT16 InvPoutMaxL                :8;   //6
    //BYTE7
    UINT16 InvPoutMaxH                :8;   //7
    //BYTE8
    UINT16 CllcTempMax                :8;   //8
    //BYTE9
    UINT16 b8Rvs                      :8;   //9
    //BYTE10
    UINT16 PhsA_ActvPwrL              :8;   //10
    //BYTE11
    UINT16 PhsA_ActvPwrH              :8;   //11
    //BYTE12
    UINT16 PhsB_ActvPwrL              :8;   //12
    //BYTE13
    UINT16 PhsB_ActvPwrH              :8;   //13
    //BYTE14
    UINT16 PhsC_ActvPwrL              :8;   //14
    //BYTE15
    UINT16 PhsC_ActvPwrH              :8;   //15
    //BYTE16
    UINT16 PhsA_ReActvPwrL            :8;   //16
    //BYTE17
    UINT16 PhsA_ReActvPwrH            :8;   //17
    //BYTE18
    UINT16 PhsB_ReActvPwrL            :8;   //18
    //BYTE19
    UINT16 PhsB_ReActvPwrH            :8;   //19
    //BYTE20
    UINT16 PhsC_ReActvPwrL            :8;   //20
    //BYTE21
    UINT16 PhsC_ReActvPwrH            :8;   //21

}LLC_PFC_COMM_MATRIX_BYTES;

typedef union
{
    UINT16  						ua16SendBuff[sizeof(LLC_PFC_COMM_MATRIX_BYTES)/sizeof(UINT16)];
    LLC_PFC_COMM_MATRIX_BYTES       bits;
}MSG_LLC_PFC_U;

#endif /* _PFC_LLC_COMM_H_ */
