#include "node_func.h"

FSM_STA_t init_sta_action (FSM_entry_t *entry, FSM_EVENT_t evt)
{
    printf ("FSM Current State: [%d] \n", entry->curr_sta);
    printf ("FSM Event: [%d] \n", evt);
    return IDEL_STA;
}


FSM_STA_t idel_sta_action (FSM_entry_t *entry, FSM_EVENT_t evt)
{
    printf ("FSM Current State: [%d] \n", entry->curr_sta);
    printf ("FSM Event: [%d] \n", evt);
    return RECV_STA;
}

FSM_STA_t recv_sta_action (FSM_entry_t *entry, FSM_EVENT_t evt)
{
    printf ("FSM Current State: [%d] \n", entry->curr_sta);
    printf ("FSM Event: [%d] ", evt);
    return RESOLVE_STA;
}

FSM_STA_t resolve_sta_action (FSM_entry_t *entry, FSM_EVENT_t evt)
{
    printf ("FSM Current State: [%d] \n", entry->curr_sta);
    printf ("FSM Event: [%d] \n", evt);
    sleep (1);
    return IDEL_STA;
}
