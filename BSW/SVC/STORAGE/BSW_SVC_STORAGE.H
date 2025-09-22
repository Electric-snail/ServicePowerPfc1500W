/*
 * BSW_STORAGE.H
 *
 *  Created on: 2025.8.26.
 *      Author:  Hongbo.jiang
 */

#ifndef BSW_SVC_STORAGE_BSW_STORAGE_H_
#define BSW_SVC_STORAGE_BSW_STORAGE_H_

#include    "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB.h"

typedef struct{
    PARAME_CALIB_DATA_T        stCalibData;
     unsigned short            u16CrcCheck;
}STORAGE_DATA_T;

extern STORAGE_DATA_T                  g_stStoreData;
extern volatile unsigned short              g_u16StoreFlag;

#define get_calib_store_addr()              (&g_stStoreData.stCalibData)
#define set_store_flag()                         g_u16StoreFlag = 1

#endif /* BSW_SVC_STORAGE_BSW_STORAGE_H_ */
