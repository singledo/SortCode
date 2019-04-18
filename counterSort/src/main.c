#include "counterSort.h"

int main(int argc, char *argv[])
{
	printf ("conter sort programe \r\n");
	u4 len = RandomLen(100);
	u4 maxval = RandomLen(100);

	u4 *arry = (u4*)malloc(sizeof(u4)*len);
	u4 *dst= (u4*)malloc(sizeof(u4)*len);
	if (arry == NULL)
	{
		printf ("malloc failed \r\n");
		exit(1);
	}
	printf ("len [%d] max val [%d] \r\n", len, maxval);

	RandomArry(arry, len, maxval);
	ShowArry(arry, len);
	CounterSort(arry, len, dst, maxval);
	ShowArry(dst, len);
	return 0;
}
