/*
 * BOOTLOAD.h
 *
 *  Created on: 2022/11/28
 *      Author: hongbo.jiang
 */

#ifndef _BOOTLOAD_H_
#define _BOOTLOAD_H_

#define  ENTER_BOOT_CMD              0x01
#define  RESPONSE_ENTER_BOOT         0x11

#define  HANDSHAKE_CMD                0x02
#define  RESPONSE_HANDSHAKE_CMD     0x12

#define  FLASH_ERASE_CMD             0x03
#define  RESPONSE_FLASH_ERASE_CMD    0x13

//#define  ASK_FLASH_HANDLE_CMD        0x04
//#define  RESPONSE_FLASH_HANDLE       0x14

#define  BOOT_VER_CMD                0x05
#define  RESPON_BOOT_VER             0x15

#define  APP_VER_CMD                 0x06
#define  RESPON_APP_VER              0x16

#define  FLASH_PROGRAM_CMD           0x07
#define  RESPONSE_FLASH_PROGRAM_CMD  0x17

#define  FLASH_CRC_CHECK_CMD            0x08
#define  RESPONSE_FLASH_CRC_CHECK_CMD   0x18

#define  ENTER_APP_CMD               0x09

extern void bootload_cmd_set_link(void *p_stAplDmTemp);
extern void send_enter_boot_status(void);
extern void send_flash_erase_responsble(unsigned char u8FlashEraseFlag);
extern void send_flash_crc_check_responsble(unsigned char u8FlashCrcFlag);
extern void send_flash_program_responsble(unsigned char u8FlashProgramFlag);

extern UINT16   g_u16EnterAppFlag;
extern UINT16   g_u16EnterBootFlag;

#ifndef DLLX64
#define u16_get_enter_boot_flag()       g_u16EnterBootFlag
#define clr_enter_boot_flag()           g_u16EnterBootFlag = 0
#define u16_get_enter_app_flag()        g_u16EnterAppFlag
#else
#define u16_get_bootload_flg()          0
#endif

#define clear_db_boot_flg()             (g_u16BootLoadFlg = 0)

#endif /* BSW_SVC_DEBUGPLATFORM_BOOTLOADER_BOOTLOAD_H_ */
