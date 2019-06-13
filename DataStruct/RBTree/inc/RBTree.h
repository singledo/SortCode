#ifndef _RBTree_h
#define _RBTree_h
#include "com.h"

#define INVAILDKEY  (0xFFFFFFFF)
#define INVAILDDATA (0xFFFFFFFF)

typedef enum Color
{
	RED=0,
	BLACK
} ColorT;

typedef ul DataT;
typedef u4 KeyT;

struct RBTreeNode
{
	struct RBTreeNode *p;
	struct RBTreeNode *l;
	struct RBTreeNode *r;
	KeyT   key;
	DataT  data;
	ColorT color;
};
typedef struct RBTreeNode RBNode;
typedef struct RBTreeNode RBTree;

#define COPYNODEWITHRELEASE(node1, node2) \
{\
	if ((u4*)(node1)->data != NULL) \
	{ \
		free ((u4*)(node1)->data);\
	} \
	(node1)->p     =    (node2)->p; \
	(node1)->l     =    (node2)->l; \
	(node1)->r     =    (node2)->r; \
	(node1)->key   =    (node2)->key; \
	(node1)->data  =    (node2)->data; \
	(node1)->color =    (node2)->color; \
	free (node2); \
}


RBNode * RBTree_NewNode(KeyT key, ColorT color, DataT data);
void RBTreeInit(RBTree *tree);
bool VaildNode(RBNode *node);
void RBTreeInsFix(RBTree **tree, RBNode *node);

#endif
