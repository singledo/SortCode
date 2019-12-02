#include "TreeMirror.h"

/* function    : NodeIsEqual 
 * description : 
 * input       :
 * return      :
 */
bool NodeIsEqual (tNode *node1, tNode *node2)
{
	if ((node1 == NULL &&  node2 != NULL) || \
			(node1 != NULL &&  node2 == NULL))
	{
		return false;
	}
	else if (node1 == NULL || node2 == NULL)
	{
		return true;
	}
	else
	{
		if (node1->u4Data == node2->u4Data )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/* function    : 
 * description : 
 * input       :
 * return      :
 */
bool TreeIsEqual (Tree *pTree1, Tree *pTree2)
{
	if (NodeIsEqual (pTree1, pTree2) == false)
	{
		return false;
	}

	if (pTree1 == NULL && pTree2 == NULL)
	{
		return true;
	}

	if (TreeIsEqual (pTree1->l, pTree2->l) == false )
	{
		return false;
	}

	if (TreeIsEqual (pTree1->r, pTree2->r) == false )
	{
		return false;
	}

	return true;
}

/* function    : 
 * description : 
 * input       :
 * return      :
 */
bool TreeIsMirror (Tree *root)
{
	if (root == NULL)
	{
		return true;
	}
	return TreeIsEqual (root->l, root->r);
}

