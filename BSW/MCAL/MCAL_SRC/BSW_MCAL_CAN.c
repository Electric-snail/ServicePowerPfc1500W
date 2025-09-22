/*
 * BSW_MCAL_CAN.c
 *
 *  Created on: 2022.8.17
 *      Author: Jiang,hongbo
 */
#include <PUBLIC_INC/MEM_HANDLE.H>
#include "CHIP_PACK/driverlib/inc/hw_types.h"
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#include "ENV_CFG/HARDWARE_ENV_CFG.h"
#include "MCAL_INC/BSW_MCAL_CAN_HW.h"
#include "MCAL_INC/BSW_MCAL_CAN.h"

#ifndef DLLX64
#include "MCAL_INC/BSW_MCAL_SYS_CLOCK.h"

volatile struct CAN_REGS *p_stCanModue[] = {&CanaRegs};

static CAN_ITEM_CFG const  gc_stCanItemCfg[]   = REG_CAN_ITEM_CFG_TAB;

static CAN_MSG_OBJ_CFG const gc_stCanaObjCfg[] = REG_CANA_MSG_OBJ_CFG_TAB;

//*****************************************************************************
//
// CAN_setBitTiming
//
//*****************************************************************************
void CAN_setBitTiming(UINT32 base, UINT16 prescaler,
                 UINT16 prescalerExtension, UINT16 tSeg1, UINT16 tSeg2,
                 UINT16 sjw)
{
    UINT16 savedInit;
    UINT32 bitReg;

    // Check the arguments.
    if(prescaler >= 64U) return;

    if((tSeg1 == 0U) || (tSeg1 >= 16U)) return;

    if(tSeg2 >= 8U) return;

    if(sjw >= 4U) return;

    if(prescalerExtension >= 16U) return;

    // To set the bit timing register, the controller must be placed in init
    // mode (if not already), and also configuration change bit enabled.
    // State of the init bit should be saved so it can be restored at the end.
    //
    savedInit = HWREGH(base + CAN_O_CTL);
    HWREGH(base + CAN_O_CTL) = savedInit | CAN_CTL_INIT | CAN_CTL_CCE;

    //
    // Set the bit fields of the bit timing register
    //
    bitReg = (UINT32)((UINT32)prescaler & CAN_BTR_BRP_M);
    bitReg |= (UINT32)(((UINT32)sjw << CAN_BTR_SJW_S) & CAN_BTR_SJW_M);
    bitReg |= (UINT32)(((UINT32)tSeg1 << CAN_BTR_TSEG1_S) &
                         CAN_BTR_TSEG1_M);
    bitReg |= (UINT32)(((UINT32)tSeg2 << CAN_BTR_TSEG2_S) &
                         CAN_BTR_TSEG2_M);
    bitReg |= (UINT32)(((UINT32)prescalerExtension << CAN_BTR_BRPE_S) &
                         CAN_BTR_BRPE_M);

    HWREG_BP(base + CAN_O_BTR) = bitReg;

    //
    // Clear the config change bit, and restore the init bit.
    //
    savedInit &= ~((UINT16)CAN_CTL_CCE);

    //
    // If Init was not set before, then clear it.
    //
    if((savedInit & CAN_CTL_INIT) == CAN_CTL_INIT)
    {
        savedInit &= ~((UINT16)CAN_CTL_INIT);
    }
    HWREGH(base + CAN_O_CTL) = savedInit;
}

