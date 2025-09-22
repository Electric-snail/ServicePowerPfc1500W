
/*
 * BSW_SVC_BASIC.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */


#include <PUBLIC_INC/AUTO_REGISTER.H>
#include "BSW_SVC_BASIC.h"

extern UINT16 SvcRegLoadStart;
extern UINT16 SvcRegLoadSize;

void bsw_svc_init(void)
{
    UINT16 i;

    AUTO_REG_OBJ *p_auto_reg = NULL;
    pf_init_func p_init_func = NULL;


    UINT16   auto_reg_item = (UINT16)((UINT32)&SvcRegLoadSize / sizeof(AUTO_REG_OBJ));
    p_auto_reg = (AUTO_REG_OBJ *)&SvcRegLoadStart;
    SVC_INIT_OBJ *p_SvcInitObj = NULL;
    for(i = 0; i < auto_reg_item; i++)
    {
       p_SvcInitObj = (SVC_INIT_OBJ *)p_auto_reg->p_reg_data;
       if(p_SvcInitObj == NULL)
           continue;
       p_init_func =(pf_svc_id_init)p_SvcInitObj->svc_id_init;
       if(p_init_func != NULL)
          p_init_func();
       p_auto_reg ++;
    }
}
