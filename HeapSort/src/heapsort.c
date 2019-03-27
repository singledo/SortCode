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
	if (u4Largest < heap->u4HeapSize &&\
		   	u4Largest != i)
	{
		SWAP(heap->u4Arry, i, u4Largest);
		Heapify(heap, u4Largest);
	}
}

void TraverArry(tHeap *heap)
{
	u4 i  = 0;
	for (i=0; i<heap->i4Index; i++)
	{
		printf ("[%d]", heap->u4Arry[i]);
	}
	printf ("\r\n");
}

void BuildHeap(tHeap *heap)
{
	int i4Index = (heap->u4HeapSize+1)/2;
	for (; i4Index>=0; i4Index--)
	{
		Heapify(heap, i4Index);
	}
	heap->i4Index = heap->u4HeapSize;
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
	if (heap->i4Index+1 > heap->u4ArrySize)
	{
		printf ("total [%d] \r\n", heap->u4ArrySize+STEPSIZE);

		heap->u4Arry = (u4*)realloc(heap->u4Arry, heap->u4ArrySize*4+STEPSIZE*4);
		if (heap->u4Arry == NULL)
		{
			printf ("Insert Failed [Malloc failed] \r\n");
			return false;
		}
		memset(heap->u4Arry+heap->u4ArrySize, 0xff, sizeof(u4)*STEPSIZE);
		heap->u4HeapSize += STEPSIZE;
		heap->u4ArrySize += STEPSIZE;
	}		

	u4 u4ParentIndex = 0;
	heap->u4Arry[heap->i4Index] = val;
	u4ParentIndex = heap->i4Index/2 ;
	Heapify(heap, u4ParentIndex);
	heap->i4Index += 1;
	heap->u4HeapSize += 1;
	return true;
}

bool HeapDelRoot(tHeap *heap, u4 *val)
{
	if (heap->i4Index > 0)
	{
		*val = heap->u4Arry[0];
		heap->u4Arry[0] = heap->u4Arry[heap->i4Index-1];
		heap->i4Index 	-= 1;
		heap->u4HeapSize -= 1;
		Heapify(heap, 0);
		return true;
	}
	else
	{
		return false;
	}
}
