#include "universal.h"

/* function: 
 *
 * descrip:
 *
 * iptpu  :
 *
 * return :
 *
 * */


/* function: 
 *
 * descrip:
 *
 * iptpu  :
 *
 * return :
 *
 * */
bool IsUniversal (char *pStr1, char *pStr2)
{
	if (pStr1 == NULL && pStr2 == NULL )
	{
		return true;
	}
	if (pStr1 == NULL && pStr2 != NULL)
	{
		return false;
	}
	if (pStr1 != NULL && pStr2 == NULL)
	{
		return true;
	}

	u32 len1 = strlen (pStr1);
	u32 len2 = strlen (pStr2);
	u32 index1 = 0, index2 = 0;

	if (len1 < len2 )
	{
		return false;
	}

	for (index1=0; index1<len1; index1++)
	{
		if (*(pStr1 + index1) == *(pStr2 + index2))
		{
			index2 += 1;
		}
	}
		
	if (index2 == len2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

char* FindUniveral (char dst [][10], u32 len1, char src[][10], u32 len2)
{
	char *pRes = (char*)malloc(len1*10 + 1);
	if (pRes == NULL)
	{
		return NULL;
	}
	memset (pRes, 0, len1*10);
	u32 index1 = 0, index2 = 0;
	u32 resIndex = 0;

	for (index1 = 0; index1 < len1; index1 ++)
	{
		for (index2=0; index2<len2; index2++)
		{
			if (IsUniversal (dst[index1], src[index2]) == true)
			{
				memcpy (pRes + resIndex*10, dst[index1], 10);
				resIndex += 1;
			}
		}
	}
	
	return pRes;
}
