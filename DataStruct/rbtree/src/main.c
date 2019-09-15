#include "rbtree.h"
#include "rbtree_show.h"

int main(int argc, char *argv[])
{
    printf ("RBTree programe ................ \r\n");
    tTree tree;
    tRB_node *pEarseNode = NULL;
    u4 index  = 0;
    u4 arry[] = {12,8,9,11,10,2,1,5,3,4};
    u4 len    = sizeof(arry)/sizeof(arry[0]);
    ull key = 0;

    rbtree_init (&tree);

    for (index=0; index<len; index++)
    {
        if (rbtree_insert (&tree, arry[index], NULL, BLACK) == true)
        {

        }
        else
        {
            printf ("[%d] [failed] \r\n", arry[index]);
        }
    }
    rbtree_show (tree.root, 0);

    printf ("\r\n\r\n  ----------------------------------------------- \r\n") ;
    for (index=0; index<len; index++)
    {
        key = arry[index];
        if (rbtree_del (&tree, key, &pEarseNode) == true)
        {
            printf ("key [%d] \r\n", key);
            free (pEarseNode);
        }
        else
        {
            printf ("earse fialed");
        }

        rbtree_show (tree.root, 0);
        printf ("\r\n\r\n  ----------------------------------------------- \r\n") ;
    }

    return 0;
}
