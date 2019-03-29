#include "heapsort.h"

/*
 * A[parent(i)] ≤A[i]
 * */
void Heapify(tHeap *heap, u4 i)
{
	u4 u4Left 		= 2*i+1;
	u4 u4Right 		= 2*i+2;
	u4 u4MinIndex 	= i;

	if (u4Left < heap->u4HeapSize && \
			heap->u4Arry[u4Left] < heap->u4Arry[u4MinIndex])
	{
		u4MinIndex = u4Left;
	}
	
	if (u4Right < heap->u4HeapSize && \
			heap->u4Arry[u4Right] < heap->u4Arry[u4MinIndex])
	{
		u4MinIndex = u4Right;
	}
	if (u4MinIndex < heap->u4HeapSize &&\
		   	u4MinIndex != i)
	{
		SWAP(heap->u4Arry, i, u4MinIndex);
		Heapify(heap, u4MinIndex);
#if 0
		printf ("swap [%d] [%d] \r\n ", i, u4MinIndex);
		TraverArry(heap);
		printf ("\r\n\r\n");
#endif
	}
}

void TraverArry(tHeap *heap)
{
	u4 i  = 0;
	for (i=0; i<heap->u4HeapSize; i++)
	{
		printf ("[%02d]", heap->u4Arry[i]);
	}
	printf ("\r\n");
}

void BuildHeap(tHeap *heap)
{
	int i4Index = 1;
	for (; i4Index <= heap->u4HeapSize; i4Index ++)
	{
		Heapify(heap, heap->u4HeapSize-i4Index);
		/*printf ("build index [%d] \r\n", i4Index);*/
	}
}

void FreeHeap(tHeap *heap)
{
	if (heap->u4Arry != NULL)
	{
		free(heap->u4Arry);
	}
}

bool MallocHeap(tHeap *heap, u4 len)
{
	if (heap->u4Arry != NULL)
	{
		heap->u4Arry = (u4*)malloc(sizeof(u4)*len);
		if (heap->u4Arry != NULL )
		{
			heap->u4HeapSize = len;
			heap->u4ArrySize = len;
			return true;
		}
	}
	return false;
}

bool HeapInsert(tHeap *heap, u32 val)
{
	if (heap->u4HeapSize+1 > heap->u4ArrySize)
	{
		printf ("total [%d] \r\n", heap->u4ArrySize+STEPSIZE);

		heap->u4Arry = (u4*)realloc(heap->u4Arry, heap->u4HeapSize*4+STEPSIZE*4);
		if (heap->u4Arry == NULL)
		{
			printf ("Insert Failed [Malloc failed] \r\n");
			return false;
		}
		memset(heap->u4Arry+heap->u4ArrySize, 0xff, sizeof(u4)*STEPSIZE);
		heap->u4ArrySize += STEPSIZE;
	}		

	u4 u4ParentIndex = 0;
	heap->u4Arry[heap->u4HeapSize] = val;
	u4ParentIndex = (heap->u4HeapSize-1)/2 ;
	Heapify(heap, u4ParentIndex);
	heap->u4HeapSize += 1;

	return true;
}

bool HeapDelRoot(tHeap *heap, u4 *val)
{
	if (heap->u4HeapSize > 0)
	{
		*val = heap->u4Arry[0];
		heap->u4Arry[0] = heap->u4Arry[heap->u4HeapSize-1];
		heap->u4HeapSize -= 1;
		Heapify(heap, 0);
		return true;
	}
	else
	{
		return false;
	}
}
