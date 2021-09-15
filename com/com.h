#ifndef _com_h
#define _com_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include <assert.h>
#include <errno.h>

typedef unsigned int	u32;
typedef unsigned short 	u16;
typedef unsigned char 	u8;

typedef unsigned int	u4;
typedef unsigned short 	u2;
typedef unsigned char 	u1;

typedef unsigned long ul;
typedef unsigned long long ull;

#define __F __FUNCTION__
#define __L  __LINE__

void RandomArry(u4 *arry, u4 len, u32 MaxVal);
void ShowArry(u4 *arry, u32 len);
u4 RandomLen(u4 maxlen);

void RandomU8(u8 *val, u8 MaxVal);

#define D(fmt, ...) \
{\
    printf("[%s],[%d]  #### ",__FUNCTION__,__LINE__); \
	debug(fmt, ##__VA_ARGS__); \
}\

#define DEBUG(fmt, ...) \
{\
    printf("[%s],[%d] #### ",__FUNCTION__,__LINE__); \
	debug(fmt, ##__VA_ARGS__); \
}\


#endif /* end of com_h*/
