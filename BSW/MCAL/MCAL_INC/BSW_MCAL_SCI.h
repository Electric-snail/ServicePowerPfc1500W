/*
 * BSW_MCAL_SCI.h
 *
 *  Created on: 2022.07.25
 *      Author: Hongbo.Jiang
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_SCI_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_SCI_H_
#include "common/include/F28x_Project.h"
#include "HARDWARE_ENV_CFG.h"
#include "PUBLIC_INC/auto_register.h"
#include "BSW_MCAL_BASIC.h"

#define     SCIB_FIFO_ENABLE                  1
#define 	SCIB_FIFO_WORD_SIZE            FIFO_16_WORD
#define 	SCIA_FIFO_WORD_SIZE            FIFO_16_WORD

#define scia_write_send_buff(u8Data)            SciaRegs.SCITXBUF.all = u8Data
#define is_scia_fifo_enable                             SciaRegs.SCIFFTX.bit.SCIFFENA

#define scib_write_send_buff(u8Data)            ScibRegs.SCITXBUF.all = u8Data
#define is_scib_fifo_enable                             ScibRegs.SCIFFTX.bit.SCIFFENA

enum SCI_ID
{
    SCIA_ID = 0,
    SCIB_ID = 1,
    SCI_MAX_ID,
};

enum SCI_BAUD
{
    BAUD_4800 = 0,
    BAUD_9600 = 1,
    BAUD_19200 = 2,
    BAUD_115200 = 3,
};

enum SCI_RX_FIFO_LEVEL
{
    FIFO_1_WORD = 1,
    FIFO_2_WORD,
    FIFO_3_WORD,
    FIFO_4_WORD,
    FIFO_5_WORD,
    FIFO_6_WORD,
    FIFO_7_WORD,
    FIFO_8_WORD,
    FIFO_9_WORD,
    FIFO_10_WORD,
    FIFO_11_WORD,
    FIFO_12_WORD,
    FIFO_13_WORD,
    FIFO_14_WORD,
    FIFO_15_WORD,
    FIFO_16_WORD,
    FIFO_MAX_WORD
};

enum SCI_PARITY_MODE{
   NONE_PARITY = 0,
   ODD_PARITY,
   EVEN_PARITY1,
};

enum SCI_STOP_BIT{
    ONE_STOP_BIT = 0,
    TWO_STOP_BIT = 1,
};

/*--- The data receive mode, by interrupt or polling method to receive the data ----*/
enum SCI_RX_MODE{
   RX_POLLING   = 0,
   RX_INTERRUP  = 1,
};

typedef struct
{
    enum SCI_ID                 				emSciId;
    enum SCI_BAUD               			emSciBaud;
    enum SCI_PARITY_MODE        	emSciParity;
    enum SCI_STOP_BIT           		emSciStopBit;
    enum SCI_RX_MODE            		emSciRxMode;
    UINT16                      					u16FifoEnable;
    enum SCI_RX_FIFO_LEVEL      	emFifoLevel;
}SCI_ITEM_CFG;

/*---SCI_MODULE------BAUD----------------PARITY-------------STOP_BIT--------------SCI_RX_MODE----FIFO_ENABLE------FIFO_LEVEL---*/
#define      REG_SCI_ITEM_CFG_TAB        \
{\
    {SCIB_ID,   			BAUD_19200,   	NONE_PARITY,   	ONE_STOP_BIT,    		RX_POLLING,      SCIB_FIFO_ENABLE,          SCIB_FIFO_WORD_SIZE},\
}

//#define get_sciHwRxError()         (ScibRegs.SCIRXST.bit.RXERROR)
//
//#define sciHwRxError_clr()          do{        ScibRegs.SCICTL1.bit.SWRESET = 0;\
//                                                            ScibRegs.SCICTL1.bit.SWRESET = 1;\
//                                                  }while(0)

extern INT16 Scia_Send_Bytes(UINT8 *p_u8SrcData, UINT16 u16Len);

extern INT8  Scia_Send_Byte(UINT8);

extern INT16 Scib_Send_Bytes(UINT8 *p_u8SrcData, UINT16 u16Len);
extern INT8  Scib_Send_Byte(UINT8);

extern void  bsw_mcal_sci_init(void);

#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_SCI_H_ */
