#ifndef _TREE_H
#define _TREE_H
#include "com.h"

#define DEFAULT_KEY (0xFFFFFFFFUL)
typedef u4 KeyT;
typedef u4* SateT;

typedef struct STreeNode
{
	struct STreeNode *p;
	struct STreeNode *l;
	struct STreeNode *r;
	KeyT key;
	SateT data;
}STreeNode;

typedef STreeNode STree;

void NodeInit(STree *root);
STreeNode* SearchTree_Search(STree *tree, KeyT val);
bool SearchTree_Insert(STree *tree, STreeNode *new);
STreeNode * SearchTree_Mininum(STree *tree);
STreeNode * SearchTree_Maxinum(STree *tree);
void Preorder(STree *tree);
void Postorder(STree *tree);
void Inorder(STree *tree);
STreeNode * SearchTree_CreateNode(KeyT key, SateT data);

bool SearchTree_Delete(STree *tree, KeyT val);
void SearchTree_FreeNode(STreeNode **node);

STreeNode * SearchTree_Seecssor(STree *tree, STreeNode *node);

STreeNode * SearchTree_Predecessor(STree *tree, STreeNode *node);

#endif

