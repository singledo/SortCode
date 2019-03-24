#ifndef _heapsort_h
#define _heapsort_h
#include "com.h"

#define SWAP(A,i,j) \
{\
	u4 temp = A[i]; \
	A[i] 	= A[j]; \
	A[j] 	= temp; \
}

struct Heap
{
	u4 *u4Arry;
	u4 u4HeapSize;
};
typedef struct Heap tHeap;

void Heapify(tHeap *heap, u32 i);
void FreeHeap(tHeap *heap);
bool MallocHeap(tHeap *heap, u4 len);
void BuildHeap(tHeap *heap);

#endif

