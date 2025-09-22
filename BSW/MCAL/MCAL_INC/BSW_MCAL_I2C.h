/*
 * BSW_MCAL_I2C.h
 *
 *  Created on: 2025.7.18.
 *      Author: jhb72
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_I2C_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_I2C_H_

// I2C
#define I2C_NO_INT_SRC                  0x0000
#define I2C_ARB_INT_SRC                0x0001
#define I2C_NACK_INT_SRC             0x0002
#define I2C_ARDY_INT_SRC             0x0003
#define I2C_RX_INT_SRC                  0x0004
#define I2C_TX_INT_SRC                  0x0005
#define I2C_SCD_INT_SRC                0x0006
#define I2C_AAS_INT_SRC                0x0007

enum I2C_ID
{
    I2CA_ID = 0,
	I2CB_ID = 1,
	I2C_MAX_ID,
};

enum I2C_MODE
{
    I2C_MASTER  = 0,
	I2C_SLAVER,
};

enum I2C_BAUD
{
    I2C_BAUD_NON    = 0,
    I2C_BAUD_100K,
    I2C_BAUD_250K,
    I2C_BAUD_500K,
    I2C_BAUD_1000K,
    I2C_BAUD_2000K,
};

enum I2C_RX_FIFO_LEVEL
{
	I2C_FIFO_NON_WORD = 0,
    I2C_FIFO_1_WORD,
	I2C_FIFO_2_WORD,
	I2C_FIFO_3_WORD,
	I2C_FIFO_4_WORD,
	I2C_FIFO_5_WORD,
	I2C_FIFO_6_WORD,
	I2C_FIFO_7_WORD,
	I2C_FIFO_8_WORD,
	I2C_FIFO_9_WORD,
	I2C_FIFO_10_WORD,
	I2C_FIFO_11_WORD,
	I2C_FIFO_12_WORD,
	I2C_FIFO_13_WORD,
	I2C_FIFO_14_WORD,
	I2C_FIFO_15_WORD,
	I2C_FIFO_16_WORD,
	I2C_FIFO_MAX_WORD
};
typedef struct
{
    enum I2C_ID                 			emI2cId;
    enum I2C_MODE               			emI2cMode;
    //单位k; 如果是从机，忽略该项
    enum I2C_BAUD                 			emBaudRate;
    //地址字节，如果是主机，忽略该项
    unsigned char                     	    u8Addr;
    unsigned short                     		u16IntSrc;
    enum I2C_RX_FIFO_LEVEL      	        emFifoLevel;
}I2C_ITEM_CFG;

#define 		REG_I2C_ITEM_CFG_TAB    {\
	{I2CA_ID,     	I2C_SLAVER,			I2C_BAUD_NON,			0x68,         1,         I2C_FIFO_NON_WORD}\
}

extern void bsw_mcal_i2c_init(void);
extern void i2ca_reset(void);
extern void i2cb_reset(void);

#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_I2C_H_ */
