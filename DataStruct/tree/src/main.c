#include "tree.h"

STree Stree;
#define LEN (5)
#define MAX (300)

int main(int argc, char *argv)
{
    printf ("binary search tree .... \r\n");
    NodeInit(&Stree);
    u4 u4Arry[LEN] = {0};
    u4 u4Index = 0;
    STreeNode *new = NULL;
    
    RandomArry(u4Arry, LEN, MAX);
    /*ShowArry(u4Arry, LEN);*/

    for (u4Index=0; u4Index<LEN; u4Index++)
    {
        new = SearchTree_CreateNode(u4Arry[u4Index], NULL);
        if (new != NULL)
        {
            if (SearchTree_Insert(&Stree, new) == false)
            {
                /*printf("Insert failed [%d] \r\n", u4Arry[u4Index]);*/
            }
            else
            {
                printf ("[%d] ", u4Arry[u4Index]);
            }
        }
    }
    printf ("\r\n######\r\n");
    Preorder(&Stree);
    printf ("\r\n");
    Postorder(&Stree);
    printf ("\r\n");
    Inorder(&Stree);
    printf ("\r\n");
}

