/*
 * BSW_MCAL_SCI.c
 *
 *  Created on: 2022.07.25
 *      Author: Hongbo.jiang
 */
#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "../MCAL/BSW_MCAL_BASIC.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_SCI.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_SYS_CLOCK.h"

volatile struct SCI_REGS * const p_stSciModue[] = {&SciaRegs,&ScibRegs};

const static SCI_ITEM_CFG gc_stSciItemCfg[] = REG_SCI_ITEM_CFG_TAB;

float g_f32LspClkFreq;

void bsw_mcal_sci_init(void)
{
    UINT16 i = 0;
    const SCI_ITEM_CFG *p_stSciItemCfg = NULL;
    UINT16 u16BaudTemp;

    g_f32LspClkFreq = SYS_CLK_GetLpsClkFreq()*1000000.0f;

    for(i = 0; i < (sizeof(gc_stSciItemCfg)/sizeof(SCI_ITEM_CFG)); i++)
    {
        p_stSciItemCfg = &gc_stSciItemCfg[i];
        if(p_stSciItemCfg->emSciId > SCI_MAX_ID)
            continue;
        p_stSciModue[p_stSciItemCfg->emSciId]->SCICTL1.all						   = 0;
        if(p_stSciItemCfg->emSciParity == NONE_PARITY){
           p_stSciModue[p_stSciItemCfg->emSciId]->SCICCR.bit.PARITYENA = 0;
        }else{
           p_stSciModue[p_stSciItemCfg->emSciId]->SCICCR.bit.PARITY     =  (p_stSciItemCfg->emSciParity - 1);
           p_stSciModue[p_stSciItemCfg->emSciId]->SCICCR.bit.PARITYENA  = 1;
        }

        p_stSciModue[p_stSciItemCfg->emSciId]->SCICCR.bit.LOOPBKENA     	= 0;
        p_stSciModue[p_stSciItemCfg->emSciId]->SCICCR.bit.STOPBITS      		= p_stSciItemCfg->emSciStopBit;
        p_stSciModue[p_stSciItemCfg->emSciId]->SCICCR.bit.SCICHAR       		= 7;  //Default set 8 char bits
        switch(p_stSciItemCfg->emSciBaud){
            case BAUD_4800:
                u16BaudTemp  = (UINT16)((float)g_f32LspClkFreq/(8*4800.0f) - 1);
            break;
            case BAUD_9600:
                u16BaudTemp  = (UINT16)((float)g_f32LspClkFreq/(8*9600.0f) - 1);
            break;
            case BAUD_19200:
                u16BaudTemp  = (UINT16)((float)g_f32LspClkFreq/(8*19200.0f) - 1);
            break;
            case BAUD_38400:
                u16BaudTemp  = (UINT16)((float)g_f32LspClkFreq/(8*38400.0f) - 1);
            break;
            case BAUD_115200:
                u16BaudTemp  = (UINT16)((float)g_f32LspClkFreq/(8*115200.0f) - 1);
            break;
            default:
               continue;
        }
        p_stSciModue[p_stSciItemCfg->emSciId]->SCIHBAUD.all = (u16BaudTemp >> 8);
        p_stSciModue[p_stSciItemCfg->emSciId]->SCILBAUD.all = u16BaudTemp & 0x00ff;
        p_stSciModue[p_stSciItemCfg->emSciId]->SCICTL2.bit.TXINTENA = 0;   //Disable the tx interrupt
        if(p_stSciItemCfg->u16FifoEnable == 0){
            p_stSciModue[p_stSciItemCfg->emSciId]->SCICTL2.bit.RXBKINTENA = 1;
        }else{
            p_stSciModue[p_stSciItemCfg->emSciId]->SCIFFTX.bit.SCIFFENA = 1;        //Enable the FIFO;
            p_stSciModue[p_stSciItemCfg->emSciId]->SCIFFTX.bit.TXFFINT  = 0;        //Disable the TX FIFO interrupt
            p_stSciModue[p_stSciItemCfg->emSciId]->SCIFFTX.bit.TXFFIL   = 1;        //When the Tx FIFO data less than the 1 bytes, the flag will be set
            p_stSciModue[p_stSciItemCfg->emSciId]->SCIFFTX.bit.TXFIFORESET = 0;
            p_stSciModue[p_stSciItemCfg->emSciId]->SCIFFTX.bit.TXFIFORESET = 1;

            p_stSciModue[p_stSciItemCfg->emSciId]->SCIFFRX.bit.RXFFIL 				= p_stSciItemCfg->emFifoLevel;
            p_stSciModue[p_stSciItemCfg->emSciId]->SCIFFRX.bit.RXFFIENA 		= 1;
            p_stSciModue[p_stSciItemCfg->emSciId]->SCIFFRX.bit.RXFIFORESET 	= 0;     //Reset the RX FIFO
            p_stSciModue[p_stSciItemCfg->emSciId]->SCIFFRX.bit.RXFIFORESET 	= 1;     //Re-enable the RX FIFO
        }
        p_stSciModue[p_stSciItemCfg->emSciId]->SCICTL1.all = 0x0023;                // enable SCI
    }
}

