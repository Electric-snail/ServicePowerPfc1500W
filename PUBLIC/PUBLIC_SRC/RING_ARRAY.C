/*
 * ring_array.c
 *
 *  Created on: 2022/8/16
 *      Author: xj8r1j
 */
#include "PUBLIC_INC/RING_ARRAY.H"
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

extern UINT32 RingRegLoadStart;
extern UINT16 RingRegLoadSize;

RING_ITEM *Find_Ring_Item(enum RING_ID enRingId){
    unsigned int i = 0;
    unsigned int u16RingNum = (UINT16)((UINT32)&RingRegLoadSize/sizeof(RING_OBJ));

    RING_OBJ *p_RingReg =(RING_OBJ *)&RingRegLoadStart;

    for(i = 0; i < u16RingNum; i ++){
        if(enRingId == p_RingReg->enRingId)
            return p_RingReg->p_stItem;
        p_RingReg++;
    }
    return NULL;
}

INT16 Load_Data_To_Ring(enum RING_ID enRingId,UINT16 *p_u16SrcData,INT16 i16TxNum)
{
	RING_ITEM *p_stRingItem = NULL;
    INT16 i;
    if(i16TxNum < 0)
        return -1;

    p_stRingItem = Find_Ring_Item(enRingId);

    if(p_stRingItem == NULL)
        return -1;

    if(p_stRingItem->i16IdelSize < i16TxNum)
        return -1;

    p_stRingItem->i16IdelSize -= i16TxNum;   //After load, the remain size, must sub before the data load.

    for(i = 0; i < i16TxNum; i++){
        *(p_stRingItem->p_u16Input) = *p_u16SrcData;
        p_stRingItem->p_u16Input ++;
        p_u16SrcData ++;
        if(p_stRingItem->p_u16Input >= \
                (p_stRingItem->p_u16HeadAddr + p_stRingItem->i16TotalSize))
        	p_stRingItem->p_u16Input = p_stRingItem->p_u16HeadAddr;
    }
    return 1;
}


INT16 Get_Data_From_Ring(enum RING_ID enRingId, UINT16 *p_u16DestAddr, INT16 i16MaxNum)
{
    INT16 i16TempData = 0;

	RING_ITEM *p_stRingItem = NULL;
    INT16 i = 0;

    p_stRingItem = Find_Ring_Item(enRingId);

    if(p_stRingItem == NULL)
        return -1;

    if(p_stRingItem->i16IdelSize < p_stRingItem->i16TotalSize){
        i16TempData = p_stRingItem->i16TotalSize - p_stRingItem->i16IdelSize; //The number of remain data;

        if(i16MaxNum < i16TempData){
            i16TempData = i16MaxNum;
        }

        for(i = 0; i < i16TempData; i ++){
            *p_u16DestAddr++ = *(p_stRingItem->p_u16Output);
            p_stRingItem->p_u16Output ++;
            if(p_stRingItem->p_u16Output >= \
                           (p_stRingItem->p_u16HeadAddr + p_stRingItem->i16TotalSize))
                p_stRingItem->p_u16Output = p_stRingItem->p_u16HeadAddr;
        }
        p_stRingItem->i16IdelSize += i16TempData;  //Must after getting the data from the ring, then change the idel_size.
        return i16TempData;
    }else{
        p_stRingItem->i16IdelSize = p_stRingItem->i16TotalSize;
        return 0;
    }
}


INT16 Get_OneData_From_Ring(enum RING_ID enRingId, UINT16 *p_u16DestAddr)
{
	RING_ITEM *p_stRingItem = NULL;

    p_stRingItem = Find_Ring_Item(enRingId);

    if(p_stRingItem == NULL)
        return -1;

    if(p_stRingItem->i16IdelSize >= p_stRingItem->i16TotalSize)
    	return -1;

    *p_u16DestAddr = *(p_stRingItem->p_u16Output++);

     if(p_stRingItem->p_u16Output >= \
          (p_stRingItem->p_u16HeadAddr + p_stRingItem->i16TotalSize))
     p_stRingItem->p_u16Output = p_stRingItem->p_u16HeadAddr;

     p_stRingItem->i16IdelSize ++;  //Must after getting the data from the ring, then change the idel_size.
     return 1;
}

short Load_OneData_To_Ring(enum RING_ID enRingId, unsigned short  u16LoadData)
{
	RING_ITEM *p_stRingItem = NULL;

    p_stRingItem = Find_Ring_Item(enRingId);

    if(p_stRingItem == NULL)
        return -1;

    if(p_stRingItem->i16IdelSize <  1)
    	return -1;

     *p_stRingItem->p_u16Input++ = u16LoadData;

     if(p_stRingItem->p_u16Input >= (p_stRingItem->p_u16HeadAddr + p_stRingItem->i16TotalSize))
    	 p_stRingItem->p_u16Input = p_stRingItem->p_u16HeadAddr;

     p_stRingItem->i16IdelSize --;  //Must after getting the data from the ring, then change the idel_size.
     return 1;
}

INT16 Get_Ring_Idel_Size(enum RING_ID enRingId)
{
	RING_ITEM *p_stRingItem = NULL;

	p_stRingItem = Find_Ring_Item(enRingId);
    if(p_stRingItem == NULL)
       return -1;
    return p_stRingItem->i16IdelSize;
}

INT16 Get_Ring_Data_Size(enum RING_ID enRingId)
{
	RING_ITEM *p_stRingItem = NULL;

	p_stRingItem = Find_Ring_Item(enRingId);

	if(p_stRingItem == NULL)
	   return -1;

    return (p_stRingItem->i16TotalSize - p_stRingItem->i16IdelSize);
}

void Reset_Ring(enum RING_ID enRingId)
{
	RING_ITEM *p_stRingItem = NULL;

	p_stRingItem = Find_Ring_Item(enRingId);

	if(p_stRingItem == NULL)
	   return;

    p_stRingItem->i16IdelSize       = p_stRingItem->i16TotalSize;
    p_stRingItem->p_u16Input        = p_stRingItem->p_u16HeadAddr;
    p_stRingItem->p_u16Output       = p_stRingItem->p_u16HeadAddr;
    p_stRingItem->enRingStaus       = RING_EMPTY;
    p_stRingItem->enRingCmd         = RING_IDLE;
}
