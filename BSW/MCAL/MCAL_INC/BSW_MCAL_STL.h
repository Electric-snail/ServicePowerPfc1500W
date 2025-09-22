/*
 * BSW_MCAL_STL.h
 *
 *  Created on: 2024.7.14
 *      Author: Pengyuan Chen
 */

#ifndef _BSW_MCAL_STA_H_
#define _BSW_MCAL_STA_H_

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"


#define MCD_EN                          1
#define PIE_HANDLER_EN                  1
#define LCM_EN                          1
#define SP_EN                           1
#define MARCH_EN                        1
#define MARCH_COPY_EN                   1
#define MARCH_CAN_EN                    0
#define MARCH_CANCOPY_EN                0
#define MARCH_CANRAM_PARITY_EN          0
#define FLASH_CRC_EN                    1

#define _FLASH                          1

extern void bsw_mcal_stl_test(void);

#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_STA_H_ */
