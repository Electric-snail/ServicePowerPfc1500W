/*
 * BSW_MCAL_MEMCFG.h
 *
 *  Created on: 2024��12��22��
 *      Author: xj8r1j
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_MEMCFG_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_MEMCFG_H_

#define    CPURDERR_BIT                               0
#define    CEINTEN_BIT                                0
#define    CEINTCLR_BIT                               0

#define    CPUWRPROT_PIEVECT_BIT                      1
#define    LOCK_PIEVECT_BIT                           4

//*****************************************************************************
//
// Values that can be passed to MemCfg_forceCorrErrorStatus(),
// MemCfg_clearCorrErrorStatus(), and MemCfg_getCorrErrorAddress() as the
// stsFlag(s) parameter and returned by MemCfg_getCorrErrorStatus().
//
//*****************************************************************************
#define MEMCFG_CERR_CPUREAD      0x0001U //!< Correctable CPU read error
//*****************************************************************************
//
// Values that can be passed to MemCfg_forceUncorrErrorStatus(),
// MemCfg_clearUncorrErrorStatus(), and MemCfg_getUncorrErrorAddress() as the
// stsFlag(s) parameter and returned by MemCfg_getUncorrErrorStatus().
//
//*****************************************************************************
#define MEMCFG_UCERR_CPUREAD     0x0001U //!< Uncorrectable CPU read error

extern void bsw_mcal_memcfg_init(void);

#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_MEMCFG_H_ */
