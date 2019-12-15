#include "rangeSum.h"

int main (int argc, char *argv[])
{
	printf ("range sum programe \r\n");

	u32 preOrder[] = {1, 2, 3, 4, 5, 6, 7};
	u32 inOrder[]  = {3, 2, 4, 1, 6, 5, 7};
	u32 u4Len = sizeof(preOrder)/sizeof(preOrder[0]);
	Tree *root = OrderArry2BTree (preOrder, inOrder, u4Len);

	TreeShow (root, 0);

	u32 l = 1;
	u32 r = 5;
	u32 res = 0;
	res = TreeRangesum (l, r, root);
	printf ("l:[%d] r:[%d] res:[%d] \r\n", l, r, res);

	return 0;
}
