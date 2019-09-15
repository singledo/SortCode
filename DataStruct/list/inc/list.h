#ifndef _list_h
#define _list_h
#include "com.h"
#define DEBUG printf

struct listnode
{
	struct listnode *next;
	u4 data;
};
typedef struct listnode tListNode;

tListNode* NewNode(u32 data);
void ListInsert(tListNode *head, u4 data );
void ListTraver(tListNode *head);
u4 ListLen(tListNode *head);

#endif

