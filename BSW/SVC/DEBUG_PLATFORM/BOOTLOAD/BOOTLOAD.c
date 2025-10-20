/*
 * BOOTLOAD.c
 *
 *  Created on: 2022.11.28
 *      Author: xj8r1j
 */
#include    "BSW_SVC_BASIC.h"
#include "DP_STACK/DP_STACK_BASIC.H"

UINT16 g_u16BootLoadFlg = 0;
UINT32 g_u32CLLCJumpBoot;

extern void ExitBoot(UINT32 EntryAddr);

void bootload_cmd_set_link(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    static UINT8 u8CmdId = 0;

    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;
    if (u8CmdId == 0x01) {
        g_u16BootLoadFlg = 1;
    } else if (u8CmdId == 0x02) {
        g_u32CLLCJumpBoot = 0xA3A4A1A2;
        ExitBoot(0x80000);
    }
}
