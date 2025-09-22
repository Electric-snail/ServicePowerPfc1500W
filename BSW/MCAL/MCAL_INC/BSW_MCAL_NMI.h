/*
 * BSW_MCAL_NMI.h
 *
 *  Created on: Sep 4, 2024
 *      Author: g8mqmx
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_NMI_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_NMI_H_

extern void   bsw_mcal_nmi_init(void);

/******macros definition zoon ****************/
#define         NMIINT_BIT                  0
#define         CLOCKFAIL_BIT               1
#define         UNCERR_BIT                  2
#define         REGPARITYERR_BIT            3
#define         LSCMPERR_BIT                4
#define         SWERR_BIT                   13
#define         ERROR_BIT                   0

#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_NMI_H_ */
