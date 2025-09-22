/*
 * BSW_SVC_BASIC.h
 *
 * *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#ifndef BSW_SVC_BASIC_H_
#define BSW_SVC_BASIC_H_

#include <PUBLIC_INC/AUTO_REGISTER.H>
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"
#include "MCAL/BSW_MCAL_BASIC.h"
#include "TASK/BSW_TASK_SERVICE.h"
#include "DEBUG_PLATFORM/PARAMETER_CTRL/PARAMETER.H"

typedef void  (*pf_svc_id_init)(void);

typedef struct
{
    const char     *svc_name;
    pf_svc_id_init  svc_id_init;
    UINT8           svc_id_status;
}SVC_INIT_OBJ;

#define REG_SVC_SECTION  __attribute__ ((used,section(".SVC_REG_SECTION")))

#define REG_SVC_INIT_ITEM(name,p_user_data)  const AUTO_REG_OBJ _auto_reg_##name REG_SVC_SECTION = {#name,AUTO_REG_SVC_INIT,p_user_data};

///-------device
#define REG_SVC_INIT(svc_name,init)                                                                      \
                static SVC_INIT_OBJ svc_init_##svc_name = {#svc_name,init,0};\
                REG_SVC_INIT_ITEM(svc_name,(void*)&svc_init_##svc_name)

extern void bsw_svc_init(void);


#endif /* BSW_SVC_BASIC_H_ */
