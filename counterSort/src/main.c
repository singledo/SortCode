#include "counterSort.h"

int main(int argc, char *argv[])
{
	printf ("conter sort programe \r\n");
	u4 len = 20;
	u4 *arry = (u4*)malloc(sizeof(u4)*len);
	if (arry == NULL)
	{
		printf ("malloc failed \r\n");
		exit(1);
	}
	RandomArry(arry, len, 50 );
	ShowArry(arry, len);


	return 0;
}
