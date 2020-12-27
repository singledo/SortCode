#include "msgClient.h"


#define MSGKEY 0x2250


typedef enum
{
    CLINET1 = 0,
}msgType;


typedef struct
{
    msgType type;
    char payload[25];
            
}msg_t;


int main (int argc, char *argv[])
{


    int queId = 0;                                                         
    int sta = 0;                                                           
    msg_t msg;                                                             
    char buf[] = "zhangjun";

    queId = msgget (MSGKEY, 0666|IPC_CREAT);                               
    if (-1 == queId) {                                                     
        perror ("msgget  failed \r\n");                                    
        exit (-1);                                                         

    }                                                                      

    msg.type = 0;
    memcpy(msg.payload, buf, strlen(buf));
    
    sta = msgsnd (queId, &msg, sizeof(msg), 0);
    if (-1 == sta) {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        exit (-1);
    }
    

    return 0;
}
