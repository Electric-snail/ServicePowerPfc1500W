/*
 * FSM_CORE.h
 *
 *  Created on: 2022/11/14
 *      Author: xj8r1j
 */

#ifndef _FSM_CORE_H_
#define _FSM_CORE_H_

#include "stdint.h"
#include "SVC/BSW_SVC_BASIC.h"

#define STATE_IS_UNCHANGE       0u
#define STATE_IS_CHANGE         1u
#define INVALID_FSM_ID          0xFF;

typedef void  (*pf_fsm_in)  		(void);
typedef void  (*pf_fsm_exe) 		(void);
typedef void  (*pf_fsm_out) 		(void);
typedef UINT8 (*pf_fsm_cond)	    (UINT16 event);

typedef struct
{
    UINT8               u8FsmStateId;
	pf_fsm_in      		fsm_in_func;
	pf_fsm_exe      	fsm_exe_func;
	pf_fsm_out     		fsm_out_func;
	pf_fsm_cond    		fsm_cond_func;
}fsm_item_obj_t;

typedef struct
{
    UINT8         			u8IsFsmInit;        //It indicate the whether the FSM has been initialized.
    UINT8					u8IsStateChange;    //It indicate the status is need to be change;
	const 				    fsm_item_obj_t *p_fsm_item_tab;     //The FSM item tabe.
	UINT8         			u8StateTotalNum;	//The total status number of FSM
	UINT8				    u8InitStateId;      //It define the initial status id of the FSM,after initialized, the u8CurStateId is the same u8InitStateId.
	UINT8         			u8PreStateId;       //It indicate the previous status id;
	UINT8         			u8CurStateId;	    //It indicate the current status id;
	UINT8         			u8NextStateId;      //It indicate the next status id;
	UINT16				    u16TrigEven;      //The happen action in current status, whether the status need to be changed, it is based on it
}fsm_obj_t;

extern void  fsm_emit_event(fsm_obj_t* p_fsm, uint16_t u16Event);
extern void  fsm_fun(fsm_obj_t* p_fsm);
extern void  fsm_init(fsm_obj_t* p_fsm);
extern UINT8 get_fsm_status(fsm_obj_t* p_fsm);

#define REG_FSM_OBJ(fsm_name,init_state_id,...) 		\
const fsm_item_obj_t  fsm_item_tab_##fsm_name[]={__VA_ARGS__};		\
fsm_obj_t             fsm_obj_##fsm_name={0,1,fsm_item_tab_##fsm_name,sizeof(fsm_item_tab_##fsm_name)/sizeof(fsm_item_obj_t),init_state_id};

#define FSM_OBJ_CALL(fsm_name)          fsm_fun(&fsm_obj_##fsm_name); 
#define FSM_INIT_CALL(fsm_name)         fsm_init(&fsm_obj_##fsm_name);
#define EMIT_FSM(fsm_name,event)		fsm_emit_event(&fsm_obj_##fsm_name,event)
#define EXTERN_FSM_OBJ(fsm_name)        extern fsm_obj_t fsm_obj_##fsm_name;
#define GET_FSM_STATUS(fsm_name)        get_fsm_status(&fsm_obj_##fsm_name)
#endif /* BSW_SVC_FSM_BSW_FSM_CORE_H_ */
