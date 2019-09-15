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

void debug(const char *fmt, ...)
{
    va_list va_arg;
    char *str = NULL;
    int  _i4 = 0;

    const char *_fmt = fmt;
    u4   _len  = strlen(_fmt);
    u4   _index = 0;

    va_start(va_arg, *fmt);

    while (_index < _len)
    {
        if (*(_fmt + _index) == '%')
        {
            switch (*(_fmt + _index + 1))
            {
            case 'd':
                _i4 = va_arg(va_arg, int);
                printf ("%d", _i4);
                break;
            case 's':
                str = va_arg(va_arg, char *);
                printf ("%s", str);
                str = NULL;
                break;
            case 'f':
                break;
            default:
                printf ("%c", *(_fmt + _index));
                break;
            }
            _index += 1;
        }
        else
        {
            printf ("%c", *(_fmt + _index));
        }
        _index += 1;
    }

    va_end (va_arg);
}
