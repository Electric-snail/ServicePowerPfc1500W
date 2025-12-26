/*
 * BSW_SVC_STORAGE.C
 *
 *  Created on: 2025.8.26
 *      Author: jhb72
 */
#include "SOFTWARE_ENV_CFG.H"
#include "PUBLIC_INC/MEM_HANDLE.H"
#include "HAL_INC/BSW_HAL_STORAGE.H"
#include "STORAGE/BSW_STORAGE.H"

extern const UINT8 crc_table[];                   // CRC table.

volatile UINT16 g_u16StoreFlag = 0;


#pragma DATA_SECTION(gc_stStoreData, ".STORAGE_REG_SECTION");
const STORAGE_DATA_T gc_stStoreData;     //存储在Flash 区
STORAGE_DATA_T 			g_stStoreData;      //存储在RAM区

void storage_init(void){
     UINT16 i = 0;
     UINT8  u8CrcData = 0;
     UINT16 u16Temp;
     UINT16 *p_u16DestAddr = (UINT16 *)&g_stStoreData;
     UINT16 *p_u16SrcAddr  =  (UINT16 *)&gc_stStoreData;
     if(ReadStorageData(p_u16DestAddr, p_u16SrcAddr, sizeof(STORAGE_DATA_T)) == 1){
         for(i = 0; i < (sizeof(STORAGE_DATA_T) - 2); i++)  {
             u16Temp      = p_u16DestAddr[i] & 0x00FF;
             u8CrcData   = crc_table[u8CrcData ^ u16Temp];
             u16Temp      = p_u16DestAddr[i] >> 8;
             u8CrcData   = crc_table[u8CrcData ^ u16Temp];
         }
         if(u8CrcData != g_stStoreData.u16CrcCheck){
             ErashStorageData((UINT16 *)&gc_stStoreData, sizeof(gc_stStoreData));
             memset_user((void *)&g_stStoreData, 0xFFFF,sizeof(STORAGE_DATA_T));
         }
     }
}


void storage_handle(void){
      UINT16   i = 0;
      UINT16  u16Temp;
      UINT16  u16CrcData = 0;
      UINT16  *p_u16SrcAddr   = (UINT16 *)&g_stStoreData;
      UINT16  *p_u16DestAddr = (UINT16 *)&gc_stStoreData;

      if(g_u16StoreFlag == 1){
          if(ErashStorageData(p_u16DestAddr, sizeof(gc_stStoreData)) == 1){

              for(i = 0; i < sizeof(STORAGE_DATA_T)/sizeof(UINT16) - 1; i ++)
              {
                  u16Temp      = p_u16SrcAddr[i] & 0x00FF;
                  u16CrcData   = crc_table[u16CrcData ^ u16Temp];
                  u16Temp      = p_u16SrcAddr[i] >> 8;
                  u16CrcData   = crc_table[u16CrcData ^ u16Temp];
              }
              g_stStoreData.u16CrcCheck =  u16CrcData;
          }
          if(1 == WriteStorageData(p_u16DestAddr, p_u16SrcAddr,sizeof(gc_stStoreData)/sizeof(UINT16)))
              g_u16StoreFlag = 0;
          storage_init();
      }
}



