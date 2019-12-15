#include "rangeSum.h"

u32 TreeRangesum (u32 l, u32 r, Tree *root)
{
	if (root == NULL)
	{
		return 0;
	}
	
	u32 rootData = root->u4Data;
	u32 resData  = 0;

	if (rootData >= l && rootData <= r)
	{
		resData += rootData;
	}
	if (root->l != NULL)
	{
		resData += TreeRangesum (l, r, root->l);
	}
	if (root->r != NULL)
	{
		resData += TreeRangesum (l, r, root->r);
	}
	return resData;
}

