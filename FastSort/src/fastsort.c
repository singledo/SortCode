#include "fastsort.h"

/*	input:  start - start index of arry.
 *			end   - end index of arry.
 * */
u4 parttion(u4 *arry, u4 start, u4 end)
{
	u4 i = start;
	u4 j = start;

	for (j=start; j<end; j++)
	{
		if (*(arry+j) <= *(arry+end))
		{
			if (i == j)
			{
				i += 1;
			}
			else if(i < j)
			{
				swap(arry+i, arry+j);
				i += 1;
			}
		}
	}

	swap(arry+i, arry+end);
	return i;
}

void FastSort(u4 *arry, u4 start, u4 end)
{
	if (start < end)
	{
		u4 u4Device = parttion(arry, start, end);
		FastSort(arry, start, u4Device-1);
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

void swap(u4 *s1, u4 *s2)
{
	u4 temp = *s1 ;
	*s1 = *s2;
	*s2 = temp;
}
