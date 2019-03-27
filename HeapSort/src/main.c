#include "heapsort.h"

int main(int argc, char *argv[])
{
	printf ("heap sort programe ..... \r\n");
	tHeap heap;
	u4 i4Index  = 0;
	u4 u4Seed 	= 0;
	u4 u4ArryLen = 16;
	u4 val = 0;

	srandom(random());

	if (MallocHeap(&heap, u4ArryLen) == false)
	{
		printf ("malloc memory for heap arry [failed] \r\n");
		return 1;
	}

	for (i4Index = 0; i4Index<u4ArryLen; i4Index++)
	{
		heap.u4Arry[i4Index] = random() % 40;
		printf ("[%d]",heap.u4Arry[i4Index]);
	}
	printf ("\r\n ################## \r\n");
	BuildHeap(&heap);
	TraverArry(&heap);
	printf ("\r\n ################## \r\n");

	for (i4Index = 0; i4Index<4; i4Index++)
	{
		val = random()%100;
		HeapInsert(&heap, val);
		TraverArry(&heap);
	}

	for (i4Index = 0; i4Index<u4ArryLen+4; i4Index++)
	{
		if (HeapDelRoot(&heap, &val) == false)
		{
			printf ("delete failed \r\n");
		}
		else
		{
			printf ("del val [%d]  index [%d]  total [%d] \r\n", val, i4Index, u4ArryLen+4);
			TraverArry(&heap);
		}

	}
	FreeHeap(&heap) ;
	return 0;
}
