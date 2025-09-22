/*
 * ring_array.h
 *
 *  Created on: 2022.8.17.
 *      Author: xj8r1j
 */

#ifndef BSW_PUBLIC_PUBLIC_INC_RING_ARRAY_H_
#define BSW_PUBLIC_PUBLIC_INC_RING_ARRAY_H_

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
//#include "../DPStack/DLL/DLL_SCI.h"

enum RING_STATUS{
    RING_EMPTY = 0,
    RING_FULL  = 1,
};

enum RING_CMD{
    RING_IDLE           = 0,
    RING_REQUEST_READ   = 1,
	RING_REQUEST_WRITE  = 2,
    RING_LOCK_READ      = 3,
    RING_LOCK_WRITE     = 4,
};

struct RING_STATUS_BITS {                     // bits description
    UINT16 OverFlow:1;                   // 1:0 Counter Mode
    UINT16 NoSpace: 1;
    UINT16 Reserve: 14;
};

union RING_ERROR {
    UINT16  u16all;
    struct RING_STATUS_BITS bits;
};

enum RING_ID
{
    SCIA_RING_TX    = 0,
    SCIA_RING_RX    = 1,
    SCIB_RING_TX    = 2,
    SCIB_RING_RX    = 3,
    CANA_RING_TX    = 4,
    CANA_RING_RX    = 5,
    CANB_RING_TX    = 6,
    CANB_RING_RX    = 7,
    MCAN_RING_TX    = 8,
    MCAN_RING_RX    = 9,
    FSIA_RING_TX    = 10,
    FSIA_RING_RX    = 11,
};

typedef struct{
    unsigned short        *p_u16HeadAddr;
    unsigned short        *p_u16Input;
    unsigned short        *p_u16Output;
    signed short          i16IdelSize;
    signed short          i16TotalSize;
    enum RING_STATUS    enRingStaus;
    enum RING_CMD       enRingCmd;
}RING_ITEM;

//Must keep the same with the RING_ID.
typedef struct{
    enum RING_ID enRingId;
    RING_ITEM    *p_stItem;
}RING_OBJ;

extern INT16 Load_Data_To_Ring(enum RING_ID enRingId,UINT16 *p_u16SrcData,   INT16 i16TxNum);
extern INT16 Get_Data_From_Ring(enum RING_ID enRingId, UINT16 *p_u16DestAdd, INT16 i16MaxNum);
extern INT16 Get_OneData_From_Ring(enum RING_ID enRingId, UINT16 *p_u16DestAdd);

extern void  Reset_Ring(enum RING_ID enRingId);
extern INT16 Get_Ring_Data_Size(enum RING_ID enRingId);
extern INT16 Get_Ring_Idel_Size(enum RING_ID enRingId);
extern signed short Load_OneData_To_Ring(enum RING_ID enRingId, unsigned short  u16LoadData);

#define REG_RING_SECTION   __attribute__ ((used,section(".RING_REG_SECTION"),retain))
#define RING_BUFF_SECTION  __attribute__ ((used,section(".RING_BUFF_SECTION"),retain))

#define REG_RING_ITEM(RING_ID,p_user_data)  const RING_OBJ auto_reg_##RING_ID REG_RING_SECTION = {RING_ID,p_user_data};

#define REG_RING_ENTITY(RING_ID, RING_SIZE)					\
        UINT16 g_ua16##RING_ID##_[RING_SIZE] RING_BUFF_SECTION ={0};		\
        static RING_ITEM g_st##RING_ID##_Ctrl = {g_ua16##RING_ID##_,g_ua16##RING_ID##_,g_ua16##RING_ID##_,RING_SIZE,RING_SIZE,RING_EMPTY,RING_IDLE};\
        REG_RING_ITEM(RING_ID,(void*)&g_st##RING_ID##_Ctrl)

#endif /* BSW_PUBLIC_PUBLIC_INC_RING_ARRAY_H_ */
