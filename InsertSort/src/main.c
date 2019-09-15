#include "InsertApi.h"

int main(int argc, char *argv[])
{
	printf ("insert sort programe \r\n");
	u32 arry[] =  {11, 9, 4, 2, 8, 44, 22, 55, 33};
	u32 len = sizeof(arry)/sizeof(arry[0]);
	TraverArry(arry, len);
	InsertSort(arry, len);
	TraverArry(arry, len);
	return 0;
}
