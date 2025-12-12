/*
 * DLL_Sci.c
 *
 *  Created on: 2022.8.16
 *      Author: Hongbo.Jiang
 */
#include "PUBLIC_INC/RING_ARRAY.H"
#include "DP_STACK/DLL/DLL_SCI.H"
#include"MCAL_INC/BSW_MCAL_SCI.h"
#include"DP_STACK/DP_STACK_BASIC.H"
#include "DP_STACK/DP_STACK_CFG.H"
#include"DP_STACK/DLL/DLL_STACK.h"


/*---- The extern valible declaration zoon ****/
extern const UINT8 crc_table[];                   // CRC table.

/**   SCI physic layer protocal  as flow ------------------------------------------------
  *   HEAD BYTE0 + HEAD BYTE1 + HEAD BYTE2 + 1 LEN BYTE  + N Data byte + 1 CRC BYTE -----
  *    0xAA          0x55        0xAA         (N + 1)       ...            ...
 ****************************************************************************************/

#if(DP_SCIA_ENABLE == 1)
UINT16  g_au16DllSciaRxMsgBuff[(DP_NWM_SIG_FRAME_RX_MAX_BYTE_LEN >> 1)] = {0};

REG_RING_ENTITY(SCIA_RING_TX, DLL_TX_RING_LEN)

//Forbid to be called in the interrupt functions
INT16 dll_scia_frame_write(void *p_vHalFrameInfo)
{
    UINT16  i = 0;
    UINT16  u16DataTemp = 0;
    UINT16  u16FrameTotalSizeBytes = 0;
    UINT16  *p_u16Data;
    //Later consider using the global variable.
    UINT16  u16ByteSize = 0, u16WordSize = 0;
    UINT8   u8CrcByte = 0;
    UINT8   u8DataTemp;
    FRAME_PROTOCOL_FORMAT *p_HalFrameInfo =(FRAME_PROTOCOL_FORMAT *)p_vHalFrameInfo;
    DLL_SCI_HEAD_DOMAIN stDllSciHead;
//    DLL_SCI_RAIL_DOMAIN stDllSciRail;
    stDllSciHead.unHeadWord0.u16all = 0x55AA;
    stDllSciHead.unHeadWord1.u16all = 0x55AA;
    stDllSciHead.u16DllDLC   = p_HalFrameInfo->stNwmDm.u16NwmDLC + sizeof(NWM_DOMAIN) * TYPE_8_BYTE_SIZE;

    u16ByteSize = (Get_Ring_Idel_Size(SCIA_RING_TX) << 1);

    u16FrameTotalSizeBytes = p_HalFrameInfo->stNwmDm.u16NwmDLC + sizeof(NWM_DOMAIN) * TYPE_8_BYTE_SIZE  \
                            + sizeof(DLL_SCI_HEAD_DOMAIN) * TYPE_8_BYTE_SIZE + sizeof(DLL_SCI_RAIL_DOMAIN) * TYPE_8_BYTE_SIZE;

    if(u16ByteSize < u16FrameTotalSizeBytes){
        //Check whether the SCIA hardware is working, if not, enable the scia send.
        return -1;
    }
    p_u16Data   = (UINT16 *)&stDllSciHead;

    u16WordSize = sizeof(DLL_SCI_HEAD_DOMAIN)/sizeof(UINT16);

    Load_Data_To_Ring(SCIA_RING_TX,p_u16Data,u16WordSize);

    for(i = 0; i < u16WordSize; i++){
        u16DataTemp = *p_u16Data++;
        u8DataTemp  = u16DataTemp & 0x00FF;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
        u8DataTemp  = u16DataTemp >> 8;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
    }

    p_u16Data   = (UINT16 *)p_HalFrameInfo;
    u16WordSize = (sizeof(FRAME_PROTOCOL_FORMAT) - sizeof(UINT16 *))/sizeof(UINT16);
    Load_Data_To_Ring(SCIA_RING_TX,p_u16Data,u16WordSize);
    for(i = 0; i < u16WordSize; i++){
        u16DataTemp = *p_u16Data++;
        u8DataTemp  = u16DataTemp & 0x00FF;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
        u8DataTemp  = u16DataTemp >> 8;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
    }

    u16WordSize = (p_HalFrameInfo->stAplDm.u16AplDLC >> 1);
    p_u16Data   = p_HalFrameInfo->p_u16AppData;
    Load_Data_To_Ring(SCIA_RING_TX,p_u16Data,u16WordSize);
    for(i = 0; i < u16WordSize; i++){
        u16DataTemp = *p_u16Data++;
        u8DataTemp  = u16DataTemp & 0x00FF;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
        u8DataTemp  = u16DataTemp >> 8;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
    }
  //  stDllSciRail.unCrc.u16all                   = (UINT16)u8CrcByte;
    Load_OneData_To_Ring(SCIA_RING_TX, 		u8CrcByte);
    return 1;
}

