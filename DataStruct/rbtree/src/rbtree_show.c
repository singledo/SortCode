#include "rbtree_show.h"

static void padding(char ch, u4 n)
{
    u4 i = 0;
    for (i=0; i<n; i++)
        putchar (ch);
}

void rbtree_show (tRB_node *node, u4 level)
{
    if (node == NULL)
    {
        padding ('\t', level);
        puts (" NIL");
    }
    else
    {
        rbtree_show (node->r, level+1);
        padding ('\t', level);
        if (node->color == BLACK)
            printf ("[%02d]\n", node->key);
        else
            printf ("#%02d#\n", node->key);
        fflush (stdout);
        rbtree_show (node->l, level+1);
    }
}
