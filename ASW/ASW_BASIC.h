/*
 * ASW_BASIC.h
 *
 * *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */
#ifndef ASW_BASIC_H_
#define ASW_BASIC_H_

typedef void(*AswInitType)(void);

typedef struct
{
	AswInitType         pf_asw_init;    // Task process entity pointer
	unsigned short      enable;			  // Task enable word
}ASW_INIT_ITEM_T;

#define ASW_INIT_ITEM_TAB   \
{\
    {pfc_controller_init,	1},       \
/*	{derating_init,			1},        */     \
	{measure_init,			1},               \
	{diagnostic_init,			1},\
/*	{sys_fsm_init,		    1},			 */   \
	{power_fsm_init,	    1},			      \
	{vpfc_mgt_init,	    	1},			      \
}


extern void asw_init(void);
extern void asw_1msTask(void);

#endif /* ASW_HAL_BASIC_H_ */

