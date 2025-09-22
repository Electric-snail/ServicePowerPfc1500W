/*
 * mem_handler.c
 *
 *  Created on: 2022.8.24
 *      Author: xj8r1j
 */
#include "PUBLIC_INC/MEM_HANDLE.H"

void memclr_user(unsigned short *p_u16Data, unsigned short u16len){
    unsigned short i = 0;
    for(i = 0; i < u16len; i ++){
        *p_u16Data ++ = 0x0000;
    }
}

void memset_user(unsigned short *p_u16Data, unsigned short u16Value, unsigned short u16len) {
	unsigned short i = 0;
	for (i = 0; i < u16len; i++) {
		*p_u16Data++ = u16Value;
	}
}

void memcpy_user(unsigned short *p_u16DestAddr, unsigned short* p_u16SrcAddr, unsigned long u32len)
{
	unsigned long i = 0;
	for (i = 0; i < u32len; i++) {
		*p_u16DestAddr++ = *p_u16SrcAddr++;
	}
}

