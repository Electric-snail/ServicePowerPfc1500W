/*
 * BSW_MCAL_MEMCFG.h
 *
 *  Created on: 2024Äê12ÔÂ22ÈÕ
 *      Author: xj8r1j
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_MEMCFG_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_MEMCFG_H_

#define    CPURDERR_BIT                               0
#define    CEINTEN_BIT                                0
#define    CEINTCLR_BIT                               0

#define    CPUWRPROT_PIEVECT_BIT                     1
#define    LOCK_PIEVECT_BIT                          4

extern void bsw_mcal_memcfg_init(void);

#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_MEMCFG_H_ */
