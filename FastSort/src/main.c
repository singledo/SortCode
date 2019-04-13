#include "fastsort.h"
#define LEN (20)


int main(int argc, char *argv[])
{
	printf ("fast sort programe ..... \r\n");

	u4 *arry = (u4*)malloc(sizeof(u4)*LEN);
	if (arry == NULL)
	{
		printf ("malloc failed \r\n");
		exit(1);
	}

	u4 i = 0;
	for (i=0; i<LEN; i++)
	{
		*(arry+i) = random() % 50;
	}
	/*swap((u4*)arry, (u4*)(arry+1));*/

	FastSort(arry, 0, LEN-1);
	FastArryTraver(arry, LEN);

	return 0;
}