void scia_send_from_ring(void){
    UINT8        u8DataTemp;
    UINT8        i;
    INT16        i16TxDataNum;
    static 		UINT8 		s_u8WordTxStatus = 0;
    static 		UINT16 	s_u16DataTemp     = 0;

    //No matter the FIFO is enable, the SCI dll layer should be keep the same as soon as possible.
    for(i = 0; i< FIFO_8_WORD; i++){   //One task, the maximum send byte from ring to sci module is 8 bytes.
        if(s_u8WordTxStatus == 0){
            i16TxDataNum = Get_Data_From_Ring(SCIA_RING_TX, &s_u16DataTemp, 1);
            if(i16TxDataNum == 1) s_u8WordTxStatus = 1;
            else break;
        }
        if(s_u8WordTxStatus == 1){
            u8DataTemp = s_u16DataTemp & 0x00FF;
            if(Scia_Send_Byte(u8DataTemp) == 1)  s_u8WordTxStatus = 2;
            else break;

         }else{
                u8DataTemp = s_u16DataTemp >> 8;
                if(Scia_Send_Byte(u8DataTemp) == 1) s_u8WordTxStatus = 0;
                else break;
        }
    }
}

INT16 dll_scia_frame_read(UINT16 *p_u16Data)
{
    static enum DLL_RX_FMS s_enDllRxFsm = HEAD_BYTE0_FMS;
    static UINT16   s_u16DllByteDLC   = 0;
    static UINT16   s_u16DataCnt      = 0;
    static UINT8    s_u8CrcData       = 0;
    static UINT16   s_u16Data         = 0;
    UINT8 u8DataTemp  = 0;
    INT16 i16FrameReciveStatus = DLL_RX_NO_FRAME;
    while(SciaRegs.SCIFFRX.bit.RXFFST > 0){
        u8DataTemp = SciaRegs.SCIRXBUF.bit.SAR;
        switch(s_enDllRxFsm){
           case HEAD_BYTE0_FMS:
               s_u8CrcData    = 0;
               if(u8DataTemp == 0xAA)
            	   s_enDllRxFsm = HEAD_BYTE1_FMS;
           break;
           case HEAD_BYTE1_FMS:
               if(u8DataTemp == 0x55){
            	   s_enDllRxFsm = HEAD_BYTE2_FMS;
               }
               else if(u8DataTemp != 0xAA){
            	   s_enDllRxFsm = HEAD_BYTE0_FMS;
               }
           break;
           case HEAD_BYTE2_FMS:
               if(u8DataTemp == 0xAA)
            	   s_enDllRxFsm = HEAD_BYTE3_FMS;
               else
            	   s_enDllRxFsm = HEAD_BYTE0_FMS;
           break;
           case HEAD_BYTE3_FMS:
               if(u8DataTemp == 0x55)
            	   s_enDllRxFsm = DLC_BYTE0_FMS;
               else
            	   s_enDllRxFsm = HEAD_BYTE0_FMS;
               break;
           case DLC_BYTE0_FMS:
               s_u16DllByteDLC = u8DataTemp;
               s_enDllRxFsm = DLC_BYTE1_FMS;
           break;
           case DLC_BYTE1_FMS:
               s_u16DllByteDLC |= (u8DataTemp << 8);
               if(s_u16DllByteDLC > DP_NWM_SIG_FRAME_RX_MAX_BYTE_LEN)
            	   s_enDllRxFsm = HEAD_BYTE0_FMS;
               else
            	   s_enDllRxFsm = DATA_BYTE_FMS;
               s_u16DataCnt   = 0;
           break;
           case DATA_BYTE_FMS:
               if((s_u16DataCnt & 0x01) == 0){       //Low byte
                    s_u16Data = u8DataTemp;
               }else{                                //High  byte
                    s_u16Data |= ((UINT16)u8DataTemp << 8);
                    p_u16Data[s_u16DataCnt >> 1] = s_u16Data;
               }
               s_u16DataCnt++;
               if(s_u16DataCnt >= s_u16DllByteDLC)
            	   s_enDllRxFsm = CRC_CHECK_BYTE_FMS;
           break;
           case CRC_CHECK_BYTE_FMS:
               if(u8DataTemp == s_u8CrcData)
                   i16FrameReciveStatus = DLL_RX_FRAME_SUCCESS;
               s_enDllRxFsm = HEAD_BYTE0_FMS;
           break;
            default:break;
         }
        s_u8CrcData   = crc_table[s_u8CrcData ^ u8DataTemp];
        if(i16FrameReciveStatus == DLL_RX_FRAME_SUCCESS) //If one frame has been recived, we should return this function to call back the frame recive handle in NWM layer.
           break;
    }
    return i16FrameReciveStatus;
}
#endif

