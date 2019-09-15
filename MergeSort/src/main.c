#include "MergeSort.h"


int main(int argc, char *argv[])
{
	printf ("Merge Sort Programe .... \r\n");
	u32 arry[][20] =
   	{
	{3, 2, 5, 6, 7, 11, 22},
	{9, 8, 7, 6, 5, 4, 3, 2,1},	
	{1, 3, 2, 4, 3, 8, 4, 231, 12, 2},
	};
	u32 i = 0;
	u32 j = 0;
	u32 len = 0;

	for (i=0; i<3; i++)
	{
		len = sizeof(arry[i])/sizeof(sizeof(arry[i][0]));
		/*TraverArry(arry[i], len);*/
		for (j=0; j<len; j++)
		{
			if (arry[i][j] == 0)
			{
				break;
			}
		}
		len = j;

		printf ("len: [%d]  \r\n", len);
		TraverArry(arry[i], len);
		MergeSort(arry[i], 0, (len-1)/2, len-1);
		TraverArry(arry[i], len);
		printf ("####### \r\n");

	}
	return 0;
}
