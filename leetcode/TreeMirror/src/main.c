#include "TreeMirror.h"
#include "tree.h"

int main (int argc, char *argv[])
{
	u32 preOrder[] = {1, 2, 3, 4, 5, 6, 7};
	u32 inOrder[]  = {3, 2, 4, 1, 6, 5, 7};


	u32 preOrder2[] = {1, 2, 3, 4, 5, 6, 8};
	u32 inOrder2[]  = {3, 2, 4, 1, 6, 5, 8};

	u32 u4Len = sizeof(preOrder)/sizeof(preOrder[0]);
	Tree *root, *left, *right;


	left = OrderArry2BTree (preOrder, inOrder, u4Len);
	right = OrderArry2BTree (preOrder2, inOrder2, u4Len);
	root = NewNode (8);
	root->l = left;
	root->r = right;
	left->p = root;
	right->p = root;
	
	TreeShow (root, 0);

	if (TreeIsMirror (root) == false)
	{
		printf ("root not mirror \r\n");
	}
	else
	{
		printf ("root is mirror \r\n");
	}
	return 0;
}
