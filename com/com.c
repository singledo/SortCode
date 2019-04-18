#include "com.h"

void RandomArry(u4 *arry, u4 len, u32 MaxVal)
{
	struct timespec time;
	u4 i = 0;
	
	if (arry == 0 || len == 0)
	{
		printf("[%s] [%d] [input error] \r\n", __FUNCTION__, __LINE__);
		return;
	}
	clock_gettime(CLOCK_REALTIME, &time);
	srand(time.tv_nsec);

	for (i=0; i<len; i++)
	{
		*(arry+i) = random()%MaxVal;
	}
}

u4 RandomLen(u4 maxlen)
{
	struct timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	srand(time.tv_nsec);
	return random()%maxlen;
}

void ShowArry(u4 *arry, u32 len)
{
	u4 i = 0;

	printf ("\r\n###### start ######\r\n");
	for (i=0; i<len; i++)
	{
		printf ("[%2d]  ", *(arry+i) );
		if ( (i+1)% 10 == 0 )
		{
			printf ("\r\n");
		}
	}

	if ( i% 10 == 0 )
	{
		printf ("###### end ######\r\n");
	}
	else
	{
		printf ("\r\n###### end ######\r\n");
	}
}
