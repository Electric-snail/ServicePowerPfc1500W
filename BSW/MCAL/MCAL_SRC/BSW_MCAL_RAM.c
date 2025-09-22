/*
 * BSW_MCAL_RAM.c
 *
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 */

#include "PUBLIC_INC/MEM_HANDLE.H"
#include "MCAL_INC/BSW_MCAL_RAM.h"

extern unsigned int RamfuncsLoadStart;
extern unsigned int RamfuncsLoadSize;
extern unsigned int RamfuncsRunStart;
void bsw_mcal_ram_init(void)
{
    unsigned short *p_u16RamRunStart  = (unsigned short *)&RamfuncsRunStart;
    unsigned short *p_u16RamLoadStart = (unsigned short *)&RamfuncsLoadStart;
    unsigned long   u32LoadSize       = (unsigned long)&RamfuncsLoadSize;

    memcpy_user(p_u16RamRunStart, p_u16RamLoadStart, u32LoadSize);
}

