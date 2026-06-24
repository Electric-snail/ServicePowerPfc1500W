/*
 * SysFsm.c
 *
 *  Created on: 2022.9.19
 */
#include "MCAL_INC/BSW_MCAL_FLASH.H"
#include "SYS_FSM/SYS_FSM.h"
#include "BOOT_PROCE/BOOT_PROCE.H"
#include "PUBLIC_INC/MEM_HANDLE.H"
#include "PUBLIC_INC/CRC_TAB.H"
#include "DEBUG_PLATFORM/BOOTLOAD/BOOTLOAD.H"

#ifndef DLLX64
#include "MCAL_INC/BSW_MCAL_WDG.h"
#include "DEBUG_PLATFORM/BOOTLOAD/BOOTLOAD.h"
extern void ExitBoot(UINT32 EntryAddr);
#endif

#pragma DATA_SECTION(g_u16AppUpdataFlag,".APP_UPDATA_FLAG");

unsigned short g_u16AppUpdataFlag;

unsigned short g_u16SysFsmCnt =	0;

void sys_fsm_init(void) {
}

unsigned short app_flash_check(void){
    unsigned long u32CrcResult;
    unsigned long *p_u32Data;
    unsigned short *p_u16AppStartAddr = (unsigned short *)APP_START_ADDR;
    u32CrcResult = check_crc32_tab_u16(p_u16AppStartAddr, (APP_FLASH_WORD_SIZE - 2));
    p_u32Data    = (unsigned long *)(APP_START_ADDR + APP_FLASH_WORD_SIZE - 2);
    if(u32CrcResult == *p_u32Data){
        return FLASH_CHECK_PASS;
    }else{
        return FLASH_CHECK_FAIL;
    }
}


unsigned short g_u16SysFsmStatus = 0;

void sys_fsm_5ms_task(void){
    bsw_mcal_service_wdg();
    
    switch(g_u16SysFsmStatus){
       case BOOT_CHECK_STATUS:{ //��������Ҫ����������APP���pass��������һ��״̬�ж��Ƿ���Ҫǿ������ģʽ
           if((g_u16AppUpdataFlag != 0xAA55)&&(app_flash_check() == FLASH_CHECK_PASS)){
               g_u16SysFsmStatus = BOOT_WAIT_STATUS;
               g_u16SysFsmCnt = 0;
           }else{ //�������bootloader ģʽ
               g_u16SysFsmStatus = BOOT_UPDATA_STATUS;
               g_u16SysFsmCnt = 0;
           }
       }break;
       case BOOT_WAIT_STATUS:{
          if(u16_get_enter_boot_flag() == 1){
              clr_enter_boot_flag();
              g_u16SysFsmStatus = BOOT_UPDATA_STATUS;
              g_u16SysFsmCnt    = 0;
          }else{
              g_u16SysFsmCnt++;     //Over 50ms,enter the flash mode
              if(g_u16SysFsmCnt > 50){
                  ExitBoot(0x86000);
              }
          }
       }break;
       case BOOT_UPDATA_STATUS:{
           boot_proce();
           if(u16_get_enter_app_flag() == 1){
               g_u16AppUpdataFlag = 0x0000;
               while(1);//wait for the watch dog over time to reset.
           }
       }break;
       default:break;
    }
}

