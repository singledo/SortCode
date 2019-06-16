#include "RBTree.h"

/* function:   RBTree_NewNode
 *
 * description: create new node for RB tree
 *
 * input: key   - key value
 *        color - node's color
 *        data  - node's data
 *
 * output: none
 *
 * return: new node's pointer
 */
RBNode * RBTree_NewNode(KeyT key, ColorT color, DataT data)
{
	RBNode *new = (RBNode*)malloc(sizeof(RBNode));
	if (new == NULL)
	{
		return NULL;
	}
	new->p      = NULL;
	new->l      = NULL;
	new->r      = NULL;
	new->key    = key;
	new->color  = color;
	new->data   = data;
	return new;
}

/* function: RBTreeInit
 *
 * description: init the init
 *
 * input: tree - point to the tree
 *
 * output: node
 *
 * return: node
 */

void RBTreeInit(RBTree *tree)
{
	if (tree == NULL)
	{
		return;
	}
	tree->p     = NULL;
	tree->l     = NULL;
	tree->r     = NULL;
	tree->key   = INVAILDKEY;
	tree->color = BLACK;
	tree->data  = INVAILDDATA;
}

/* function: VaildNode
 *
 * description: check the part of node
 *
 * input: node - source node
 *
 * output: none
 *
 * return: false
 *         true
 */
bool VaildNode(RBNode *node)
{
	if (node == NULL || node->key == INVAILDKEY)
	{
		return false;
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

bool RBTree_Search(const RBTree const **tree, RBNode *src, RBNode **dest)
{
	RBNode *pre, *next;
	RBNode *root = (RBNode*)(*tree);
	pre = next = NULL;
	if (tree == NULL || root == NULL || VaildNode(root) == false ||\
		VaildNode(src) == false)
	{
		return false;
	}
	pre = next = root;
	while (next != NULL)
	{
		pre = next;
		if (src->key < next->key)
		{
			next = next->l;
		}
		else if (src->key == next->key)
		{
			*dest = next;
			return true;
		}
		else
		{
			next = next->r;
		}
	}
	dest = NULL;
	return false;
}

/* function: RBTreeIsExit
 *
 * description: the node is exit in the tree
 *
 * input: tree - tree's pointer
 *
 * output: none
 *
 * return: false - not exit
 *         true  - exit
 */

bool RBTreeIsExit(const RBTree const **tree, RBNode *src)
{
	RBNode *pre, *next;
	RBNode *root = (RBNode*)(*tree);
	pre = next = NULL;
	if (tree == NULL || root == NULL || VaildNode(root) == false ||\
		VaildNode(src) == false)
	{
		return false;
	}
	pre = next = root;
	while (next != NULL)
	{
		pre = next;
		if (src->key < next->key)
		{
			next = next->l;
		}
		else if (src->key == next->key)
		{
			return true;
		}
		else
		{
			next = next->r;
		}
	}
	return false;
}


/* function: LeftRotate
 *
 * description:
 *
 * input: tree - root node of the tree
 *        pivot - 
 *
 * output: none
 *
 * return: none
 */

void LeftRotate(RBTree **tree, RBNode *pivot)
{
	/*                  x                                         x
	 *                  |                                         | 
	 *                pivot                                       Y
	 *             /        \     ============>             /        \
	 *            X          Y                           pivot        y-r
	 *          /   \      /   \                      /         \
	 *        x-l   x-r  y-l   y-r                   X           y-l
     *                                             /    \
     *                                           x-l    x-r
	 * */           
    if (tree == NULL || pivot == NULL)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        printf ("input Error \r\n");
        return;
    }
    RBNode *l = pivot->l;
    RBNode *r = pivot->r;
    RBNode *p = pivot->p;
    
    if (r != NULL)
    {
        pivot->r = r->l;
        if (r->l==NULL)
        {
            r->l->p=pivot;
        }
    }
    if (p == NULL)
    {
        *tree = r;
    }
    else
    {
        if (pivot == p->l)
        {
            p->l = r;
        }
        else
        {
            p->r = r;
        }
        r->p = p;
    }
}

/* function: RightRotate
 *
 * description: right rotate by the pivot node
 *
 * input: tree - root node of the tree
 *        pivot - pivot node
 *
 * output: none
 
 * return: none
 */

void RightRotate(RBTree **tree, RBNode *pivot)
{
    /*                  x                           x 
     *                  |                           |
     *                pivot                         X
     *             /        \                   /      \
     *            X          Y    ==>>        x-l     pivot
     *          /   \      /   \                     /      \
     *        x-l   x-r  y-l   y-r                 x-r       Y
     *                                                    /     \
     *                                                  y-l      y-r
     */

    if (tree == NULL || pivot == NULL)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        printf ("input Error \r\n");
        return;
    }
    RBNode *l = pivot->l;
    RBNode *r = pivot->r;
    RBNode *p = pivot->p;
    if (l != NULL)
    {
        pivot->l = l->r;
        if (l->r != NULL)
        {
            l->r->p = pivot;
        }
    }
    if (p != NULL)
    {
        if (pivot == p->l)
        {
            p->l = l;
        }
        else
        {
            p->r = l;
        }
        l->p = p;
    }
    else
    {
        *tree = l;
    }
}