UINT8 Get_Scia_Send_Aly_Send_FIFO(void)
{
  if(SciaRegs.SCIFFTX.bit.SCIFFENA == 0)
        return 0;
  return(FIFO_16_WORD - SciaRegs.SCIFFTX.bit.TXFFST);
}

INT8 Scia_Send_Byte(UINT8 u8Data){
    UINT16 u16TempData;
   if(SciaRegs.SCIFFTX.bit.SCIFFENA == 0){ //FIFO enable
       if(SciaRegs.SCICTL2.bit.TXRDY == 1) SciaRegs.SCITXBUF.all = u8Data;
       else return -1;

   }else{
       u16TempData = SciaRegs.SCIFFTX.bit.TXFFST;
       if(u16TempData < FIFO_16_WORD) SciaRegs.SCITXBUF.all = u8Data;
       else return -1;
   }
   return 1;
}

INT16 Scia_Send_Bytes_FIFO(UINT8 *p_u8SrcData, UINT16 u16Len)
{
    UINT16 u16TempData, i;
    if(SciaRegs.SCIFFTX.bit.SCIFFENA == 0)
        return -1;
    u16TempData = SciaRegs.SCIFFTX.bit.TXFFST;
    if((u16TempData + u16Len) > FIFO_16_WORD)
        return -1;
    /****The FIFO can load u16Len length data***/
    for(i = 0; i < u16Len; i++){
        SciaRegs.SCITXBUF.all = *p_u8SrcData++;
    }
    return 1;
}


UINT8 Get_Scib_Send_Aly_Send_FIFO(void)
{
  if(ScibRegs.SCIFFTX.bit.SCIFFENA == 0)
        return 0;
  return(FIFO_16_WORD - ScibRegs.SCIFFTX.bit.TXFFST);
}

INT8 Scib_Send_Byte(UINT8 u8Data){
    UINT16 u16TempData;
   if(ScibRegs.SCIFFTX.bit.SCIFFENA == 0){ //FIFO enable
       if(ScibRegs.SCICTL2.bit.TXRDY == 1) ScibRegs.SCITXBUF.all = u8Data;
       else return -1;

   }else{
       u16TempData = ScibRegs.SCIFFTX.bit.TXFFST;
       if(u16TempData < FIFO_16_WORD) ScibRegs.SCITXBUF.all = u8Data;
       else return -1;
   }
   return 1;
}

INT16 Scib_Send_Bytes_FIFO(UINT8 *p_u8SrcData, UINT16 u16Len)
{
    UINT16 u16TempData, i;
    if(ScibRegs.SCIFFTX.bit.SCIFFENA == 0)
        return -1;
    u16TempData = ScibRegs.SCIFFTX.bit.TXFFST;
    if((u16TempData + u16Len) > FIFO_16_WORD)
        return -1;
    /****The FIFO can load u16Len length data***/
    for(i = 0; i < u16Len; i++){
        ScibRegs.SCITXBUF.all = *p_u8SrcData++;
    }
    return 1;
}



