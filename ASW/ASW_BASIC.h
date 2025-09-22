/*
 * ASW_BASIC.h
 *
 * *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */
#ifndef ASW_BASIC_H_
#define ASW_BASIC_H_



typedef void  (*pf_asw_id_init)(void);

typedef struct
{
    const char     			*asw_name;
    pf_asw_id_init  			 asw_id_init;
    unsigned char           asw_id_status;
}ASW_INIT_OBJ;

#define REG_ASW_SECTION  __attribute__ ((used,section(".ASW_REG_SECTION")))

#define REG_ASW_INIT_ITEM(name,p_user_data)  const AUTO_REG_OBJ _auto_reg_##name REG_ASW_SECTION = {#name,AUTO_REG_ASW_INIT,p_user_data};

///-------device
#define REG_ASW_INIT(asw_name,init)                                                                      \
                static ASW_INIT_OBJ asw_init_##asw_name = {#asw_name,init,0};\
                REG_ASW_INIT_ITEM(asw_name,(void*)&asw_init_##asw_name)

extern void asw_init(void);

#endif