//*****************************************************************************
//
// CAN_setBitRate
//
//*****************************************************************************
//bitTime means one baud bit include how many clock of CAN Clock after bit rate prescale
void CAN_setBitRate(UINT32 base, UINT32 clock, UINT32 bitRate,
               UINT16 bitTime)
{
    UINT16 brp;
    UINT16 tPhase;
    UINT16 phaseSeg2;
    UINT16 tSync = 1U;
    UINT16 tProp = 2U;
    UINT16 tSeg1;
    UINT16 tSeg2;
    UINT16 sjw;
    UINT16 prescaler;
    UINT16 prescalerExtension;

    // Check the arguments.
    if(base != (UINT32)&CanaRegs)
        return;
    if((bitTime <= 7U) || (bitTime >= 26U))
        return;
    if(bitRate > 1000000U)
        return;
    // Calculate bit timing values
    //
    brp = (UINT16)(clock / (bitRate * bitTime));
    tPhase = bitTime - (tSync + tProp);
    if((tPhase / 2U) <= 8U)
    {
        phaseSeg2 = tPhase / 2U;
    }
    else
    {
        phaseSeg2 = 8U;
    }
    tSeg1 = ((tPhase - phaseSeg2) + tProp) - 1U;
    tSeg2 = phaseSeg2 - 1U;
    if(phaseSeg2 > 4U)
    {
        sjw = 3U;
    }
    else
    {
        sjw = tSeg2;
    }
    prescalerExtension = ((brp - 1U) / 64U);
    prescaler = ((brp - 1U) % 64U);

    //
    // Set the calculated timing parameters
    //
    CAN_setBitTiming(base, prescaler, prescalerExtension, tSeg1, tSeg2, sjw);
}

