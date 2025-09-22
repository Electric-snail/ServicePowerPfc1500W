/*
 * BSW_MCAL_ANALOGSUB.c
 *
 *  Created on: Sep 17, 2024
 *      Author: Pengyuan Chen
 *
 */
#include "CHIP_PACK/driverlib/inc/hw_types.h"
#include "MCAL/MCAL_INC/BSW_MCAL_ANALOGSUB.h"
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#include "../CHIP_PACK/common/include/F28x_Project.h"


void BSW_MCAL_ASysCtl_lockVREG(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_VREGCTL;

    EDIS;
}
