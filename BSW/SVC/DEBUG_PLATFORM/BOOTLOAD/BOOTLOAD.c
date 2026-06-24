/*
 * BOOTLOAD.c
 *
 *  Created on: 2022.11.28
 *      Author: xj8r1j
 */
#include "DP_STACK/DP_STACK_BASIC.H"
#include "SYS_FSM/SYS_FSM.h"
#include "DP_STACK/NWM/NWM_STACK.h"
#include "DP_STACK/TPL/TPL_STACK.h"
#include "DEBUG_PLATFORM/BOOTLOAD/BOOTLOAD.H"
#include "BOOT_PROCE/BOOT_PROCE.H"

UINT16   g_u16EnterAppFlag   = 0;
UINT16   g_u16EnterBootFlag  = 0;

//#pragma DATA_SECTION(gc_ua16AppVer,".APP_VER");

const unsigned char *gc_ua16AppVer = {"V2.00"};

const unsigned char  *gc_ua16BootVer = {"V1.00"};

extern void ExitBoot(UINT32 EntryAddr);

void send_enter_boot_status(void){
    FRAME_PROTOCOL_FORMAT                   stParamRstFrame = {0};
    stParamRstFrame.stAplDm.u16AplDLC                       = 0;
    stParamRstFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = 0x06;
    stParamRstFrame.stAplDm.unAplCmd.bits.uh8CmdId          = RESPONSE_ENTER_BOOT;
    stParamRstFrame.p_u16AppData                            = NULL;
    stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;

    Tpl_Single_Frame_Send(&stParamRstFrame);
}

void send_flash_erase_responsble(unsigned char u8FlashEraseFlag){
    FRAME_PROTOCOL_FORMAT                   stParamRstFrame = {0};
    unsigned short ua16RespBuff[1];
    stParamRstFrame.stAplDm.u16AplDLC                       = 2;
    stParamRstFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = 0x06;
    stParamRstFrame.stAplDm.unAplCmd.bits.uh8CmdId          = RESPONSE_FLASH_ERASE_CMD;
    ua16RespBuff[0]                                         = u8FlashEraseFlag;
    stParamRstFrame.p_u16AppData                            = ua16RespBuff;
    stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;

    Tpl_Single_Frame_Send(&stParamRstFrame);
}

void send_flash_program_responsble(unsigned char u8FlashProgramFlag){
    FRAME_PROTOCOL_FORMAT                   stParamRstFrame = {0};
    unsigned short ua16RespBuff[1];
    stParamRstFrame.stAplDm.u16AplDLC                       = 2;
    stParamRstFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = 0x06;
    stParamRstFrame.stAplDm.unAplCmd.bits.uh8CmdId          = RESPONSE_FLASH_PROGRAM_CMD;
    ua16RespBuff[0]                                         = u8FlashProgramFlag;
    stParamRstFrame.p_u16AppData                            = ua16RespBuff;
    stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;

    Tpl_Single_Frame_Send(&stParamRstFrame);
}

void send_flash_crc_check_responsble(unsigned char u8FlashCrcFlag){
    FRAME_PROTOCOL_FORMAT                   stParamRstFrame = {0};
    unsigned short ua16RespBuff[1];
    stParamRstFrame.stAplDm.u16AplDLC                       = 2;
    stParamRstFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = 0x06;
    stParamRstFrame.stAplDm.unAplCmd.bits.uh8CmdId          = RESPONSE_FLASH_CRC_CHECK_CMD;
    ua16RespBuff[0]                                         = u8FlashCrcFlag;
    stParamRstFrame.p_u16AppData                            = ua16RespBuff;
    stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;

    Tpl_Single_Frame_Send(&stParamRstFrame);
}



