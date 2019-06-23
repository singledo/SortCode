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

#define EXCHANGE(pEx1, pEx2) \
{\
	u4 temp = pEx1;\
	pEx1 = pEx2; \
	pEx2 = temp; \
}



RBNode * RBTree_NewNode(KeyT key, ColorT color, DataT data);

void RBTreeInit(RBTree *tree);

bool VaildNode(RBNode *node);

bool RBTree_Search(const RBTree const **tree, RBNode *src, RBNode **dest);

bool RBTreeIsExit(const RBTree const **tree, RBNode *src);

void LeftRotate(RBTree **tree, RBNode *pivot);

void RightRotate(RBTree **tree, RBNode *pivot);

bool RBTreeInsert(RBTree **root, RBNode *new);

void RBTreeInsFix(RBTree **tree, RBNode *node);

bool RBTreeKeyIsExit(const RBTree *tree, KeyT key);

RBNode * RBTreeKeySearch(const RBTree * tree, KeyT key);

bool RBNodeFree(RBNode **node);

RBNode * RBTreeKeySuccessor(RBTree *tree, KeyT key);

void RBTreeDelFix(RBTree **tree, RBNode **node);

#endif
