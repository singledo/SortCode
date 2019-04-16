#include "counterSort.h"


/*	input: 	arry - orgin arry
 *			len  - arry's length
 *			k    - dest arry's max val
 *	outout: dest - destion arry
 * */
void CounterSort(u4 *arry, u4 len, u4 *dest, u4 k)
{
	int i = 0;
	int j = 0;

	u4 *c = (u4*)malloc(sizeof(u4)*(k+1));
	if (c == NULL)
	{
		printf ("[%s] [%d] malloc failed \r\n", __F, __L);
		return;
	}

	// node in c is respresent the number of the val in the orgin arry
	for (i=0; i<len; i++)
	{
		c[*(arry+i)] += c[*(arry+i)] + 1;
	}
	
	// node in c is respresent the number of the val that less than val in the orgin arry
	for (i=1; i<k; i++)
	{
		c[i] = c[i] + c[i-1];
	}

	if (dest == NULL)
	{
		printf ("[%s] [%d] input NULL pointer\r\n", __F, __L);
		free(c);
		return;
	}

	for(i=len-1,j=k; i>0; i--) 
	{
		while(c[j]>0)
		{
			*(dest+i) = 
		}
	}


}



