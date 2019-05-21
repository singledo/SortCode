#include "tree.h"

/*************************************************/
/*                                               */
/*function name:                         NodeInit*/
/*                                               */
/*description: initilizate the search tree's node*/
/*                                               */
/*input: root - search tree's node               */
/*************************************************/

void NodeInit(STree *root)
{
	root->p = NULL;
	root->l = NULL;
	root->r = NULL;
	root->key = DEFAULT_KEY;
	root->data = NULL;
}

/* function: SearchTree_CreateNode
 *
 * description: create a node fore search tree
 *
 * input: key  - key value 
 *        data - satelite data 
 *
 * output: null
 *
 * return: new node's pointer
 */

STreeNode * SearchTree_CreateNode(KeyT key, SateT data)
{
    if (key ==  DEFAULT_KEY)
    {
        return NULL;
    }
	STreeNode  *new = (STreeNode *)malloc(sizeof(STreeNode));
	if (new == NULL)
	{
		return NULL;
	}
	NodeInit(new);
	new->key = key;
	new->data = data;
	return new;
}

/* function: SearchTree_Insert
 *
 * description: insert a new node in tree .
 *
 * input:     tree      - target tree
 *            STreeNode - new node insert to tree
 * output: null
 *
 * return: false - insert failed 
 *         true  - insert succ
 */

bool SearchTree_Insert(STree *tree, STreeNode *new)
{
    STreeNode *pNodePre = tree;
    STreeNode *pNodeNext = NULL;
    if (new == NULL || tree == NULL)
    {
        return false;
    }
    if (SearchTree_Search(tree, new->key) != NULL)
    {
        /*have been exist*/
        return false;
    }
    pNodeNext = pNodePre;
    while (pNodeNext != NULL)
    {
        pNodePre = pNodeNext;
        if (new->key < pNodeNext->key)
        {
            pNodeNext = pNodeNext->l;
        }
        else if (new->key < pNodeNext->key)
        {
            /*in fact, we should not go here.*/
            return false;
        }
        else
        {
            pNodeNext = pNodeNext->r;
        }
    }
    if (pNodePre->key == DEFAULT_KEY)
    {
        pNodePre->key  = new->key;
        pNodePre->data = new->data;
        free(new);
        return true;
    }
    if (new->key < pNodePre->key)
    {
        pNodePre->l = new;
        new->p      = pNodePre;
    }
    else if (new->key == pNodePre->key)
    {
        /*in fact, rouine will not come here*/
        return false;
    }
    else
    {
        pNodePre->r = new;
        new->p      = pNodePre;
    }
    return true;
}

void SearchTree_Delete(STree *tree, KeyT val)
{

}

/* function: SearchTree_Search
 *
 * description: search special key in tree
 *
 * input:       tree - target tree 
 *              val  - special key val
 * output:      NULL
 *
 * return:      null  - not find 
 *              other - spcial node  pointer
 */

STreeNode* SearchTree_Search(STree *tree, KeyT val)
{
    STreeNode *phead = tree;
    STreeNode *pnext = NULL;
    if (phead == NULL)
    {
        return NULL;
    }
    pnext = phead;
    while (pnext != NULL)
    {
        if (val < pnext->key)
        {
            pnext = pnext->l;
        }
        else if (val == pnext->key)
        {
            return pnext;
        }
        else
        {
            pnext = pnext->r;
        }
    }
    return NULL;
}

/* function: SearchTree_Mininum
 *
 * description: find the mininum key value in tree
 *
 * input:    tree - target tree 
 *
 * output:   none 
 *
 * return:  the node pointer with smallest key value
 */

STreeNode * SearchTree_Mininum(STree *tree)
{
    STreeNode *pNodePre = tree;
    STreeNode *pNodeNext = NULL;

    if (tree == NULL)
    {
        return NULL;
    }
    pNodeNext = pNodePre;
    while (pNodeNext != NULL)
    {
        pNodePre = pNodeNext;
        pNodeNext = pNodeNext->l;
    }
    return pNodePre;
}

/* function: SearchTree_Maxinum
 *
 * description: find the maxinum key value in tree
 *
 * input:    tree - target tree 
 *
 * output:   none 
 *
 * return:  the node pointer with biggest key value
 */

STreeNode * SearchTree_Maxinum(STree *tree)
{
    STreeNode *pNodePre = tree;
    STreeNode *pNodeNext = NULL;

    if (tree == NULL)
    {
        return NULL;
    }
    pNodeNext = pNodePre;
    while (pNodeNext != NULL)
    {
        pNodePre = pNodeNext;
        pNodeNext = pNodeNext->r;
    }
    return pNodePre;

}

/* function:     Preorder
 *
 * description: preorder traver for tree 
 *
 * input:       tree 
 *
 * output: null
 *
 * return: node
 */

void Preorder(STree *tree)
{
    if (tree != NULL)
    {
        printf ("[%d]  ", tree->key);
        Preorder(tree->l);
        Preorder(tree->r);
    }
}

/* function:     Postorder for tree
 *
 * description:   Postorder traver for tree 
 *
 * input:       tree 
 *
 * output: null
 *
 * return: node
 */

void Postorder(STree *tree)
{
    if (tree != NULL)
    {
        Preorder(tree->l);
        Preorder(tree->r);
        printf ("[%d]  ", tree->key);
    }
}

/* function:    Inorder
 *
 * description: preorder traver for tree 
 *
 * input:       tree 
 *
 * output: null
 *
 * return: node
 */

void Inorder(STree *tree)
{
    if (tree != NULL)
    {
        Preorder(tree->l);
        printf ("[%d]  ", tree->key);
        Preorder(tree->r);
    }
}


STreeNode * SearchTree_Seecssor(STree *tree, STreeNode *node)
{

}


STreeNode * SearchTree_Predecessor(STree *tree, STreeNode *node)
{

}