#if(DP_SCIB_ENABLE == 1)

UINT16  g_au16DllScibRxMsgBuff[(DP_NWM_SIG_FRAME_RX_MAX_BYTE_LEN >> 1)] = {0};

REG_RING_ENTITY(SCIB_RING_TX, DLL_TX_RING_LEN)

UINT16 g_u16Test = 0;
//Forbid to be called in the interrupt functions
INT16 dll_scib_frame_write(void *p_vHalFrameInfo)
{
    UINT16  i = 0;
    UINT16  u16DataTemp = 0;
    UINT16  u16FrameTotalSizeBytes = 0;
    UINT16  *p_u16Data;
    //Later consider using the global variable.
    UINT16  u16ByteSize = 0, u16WordSize = 0;
    UINT8   u8CrcByte = 0;
    UINT8   u8DataTemp;
    FRAME_PROTOCOL_FORMAT *p_HalFrameInfo =(FRAME_PROTOCOL_FORMAT *)p_vHalFrameInfo;
    DLL_SCI_HEAD_DOMAIN stDllSciHead;
    stDllSciHead.unHeadWord0.u16all = 0x55AA;
    stDllSciHead.unHeadWord1.u16all = 0x55AA;
    stDllSciHead.u16DllDLC   = p_HalFrameInfo->stNwmDm.u16NwmDLC + sizeof(NWM_DOMAIN) * TYPE_8_BYTE_SIZE;

    u16ByteSize = (Get_Ring_Idel_Size(SCIB_RING_TX) << 1);

    u16FrameTotalSizeBytes = stDllSciHead.u16DllDLC + sizeof(DLL_SCI_HEAD_DOMAIN) * TYPE_8_BYTE_SIZE + sizeof(DLL_SCI_RAIL_DOMAIN) * TYPE_8_BYTE_SIZE;

    if(u16ByteSize < u16FrameTotalSizeBytes){
        //Check whether the SCIB hardware is working, if not, enable the scib send.
        return -1;
    }
    if(u16FrameTotalSizeBytes == 504){
    	g_u16Test++;
    }
    p_u16Data   = (UINT16 *)&stDllSciHead;

    u16WordSize = sizeof(DLL_SCI_HEAD_DOMAIN)/sizeof(UINT16);

    Load_Data_To_Ring(SCIB_RING_TX,p_u16Data,u16WordSize);

    for(i = 0; i < u16WordSize; i++){
        u16DataTemp = *p_u16Data++;
        u8DataTemp  = u16DataTemp & 0x00FF;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
        u8DataTemp  = u16DataTemp >> 8;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
    }

    p_u16Data   = (UINT16 *)p_HalFrameInfo;
    u16WordSize = (sizeof(FRAME_PROTOCOL_FORMAT) - sizeof(UINT16 *))/sizeof(UINT16);
    Load_Data_To_Ring(SCIB_RING_TX,p_u16Data,u16WordSize);
    for(i = 0; i < u16WordSize; i++){
        u16DataTemp = *p_u16Data++;
        u8DataTemp  = u16DataTemp & 0x00FF;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
        u8DataTemp  = u16DataTemp >> 8;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
    }

    u16WordSize = (p_HalFrameInfo->stAplDm.u16AplDLC >> 1);
    p_u16Data   = p_HalFrameInfo->p_u16AppData;
    Load_Data_To_Ring(SCIB_RING_TX,p_u16Data,u16WordSize);
    for(i = 0; i < u16WordSize; i++){
        u16DataTemp = *p_u16Data++;
        u8DataTemp  = u16DataTemp & 0x00FF;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
        u8DataTemp  = u16DataTemp >> 8;
        u8CrcByte   = crc_table[u8CrcByte ^ u8DataTemp];
    }
  //  stDllSciRail.unCrc.u16all                   = (UINT16)u8CrcByte;
    Load_OneData_To_Ring(SCIB_RING_TX, 		u8CrcByte);

    return 1;
}

