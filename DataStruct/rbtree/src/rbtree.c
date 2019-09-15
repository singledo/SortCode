#include "rbtree.h"

/****************************************************
 *  Function Name : key_compare 
 *  Description   : 
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
bool key_compare (ull key1, ull key2)
{
    return key1 == key2;
}

/****************************************************
 *  Function Name : rbtree_init 
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void rbtree_init (tTree *tree)
{
    assert (tree);
    tree->root    = NULL;
    tree->compare = key_compare;
    tree->creat   = rbtree_create_node;
    tree->free    = rbtree_free;
}

/****************************************************
 *  Function Name : rbtree_create_node
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
tRB_node* rbtree_create_node(ull key, void *data, tColor color)
{
    tRB_node * new = (tRB_node*)malloc(sizeof(tRB_node));
    if (new == NULL)
    {
        return NULL;
    }
    new->key   = key;
    new->data  = data;
    new->color = color;
    new->l     = NULL;
    new->r     = NULL;
    new->pa    = NULL;
    return new;
}

/****************************************************
 *  Function Name : rbtree_free
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void rbtree_free(tRB_node *del)
{
    assert (del);
    if (del->data != NULL)
    {
        free (del->data);
    }
    free (del);
}

/****************************************************
 *  Function Name : rbtree_set_sub_l
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void rbtree_set_sub_l(tRB_node *dest, tRB_node *left)
{
    assert (dest);
    dest->l = left;
}

/****************************************************
 *  Function Name : rbtree_set_sub_r
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void rbtree_set_sub_r(tRB_node *dest, tRB_node *right)
{
    assert (dest);
    dest->r = right;
}

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void rbtree_set_parent(tRB_node *dest, tRB_node *pa)
{
    assert (dest);
    dest->pa = pa;
}

/****************************************************
 *  Function Name : rbtree_set_color
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void rbtree_set_color(tRB_node *dest, tColor color)
{
    dest->color = color;
}

/****************************************************
 *  Function Name : rbtree_lookup
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
tRB_node* rbtree_lookup(tTree *tree, ull key)
{
    assert (tree);
    tRB_node *t_node = tree->root;
    ull d_key = key;
    ull t_key;

    while (t_node != NULL)
    {
        t_key = t_node->key;
        if (t_key < d_key)
        {
            t_node = t_node->r;
        }
        else if (t_key == d_key)
        {
            return t_node;
        }
        else
        {
            t_node = t_node->l;
        }
    }
    return NULL;
}

/****************************************************
 *  Function Name : rbtree_insert_point
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
tRB_node* rbtree_insert_point(tTree *tree, ull key)
{
    assert (tree);
    tRB_node *t_node = tree->root;
    tRB_node *pre_node = NULL;
    ull d_key = key;
    ull t_key;

    while (t_node != NULL)
    {
        pre_node = t_node;
        t_key = t_node->key;
        if (t_key < d_key)
        {
            t_node = t_node->r;
        }
        else if (t_key == d_key)
        {
            return NULL;
        }
        else
        {
            t_node = t_node->l;
        }
    }
    return pre_node;
}

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
/*           pa         pa
 *           |           |
 *           p   ===>    q
 *         /               \
 *        q                 p
 *         \              /
 *         q-r          q-r
 * */
void rbtree_right_rotate (tTree *tree, tRB_node *node)
{
    tRB_node *p = node;
    tRB_node *q = p->l;
    tRB_node *pa = p->pa;

    if (pa == NULL)
    {
        tree->root = q;
    }
    else
    {
        if (p == pa->l)
        {
            rbtree_set_sub_l (pa, q);
        }
        else
        {
            rbtree_set_sub_r (pa, q);
        }
    }
    rbtree_set_parent (q, pa);
    rbtree_set_parent (p, q);
    p->l = q->r;
    if (p->l)
        rbtree_set_parent (p->l, p);
    q->r = p;
}

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
/*            pa                       pa
 *            |                         |
 *            p                         q
 *              \       ===>          /
 *               q                   p
 *              /                     \
 *            q-l                       q-l
 * */
void rbtree_left_rotate (tTree *tree, tRB_node *node)
{
    tRB_node *p = node;
    tRB_node *q = node->r;
    tRB_node *pa = p->pa;
    if (pa == NULL)
    {
        tree->root = q;
    }
    else
    {
        if (p == pa->l)
        {
            rbtree_set_sub_l (pa, q);
        }
        else
        {
            rbtree_set_sub_r (pa, q);
        }
    }
    rbtree_set_parent (q, pa);
    rbtree_set_parent (p, q);
    p->r = q->l;
    if (p->r)
        rbtree_set_parent (p->r, p);
    rbtree_set_sub_l (q, p);
}

