/*
 * CRC_TAB.H
 *
 *  Created on: 2026.6.3
 *      Author: Hongbo.Jiang
 */

#ifndef PUBLIC_PUBLIC_INC_CRC_TAB_H_
#define PUBLIC_PUBLIC_INC_CRC_TAB_H_

extern unsigned char check_crc8_tab(unsigned short *p_u16Data, unsigned short len);

//extern unsigned short check_crc16_tab_u16(unsigned short *p_u16Msg, unsigned short u16DataLen);

//extern unsigned short check_crc16_tab_u8(UINT8 *p_u8Msg, unsigned short u16DataLen);
extern unsigned long check_crc32_tab_u16(unsigned short *p_u16Msg, unsigned short u16DataLen);


#endif /* PUBLIC_PUBLIC_INC_CRC_TAB_H_ */
