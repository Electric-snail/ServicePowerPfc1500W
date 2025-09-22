/*
 * mem_handle.h
 *
 *  Created on: 2022/8/24
 *      Author: xj8r1j
 */

#ifndef BSW_PUBLIC_PUBLIC_INC_MEM_HANDLE_H_
#define BSW_PUBLIC_PUBLIC_INC_MEM_HANDLE_H_

#include "PUBLIC_INC/LINE_BUFF.H"
#include "PUBLIC_INC/RING_ARRAY.H"

enum BUFF_TYPE{
    LINE_BUFF_TYPE   = 0,
    RING_BUFF_TYPE   = 1,
    HEAP_BUFF_TYPE   = 2,
    STACK_BUFF_TYPE  = 3,
};

typedef struct{
    enum    BUFF_TYPE       enBuffType;
    void                    *p_BuffObj;
}BUFF_CTRL_OBJ;

extern void memclr_user(unsigned short *p_u16DestAddr, unsigned short u16len);

extern void memset_user(unsigned short *p_u16DestAddr, unsigned short u16Value, unsigned short u16len);

extern void memcpy_user(unsigned short *p_u16DestAddr, unsigned short* p_u16SrcAddr, unsigned long);
#endif /* BSW_PUBLIC_PUBLIC_INC_MEM_HANDLE_H_ */
