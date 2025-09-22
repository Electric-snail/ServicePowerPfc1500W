/*
 * ASW_BASIC.C
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */


#include "PUBLIC_INC/AUTO_REGISTER.H"
#include "SOFTWARE_ENV_CFG.H"
#include "TASK/BSW_TASK_SERVICE.H"
#include "ASW_BASIC.h"

extern UINT16 AswRegLoadStart;
extern UINT16 AswRegLoadSize;

void asw_init(void)
{
    UINT16 i;

    AUTO_REG_OBJ *p_auto_reg = NULL;
    pf_init_func p_init_func = NULL;


    UINT16   auto_reg_item = (UINT16)((UINT32)&AswRegLoadSize / sizeof(AUTO_REG_OBJ));
    p_auto_reg = (AUTO_REG_OBJ *)&AswRegLoadStart;
    ASW_INIT_OBJ *p_AswInitObj = NULL;
    for(i = 0; i < auto_reg_item; i++)
    {
        p_AswInitObj = (ASW_INIT_OBJ *)p_auto_reg->p_reg_data;
       if(p_AswInitObj == NULL)
           continue;
       p_init_func =(pf_asw_id_init)p_AswInitObj->asw_id_init;
       if(p_init_func != NULL)
          p_init_func();
       p_auto_reg ++;
    }
}

void asw_1msTask(void)
{
}

REG_TASK(asw_1msTask,		1,			1,				0);

