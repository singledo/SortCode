#include "_fsm.h"

static Action FSM_find_action (FSM_entry_t *entry, FSM_EVENT_t evt, FSM_node_t *table)
{
    assert (entry != NULL);
    assert (table != NULL);
    int i = 0;
    FSM_node_t *p_node = NULL;
    for (i=0; i<entry->st_count; i++) {
        p_node = table+i;
        if ((entry->curr_sta == p_node->curr_sta) && (p_node->event == evt)) {
            return p_node->action;
        }
    }
    return NULL;
}

FSM_STA_t FMS_next_sta (FSM_entry_t *entry, FSM_EVENT_t evt)
{
    FSM_STA_t next_sta = WRONG_MAX_STA;
    FSM_node_t *table = entry->table;
    Action action = FSM_find_action (entry, evt, table);
    if (NULL == action) {
        return next_sta;
    }
    next_sta = action (entry, evt);
    return next_sta;
}


/*
 * By zhangjun on 20.01.22.
 * function: FSM_register_table
 * description:
 * input arg:
 * output:
 * return:
 */
bool FSM_register_table (FSM_entry_t *entry, FSM_node_t *table, int table_counts)
{
    assert (entry != NULL);
    assert (table != NULL);

    entry->table = table;
    entry->st_count = table_counts;

    return true;
}

/*
 * By zhangjun on 20.01.22.
 * function: FSM_init
 * description:
 * input arg:
 * output:
 * return:
 */
void FSM_init (FSM_entry_t *entry)
{
    entry->curr_sta = INIT_STA;
    entry->table = NULL;
    entry->st_count = 0;
}

