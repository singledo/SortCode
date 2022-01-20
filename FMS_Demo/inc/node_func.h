#ifndef _node_func_h
#define _node_func_h

#include "_fsm.h"


FSM_STA_t init_sta_action (FSM_entry_t *entry, FSM_EVENT_t evt);

FSM_STA_t idel_sta_action (FSM_entry_t *entry, FSM_EVENT_t evt);

FSM_STA_t recv_sta_action (FSM_entry_t *entry, FSM_EVENT_t evt);

FSM_STA_t resolve_sta_action (FSM_entry_t *entry, FSM_EVENT_t evt);

#endif
