/*
 * BSW_MCAL_CMPSS_COMM.h
 *
 *  Created on: 2024.06.27
 *      Author: rjgslg
 */

#ifndef BSW_MCAL_CMPSS_COMM_H_
#define BSW_MCAL_CMPSS_COMM_H_

#include "../CHIP_PACK/common/include/F28x_Project.h"
#include "../ENV_CFG/HARDWARE_ENV_CFG.h"
#include "../MCAL/BSW_MCAL_BASIC.h"



/*COMPDACHCTL-  SWLOADSEL*/
#define SWLOADSEL_SYSCLK           0
#define SWLOADSEL_EPWMSYNCPER      1


/*COMPDACHCTL/COMPDACLCTL-  DACSOURCE*/
#define DACHVALA_SRC_DACxVALAS     0
#define DACHVALA_SRC_RAMP_GEN      1

/*COMPDACHCTL-  DACSOURCE*/
#define SWLOADSEL_SYSCLK           0
#define SWLOADSEL_EPWMSYNCPER      1

/*COMPCTL-  COMPHSOURCE/COMPLSOURCE*/
#define CMPINSRC_IN_DAC            0
#define CMPINSRC_EXT_PIN           1

/*COMPCTL-  COMPHINV/COMPLINV*/
#define CMPOUTINV_NOTINV           0
#define CMPOUTINV_INV              1

/*COMPCTL-  CTRIPHSEL/CTRIPLSEL/CTRIPOUTHSEL/CTRIPOUTLSEL*/
#define CTRIPxSEL_ASYNC            0
#define CTRIPxSEL_SYNC             1
#define CTRIPxSEL_DFILT            2
#define CTRIPxSEL_DFILTLATCH       3

/*COMPCTL-  ASYNCHEN/ASYNCLEN*/
#define ASYNC_ORDFILTLATCH_EN      1
#define ASYNC_ORDFILTLATCH_DIS     0

/*COMPCTL-  COMPDACE*/
#define COMPDAC_EN                 1
#define COMPDAC_DIS                0

/*COMPHYSCTL - COMPHYS*/
typedef enum{
    COMPHYS_None = 0,
    COMPHYS_1xTypeHyst,
    COMPHYS_2xTypeHyst,
    COMPHYS_3xTypeHyst,
    COMPHYS_4xTypeHyst,
}COMPHYS_TYPEHYST;

#endif /*BSW_MCAL_CMPSS_COMM_H_ */
