#include "heapsort.h"

int main(int argc, char *argv[])
{
	printf ("heap sort programe ..... \r\n");
	tHeap heap;
	u4 u4Index  = 0;
	u4 u4Seed 	= 0;
	u4 u4ArryLen = 20;

	srandom(random());

	if (MallocHeap(&heap, u4ArryLen) == false)
	{
		printf ("malloc memory for heap arry [failed] \r\n");
		return 1;
	}

	for (u4Index = 0; u4Index<u4ArryLen; u4Index++)
	{
		heap.u4Arry[u4Index] = random() % 40;
		printf ("[%d]  ", heap.u4Arry[u4Index]);
		if (u4Index % 10 == 0 && u4Index != 0)
		{
			printf ("\r\n");
		}
	}
	
	BuildHeap(&heap);

	printf ("\r\n");
	
	FreeHeap(&heap) ;
	return 0;
}
