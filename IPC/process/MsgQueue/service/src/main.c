#include "msgService.h"


int main (int argc, char *argv[])
{
    
    int queId = 0;
    int sta = 0;
    msg_t msg;
    
    queId = msgget (MSGKEY, IPC_CREAT);
    if (-1 == queId) {
        perror ("msgget  failed \r\n");
        printf ("errno:[%d] [%s] \r\n", errno, strerror(errno));
        exit (-1);
    }

    while (1) {
        sta = msgrcv (queId, &msg, sizeof(msg_t), 0, 0);
        if (-1 == sta) {
            exit (-1);
        }
        printf ("type: [%d] payload: [%s] \r\n", msg.type, msg.payload);
    }

    
    return 0;
}
