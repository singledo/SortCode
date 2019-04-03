#ifndef _fastsort_h
#define _fastsort_h

#include "com.h"

#define SWAP(A, i, j) \
{ \
	u4 temp = A[i]; \
	A[i] = A[i]; \
	A[j] = temp; \
}

void FastSort(u4 *arry, u4 start, u4 end);

u4 parttion(u4 *arry, u4 start, u4 end);

void FastArryTraver(u4 *arry, u4 len);


#endif

