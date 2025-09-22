/*
 * BSW_MCAL_SYS.h
 *
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_SYS_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_SYS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define    CORRECTABLE_ERR_BIT                  		2
#define    	RAM_ACC_VIOL_BIT                     		4

extern void bsw_mcal_sys_init(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_SYS_H_ */
