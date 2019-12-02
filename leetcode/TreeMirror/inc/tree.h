#ifndef _Tree_h
#define _Tree_h
#include "com.h"

struct Node
{
	struct Node *l;
	struct Node *r;
	struct Node *p;
	u32    u4Data;
};

typedef struct Node tNode;
typedef struct Node Tree;

tNode *NewNode (u32 u4Data);
void TreeShow(tNode *node, u4 level);
tNode * OrderArry2BTree (u32 pre[], u32 in[], u32 len);

#endif
