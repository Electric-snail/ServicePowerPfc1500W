/*
 * CommTest.h
 *
 *  Created on: 2022/10/22
 *      Author: xj8r1j
 */

#ifndef BSW_SVC_DEBUGPLATFORM_COMM_TEST_COMMTEST_H_
#define BSW_SVC_DEBUGPLATFORM_COMM_TEST_COMMTEST_H_

#define COMM_TEST_STOP_CMD                     0
#define COMM_TEST_RUN_CMD                      1

#define COMM_TEST_TASK_PERIOD                  50


#define RX_TEST_RUN_CMD_ID                         0x00
#define RX_TEST_DATA_CMD_ID                        0x01
#define TX_TEST_RUN_CMD_ID                         0x02
#define TX_TEST_DATA_CMD_ID                        0x03
#define TX_TEST_FEEDBACK_NUM_CMD_ID                0x04

typedef struct
{
	UINT8   u8CommTestCmd;
	UINT16  u16AplDLC;
	UINT16  u16Intv;
}COMM_TEST_RX_INFO;

typedef struct
{
	UINT8   u8CommTestCmd;
	UINT16  u16Intv;
    UINT32  u32SuccRxCnt;
}COMM_TEST_TX_INFO;

extern void CommTestCmdSetLink(void *p_stAplDmTemp);
#endif /* BSW_SVC_DEBUGPLATFORM_COMM_TEST_COMMTEST_H_ */
