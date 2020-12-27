#ifndef _msgService_h
#define _msgService_h

#include "com.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

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



#endif //_msgService_ 
