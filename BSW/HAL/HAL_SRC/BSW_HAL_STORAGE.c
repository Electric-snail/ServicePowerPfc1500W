/*
 * BSW_HAL_STORAGE.c
 *
 *  Created on: 2023.3.20
 *      Author: xj8r1j
 */
#include "SOFTWARE_ENV_CFG.h"
#include "MCAL_INC/BSW_MCAL_FLASH.h"
#include "HAL_INC/BSW_HAL_STORAGE.h"

UINT16 ReadStorageData(UINT16 *p_u16DestAddr, UINT16 *p_u16SrcAddr,  UINT16 u16Len){
    UINT32 u32TempData      = ( (UINT32)p_u16SrcAddr + 1) & 0xFFFFFFFE;   //如果不是双字对齐，则向后一个字，使其双字对齐
    UINT16 *p_u16TempData = (UINT16 *)u32TempData;
#ifndef DLLX64
    bsw_mcal_flash_read(p_u16DestAddr, p_u16TempData, u16Len);
#endif
    return 1;
}

UINT16 WriteStorageData(UINT16 *p_u16DestAddr, UINT16 *p_u16SrcAddr,  UINT16 u16Len){
    UINT32 u32TempData    =( (UINT32)p_u16DestAddr + 1) & 0xFFFFFFFE;   //如果不是双字对齐，则向后一个字，使其双字对齐
    UINT16 *p_u16TempData = (UINT16 *)u32TempData;
#ifndef DLLX64
    if(bsw_mcal_flash_write(p_u16TempData,	p_u16SrcAddr,	   u16Len) == 1)
       return 1;
#endif
    return 0;
}


UINT16 ErashStorageData(UINT16 *p_u16DestAddr, UINT16 u16Size){
    UINT32 u32TempData     = ((UINT32)p_u16DestAddr + 1)& 0xFFFFFFFE;
    UINT16 *p_u16TempData = (UINT16 *)u32TempData;
#ifndef DLLX64
    if( bsw_mcal_flash_erase(p_u16TempData, u16Size) == 1)
    return 1;
#endif
    return 0;
}