//*****************************************************************************
//
// CAN_setupMessageObject
//
//*****************************************************************************
void CAN_setupMessageObject(UINT32 base,                  UINT32 objID,         UINT32 msgID,  \
                            enum CAN_FRAME_TYPE  frame,   enum CAN_MSG_OBJ_TYPE     msgType,   \
                            UINT32 msgIDMask,             UINT32 flags,         UINT16 msgLen)
{
    UINT32 cmdMaskReg = 0U;
    UINT32 maskReg = 0U;
    UINT32 arbReg = 0U;
    UINT32 msgCtrl = 0U;

    // Check the arguments.
    // Wait for busy bit to clear
    while((HWREGH(base + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) == CAN_IF1CMD_BUSY);
    switch(msgType){
        // Transmit message object.
        case MSG_OBJ_TYPE_TX:{
            // Set message direction to transmit.
            arbReg = CAN_IF1ARB_DIR;
            break;
        }
        // Remote frame receive remote, with auto-transmit message object.
        case MSG_OBJ_TYPE_RXTX_REMOTE:{
            // Set message direction to Tx for remote receivers.
            arbReg = CAN_IF1ARB_DIR;
            // Set this object to auto answer if a matching identifier is seen.
            msgCtrl = (UINT32)((UINT32)CAN_IF1MCTL_RMTEN |
                                 (UINT32)CAN_IF1MCTL_UMASK);
            break;
        }
        // Transmit remote request message object (CAN_MSG_OBJ_TYPE_TX_REMOTE)
        // or Receive message object (CAN_MSG_OBJ_TYPE_RX).
        default:{
           // Set message direction to read.
           arbReg = 0U;
           break;
        }
    }

    // Set values based on Extended Frame or Standard Frame
    if(frame == MSG_FRAME_EXT){
        // Configure the Mask Registers for 29 bit Identifier mask.
        if((flags & CAN_MSG_OBJ_USE_ID_FILTER) == CAN_MSG_OBJ_USE_ID_FILTER){
            maskReg = msgIDMask & CAN_IF1MSK_MSK_M;
        }
        // Set the 29 bit version of the Identifier for this message
        // object. Mark the message as valid and set the extended ID bit.
        arbReg |= (msgID & CAN_IF1ARB_ID_M) | CAN_IF1ARB_MSGVAL |           \
                  CAN_IF1ARB_XTD;
    }
    else{
        // Configure the Mask Registers for 11 bit Identifier mask.
        if((flags & CAN_MSG_OBJ_USE_ID_FILTER) == CAN_MSG_OBJ_USE_ID_FILTER){
           maskReg = ((msgIDMask << CAN_IF1ARB_STD_ID_S) &
                      CAN_IF1ARB_STD_ID_M);
        }
        // Set the 11 bit version of the Identifier for this message
        // object. The lower 18 bits are set to zero. Mark the message as valid.
        arbReg |= ((msgID << CAN_IF1ARB_STD_ID_S) & CAN_IF1ARB_STD_ID_M) |
                  CAN_IF1ARB_MSGVAL;
    }
    // If the caller wants to filter on the extended ID bit then set it.
    maskReg |= (flags & CAN_MSG_OBJ_USE_EXT_FILTER);
    // The caller wants to filter on the message direction field.
    maskReg |= (flags & CAN_MSG_OBJ_USE_DIR_FILTER);
    // If any filtering is requested, set the UMASK bit to use mask register
    if(((flags & CAN_MSG_OBJ_USE_ID_FILTER) |               \
        (flags & CAN_MSG_OBJ_USE_DIR_FILTER) |              \
        (flags & CAN_MSG_OBJ_USE_EXT_FILTER)) != 0U){
        msgCtrl |= CAN_IF1MCTL_UMASK;
    }
    // msgCtrl |= CAN_IF1MCTL_UMASK;
    // Set the data length for the transfers.
    // This is applicable for Tx mailboxes.
    msgCtrl |= ((UINT32)msgLen & CAN_IF1MCTL_DLC_M);
    // If this is a single transfer or the last mailbox of a FIFO, set EOB bit.
    // If this is not the last entry in a FIFO, leave the EOB bit as 0.
    if((flags & CAN_MSG_OBJ_FIFO) == 0U){
        msgCtrl |= CAN_IF1MCTL_EOB;
    }
    // Enable transmit interrupts if they should be enabled.
    msgCtrl |= (flags & CAN_MSG_OBJ_TX_INT_ENABLE);
    // Enable receive interrupts if they should be enabled.
    msgCtrl |= (flags & CAN_MSG_OBJ_RX_INT_ENABLE);
    // Set the Control, Arb, and Mask bit so that they get transferred to the Message object.
    cmdMaskReg |= CAN_IF1CMD_ARB;
    cmdMaskReg |= CAN_IF1CMD_CONTROL;
    cmdMaskReg |= CAN_IF1CMD_MASK;
    cmdMaskReg |= CAN_IF1CMD_DIR;
    // Write out the registers to program the message object.
    HWREG_BP(base + CAN_O_IF1MSK) = maskReg;
    HWREG_BP(base + CAN_O_IF1ARB) = arbReg;
    HWREG_BP(base + CAN_O_IF1MCTL) = msgCtrl;
    // Transfer data to message object RAM
    HWREG_BP(base + CAN_O_IF1CMD) = cmdMaskReg | (objID & CAN_IF1CMD_MSG_NUM_M);
}

void BSW_MCAL_CanInit(void){
    UINT32  u32BasicAddr    = 0;
    UINT16  u16Delay        = 0;
    UINT32  u32Baurd        = 0;
    UINT8   i = 0, j        = 0;
    UINT32  u32SysClk       = 0;
    UINT8   u8ObjId         = 0;
    UINT32  u32MskId        = 0;
    UINT32  u32AbrId        = 0;
    UINT32  u32Flg          = 0;
    UINT32  u32IntEna        = 0;
    enum    CAN_MODULE_ID      emCANId;
    enum    CAN_FRAME_TYPE     emFrameType;
    enum    CAN_MSG_OBJ_TYPE   emMsgType;
    for(i = 0; i < sizeof(gc_stCanItemCfg)/sizeof(CAN_ITEM_CFG); i++){
          emCANId = gc_stCanItemCfg[i].emCanMoudleId;
          if(emCANId >= CAN_MODULE_MAX_ID)
              continue;
          u32BasicAddr = (UINT32)p_stCanModue[emCANId];
          HWREGH(u32BasicAddr + CAN_O_CTL) |= ((UINT16)CAN_CTL_INIT |       \
                                       (UINT16)CAN_INIT_PARITY_DISABLE);

          HWREGH(u32BasicAddr + CAN_O_RAM_INIT) = CAN_RAM_INIT_CAN_RAM_INIT |
                                            CAN_RAM_INIT_KEY;

           while(!((HWREGH(u32BasicAddr + CAN_O_RAM_INIT) & CAN_RAM_INIT_MASK) ==   \
                    (CAN_RAM_INIT_RAM_INIT_DONE | CAN_RAM_INIT_KEY2 |       \
                     CAN_RAM_INIT_KEY0)));
            // Force module to reset state
            HWREGH(u32BasicAddr + CAN_O_CTL) |=  CAN_CTL_SWR;
            HWREGH(u32BasicAddr + CAN_O_CTL) |= CAN_CTL_ABO;
            // Delay for 14 cycles
            u16Delay = 100;
            while (u16Delay--);
            //
            // Enable write access to the configuration registers
            HWREGH(u32BasicAddr + CAN_O_CTL) |= CAN_CTL_CCE;

            if(gc_stCanItemCfg[i].emCanBaud == BAUD_1000000)
                u32Baurd = 1000000;
            else if(gc_stCanItemCfg[i].emCanBaud == BAUD_800000)
                u32Baurd = 800000;
            else if(gc_stCanItemCfg[i].emCanBaud == BAUD_500000)
                u32Baurd = 500000;
            else if(gc_stCanItemCfg[i].emCanBaud == BAUD_250000)
                u32Baurd = 250000;
            else
                u32Baurd = 1;

            u32SysClk = SYS_CLK_GetSysClkFreq() * 1000000.0f;  //From M -> Hz

            CAN_setBitRate(u32BasicAddr, u32SysClk, u32Baurd, 20);

            //Enable the Interrupt Line0,  Interrupt error, interrupt status.
            HWREG_BP(u32BasicAddr + CAN_O_CTL) |= (CAN_INT_IE0 | CAN_INT_ERROR);

            if(gc_stCanItemCfg[i].emCanMoudleId     == CANA_MODULE_ID){
                for(j = 0; j < sizeof(gc_stCanaObjCfg)/sizeof(CAN_MSG_OBJ_CFG); j ++){
                    u8ObjId     = gc_stCanaObjCfg[j].emCanObjId;
                    u32MskId    = gc_stCanaObjCfg[j].u32MskId;
                    u32AbrId    = gc_stCanaObjCfg[j].u32MsgId;
                    emFrameType = gc_stCanaObjCfg[j].emCanExtSdType;
                    emMsgType   = gc_stCanaObjCfg[j].emCanTxRxType;
                    if(gc_stCanaObjCfg[j].u8RxIntEna == 1){
                        u32Flg |= CAN_MSG_OBJ_RX_INT_ENABLE;
                        u32IntEna = 0x00000001;
                    }
                    if(gc_stCanaObjCfg[j].u8TxIntEna == 1){
                        u32Flg |= CAN_MSG_OBJ_TX_INT_ENABLE;
                        u32IntEna = 0x00000001;
                    }
                    if(gc_stCanaObjCfg[j].emCanMaskEna == ENA_MASK)
                        u32Flg |= CAN_MSG_OBJ_USE_ID_FILTER;
                    //Don't use the FIFO
                    u32Flg &=~(CAN_MSG_OBJ_FIFO);

                    CAN_setupMessageObject(u32BasicAddr, u8ObjId, u32AbrId,\
                                           emFrameType, emMsgType,\
                                           u32MskId,    u32Flg, 8);
                }
            }
            else
            {
                // do nothing
            }
            HWREG_BP(u32BasicAddr + CAN_O_GLB_INT_CLR) = 0x00000003; //Clear global all error

            HWREG_BP(u32BasicAddr + CAN_O_GLB_INT_EN) |= u32IntEna;
            //Start the CAN module.
            HWREGH(u32BasicAddr + CAN_O_CTL) &= ~(CAN_CTL_INIT | CAN_CTL_CCE);
    }
}
//*****************************************************************************
//
// CAN_sendMessage
//
//*****************************************************************************
INT16 CANA_Send_Message_ChageId(CAN_MSG_OBJ_T *p_sTCANMsgObj, enum CAN_OBJ_ID emObjId)
{
    UINT32 u32MsgCtrl       = 0UL;
    UINT32 u32TempData      = 0UL;
    UINT32 u32ArbData       = 0UL;
    UINT32 u32DataAddr      = (UINT32)NULL;
    UINT8  i = 0;
    if(emObjId > OBJ_ID_MAX)        return -1;
    if(p_sTCANMsgObj->u8DLC > 8)    return -1;

    CanaRegs.CAN_IF1CMD.all       = (CAN_IF1CMD_CONTROL | emObjId); //Read data from emObjId to interface register sets

    while(CanaRegs.CAN_IF1CMD.bit.Busy == CAN_IF1CMD_BUSY);

    if(p_sTCANMsgObj ->u32Id & 0x80000000)  //Extend frame
    {
        u32ArbData = p_sTCANMsgObj ->u32Id & 0x1FFFFFFF; //get the extend id
        u32ArbData |= (1UL << 31) | ( 1UL << 30) |(1UL << 29);
    }else{
        u32ArbData = (p_sTCANMsgObj ->u32Id & 0x7FF) << 18; //get the stand id
        u32ArbData |= (1UL << 31) | (1UL << 29);
    }

    CanaRegs.CAN_IF1ARB.all = u32ArbData;   //Set the Id;

    u32MsgCtrl = CanaRegs.CAN_IF1MCTL.all; //Read the ctrl register and set dlc is 0XFF

    if(u32MsgCtrl & CAN_IF1MCTL_NEWDAT)
        return -1;

    u32MsgCtrl &= (~CAN_IF1MCTL_NEWDAT)&(~CAN_IF1MCTL_MSGLST)&(~CAN_IF1MCTL_INTPND)&(~CAN_IF1MCTL_DLC_M);                 //NewData = 0,

    u32MsgCtrl |= p_sTCANMsgObj->u8DLC;

    CanaRegs.CAN_IF1MCTL.all = u32MsgCtrl;

    u32DataAddr = (UINT32)&CanaRegs.CAN_IF1DATA.all;

    for(i = 0; i < p_sTCANMsgObj->u8DLC; i++){
         HWREGB(u32DataAddr) = p_sTCANMsgObj->u8data[i];
         u32DataAddr ++;
    }

    u32TempData = (UINT32)CAN_IF1CMD_DATA_B | (UINT32)CAN_IF1CMD_DATA_A | (UINT32)CAN_IF1CMD_CONTROL |(UINT32)CAN_IF1CMD_ARB \
            | (UINT32)CAN_IF1CMD_DIR | (UINT32)CAN_IF1CMD_TXRQST | (UINT32)emObjId;

    CanaRegs.CAN_IF1CMD.all = u32TempData;

    return 1;
}


INT16 CANA_Send_Message_UnChageId(CAN_MSG_OBJ_T *p_sTCANMsgObj, enum CAN_OBJ_ID emObjId)
{
    UINT32 u32MsgCtrl   = 0UL;
    UINT32 u32TempData  = 0UL;
    UINT32 u32DataAddr  = (UINT32)NULL;
    UINT8  i = 0;
    if(emObjId > OBJ_ID_MAX)        return -1;
    if(p_sTCANMsgObj->u8DLC > 8)    return -1;

    CanaRegs.CAN_IF1CMD.all       = (CAN_IF1CMD_CONTROL | emObjId); //Read data from emObjId to interface register sets

    while(CanaRegs.CAN_IF1CMD.bit.Busy == CAN_IF1CMD_BUSY);

    u32MsgCtrl = CanaRegs.CAN_IF1MCTL.all; //Read the ctrl register and set dlc is 0XFF

    if(u32MsgCtrl & CAN_IF1MCTL_NEWDAT)
        return -1;

    u32MsgCtrl &= (~CAN_IF1MCTL_NEWDAT)&(~CAN_IF1MCTL_MSGLST)&(~CAN_IF1MCTL_INTPND)&(~CAN_IF1MCTL_DLC_M);                 //NewData = 0,

    u32MsgCtrl |= p_sTCANMsgObj->u8DLC;

    CanaRegs.CAN_IF1MCTL.all = u32MsgCtrl;

    u32DataAddr = (UINT32)&CanaRegs.CAN_IF1DATA.all;

    for(i = 0; i < p_sTCANMsgObj->u8DLC; i++){
         HWREGB(u32DataAddr) = p_sTCANMsgObj->u8data[i];
         u32DataAddr ++;
    }

    u32TempData = (UINT32)CAN_IF1CMD_DATA_B | (UINT32)CAN_IF1CMD_DATA_A | (UINT32)CAN_IF1CMD_CONTROL \
            | (UINT32)CAN_IF1CMD_DIR | (UINT32)CAN_IF1CMD_TXRQST | (UINT32)emObjId;

    CanaRegs.CAN_IF1CMD.all = u32TempData;
    return 1;
}




INT16 CANA_Is_Message_Sent(enum CAN_OBJ_ID emObjId)
{
    UINT32 u32MsgCtrl   = 0UL;
    CanaRegs.CAN_IF1CMD.all       = (CAN_IF1CMD_CONTROL | emObjId); //Read data from emObjId to interface register sets

    while(CanaRegs.CAN_IF1CMD.bit.Busy == CAN_IF1CMD_BUSY);

    u32MsgCtrl = CanaRegs.CAN_IF1MCTL.all; //Read the ctrl register and set dlc is 0XFF

    if(u32MsgCtrl & CAN_IF1MCTL_NEWDAT)
        return 0;
    else
        return 1;
}

#pragma CODE_SECTION(CANAMessageGet, ".TI.ramfunc");
unsigned char CANAMessageGet(CAN_MSG_OBJ_T *p_stMsgObj, enum CAN_OBJ_ID emObjId)
{
    UINT32 ui32CmdMaskReg;
    UINT32 ui32ArbReg;
    UINT32 ui32MsgCtrl;
    UINT8  i = 0;
    UINT32 ui32Base = (UINT32)&CanaRegs;
    // This is always a read to the Message object as this call is setting a
    // message object.
    ui32CmdMaskReg = (CAN_IF2CMD_DATA_A | CAN_IF2CMD_DATA_B |CAN_IF2CMD_CONTROL | CAN_IF2CMD_MASK | \
                       CAN_IF2CMD_ARB | CAN_IF2CMD_CLRINTPND | CAN_IF2CMD_TXRQST);

    // Set up the request for data from the message object.
    HWREGH(ui32Base + CAN_O_IF2CMD + 2) =  ui32CmdMaskReg >> 16;

    // Transfer the message object to the message object specified by ui32ObjID.
    HWREGH(ui32Base + CAN_O_IF2CMD) = emObjId & CAN_IF2CMD_MSG_NUM_M;

    // Wait for busy bit to clear
    while(HWREGH(ui32Base + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY)
    {
    }

    // Read out the IF Registers.
    ui32ArbReg  = HWREG(ui32Base + CAN_O_IF2ARB);
    ui32MsgCtrl = HWREG(ui32Base + CAN_O_IF2MCTL);

    p_stMsgObj->u32Flg = 0x00000000;

    // Determine if this is a remote frame by checking the TXRQST and DIR bits.
    if((!(ui32MsgCtrl & CAN_IF2MCTL_TXRQST) && (ui32ArbReg & CAN_IF2ARB_DIR)) ||
       ((ui32MsgCtrl & CAN_IF2MCTL_TXRQST) && (!(ui32ArbReg & CAN_IF2ARB_DIR))))
    {
        p_stMsgObj->u32Flg |= MSG_OBJ_REMOTE_FRAME;
    }

    // Get the identifier out of the register, the format depends on size of
    // the mask.
    if(ui32ArbReg & CAN_IF2ARB_XTD){
        // Set the 29 bit version of the Identifier for this message object.
        p_stMsgObj->u32Id = ui32ArbReg & 0x1FFFFFFF;

        p_stMsgObj->u32Flg |= MSG_OBJ_EXTENDED_ID;
    }
    else{
        // The Identifier is an 11 bit value.
        p_stMsgObj->u32Id = (ui32ArbReg & CAN_IF2ARB_STD_ID_M) >> 18;
    }

    // See if there is new data available.
    if(ui32MsgCtrl & CAN_IF2MCTL_NEWDAT)
    {
        // Get the amount of data needed to be read.
        p_stMsgObj->u8DLC = (ui32MsgCtrl & CAN_IF2MCTL_DLC_M);

        // Don't read any data for a remote frame, there is nothing valid in
        // that buffer anyway.
        if((p_stMsgObj->u32Flg & MSG_OBJ_REMOTE_FRAME) == 0)
        {
            // Read out the data from the CAN registers.
            for(i = 0; i < p_stMsgObj->u8DLC; i++)
               p_stMsgObj->u8data[i] =  HWREGB(ui32Base + CAN_O_IF2DATA + i);
        }
        // Now clear out the new data flag.
        HWREGH(ui32Base + CAN_O_IF2CMD + 2) = CAN_IF2CMD_TXRQST >> 16;
        // Transfer the message object to the message object specified by
        // ui32ObjID.
        HWREGH(ui32Base + CAN_O_IF2CMD) = emObjId & CAN_IF2CMD_MSG_NUM_M;
        // Wait for busy bit to clear
        while(HWREGH(ui32Base + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY)
        {
        }
    }
    else
    {
        // Along with the MSG_OBJ_NEW_DATA not being set the amount of data
        // needs to be set to zero if none was available.
        p_stMsgObj->u8DLC = 0;
        return 0;
    }
    return 1;
}
#else

CAN_MSG_OBJ_T  g_stCanMsgTxTest[] =       { {0x20A, 0, 0, {0,0,0,0,0,0,0,0}},   {0x30A, 0, 0, {0,0,0,0,0,0,0,0}},  {0x31A, 0, 0, {0,0,0,0,0,0,0,0}},\
                                            {0x210, 0, 0, {0,0,0,0,0,0,0,0}},   {0x211, 0, 0, {0,0,0,0,0,0,0,0}},  {0x212, 0, 0, {0,0,0,0,0,0,0,0}}, \
                                            {0x212, 0, 0, {0,0,0,0,0,0,0,0}},   {0x213, 0, 0, {0,0,0,0,0,0,0,0}},  {0x214, 0, 0, {0,0,0,0,0,0,0,0} },
                                            {0x215, 0, 0, {0,0,0,0,0,0,0,0} },  {0x216, 0, 0, {0,0,0,0,0,0,0,0}}\
                                          };


CAN_MSG_OBJ_T   g_stCanMsgRxTest;

unsigned short g_u16MsgRxFlag;

INT16 CANA_Send_Message_ChageId(CAN_MSG_OBJ_T* p_sTCANMsgObj, unsigned short emObjId)
{
    unsigned char u8Index;
    for (u8Index = 0; u8Index < sizeof(g_stCanMsgTxTest) / sizeof(CAN_MSG_OBJ_T); u8Index++) {
        if (g_stCanMsgTxTest[u8Index].u32Id == p_sTCANMsgObj->u32Id)
        {
            memcpy_user((unsigned short*)g_stCanMsgTxTest[u8Index].u8data, (unsigned short*)p_sTCANMsgObj->u8data, p_sTCANMsgObj->u8DLC);
            return 1;
        }
    }
    return 0;
}

unsigned char CANAMessageGet(CAN_MSG_OBJ_T* p_sTCANMsgObj, unsigned short u16CanObjId) {
    unsigned i = 0;
    if (1 == g_u16MsgRxFlag) {
        g_u16MsgRxFlag = 0;
        p_sTCANMsgObj->u32Id = g_stCanMsgRxTest.u32Id;
        if (g_stCanMsgRxTest.u8DLC > 8)
            return 0;
        p_sTCANMsgObj->u8DLC = g_stCanMsgRxTest.u8DLC;
        for (i = 0; i < g_stCanMsgRxTest.u8DLC; i++) {
            memcpy_user((unsigned short*)p_sTCANMsgObj->u8data, (unsigned short*)g_stCanMsgRxTest.u8data, g_stCanMsgRxTest.u8DLC);
            return 1;
        }
    }
    return 0;
}

#endif
