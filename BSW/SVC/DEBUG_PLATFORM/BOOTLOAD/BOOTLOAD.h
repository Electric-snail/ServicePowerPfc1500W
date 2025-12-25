/*
 * BOOTLOAD.h
 *
 *  Created on: 2022/11/28
 *      Author: xj8r1j
 */

#ifndef _BOOTLOAD_H_
#define _BOOTLOAD_H_

extern void bootload_cmd_set_link(void *p_stAplDmTemp);
extern UINT16 	g_u16BootLoadFlg;
extern UINT32 	g_u32CLLCJumpBoot;

#ifndef DLLX64
#define u16_get_bootload_flg()          g_u16BootLoadFlg
#else
#define u16_get_bootload_flg()          0
#endif

#define clear_db_boot_flg()             (g_u16BootLoadFlg = 0)

#endif /* BSW_SVC_DEBUGPLATFORM_BOOTLOADER_BOOTLOAD_H_ */
