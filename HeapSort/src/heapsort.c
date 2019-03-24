#include "heapsort.h"

/*
 * A[parent(i)] ≤A[i]
 * */
void Heapify(tHeap *heap, u4 i)
{
	u4 u4Left 		= 2*i;
	u4 u4Right 		= 2*i+1;
	u4 u4Largest 	= i;
	
	if (u4Left <= heap->u4HeapSize && \
			heap->u4Arry[u4Left] < heap->u4Arry[u4Largest])
	{
		u4Largest = u4Left;
	}
	
	if (u4Right <= heap->u4HeapSize && \
			heap->u4Arry[u4Right] < heap->u4Arry[u4Largest])
	{
		u4Largest = u4Right;
	}
	if (u4Largest != i)
	{
		SWAP(heap->u4Arry, i, u4Largest);
		Heapify(heap, u4Largest);
	}
}

void BuildHeap(tHeap *heap)
{
	u4 u4Index = 0;
	for (u4Index = (heap->u4HeapSize+1)/2; u4Index>=0 ; u4Index--)
	{
		Heapify(heap, u4Index);
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
			return true;
		}
	}
	return false;
}
