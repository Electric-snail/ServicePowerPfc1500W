/*
 * BSW_SVC_BASIC.h
 *
 * *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#ifndef BSW_SVC_BASIC_H_
#define BSW_SVC_BASIC_H_

#include "SOFTWARE_ENV_CFG.h"

typedef void(*SvcInitType)(void);

typedef struct
{
	SvcInitType pf_svc_init;    // Task process entity pointer
	UINT8       enable;			  // Task enable word
}SVC_INIT_ITEM_T;

#ifndef DLLX64
#define SVC_INIT_TAB \
{\
  {bsw_svc_vScheInit,			1},\
  {apl_init,                    			1},\
  {param_core_init,             	1},\
  {storage_init,                		1},\
/*  {sfra_init,                   1},*/\
  {sw_scope_init,               	1},\
}
#else
#define SVC_INIT_TAB \
{\
	{bsw_svc_vScheInit,			1},\
	{sys_fsm_init	,			1},\
}
#endif
extern void bsw_svc_init(void);


#endif /* BSW_SVC_BASIC_H_ */
