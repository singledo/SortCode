#include "tree.h"

STree Stree;
#define LEN (600)
#define MAX (3000)

int main(int argc, char *argv)
{
    printf ("binary search tree .... \r\n");
    NodeInit(&Stree);
    u4 u4Arry[LEN] = {0};
    u4 u4Index = 0;
    STreeNode *new = NULL;
    STreeNode *ret_node = NULL;
    STreeNode *successor_node = NULL;
    
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
    printf ("pre order \r\n");
    Preorder(&Stree);
    printf ("\r\n");

    printf ("post order \r\n");
    Postorder(&Stree);
    printf ("\r\n");

    printf ("in order \r\n");
    Inorder(&Stree);
    printf ("\r\n");

    printf ("#  travel compelete #####\r\n\r\n");
    
    printf ("tree search ##### \r\n");
    for (u4Index=0; u4Index<LEN; u4Index++)
    {
        ret_node = SearchTree_Search(&Stree, u4Arry[u4Index]);
        if (ret_node != NULL)
        {
            printf ("search succ [%d] \r\n", ret_node->key);
        }
        else
        {
            printf ("search failed [%d] \r\n", u4Arry[u4Index]);
        }
    }
    printf ("tree search [end] ##### \r\n");

    printf ("tree successor search ##### \r\n");
    for (u4Index=0; u4Index<LEN; u4Index++)
    {
        ret_node = SearchTree_Search(&Stree, u4Arry[u4Index]);
        if (ret_node != NULL)
        {
            successor_node = SearchTree_Seecssor(&Stree, ret_node);
            if (successor_node != NULL)
            {
                printf ("successor cur [%d]  successor [%d] success \r\n", ret_node->key,\
                        successor_node->key);
            }
            else
            {
                printf ("successor [%d] failed \r\n", ret_node->key);
            }
        }
        else
        {
            printf ("search failed [%d] \r\n", u4Arry[u4Index]);
        }
    }
    printf ("tree successor search [end] ##### \r\n");
    printf ("\r\n\r\n");

    for (u4Index=0; u4Index<LEN; u4Index++)
    {
        if (SearchTree_Delete(&Stree, u4Arry[u4Index]) == false)
        {
            printf ("delete [%d] failed \r\n", u4Arry[u4Index]);
        }
        else
        {
            printf ("delete [%d] ------  success\r\n", u4Arry[u4Index]);
        }
    }

}

