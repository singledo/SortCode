#include "_fsm.h"
#include "node_func.h"
/*
 *      -------------         -------------     -------------        -------------
 *      +    INIT   +   --->  +    IDEL   + --->+    RECV   + ------>+    RESOLVE +
 *      -------------         -------------     -------------        -------------
 *                                 /\                                  |
 *                                 |                                   |
 *                                 |                                   |
 *                                 +------------------------------------
 * */
FSM_node_t table[] = {
    {INIT_STA, SUCCESS_EVT,  init_sta_action, IDEL_STA},
    {IDEL_STA, SUCCESS_EVT,  idel_sta_action, RECV_STA},
    {RECV_STA, SUCCESS_EVT,  recv_sta_action, RESOLVE_STA},
    {RESOLVE_STA, SUCCESS_EVT, resolve_sta_action, IDEL_STA},
    {},
};

int main (int argc, char *argv[])
{
    printf ("FSM Demo \n");

    bool bret = false;
    FSM_node_t *p_table = table;
    int table_len = sizeof(table)/sizeof(table[0]);
    FSM_STA_t next_sta = WRONG_MAX_STA;

    FSM_entry_t fsmEntry;

    FSM_init (&fsmEntry);

    bret = FSM_register_table (&fsmEntry, p_table, table_len);
    if (false == bret) {
        printf ("[%s@%d] [%s]\n", __FUNCTION__, __LINE__, strerror (errno));
        return 1;
    }

    while (1) {
        next_sta = FMS_next_sta (&fsmEntry, SUCCESS_EVT);
        fsmEntry.curr_sta  = next_sta;
        fflush (stdout);
        sleep (1);
    }

    return 0;
}
