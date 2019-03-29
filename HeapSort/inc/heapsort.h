#ifndef _heapsort_h
#define _heapsort_h
#include "com.h"

#define STEPSIZE (2)

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
	u4 u4ArrySize;
};
typedef struct Heap tHeap;

void TraverArry(tHeap *heap);
void Heapify(tHeap *heap, u32 i);
void FreeHeap(tHeap *heap);
bool MallocHeap(tHeap *heap, u4 len);
void BuildHeap(tHeap *heap);
bool HeapInsert(tHeap *heap, u32 val);
bool HeapDelRoot(tHeap *heap, u4 *val);

#endif

