/*
 * FSM_CORE.c
 *
 *  Created on: 2022.9.17
 *      Author: hongbo.jiang
 */
#ifdef DLLX64
	#include "BSW_FSM_CORE.h"
#else
	#include "FSM/BSW_FSM_CORE.h"
#endif

void fsm_init(fsm_obj_t* p_fsm) {
	UINT8 i = 0;
	if (p_fsm == NULL)
		return;
	p_fsm->u8PreStateId = p_fsm->u8InitStateId;
	p_fsm->u8CurStateId = p_fsm->u8InitStateId;
	p_fsm->u8NextStateId = p_fsm->u8InitStateId;
	p_fsm->u8IsFsmInit = 1;
	p_fsm->u8IsStateChange = STATE_IS_CHANGE;
	for (i = 0; i < p_fsm->u8StateTotalNum; i++)
	{
		if (p_fsm->p_fsm_item_tab[i].u8FsmStateId != i) {
			p_fsm->u8IsFsmInit = 0;
			p_fsm->u8IsStateChange = STATE_IS_UNCHANGE;
		}
	}


}

void fsm_fun(fsm_obj_t* p_fsm)
{
	const fsm_item_obj_t* p_fsm_item;
	if (p_fsm->u8IsFsmInit == 0) { return; }

	if (p_fsm->u8IsStateChange > 0)
	{
		p_fsm->u8IsStateChange = 0;
		p_fsm->u8PreStateId = p_fsm->u8CurStateId;
		p_fsm->u8CurStateId = p_fsm->u8NextStateId;
		p_fsm_item = &p_fsm->p_fsm_item_tab[p_fsm->u8PreStateId];
		if (p_fsm_item == NULL)
			return;
		if (p_fsm_item->fsm_out_func != NULL) {
			p_fsm_item->fsm_out_func();
		}
		p_fsm_item = &p_fsm->p_fsm_item_tab[p_fsm->u8CurStateId];
		if (p_fsm_item == NULL)
			return;
		if (p_fsm_item->fsm_in_func != NULL) {
			p_fsm_item->fsm_in_func();
		}
		p_fsm->u16TrigEven = 0;
	}
	p_fsm_item = &p_fsm->p_fsm_item_tab[p_fsm->u8CurStateId];
	if (p_fsm_item == NULL)
		return;
	if (p_fsm_item->fsm_exe_func != NULL) {
		p_fsm_item->fsm_exe_func();
	}
}

void fsm_emit_event(fsm_obj_t* p_fsm, UINT16 u16TrigEvent)
{
	const fsm_item_obj_t* p_fsm_item;
	UINT8 u8NextStatusId = 0;
	if (p_fsm == NULL)
		return;
	if ((u16TrigEvent <= p_fsm->u16TrigEven) && (p_fsm->u8IsStateChange == 1))
		return;
	p_fsm_item = &p_fsm->p_fsm_item_tab[p_fsm->u8CurStateId];
	if (p_fsm_item == NULL)
		return;
	if (p_fsm_item->fsm_cond_func != NULL)
	{
		p_fsm->u16TrigEven = u16TrigEvent;
		u8NextStatusId = p_fsm_item->fsm_cond_func(p_fsm->u16TrigEven);
		if (u8NextStatusId != p_fsm->u8CurStateId) {
			if (u8NextStatusId < p_fsm->u8StateTotalNum) {
				p_fsm->u8NextStateId = u8NextStatusId;
				p_fsm->u8IsStateChange = 1;
			}
		}
	}
}

UINT8 get_fsm_status(fsm_obj_t* p_fsm){
	if(p_fsm == NULL)
		return	INVALID_FSM_ID;
	return p_fsm->u8CurStateId;
}
