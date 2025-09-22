/*
 * BSW_MCAL_NMI.c
 *
 *  Created on: Sep 4, 2024
 *      Author: Pengyuan Chen
 */
#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_SYS_CLOCK.h"
#include "../MCAL/MCAL_INC/BSW_MCAL_NMI.h"
#include "../CHIP_PACK/driverlib/inc/hw_memmap.h"
#include "../CHIP_PACK/driverlib/inc/hw_nmi.h"
#include "../BSW/CHIP_PACK/driverlib/inc/hw_ints.h"

void bsw_mcal_nmi_init(void){
    EALLOW;
    NmiIntruptRegs.NMIFLGCLR.all    = (1U << NMIINT_BIT) | (1U << CLOCKFAIL_BIT) |(1U << UNCERR_BIT)      \
                                  |(1U << REGPARITYERR_BIT)|(1U << LSCMPERR_BIT) | (1 << SWERR_BIT);
    NmiIntruptRegs.ERRORSTSCLR.all  = (1U << ERROR_BIT);

    NmiIntruptRegs.ERRORCTL.all     = 1U;      //the high valid of error reset pin

    NmiIntruptRegs.ERRORLOCK.all    = 1U;      //lock the error ctrl register

    NmiIntruptRegs.NMICFG.all       = 1U; //Enable NMI
    EDIS;
}


