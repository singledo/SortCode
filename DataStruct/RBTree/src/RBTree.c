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

bool RBTreeKeyIsExit(const RBTree *tree, KeyT key)
{
	if (tree == NULL)
	{
		return false;
	}
	RBNode *next = tree;
	while (next != NULL)
	{
		if (key < next->key)
		{
			next = next->l;
		}
		else if (key == next->key)
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

/* function: RBTreeKeySearch
 *
 * description:
 *
 * input:
 *
 * output:
 *
 * return:
 */

RBNode * RBTreeKeySearch(const RBTree * tree, KeyT key)
{
	if (tree == NULL)
	{
		return NULL;
	}
	RBNode *next = tree;
	RBNode *pre  = tree;
	
	while (next != NULL)
	{
		pre = next;
		if (key < next->key)
		{
			next = next->l;
		}
		else if (key == next->key)
		{
			return pre;
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

RBNode * RBTreeKeySuccessor(RBTree *tree, KeyT key)
{
	if (tree == NULL || RBTreeKeyIsExit(tree, key) == false)
	{
		DEBUG("TREE Is Empty Or The Key Not Exit In The Tree \r\n");
		return NULL;
	}
	RBNode *node = RBTreeKeySearch(tree, key);
	if (node == NULL)
	{
		DEBUG("Tree Key Search Failed, key [%d] \r\n", key);
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
		return p;
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

bool RBNodeFree(RBNode **node)
{
	if (*node == NULL)
	{
		return false;
	}
	free (*node);
	*node = NULL;
	return true;
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

bool RBTreeDelete(RBTree **root, KeyT key)
{
    if (root == NULL)
    {
		DEBUG("Input Tree Is NULL \r\n");
        return false;
    }

	if (RBTreeKeyIsExit(*root, key) == false)
    {
		DEBUG("Not A Node In The Tree With Specified key [%d] \r\n", key);
        return false;
    }

	RBNode *target = RBTreeKeySearch(*root, key);
	RBNode *z = NULL;
	if (target == NULL)
	{
		DEBUG("Find Failed Specifiled Node with key [%d] \r\n", key);
		return false;
	}

	RBNode *successor_node = NULL;
	RBNode *p = target->p;
	ColorT  del_color = BLACK;

	/*case 1: destination node have no children node */
	/*              
	 *              pa                               pa
	 *           /       \                         /     \
	 *          Del       l      =====>         NULL      l
	 * */
    if (target->l == NULL && target->r == NULL)
    {
		/* root node */
		if (p == NULL)
		{
			RBTreeInit(*root);
		}
		else
		{
			if (target == p->r)
			{
				p->r = NULL;
			}
			else
			{
				p->l = NULL;
			}
			del_color = target->color;
			if (RBNodeFree(&target) == false)
			{
				DEBUG("free failed  key [%d] \r\n", key);
			}
		}
    }

	/*case 2: one children node */
	/*          pa                                  pa           
	 *       /       \                           /       \
	 *      R         Del               ====>   R         Del-R
	 *                  \
	 *                  Del-R
	 * */
    else if (target->l == NULL || target->r == NULL)
    {
		if (target->l != NULL)
		{
			if (target == p->l)
			{
				p->l         = target->l;
				target->l->p = p;
			}
			else
			{
				p->l         = target->r;
				target->r->p = p;
			}
		}
		else
		{
			if (target == p->l)
			{
				p->r         = target->l;
				target->l->p = p;
			}
			else
			{
				p->r         = target->r;
				target->r->p = p;
			}
		}
		del_color = target->color;
		if (RBNodeFree(&target) == false)
		{
			DEBUG("free failed  key [%d] \r\n", key);
		}
    }

	/*case 3 : two children node;*/
	/*                    pa
	 *                 /        \
	 *                pa-L      DeL
	 *                       /       \
	 *                     Del-L    Del-R
	 *
	 * */
    else
    {
		successor_node = RBTreeKeySuccessor(*root, key);
		if (successor_node == NULL)
		{
			DEBUG("Find Successor Node Failed; key [%d] \r\n", key);
			return false;
		}
		p = successor_node->p;
		if (successor_node == p->l)
		{
			p->l = NULL;
		}
		else
		{
			p->r = NULL;
		}
		del_color = target->color;
		COPYNODEWITHRELEASE(target, successor_node);
    }
	if (del_color == BLACK)
	{
    	RBTreeDelFix(root, p);
	}
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

void RBTreeDelFix(RBTree **tree, RBNode **del)
{
	/*left children node*/
    RBNode *pNode = *del;
    RBNode *root  = *tree;
    RBNode *p  = NULL;
    RBNode *w  = NULL;
    RBNode *wl = NULL;
    RBNode *wr = NULL;

    while ( pNode != root && pNode->color == BLACK )
    {
        p = pNode->p;
        w = pNode->r;
        if (w != NULL)
        {
            wl = w->l;
            wr = w->r;
        }
        else
        {
            wl = NULL;
            wr = NULL;
        }

        if (pNode == pNode->p->l)
        {
            /*  case 1: brother node w, w's color is RED
             *
             *          step 1: exchange  pa node and W color
             *          step 2: left rotate with the pa
             *
             *            |                                    |            
             *           pa-B                                 W-B
             *        /         \                          /       \
             *      x-B         W-R         =====>>      pa-R      WR-B
             *                /     \                  /       \
             *              WL-B   WR-B              X-B      WL-B
             */
            if (w->color = RED)
            {
                EXCHANGE(p->color, w->color);
                LeftRotate(&root, p);
                continue;
            }

            /*
             *   case 2: w's color is BLACK, and with two BLACK children
             *   
             *           step 1: delete a black (x,w,pa)
             *           step 2: x move to pa node.
             *        |                                  |          
             *       pa-R                               pa-R (nex x)
             *    /       \                          /       \
             *  x-B       W-B           ======>>   x-B       W-R
             *          /     \                            /     \
             *        WL-B   WR-B                        WL-B   WR-B
            */
            else if ( (wl != NULL && wl->color == BLACK) && \
                      (wr != NULL && wr->color == BLACK))
            {
                w->color = RED;
                pNode = p;
                continue;
            }
            /*
             *   case 3: w's color is BLACK, left children node's color is RED, right children node's color is black
             *
             *            step 1: exchange color between WL and W .
             *            step 2: right rotate with W
             *
             *            |                                       |             
             *           pa-R                                    pa-R
             *        /        \                              /        \
             *      X-B        W-B           =====>>        X-B        WL-B
             *              /      \                                       \
             *            WL-R     WR-B                                    W-R
             *                                                               \
             *                                                              WR-B
             */
            else if (wr != NULL && wr->color == BLACK)
            {
                EXCHANGE(wl->color, w->color); 
                RightRotate(&root, w);
                continue;
            }
            /*
             *  case 4:  w's color is BLACK, right children's color is RED
             *
             *           |                                     |            
             *          pa-R                                   W-R
             *       /        \          ========>>         /      \
             *     X-B        W-B                         pa-B     WR-B
             *             /      \                     /      \
             *           WL-R     WR-R                X-B     WL-R
            */
            w->color = p->color;
            p->color = BLACK;   
            w->r->color = BLACK;
            LeftRotate(&root, pNode->p);
            pNode = root;
        }

        /*right children node*/
        else
        {
            /*  case 5: brother node w, w's color is RED
             *
             *          step 1: exchange  pa node and W color
             *          step 2: right rotate with the pa
             *
             *            |                                    |            
             *           pa-B                                 W-B
             *        /         \                          /       \
             *      W-R         X-B         =====>>      WL-B      pa-R
             *    /     \                                        /      \
             *  WL-B   WR-B                                    WR-B      X-B
             */
            if (w->color = RED)
            {
                EXCHANGE(w->color, p->color);
                RightRotate(&root, p);
                continue;
            }

            /*
             *   case 6: w's color is BLACK, and with two BLACK children
             *   
             *           step 1: delete a black (x,w,pa)
             *           step 2: x move to pa node.
             *
             *            |                                  |          
             *           pa-R                               pa-R (nex x)
             *        /       \                          /       \
             *      W-B       X-B           ======>>   W-R       X-B
             *    /     \                            /     \
             *  WL-B   WR-B                        WL-B   WR-B           
             */
            else if ( (wl != NULL && wl->color == BLACK) && \
                      (wr != NULL && wr->color == BLACK))
            {
                w->color = RED;
                pNode = p;
                continue;
            }
             /*
             *   case 7: w's color is BLACK, left children node's color is RED, 
             *   left children node's color is black
             *
             *            step 1: exchange color between WR and W .
             *            step 2: right rotate with W
             *
             *            |                                       |             
             *           pa-R                                    pa-R
             *        /        \                              /        \
             *      W-B        X-B           =====>>        WR-B       X-B
             *    /      \                                /
             *  WL-B     WR-R                           W-R
             *                                          /
             *                                        WL-B        
             */

            else if (wr != NULL && wl->color == BLACK)
            {
                EXCHANGE(w->color, wr->color);
                LeftRotate(&root, w);
                continue;
            }
             /*
             *  case 8:  w's color is RED, right children's color is RED
             *
             *               |                                     |       
             *              pa-R                                  X-B     
             *           /        \          ========>>        /       \
             *         X-B        W-B                        WL-R    pa-R
             *      /      \                                       /      \
             *     WL-R     WR-R                                 WR-R     W-B
             */
            w->color = p->color;
            p->color = BLACK;   
            w->l->color = BLACK;
            RightRotate(&root, pNode->p);
            pNode = root;
        }
    }
    pNode->color = BLACK;
}