/****************************************************
 *  Function Name : rbtree_insert_fix 
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void rbtree_insert_fix (tTree *tree, tRB_node *node)
{
    tRB_node *z = node;
    tRB_node *pa, *un, *gr;
    pa = un = gr = NULL;
    
    while ((pa=z->pa) != NULL \
           && (pa->color == RED))
    {
        gr = pa->pa;
        if (pa == gr->l)
        {
            un = gr->r;
            if (un && un->color == RED)
            { /*case 1*/
                rbtree_set_color (gr, RED);
                rbtree_set_color (un, BLACK);
                rbtree_set_color (pa, BLACK);
                z = gr;
            }
            else 
            { /*case 2*/
                if (z == pa->r)
                {
                    rbtree_left_rotate (tree, pa);
                    z = pa;
                    pa = z->pa;
                }
                /*case 3*/
                rbtree_set_color (pa, BLACK);
                rbtree_set_color (gr, RED);
                rbtree_right_rotate (tree, gr);
            }
        }
        else
        {
            un = gr->l;
            if (un && un->color == RED)
            { /*case 4*/
                rbtree_set_color (gr, RED);
                rbtree_set_color (un, BLACK);
                rbtree_set_color (pa, BLACK);
                z = gr;
            }
            else 
            {
                if (z == pa->l)
                { /*case 5*/
                    rbtree_right_rotate (tree, gr);
                    z = pa;
                    pa = z->pa;
                }
                /*case 6*/
                rbtree_set_color (pa, BLACK);
                rbtree_set_color (gr, RED);
                rbtree_left_rotate (tree, gr);
            }
        }
    }
    rbtree_set_color (tree->root, BLACK);
}

/****************************************************
 *  Function Name : rbtree_insert
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
bool rbtree_insert (tTree *tree, ull key, void *data, tColor color)
{
    assert (tree);

    tRB_node *pInsertNode = NULL;
    tRB_node *newNode = NULL;
   
    if (rbtree_lookup (tree, key) != NULL) 
    {
        return false;
    }

    if ((tree->root != NULL) && \
        (pInsertNode = rbtree_insert_point (tree, key)) == NULL)
    {
        return false;
    }
    
    newNode = tree->creat (key, data, color);
    if (newNode == NULL)
    {
        return false;
    }
    rbtree_set_color (newNode, RED);
    if (tree->root == NULL)
    {
        tree->root = newNode;
    }
    else
    {
        if (key > pInsertNode->key)
        {
            rbtree_set_sub_r (pInsertNode, newNode);
        }
        else
        {
            rbtree_set_sub_l (pInsertNode, newNode);
        }
        rbtree_set_parent (newNode, pInsertNode);
    }
    rbtree_insert_fix (tree, newNode);
    return true;
}

/****************************************************
 *  Function Name : rbtree_successor
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
tRB_node* rbtree_successor(tTree *tree, ull key)
{
    tRB_node *node = rbtree_lookup (tree, key);
    tRB_node *pre  = NULL;

    if (node == NULL)
    {
        return NULL;
    }
    if (node->r)
    {
        node = node->r;
        pre = node;
        while (node != NULL)
        {
            pre = node;
            node = node->l;
        }
    }
    else
    {
        pre = node->pa;
        while ((pre != NULL) && \
               (node == pre->r))
        {
            node = pre;
            pre = pre->pa;
        }
    }
    return pre;
}

/****************************************************
 *  Function Name : rbtree_del
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
enum DEL_ERROR
{
    ERROR_NOSUCCESSOR, 
    ERROT_NOFIND,
};
bool rbtree_del(tTree *tree, ull key, tRB_node **dest_node)
{
    tRB_node *del_node = rbtree_lookup (tree, key);
    tRB_node *pa, *sub, *successor;
    tRB_node *fixNode = NULL;

    if (del_node == NULL)
    {
        return false;
    }
    if ((del_node->l != NULL ) && \
        (del_node->r != NULL) )
    {
        successor = rbtree_successor (tree, key);
        if (successor == NULL)
        {
            /*routine should not come here*/
            return false;
        }
        del_node->key = successor->key;
        if (del_node->data)
        {
            free (del_node->data);
        }
        del_node->data = successor->data;
        successor->data = NULL;
        /*delete successor node */
        if (successor->r != NULL)
        {
            if (successor == successor->pa->l)
            {
                successor->pa->l = successor->r;
            }
            else
            {
                successor->pa->r = successor->r;
            }
            rbtree_set_parent (successor->r, successor->pa);
        }
        else
        {
            if (successor == successor->pa->l)
            {
                successor->pa->l = NULL;
            }
            else
            {
                successor->pa->r = NULL;
            }
        }
        fixNode = successor->r;
        del_node = successor;
    }
    else if ((del_node->l != NULL) || \
             (del_node->r != NULL))
    {
        sub = del_node->l?del_node->l:del_node->r;
        if (del_node->pa == NULL)
        {
            tree->root = sub;
            rbtree_set_parent (sub, NULL);
        }
        else
        {
            if (del_node == del_node->pa->l)
            {
                rbtree_set_sub_l (del_node->pa, sub);
            }
            else
            {
                rbtree_set_sub_r (del_node->pa, sub);
            }
            rbtree_set_parent (sub, del_node->pa);
        }
        fixNode = sub;
    }
    else
    {
        pa = del_node->pa;
        if (pa == NULL)
        {
            tree->root = NULL;
        }
        else
        {
            if (del_node == pa->l)
            {
                pa->l = NULL;
            }
            else
            {
                pa->r = NULL;
            }
        }
        fixNode = NULL;
    }
    *dest_node = del_node;
    if (del_node != NULL && \
        del_node->color == BLACK)
    {
        rbtree_del_fix (tree, fixNode);
    }
    return true;
}

