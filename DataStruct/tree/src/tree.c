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
    memset(new, 0, sizeof(STreeNode));
    NodeInit(new);
    new->key = key;
    new->data = data;
    return new;
}

/* function:
 *
 * description:
 *
 * input:
 *
 * output:
 *
 * return:
 */

void SearchTree_FreeNode(STreeNode **node)
{
    if (*node == NULL)
    {
        return;
    }
    if ( (*node)->data != NULL)
    {
        free( (*node)->data);
    }
    free(*node);
    *node = NULL;
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

/* function:
 *
 * description:
 *
 * input:
 *
 * output:
 *
 * return:
 */

bool SearchTree_Delete(STree *tree, KeyT val)
{
    STreeNode *dest_node = SearchTree_Search(tree, val);
    STreeNode *p = NULL;

    if (dest_node == NULL)
    {
        /*not find the special node in tree*/
        return false;
    }
    if (dest_node->r == NULL && dest_node->l == NULL)
    {

        if (tree == dest_node)  
        {
            tree->key = DEFAULT_KEY;
            if (tree->data != NULL)
            {
                free (tree->data);
            }
            return true;
        }
        else
        {
            p = dest_node->p;
            if (p->r == dest_node)
            {
                p->r = NULL;
            }
            else
            {
                p->l = NULL;
            }
            if (dest_node->data != NULL)
            {
                free (dest_node->data);
            }
            free(dest_node);
        }
    }
    else if (dest_node->l == NULL || dest_node->r == NULL)
    {

        if (tree == dest_node)
        {
            STreeNode * new_root = NULL;
            if (tree->l == NULL)
            {
                new_root = tree->r;
            }
            else
            {
                new_root = tree->l;
            }
            if (tree->data != NULL)
            {
                free(tree->data);
            }
            tree->key   = new_root->key;
            tree->data  = new_root->data;
            tree->l     = new_root->l;
            tree->r     = new_root->r;
            if (new_root->l != NULL)
            {
                new_root->l->p = tree;
            }
            if (new_root->r != NULL)
            {
                new_root->r->p = tree;
            }
            free(new_root);
            return true;
        }
        else
        {
            p = dest_node->p;
            if (dest_node == p->l)
            {
                if (dest_node->r == NULL)
                {
                    p->l = dest_node->l;
                    dest_node->l->p = p;
                }
                else
                {
                    p->l = dest_node->r;
                    dest_node->r->p = p;
                }
            }
            else
            {
                if (dest_node->r == NULL)
                {
                    p->r = dest_node->l;
                    dest_node->l->p = p;
                }
                else
                {
                    p->r = dest_node->r;
                    dest_node->r->p = p;
                }
            }
        }
        if (dest_node->data != NULL)
        {
            free(dest_node->data);
        }
        free(dest_node);
    }
    else
    {

        STreeNode *successor_node = SearchTree_Seecssor(tree, dest_node);
        STreeNode temp_node ;
        
        memset(&temp_node, 0, sizeof(temp_node));
        STreeNode *temp = NULL;
        if (successor_node == NULL)
        {

            /*routine should not run in here*/
            return false;
        }
        else
        {

            /*the successor node must in dest_node's right sub tree*/
            /*and the seccessor node have no left children */
            temp = successor_node->p;

            printf ("[1] temp poninter \r\n");
            printf ("p [%08x] cur [%08x] l [%08x] r [%08x] \r\n", \
                    (u4)temp->p, (u4)temp, (u4)temp->l, \
                    (u4)temp->r);

            printf ("successor  poninter \r\n");
            printf ("p [%08x] cur [%08x] l [%08x] r [%08x] \r\n", \
                    (u4)successor_node->p, (u4)successor_node, (u4)successor_node->l, \
                    (u4)successor_node->r);

            memcpy(&temp_node, successor_node, sizeof(STreeNode));
            /*delete the successor node */
            if (temp->r == successor_node)
            {
                temp->r = successor_node->r;
            }
            else
            {
                temp->l = successor_node->r;
            }

            if (successor_node->r != NULL)
            {
                successor_node->r->p = temp;
            }
            if (dest_node->data != NULL)
            {
                free(dest_node->data);
            }
            free(successor_node);

            
            dest_node->key = temp_node.key;
            dest_node->data = temp_node.data;
        }
    }
	return true;
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
        printf ("[%d]   p [%08x] cur [%08x] l [%08x] r [%08x] \r\n", \
                tree->key, (u4)tree->p, (u4)tree, (u4)tree->l, (u4)tree->r);
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

/* function: SearchTree_Seecssor   
 *
 * description: find the seccessor node
 *
 * input:  tree - destion tree 
 *         node - current node
 *
 * output: None
 *
 * return: successor node pointer
 */

STreeNode * SearchTree_Seecssor(STree *tree, STreeNode *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->r != NULL)
    {
        return SearchTree_Mininum(node->r);
    }
    else
    {
        STreeNode *p = node->p;
        STreeNode *temp = node;
        while (p!=NULL && p->r==temp)
        {
            temp = p;
            p    = p->p;
        }
        return p;
    }
}

/* function: 
 *
 * description: find the predecessor node
 *
 * input:  tree - destion tree 
 *         node - current node
 *
 * output: None
 *
 * return: predecessor node pointer
 */

STreeNode * SearchTree_Predecessor(STree *tree, STreeNode *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->l != NULL)
    {
        return SearchTree_Maxinum(node->l);
    }
    else
    {
        STreeNode * p =  node->p;
        STreeNode * temp = node;
        while (p!=NULL && temp == p->l)
        {
            temp = p;
            p    = p->p;
        }
        return p;
    }
}
