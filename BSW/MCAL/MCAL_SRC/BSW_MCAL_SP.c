/*
 * BSW_MCAL_SP_SF.c
 *
 *  Created on: 2024.6.25
 *      Author: hongbo.jiang
 */
extern unsigned short get_sp();

extern unsigned short HWI_STKBOTTOM;
extern unsigned short HWI_STKTOP;

void bsw_mcal_sp_init(void){
    unsigned long u32Sp       = 0;
    unsigned long u32EndStack = (unsigned long)&HWI_STKTOP;

    u32Sp = (unsigned long)get_sp();
    u32Sp += 64;
    while(u32Sp <= u32EndStack){
        *(unsigned short *)u32Sp = 0xAA55;
        u32Sp++;
    }
}