/* function: RBTreeInsert
 *
 * description: insert a node to tree
 *
 * input: root - destination tree
 *        new  - new node
 *
 * output: none
 *
 * return: false - insert operation failed
 *         true  - insert operation success
 */

bool RBTreeInsert(RBTree **root, RBNode *new)
{
	RBNode *pre , *next ;

	pre = next = NULL;

	/*step 1: check input argument*/
	if (*root == NULL || new == NULL || \
		VaildNode(new) == false)
	{
		return false;
	}
	/*the tree is empty, copy the new node to root node*/
	if (VaildNode(*root) == false)
	{
		COPYNODEWITHRELEASE(*root, new);
		(*root)->color = BLACK;
		return true;
	}
	/*the insert node is exit in tree */
	if (RBTreeIsExit(root, new) == true)
	{
		return false;
	}

	/* step 2: find the parent node of the insert node*/
	pre = next = *root;
	while (next != NULL)
	{
		pre = next;
		if (new->key < next->key)
		{
			next = next->l;
		}
		else if (new->key == next->key)
		{
			/*routine should not come to here*/
			return false;
		} 
		else
		{
			next = next->r;
		}
	}

	/* step 3: inset the new node into tree*/
	if (new->key < pre->key)
	{
		pre->l = new;
	}
	else if (new->key == pre->key)
	{
		/*routine should come to here */
		return false;
	}
	else
	{
		pre->r = new;
	}
	new->p = pre;
	new->color = RED;
	RBTreeInsFix(root, new);
}

/* function:  RBTreeInsFix
 *
 * description: insert node to the tree will break the tree attribute.
 *              the function is rebuild the true attribute.
 *
 * input: tree - tree pointer 
 *        node - insert node
 *
 * output: none 
 *
 * return: none
 */
