#include "fastsort.h"

u4 parttion(u4 *arry, u4 start, u4 end)
{
	u4 i = start-1;
	u4 j = start;

	for (j=start; j<=end; j++)
	{
		if (*(arry+j) <= *(arry+end))
		{
			i += 1;
			SWAP(arry, i, j);
		}
	}
	i += 1;
	SWAP(arry, i, j);
	return i;
}

void FastSort(u4 *arry, u4 start, u4 end)
{
	if (start < end)
	{
		u4 u4Device = parttion(arry, start, end);
		FastSort(arry, start, u4Device - 1);
		FastSort(arry, u4Device + 1, end);
	}
}

void FastArryTraver(u4 *arry, u4 len)
{
	u4 i = 0;
	for (i=0; i<len; i++)
	{
		printf ("[%02d] ", *(arry+i));
	}
	printf ("\r\n");
}
