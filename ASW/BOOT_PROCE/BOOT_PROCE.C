/*
 * BOOT_PROCE.C
 *
 *  Created on: 2026.5.29
 *      Author: Hongbo.Jiang
 */

#include "MCAL_INC/BSW_MCAL_FLASH.H"
#include "BOOT_PROCE/BOOT_PROCE.H"
#include "DEBUG_PLATFORM/BOOTLOAD/BOOTLOAD.h"
#include "PUBLIC_INC/CRC_TAB.H"
FLASH_PROGRAM_T g_stFlashProgram;
unsigned short g_ua16BootBuff[FLASH_SECTOR_SIZE];

void boot_proce_init(void){
    g_stFlashProgram.emFlashStatus          = FLASH_INIT_STATUS;
    g_stFlashProgram.emFlashHandleFlag      = FLASH_NOT_DONE;
    g_stFlashProgram.p_u16FlashDataBuff     = g_ua16BootBuff;
    g_stFlashProgram.u16FlashCmd            = FLASH_IDEL;
    g_stFlashProgram.u32FlashProAddr        = 0x00000000;
}
void boot_proce(void){
    static unsigned long        s_u32BootFlashAddr = 0;
    static unsigned short       s_u16TimeOutCnt    = 0;
    unsigned long u32CrcResult = 0;
    unsigned short *p_u16Data;
    unsigned long *p_u32Data;
    switch(g_stFlashProgram.emFlashStatus){
        case FLASH_INIT_STATUS:{
            if(1 == bsw_mcal_flash_fsm_init()){
                g_stFlashProgram.emFlashStatus = FLASH_IDEL_STATUS;
            }
        }break;
        case FLASH_IDEL_STATUS:{
            if(g_stFlashProgram.u16FlashCmd == FLASH_ERASE){
                g_stFlashProgram.emFlashStatus = FLASH_ERASE_STATUS;

            }else if(g_stFlashProgram.u16FlashCmd == FLASH_PROGRAM){
                if(g_stFlashProgram.u32FlashProAddr == APP_START_ADDR){
                    g_stFlashProgram.emFlashStatus    = FLASH_PROGRAM_STATUS;
                    s_u32BootFlashAddr               = g_stFlashProgram.u32FlashProAddr;
                }else{
                    g_stFlashProgram.emFlashHandleFlag = FLASH_ADDR_ERR;
                    g_stFlashProgram.u16FlashCmd       = FLASH_IDEL;
                }
            }
        }break;
        case FLASH_ERASE_STATUS:{
            if(1 == bsw_mcal_flash_erase(APP_START_ADDR, (APP_FLASH_WORD_SIZE/FLASH_SECTOR_SIZE))){
                g_stFlashProgram.emFlashStatus      = FLASH_IDEL_STATUS;
                g_stFlashProgram.emFlashHandleFlag = FLASH_SUCCESS;
            }else{
                g_stFlashProgram.emFlashHandleFlag = FLASH_ERASS_ERR;
            }
            send_flash_erase_responsble(g_stFlashProgram.emFlashHandleFlag);
            g_stFlashProgram.u16FlashCmd           = FLASH_IDEL;
        }break;
        case FLASH_PROGRAM_STATUS:{
            if(g_stFlashProgram.u16FlashCmd == FLASH_CRC_CHECK){
                s_u16TimeOutCnt                = 0;
                g_stFlashProgram.emFlashStatus = FLASH_CHECK_STATUS;
            }
            if(g_stFlashProgram.u16FlashCmd == FLASH_PROGRAM){
                s_u16TimeOutCnt = 0;
                if((g_stFlashProgram.u32FlashProAddr >= 0x00090000)\
                    ||(s_u32BootFlashAddr != g_stFlashProgram.u32FlashProAddr)){
                    g_stFlashProgram.emFlashHandleFlag = FLASH_ADDR_ERR;
                }else if(g_stFlashProgram.u16FlashSize & 0x03ff){
                    g_stFlashProgram.emFlashHandleFlag = FLASH_SIZE_ERR;
                }else if(1 == bsw_mcal_flash_write(g_stFlashProgram.u32FlashProAddr, \
                        g_stFlashProgram.p_u16FlashDataBuff, g_stFlashProgram.u16FlashSize)){
                        if(1== bsw_mcal_flash_verify(g_stFlashProgram.u32FlashProAddr, g_stFlashProgram.p_u16FlashDataBuff, g_stFlashProgram.u16FlashSize)){
                            s_u32BootFlashAddr += g_stFlashProgram.u16FlashSize;
                            g_stFlashProgram.emFlashHandleFlag = FLASH_SUCCESS;
                            g_stFlashProgram.u16FlashCmd = FLASH_IDEL;
                        }else{
                            g_stFlashProgram.emFlashHandleFlag = FLASH_VERIFY_ERR;
                            g_stFlashProgram.u16FlashCmd       = FLASH_IDEL;
                        }
                }else{
                    g_stFlashProgram.emFlashHandleFlag = FLASH_PROGRAM_ERR;
                }
                send_flash_program_responsble(g_stFlashProgram.emFlashHandleFlag);
                g_stFlashProgram.u16FlashCmd = FLASH_IDEL;
            }else{
                s_u16TimeOutCnt++;
                if(s_u16TimeOutCnt > 500){
                    g_stFlashProgram.emFlashStatus      = FLASH_IDEL_STATUS; //Éý¼¶ÖÐ¶Ï,·µ»Ø¿ÕÏÐ×´Ì¬;
                    g_stFlashProgram.u16FlashCmd        = FLASH_IDEL;        //Çå³ýÃüÁî;
                }
            }
        }break;
        case FLASH_CHECK_STATUS:{
            p_u16Data =(unsigned short *)APP_START_ADDR;
            u32CrcResult = check_crc32_tab_u16(p_u16Data, (APP_FLASH_WORD_SIZE - 2));
            g_stFlashProgram.emFlashStatus     = FLASH_IDEL_STATUS;
            g_stFlashProgram.u16FlashCmd       = FLASH_IDEL; //Clear the flash cmd
            p_u32Data                          = (unsigned long *)(APP_START_ADDR + APP_FLASH_WORD_SIZE - 2);
            if(u32CrcResult == *p_u32Data){
                g_stFlashProgram.emFlashHandleFlag = FLASH_SUCCESS;
            }else{
                g_stFlashProgram.emFlashHandleFlag = FLASH_VERIFY_ERR;
            }
           send_flash_crc_check_responsble(g_stFlashProgram.emFlashHandleFlag);
        }break;
        default:break;
    }
}