void RBTreeInsFix(RBTree **tree, RBNode *node)
{
	/*parent node is the left children */
	/*  
	 * case 1  -  uncle node's color is red, next pivot is gr;
	 *
	 *               gr-B                     gr-R    
	 *              /    \                   /    \
	 *            pa-R   un-R ========>    pa-B   un-B
	 *            /                        /          
	 *           z-R                      z-R             
	 *
	 *  case 2  - povit node is the right children node . next povit node is pa
	 *
	 *            X                  X
	 *            |                  |
	 *           gr-B               gr-B      
	 *          /    \             /    \
	 *         pa-R   un-B ====>  z-R   un-B
	 *            \               /
	 *            z-R            pa-R       
	 *
	 *  case 3  - povit node is the left children node
	 *
	 *             X                   X       
	 *             |                   |       
	 *            gr-B                pa-B     
	 *           /    \              /    \
	 *          pa-R   un-B         z-R   gr-R
	 *          /                            \
	 *         z-B                           un-B
	 * */

	/*parent node is the right children */
	/*   case 4  -  uncle node's color is red, next pivot is gr;
	 *
	 *                      gr-B                          gr-R
	 *                    /      \                      /      \
	 *                  un-R     pa-R    ======>      un-B     pa-B
	 *                             \                             \
	 *                             z-R                           z-R
	 *
	 *   case 5  - povit node is the left children node . next povit node is pa
	 *
	 *                          gr-B                            gr-B      
	 *                        /      \                        /      \
	 *                      un-B     pa-R     =======>      un-B     z-R
	 *                                /                                \
	 *                              z-R                                pa-R
	 *
	 *   case 6  - povit node is the right children node
	 *
	 *                           X                                   X
	 *                           |                                   |
	 *                          gr-B                                pa-B     
	 *                        /      \                            /      \
	 *                      un-B     pa-R      ========>        gr-R     Z-R
	 *                                 \                        /
	 *                                 z-R                     un-B
	 * */
	RBNode *z = node;
	RBNode *pa, *gr, *un;
	pa = gr = un = NULL;

	/*two layer case, z->p is the root node, so
	 * not go to the while inside */
	while (z->p != NULL && z->p->color == RED)
	{
		pa = z->p;
		gr = pa->p;
		if (pa == gr->l)
		{
			un = gr->r;
			/*case 1: uncle node's color is red*/
			if (un->color == RED)
			{
				un->color = BLACK;
				pa->color = BLACK;
				gr->color = RED;
				z = gr;
			}
			/*case 2: z is the right child node */
			else if (z == pa->r)
			{
				z = z->p;
				LeftRotate(tree, z);
			}
		    /*case 3: z is the left children node*/
			pa->color = RED;
			gr->color = BLACK;
			RightRotate(tree, gr);
		}
		else
		{
			un = gr->l;
			/* case 4 */
			if (un->color == RED)
			{
				un->color = BLACK;
				pa->color = BLACK;
				gr->color = RED;
				z = gr;
			}
			/*case 5 */
			else if (z == pa->l)
			{
				z = pa;
				LeftRotate(tree, z);
			}
			pa->color = RED;
			gr->color = BLACK;
			LeftRotate(tree, gr);
		}
	}
}

/* function: RBTreeSuccessor
 *
 * description: find the next bigger node
 *
 * input: root - root node
 *        node - specified node
 *
 * output: none
 *
 * return: destnation
 *
 */

RBNode* RBTreeSuccessor(RBTree *root, RBNode *node)
{
    if (root == NULL || node == NULL)
    {
        return NULL;
    }

    if (RBTreeIsExit(&root, node) == false)
    {
        return NULL;
    }

    if (node->r == NULL)
    {
        RBNode *p = node->p;
        RBNode *curr = node;
        while (p != NULL && curr == p->r)
        {
            curr = p;
            p   = p->p;
        }
    }
    else
    {
        RBNode *next = NULL;
        RBNode *pre  = NULL;

        pre  = node->r;   
        next = node->r;
        while (next != NULL)
        {
            pre = next;
            next = next->l;
        }
        return pre;
    }
}

/* function:  RBTreeDelete
 *
 * description: delete a node from the tree
 *
 * input: root - root node
 *        node - specified node
 *
 * output: none
 *
 * return: false  - delete failed 
 *         true   - delete success
 *
 */

bool RBTreeDelete(RBTree **root, RBNode *node)
{
    if (root == NULL || node == NULL)
    {
        return false;
    }
    if (RBTreeIsExit(root, node) == false)
    {
        return false;
    }
    if (node->l == NULL && node->r == NULL)
    {

    }
    else if (node->l == NULL || node->r == NULL)
    {

    }
    else
    {

    }
    RBTreeDelFix(root, node);
}

void RBTreeDelFix(RBTree **tree, RBNode *node)
{

}