void scib_send_from_ring(void){
    UINT16       u16DataTemp;
    UINT8        i;
    INT16        i16TxDataNum;
    //No matter the FIFO is enable, the SCI dll layer should be keep the same as soon as possible.
#if(SCIB_FIFO_ENABLE == 1)
    UINT16       ua16DataBuff[16] = {0};
    if(ScibRegs.SCIFFTX.bit.TXFFST == 0){
        #if(PC_COMM_INF_MODULE == SCIB_MODULE)
    	 i16TxDataNum = Get_Data_From_Ring(SCIB_RING_TX, ua16DataBuff, (SCI_TO_PC_FIFO >> 1));
        #else
         i16TxDataNum = Get_Data_From_Ring(SCIB_RING_TX, ua16DataBuff, (SCI_TO_CTR_FIFO >> 1));
        #endif
        for(i = 0;i < i16TxDataNum; i++){
            u16DataTemp = ua16DataBuff[i];
            ScibRegs.SCITXBUF.all = u16DataTemp & 0x00FF;
            ScibRegs.SCITXBUF.all = u16DataTemp >> 8;
        }
    }
#else
    static UINT8 s_u8WordTxStatus = 0;
    static UINT16 s_u16DataTemp;
    for(i = 0; i< FIFO_8_WORD; i++){   //One task, the maximum send byte from ring to sci module is 8 bytes.
        if(s_u8WordTxStatus == 0){
            i16TxDataNum = Get_Data_From_Ring(SCIB_RING_TX, &s_u16DataTemp, 1);
            if(i16TxDataNum == 1) s_u8WordTxStatus = 1;
            else break;
        }
        if(s_u8WordTxStatus == 1){
            u8DataTemp = s_u16DataTemp & 0x00FF;
            if(Scib_Send_Byte(u8DataTemp) == 1)  s_u8WordTxStatus = 2;
            else break;

         }else{
                u8DataTemp = s_u16DataTemp >> 8;
                if(Scib_Send_Byte(u8DataTemp) == 1) s_u8WordTxStatus = 0;
                else break;
        }
    }
#endif
}