/****************************************************
 *  Function Name : rbtree_del_fix 
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void rbtree_del_fix (tTree *tree, tRB_node *node)
{
    tRB_node *pa, *w, *wl, *wr;
    while ( (node) && \
            ((node != tree->root) || (node->color != BLACK)))
    {
        pa = node->pa;
        if (pa && node == pa->l)
        {
            w = pa->r;
            if (w && w->color == RED)
            {
                /* case 1: brother node w, w's color is RED */
                rbtree_set_color (pa, RED);
                rbtree_set_color (w, BLACK);
                rbtree_left_rotate (tree, pa);
            }

            if (w  && \
                (w->l && w->l->color == BLACK) && \
                (w->r && w->r->color == BLACK) )
            {  
                /* case 2: w's color is BLACK, and with two BLACK children */
                w->color = BLACK;
                node = pa;
            }
            else 
            {
                /* case 3: w's color is BLACK, left children node's color is RED,
                 * right children node's color is black */
                if (w && \
                    w->r && w->r->color == BLACK)
                {
                    rbtree_set_color (w, RED);
                    if (w->l)
                    {
                        rbtree_set_color (w->l, BLACK);
                    }
                    rbtree_right_rotate (tree, w);
                }

                if (w && pa && w->l)
                {
                    /* case 3-2:  w's color is BLACK, right children's color is RED */
                    rbtree_set_color (w, pa->color);
                    rbtree_set_color (pa, BLACK);
                    rbtree_set_color (w->r, BLACK);
                    rbtree_left_rotate (tree, tree->root);
                    node = tree->root;
                }
                break;
            }
        }
        else if (pa && node == pa->r)
        {
            w = pa->l;
            if (w && \
                w->color == RED)
            {
                /* case 1: brother node w, w's color is RED */
                rbtree_set_color (pa, RED);
                rbtree_set_color (w, BLACK);
                rbtree_right_rotate (tree, pa);

            }
            if (w  && \
                (w->l && w->l->color == BLACK ) && \
                (w->r && w->r->color == BLACK) )
            {
                /* case 2: w's color is BLACK, and with two BLACK children */
                w->color = BLACK;
                node = pa;
            }
            else
            {
                if (w && \
                    w->l && w->l->color == BLACK)
                {
                    rbtree_set_color (w, RED);
                    if (w->r)
                    {
                        rbtree_set_color (w->r, BLACK);
                    }
                    rbtree_left_rotate (tree, w);
                }
                if (w && pa && w->l)
                {
                    /* case 3-2:  w's color is BLACK, right children's color is RED */
                    rbtree_set_color (w, pa->color);
                    rbtree_set_color (pa, BLACK);
                    rbtree_set_color (w->l, BLACK);
                    rbtree_right_rotate (tree, pa);
                    node = tree->root;
                }
                break;

            }
        }
        else
        {
            break;
        }
    }
    if (tree->root)
    {
        tree->root->color = BLACK;
    }
}
