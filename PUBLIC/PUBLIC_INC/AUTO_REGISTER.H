/*
 * register.h
 *
 *  Created on: 2022-07-21
 *      Author: Hongbo.jiang
 */

#ifndef BSW_BASIC_REGISTER_H_
#define BSW_BASIC_REGISTER_H_

#include "PUBLIC_INC/AUTO_REGISTER.H"

enum AUTO_REG_TYPE
{
    AUTO_REG_TYPE_RSV          	= 0x00,

    AUTO_REG_TASK               		= 0x01,

    AUTO_REG_SVC_INIT           	= 0x02,

    AUTO_REG_PARAM_CFG         = 0x03,

    AUTO_REG_PARAM_CFG_CB  = 0x04,

    AUTO_REG_ASW_INIT              = 0x05,

    AUTO_REG_ISR_TEST              = 0x06,

    AUTO_REG_ISR_INIT               = 0x07,
};

typedef struct
{
    const char            					*name;
    enum AUTO_REG_TYPE   	 emType;
    void                  						*p_reg_data;
    unsigned long         					u32Rvs;
}AUTO_REG_OBJ;

#define AUTO_REG_SECTION  __attribute__((used,section(".AUTO_REG_SECTION"),retain))

#define AUTO_REG_ITEM(name,type,p_user_data)  const AUTO_REG_OBJ __auto_reg_##name AUTO_REG_SECTION = {#name,type,p_user_data}




typedef void (*pf_init_func)(void);

extern void *auto_reg_get_func_cont_by_index(enum AUTO_REG_TYPE emRegType, unsigned int u16FindIndex);

#endif /* BSW_BASIC_REGISTER_H_ */