void scib_err_handler(void){
	static unsigned short s_u16SciErrCnt = 0;
	 if(ScibRegs.SCIRXST.all | (1 << RXERR_BIT ) | (1 << FE_BIT) | (1 << OE_BIT)  |  (1 << PE_BIT)){
		 s_u16SciErrCnt ++;
		 if(s_u16SciErrCnt > 5){
			 bsw_mcal_sci_init();
			 NOP;
			 NOP;
			 NOP;
			 NOP;
			 NOP;
			 NOP;
			 NOP;
			 NOP;
			 NOP;
			 NOP;
			 s_u16SciErrCnt = 0;
		//	 g_u16SciErrCnt++;
		 }
	 }
}
INT16 dll_scib_frame_read(UINT16 *p_u16Data)
{
	   static enum DLL_RX_FMS 	s_enDllRxFsm = HEAD_BYTE0_FMS;
	    static UINT16   s_u16DllByteDLC   = 0;
	    static UINT16   s_u16DataCnt      = 0;
	    static UINT8    s_u8CrcData       = 0;
	    static UINT16   s_u16Data         = 0;
	    UINT8 u8DataTemp  = 0;
	    INT16 i16FrameReciveStatus = DLL_RX_NO_FRAME;
	    while(ScibRegs.SCIFFRX.bit.RXFFST > 0){
	        u8DataTemp = ScibRegs.SCIRXBUF.bit.SAR;
	        switch(s_enDllRxFsm){
	           case HEAD_BYTE0_FMS:
	               s_u8CrcData    = 0;
	               if(u8DataTemp == 0xAA)
	            	   s_enDllRxFsm = HEAD_BYTE1_FMS;
	           break;
	           case HEAD_BYTE1_FMS:
	               if(u8DataTemp == 0x55){
	            	   s_enDllRxFsm = HEAD_BYTE2_FMS;
	               }
	               else if(u8DataTemp != 0xAA){
	            	   s_enDllRxFsm = HEAD_BYTE0_FMS;
	               }
	           break;
	           case HEAD_BYTE2_FMS:
	               if(u8DataTemp == 0xAA)
	            	   s_enDllRxFsm = HEAD_BYTE3_FMS;
	               else
	            	   s_enDllRxFsm = HEAD_BYTE0_FMS;
	           break;
	           case HEAD_BYTE3_FMS:
	               if(u8DataTemp == 0x55)
	            	   s_enDllRxFsm = DLC_BYTE0_FMS;
	               else
	            	   s_enDllRxFsm = HEAD_BYTE0_FMS;
	               break;
	           case DLC_BYTE0_FMS:
	               s_u16DllByteDLC = u8DataTemp;
	               s_enDllRxFsm = DLC_BYTE1_FMS;
	           break;
	           case DLC_BYTE1_FMS:
	               s_u16DllByteDLC |= (u8DataTemp << 8);
	               if(s_u16DllByteDLC > DP_NWM_SIG_FRAME_RX_MAX_BYTE_LEN)
	            	   s_enDllRxFsm = HEAD_BYTE0_FMS;
	               else
	            	   s_enDllRxFsm = DATA_BYTE_FMS;
	               s_u16DataCnt   = 0;
	           break;
	           case DATA_BYTE_FMS:
	               if((s_u16DataCnt & 0x01) == 0){       //Low byte
	                    s_u16Data = u8DataTemp;
	               }else{                                //High  byte
	                    s_u16Data |= ((UINT16)u8DataTemp << 8);
	                    p_u16Data[s_u16DataCnt >> 1] = s_u16Data;
	               }
	               s_u16DataCnt++;
	               if(s_u16DataCnt >= s_u16DllByteDLC)
	            	   s_enDllRxFsm = CRC_CHECK_BYTE_FMS;
	           break;
	           case CRC_CHECK_BYTE_FMS:
	               if(u8DataTemp == s_u8CrcData)
	                   i16FrameReciveStatus = DLL_RX_FRAME_SUCCESS;
	               s_enDllRxFsm = HEAD_BYTE0_FMS;
	           break;
	            default:break;
	         }
	        s_u8CrcData   = crc_table[s_u8CrcData ^ u8DataTemp];
	        if(i16FrameReciveStatus == DLL_RX_FRAME_SUCCESS) //If one frame has been recived, we should return this function to call back the frame recive handle in NWM layer.
	           break;
	    }
	    return i16FrameReciveStatus;
}

#endif

