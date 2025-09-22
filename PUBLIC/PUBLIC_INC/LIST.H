/*
 * list.h
 *
 *  Created on: 2022-07-21
 *      Author: Hongbo.jiang
 */

#ifndef BSW_BASIC_LIST_H_
#define BSW_BASIC_LIST_H_

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

typedef struct list_head list_t;

struct list_head
{
    struct list_head *next;
    struct list_head *prev;
};

static INLINE void LIST_ADD_MID(struct list_head *new_node,
                                 struct list_head *prev_node,
                                 struct list_head *next_node)
{
    next_node->prev = new_node;
    prev_node->next = new_node;
    new_node->prev  = prev_node;
    new_node->next  = next_node;
}

static INLINE void INIT_LIST_HEAD(struct list_head *pst_list)
{
    pst_list->next = pst_list;
    pst_list->prev = pst_list;
}

static INLINE void LIST_ADD_BACK(struct list_head *p_new,struct list_head *p_head)
{
    LIST_ADD_MID(p_new, p_head,p_head->next);
}

static INLINE void LIST_ADD_FRONT(struct list_head *p_new,struct list_head *p_head)
{
    LIST_ADD_MID(p_new, p_head->prev,p_head);
}

static INLINE void LIST_ADD_RAIL(struct list_head *p_new,struct list_head *p_head)
{
    LIST_ADD_MID(p_new, p_head->prev,p_head);
}

#define LIST_FOR_EACH_PREV(POS,HEAD) \
    for((POS) =(HEAD)->prev; (POS) != (HEAD);(POS)=(POS)->prev)

#define LIST_FOR_EACH_NEXT(NEXT,HEAD) \
    for((NEXT) =(HEAD)->next; (NEXT) != (HEAD);(NEXT)=(NEXT)->next)

#define LIST_ENTRY(ptt, type, member)           \
     (type*)((unsigned long)(ptt) - ((unsigned long)&(((type *)0)->member)))


#endif /* BSW_BASIC_LIST_H_ */
