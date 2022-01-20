#ifndef _fsm_h
#define _fsm_h

#include "com.h"

typedef enum {
    SUCCESS_EVT = 0,
    FAILED_EVT ,
}FSM_EVENT_t;

typedef enum {
    INIT_STA = 0,
    IDEL_STA,
    RECV_STA,
    RESOLVE_STA,
    WRONG_MAX_STA,
}FSM_STA_t;

typedef struct FSM_node FSM_node_t;
typedef struct FSM_entry FSM_entry_t;
typedef FSM_STA_t (*Action) (FSM_entry_t *entry, FSM_EVENT_t evt);

struct FSM_node
{
    FSM_STA_t curr_sta;
    FSM_EVENT_t event;
    Action action;
    FSM_STA_t next_sta;
};

struct FSM_entry
{
    FSM_STA_t curr_sta;
    FSM_node_t * table;
    int st_count;
};


FSM_STA_t FMS_next_sta (FSM_entry_t *entry, FSM_EVENT_t evt);

bool FSM_register_table (FSM_entry_t *entry, FSM_node_t *table, int table_counts);

void FSM_init (FSM_entry_t *entry);

#endif
