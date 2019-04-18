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
	int dst_index = 0;

	int *c = (u4*)malloc(sizeof(u4)*(k+1));
	if (c == NULL)
	{
		printf ("[%s] [%d] malloc failed \r\n", __F, __L);
		return;
	}
	memset(c, 0, sizeof(u4)*(k+1));
	memset(dest, 0, sizeof(u4)*(len));
	
	/*printf ("orgin orde ");*/
	/*ShowArry(arry, len);*/
	// node in c is respresent the number of the val in the orgin arry
	for (i=0; i<len; i++)
	{
		c[*(arry+i)] = c[*(arry+i)] + 1;
	}

	/*printf ("counter [1] ");*/
	/*ShowArry(c, k);*/
	// node in c is respresent the number of the val that less than val in the orgin arry
	for (i=1; i<k; i++)
	{
		c[i] = c[i] + c[i-1];
	}

	/*printf ("counter [2] ");*/
	/*ShowArry(c, k);*/
	if (dest == NULL)
	{
		printf ("[%s] [%d] input NULL pointer\r\n", __F, __L);
		free(c);
		return;
	}

	for (i=len; i>0; i--)
	{
		dst_index = i - 1;
		c[arry[dst_index]] -= 1;
		*(dest + c[arry[dst_index]] ) = arry[dst_index];
		/*printf ("#%02d# %d # \r\n", arry[dst_index], c[arry[dst_index]]);*/
	}

	/*printf ("\r\nsort arry ");*/
	/*ShowArry(dest, len);*/
	free(c);
}



