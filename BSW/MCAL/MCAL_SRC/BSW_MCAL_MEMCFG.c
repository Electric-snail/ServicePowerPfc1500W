/*
 * BSW_MCAL_MEMCFG.c
 *
 *  Created on: 2024.12.22
 *      Author: hongbo.jiang
 */
#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "../CHIP_PACK/driverlib/memcfg.h"
#include "MCAL_INC/BSW_MCAL_MEMCFG.h"
#define    LOCK_M1_BIT                               1
#define    LOCK_M0_BIT                               0

#define    LOCK_LS0_BIT                               0
#define    LOCK_LS1_BIT                               1

#define    CEINTEN_BIT                                0
#define    CEINTCLR_BIT                               0

#define    CPUWRITE_BIT                               1
#define    CPUFETCH_BIT                               0

#define    FETCHPROT_M1_BIT                           8
#define    FETCHPROT_M0_BIT                           0

#define    FETCHPROT_LS0_BIT                          0
#define    FETCHPROT_LS1_BIT                          8

#define    CPUWRPROT_LS0_BIT                          1
#define    CPUWRPROT_LS1_BIT                          9

void bsw_mcal_memcfg_init(void){
    EALLOW;
    //by now through debug, when enable the CPU fetch protection, it will enter the illegal interrupt
    //by now, can't confirm which interrupt will be serviced for CPU write protection.
    AccessProtectionRegs.MAVCLR.all     = 1 << CPUFETCH_BIT;
    //
    AccessProtectionRegs.MAVINTEN.all   = 1 << CPUFETCH_BIT;

   //CPU write the PIEVECT is blocked.
    MemCfgRegs.DxACCPROT1.all           = (1U << CPUWRPROT_PIEVECT_BIT);
    //As the code run in the LSxRAM, so the M0,M1 can be configure the no access for fetch;
    //CPU write M0/M1 is allowed, fetch M0,M1 is block;
    MemCfgRegs.DxACCPROT0.all           = (1U << FETCHPROT_M1_BIT) | (1U << FETCHPROT_M0_BIT);

    //CPU write/fetch to LSxRAM is allowed
    //Now, when the cpu write access protection is happen, the software flow is not under control, so the write access protection forbidden to enable.
    MemCfgRegs.LSxACCPROT0.all          = 0UL;

    //lock the ACCPROT, INTI, MSEL for PIEVECT, M0, M1 register;
    MemCfgRegs.LSxLOCK.all              = (1 << LOCK_LS0_BIT) | (1 << LOCK_LS1_BIT);

    MemCfgRegs.DxLOCK.all               = (1UL << LOCK_PIEVECT_BIT) | (1UL << LOCK_M1_BIT) | (1UL << LOCK_M0_BIT);

    MemoryErrorRegs.UCERRCLR.all        = MEMCFG_UCERR_CPUREAD;
    MemoryErrorRegs.CERRCLR.all         = MEMCFG_CERR_CPUREAD;
    MemoryErrorRegs.CEINTCLR.all        = MEMCFG_CERR_CPUREAD;
    MemoryErrorRegs.CERRTHRES.all       = 6UL;  //The ECC correct threshold is 6 times
    MemoryErrorRegs.CEINTEN.all         = (1 << CEINTEN_BIT);  //the correct error interrupt is enable.
    EDIS;
}



