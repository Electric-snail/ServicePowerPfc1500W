/*
 * auto_register.c
 *
 *  Created on: 2022-07-21
 *      Author: Hongbo.jiang
 */
#include "PUBLIC_INC/AUTO_REGISTER.H"
#include "ENV_CFG/SOFTWARE_ENV_CFG.h"


extern unsigned long AutoRegLoadStart;
extern unsigned int  AutoRegLoadSize;

void *auto_reg_get_func_cont_by_index(enum AUTO_REG_TYPE emRegType, unsigned int u16FindIndex)
{
    AUTO_REG_OBJ *p_auto_reg = NULL;
    UINT16 i;
    UINT16 u16MatchIndex = 0;

    unsigned long auto_reg_section_addr = (unsigned long)&AutoRegLoadStart;
    unsigned long auto_reg_section_len  = (unsigned long)&AutoRegLoadSize;
    //unsigned long auto_reg_section_end  = (unsigned long)(AUTO_SECTION_END);
    unsigned int   auto_reg_item = ((unsigned int)auto_reg_section_len / sizeof(AUTO_REG_OBJ));


    if(u16FindIndex > auto_reg_item)  return NULL;

    p_auto_reg = (AUTO_REG_OBJ *)(auto_reg_section_addr);

    for(i = 0; i < auto_reg_item; i++)
    {
        if(p_auto_reg[i].emType == emRegType)
        {
            if(u16MatchIndex == u16FindIndex)
            {
                //DBG_I("[%d]: %s type:%d addr:0x%x",i,p_auto_reg->name,p_auto_reg->type,p_auto_reg->p_user_reg_data);
                return p_auto_reg[i].p_reg_data;
            }
            u16MatchIndex++;
        }
    }
    return NULL;
}