void bootload_cmd_set_link(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    static UINT8 u8CmdId = 0;
    FRAME_PROTOCOL_FORMAT   stParamRstFrame = {0};
    unsigned short u16AppTxDataBuff[4];
    unsigned long u32FlashStartAddr = 0;
    unsigned long u32FlashByteSize    = 0;
    unsigned long  *p_u32Addr;
    unsigned short *p_u16DataDestBuff;
    unsigned short *p_u16DataSrcAddr;
    unsigned short u16TempData, i;
    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;
    if (ENTER_APP_CMD == u8CmdId) {
        g_u16EnterAppFlag = 1;
    }else if (ENTER_BOOT_CMD == u8CmdId) {
        g_u16EnterBootFlag = 1;
        if(BOOT_UPDATA_STATUS == u16_get_sys_fsm_status()){
            send_enter_boot_status();
        }
    }else if(HANDSHAKE_CMD == u8CmdId){
        //Check the data length is coordinate with the APL protocol
        p_u32Addr   = (unsigned long *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT32);
        u32FlashStartAddr = *p_u32Addr++;
        u32FlashByteSize    = *p_u32Addr;
        stParamRstFrame.stAplDm.u16AplDLC                       = 2;
        stParamRstFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = p_stAplDm->unAplCmd.bits.ul8CmdSet;
        stParamRstFrame.stAplDm.unAplCmd.bits.uh8CmdId          = RESPONSE_HANDSHAKE_CMD;
        stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;
        stParamRstFrame.p_u16AppData                            = u16AppTxDataBuff;
        if((u32FlashStartAddr == APP_START_ADDR)&&(u32FlashByteSize == (APP_FLASH_WORD_SIZE << 1))){
            u16AppTxDataBuff[0] = 0x01;
        }else{
            u16AppTxDataBuff[0] = 0x00;
        }
        Tpl_Single_Frame_Send(&stParamRstFrame);
    }else if(FLASH_ERASE_CMD == u8CmdId){
        clr_flash_handle_flag();
        set_erase_flash_cmd();
   /* }else if(ASK_FLASH_HANDLE_CMD == u8CmdId){
        stParamRstFrame.stAplDm.u16AplDLC                       = 1;
        stParamRstFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = p_stAplDm->unAplCmd.bits.ul8CmdSet;
        stParamRstFrame.stAplDm.unAplCmd.bits.uh8CmdId          = RESPONSE_FLASH_HANDLE;
        stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;
        stParamRstFrame.p_u16AppData                            = u16AppTxDataBuff;
        u16AppTxDataBuff[0]                                     = get_flash_handle_status();
        Tpl_Single_Frame_Send(&stParamRstFrame);*/
    }else if(APP_VER_CMD == u8CmdId){
        stParamRstFrame.stAplDm.u16AplDLC                       = 6;
        stParamRstFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = p_stAplDm->unAplCmd.bits.ul8CmdSet;
        stParamRstFrame.stAplDm.unAplCmd.bits.uh8CmdId          = RESPON_APP_VER;
        stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;
        stParamRstFrame.p_u16AppData                            = u16AppTxDataBuff;
        u16AppTxDataBuff[0]                                     = gc_ua16AppVer[0] + (gc_ua16AppVer[1]<<8);
        u16AppTxDataBuff[1]                                     = gc_ua16AppVer[2] + (gc_ua16AppVer[3]<<8);
        u16AppTxDataBuff[2]                                     = gc_ua16AppVer[4] + (gc_ua16AppVer[5]<<8);
        Tpl_Single_Frame_Send(&stParamRstFrame);
    }else if(BOOT_VER_CMD == u8CmdId){
        stParamRstFrame.stAplDm.u16AplDLC                       = 6;
        stParamRstFrame.stAplDm.unAplCmd.bits.ul8CmdSet         = p_stAplDm->unAplCmd.bits.ul8CmdSet;
        stParamRstFrame.stAplDm.unAplCmd.bits.uh8CmdId          = RESPON_BOOT_VER;
        stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;
        stParamRstFrame.p_u16AppData                            = u16AppTxDataBuff;
        u16AppTxDataBuff[0]                                     = gc_ua16BootVer[0] + (gc_ua16BootVer[1]<<8);
        u16AppTxDataBuff[1]                                     = gc_ua16BootVer[2] + (gc_ua16BootVer[3]<<8);
        u16AppTxDataBuff[2]                                     = gc_ua16BootVer[4] + (gc_ua16BootVer[5]<<8);
        Tpl_Single_Frame_Send(&stParamRstFrame);
    }else if(FLASH_PROGRAM_CMD == u8CmdId){
        u16TempData = (p_stAplDm->u16AplDLC - 4) >> 1;
        set_flash_grogram_word_size(u16TempData);
        p_u32Addr   = (unsigned long *)p_stAplDm + sizeof(APL_DOMAIN)/sizeof(UINT32);
        set_flash_grogram_addr(*p_u32Addr++);
        p_u16DataDestBuff = get_flash_grogram_buff_addr();
        p_u16DataSrcAddr = (unsigned short *)p_u32Addr;
        for (i = 0; i < u16TempData; i++) {
            *p_u16DataDestBuff++ = *p_u16DataSrcAddr++;
        }
        clr_flash_handle_flag();
        set_program_flash_cmd();
    }else if(FLASH_CRC_CHECK_CMD == u8CmdId){
        set_program_crc_check_cmd();
    }
}
