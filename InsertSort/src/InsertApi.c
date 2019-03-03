#include "InsertApi.h"

void InsertSort(u32 *arry, u32 len)
{
	int i = 0, j = 0;
	u32 temp = 0;
	
	for (i=1; i<len; i++)
	{
		temp = *(arry+i);
		j = i - 1;
		while (j>=0 && *(arry+j)>temp)
		{
			*(arry+j+1) = *(arry+j);
			j -= 1;
		}
		*(arry+j+1) = temp;
	}
}

void TraverArry(u32 *arry, u32 len)
{
	u32 i = 0;
	for (i=0; i<len; i++)
	{
		printf ("%d  ", *(arry+i));
	}
	printf ("\r\n");
}


