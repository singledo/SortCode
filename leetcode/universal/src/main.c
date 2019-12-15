#include "universal.h"

int main (int argc, char *argv[])
{
	printf ("find universal word !!! \r\n");
	
	char dst[] = "aabbcc";
	char src[] = "abd";

	if (IsUniversal (dst, src) == false)
	{
		printf ("[%s] [%s] [failed] \r\n", dst, src );
	}
	else
	{
		printf ("[%s] [%s] [success] \r\n", dst, src );
	}

	char A[][10] = {"amazon","apple","facebook","google","leetcode"};
	char B[][10] = {"lo","eo"};
	u32 len1 = sizeof(A)/sizeof(A[0]);
	u32 len2 = sizeof(B)/sizeof(B[0]);


	char *pRes = FindUniveral (A, len1, B, len2);
	u32 index = 0;


	if (pRes != NULL)
	{
		for (index=0; index<len1; index++)
		{
			printf ("[%s] \r\n", *(pRes+index*10));
		}
	}

	return 0;
}
