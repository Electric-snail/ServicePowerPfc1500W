/*
 * BSW_HAL_STORAGE.h
 *
 *  Created on: 2023.3.20
 *      Author: xj8r1j
 */

#ifndef BSW_HAL_HAL_INC_BSW_HAL_STORAGE_H_
#define BSW_HAL_HAL_INC_BSW_HAL_STORAGE_H_


extern UINT16 ReadStorageData(UINT16 *p_u16DestAddr, UINT16 *p_u16SrcAddr,  UINT16 u16Len);

extern UINT16 WriteStorageData(UINT16 *p_u16DestAddr, UINT16 *p_u16SrcAddr,  UINT16 u16Len);

extern UINT16 ErashStorageData(UINT16 *p_u16DestAddr, UINT16 u16Size);


#endif /* BSW_HAL_HAL_INC_BSW_HAL_STORAGE_H_ */
