#include "tree.h"

/* function    : 
 * description : 
 * input       :
 * return      :
 */
static void padding(char ch, u4 n)
{
    u4 i = 0;
    for (i=0; i<n; i++)
        putchar (ch);
}

/* function    : TreeShow
 * description : display tree's data 
 * input       :
 * return      :
 */
void TreeShow(tNode *node, u4 level)
{
    if (node == NULL)
    {
        padding ('\t', level);
        puts (" #");
    }
    else
    {
        TreeShow (node->r, level+1);
        padding ('\t', level);
        printf ("[%02d]\n", node->u4Data);
        fflush (stdout);
        TreeShow(node->l, level+1);
    }
}

/* function    : NewNode 
 * description : Create new node
 * input       : u4Data - node's data filed
 * return      : pointer for new node
 */
tNode *NewNode (u32 u4Data)
{
	tNode *new = (tNode*)malloc(sizeof(tNode));
	if (new == NULL)
	{
		return NULL;
	}
	new->l = NULL;
	new->r = NULL;
	new->p = NULL;
	new->u4Data = u4Data;
	return new;
}

/* function    : OrderArry2BTree 
 * description : create tree by inorder and preorder
 * input       : pre - preorder for tree
 *               in  - inorder for tree
 * return      : pointer for root
 */
tNode * OrderArry2BTree (u32 pre[], u32 in[], u32 len)
{
	if (len == 0 )
	{
		return NULL;
	}
	
	u32 mid = 0, start = 0, end = len;
	u32 rootData = pre[0];

	for (mid=0; mid<end; mid++)
	{
		if (rootData == in[mid])
		{
			break;
		}
	}
	
	if (mid > end)
	{
		printf ("not find root node in inorder arry \r\n");
		return NULL;
	}

	tNode *new = NewNode (rootData);
	if (new == NULL)
	{
		printf ("Create node failed  \r\n");
		return NULL;
	}

	new->l = OrderArry2BTree (&pre[1], &in[0], mid);
	if (new->l != NULL)
	{
		new->l->p = new;
	}

	new->r = OrderArry2BTree (&pre[mid+1], &in[mid+1], mid);
	if (new->r != NULL)
	{
		new->r->p = new;
	}

	return new;
}



