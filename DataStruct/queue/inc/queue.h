#ifndef _QUEUE_H
#define _QUEUE_H
#include "com.h"

typedef u4 DataType;
struct Queue
{
	struct Queue *next;
	struct Queue *last;
	DataType data;
};
typedef struct Queue  Queue;
typedef struct Queue  QueueNode;

#endif
