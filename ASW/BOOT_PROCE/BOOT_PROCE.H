/*
 * BOOT_PROCE.H
 *
 *  Created on: 2026��6��2��
 *      Author: Administrator
 */

#ifndef ASW_BOOT_PROCE_BOOT_PROCE_H_
#define ASW_BOOT_PROCE_BOOT_PROCE_H_

#define  FLASH_IDEL             0x00
#define  FLASH_ERASE            0x01
#define  FLASH_PROGRAM          0x02
#define  FLASH_CRC_CHECK        0x03
#define  FLASH_MATCH_CHEK       0x04

typedef enum{
    FLASH_INIT_STATUS = 0,
    FLASH_IDEL_STATUS,
    FLASH_ERASE_STATUS,
    FLASH_PROGRAM_STATUS,
    FLASH_CHECK_STATUS,
}FLASH_STATUS;

typedef enum{
    FLASH_SUCCESS = 0,
    FLASH_CRC_ERR,
    FLASH_ERASS_ERR,
    FLASH_OVER_TIME,
    FLASH_ADDR_ERR,
    FLASH_SIZE_ERR,
    FLASH_PROGRAM_ERR,
    FLASH_VERIFY_ERR,
    FLASH_NOT_DONE = 0xFF,
}FLASH_HANDLE_FLAG;

typedef struct{
    unsigned long       u32FlashProAddr;
    unsigned short      u16FlashSize;
    unsigned short      u16FlashCmd;
    FLASH_STATUS        emFlashStatus;
    FLASH_HANDLE_FLAG   emFlashHandleFlag;
    unsigned short      *p_u16FlashDataBuff;
}FLASH_PROGRAM_T;

extern void boot_proce(void);
extern void boot_proce_init(void);
extern unsigned short g_ua16BootBuff[];
extern FLASH_PROGRAM_T g_stFlashProgram;

#define  get_flash_grogram_buff_addr()                  g_ua16BootBuff
#define  set_erase_flash_cmd()                          g_stFlashProgram.u16FlashCmd        = FLASH_ERASE
#define  set_program_flash_cmd()                        g_stFlashProgram.u16FlashCmd        = FLASH_PROGRAM
#define  set_program_crc_check_cmd()                    g_stFlashProgram.u16FlashCmd        = FLASH_CRC_CHECK
#define  clr_flash_handle_flag()                        g_stFlashProgram.emFlashHandleFlag  = FLASH_NOT_DONE
#define  get_flash_handle_status()                      g_stFlashProgram.emFlashHandleFlag

#define  set_flash_grogram_word_size(u16WordSize)       g_stFlashProgram.u16FlashSize = u16WordSize
#define  set_flash_grogram_addr(u32ProgramAddr)         g_stFlashProgram.u32FlashProAddr = u32ProgramAddr

#endif /* ASW_BOOT_PROCE_BOOT_PROCE_H_ */
