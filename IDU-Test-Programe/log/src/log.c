#include "com.h"
#include "log.h"

int gLogFD = -1;
char gPath[LOGPATHMAX];

pthread_spinlock_t gLock;


/* @zhangjun 02.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
int logInit (char *path)
{
    int ret;

    ret = pthread_spin_init (&gLock, PTHREAD_PROCESS_SHARED);
    if (-1 == ret) {
        return -1;
    }

    memset (gPath, 0, LOGPATHMAX);
    memcpy (gPath, path, strlen(path));

	if (access (path, F_OK) == 0) {
        return 0;
	}

    gLogFD = open (path, O_CREAT | 0666);
    if (gLogFD == -1) {
        return -1;
    }
    close (gLogFD);
    gLogFD = -1;

    return 0;
}


/* @zhangjun 02.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
int logInfo (char *fmt, ...)
{
    static char buf[1024];
    va_list ap;
    int iret ;
    time_t timep;

    memset (buf, 0, 1024);
    pthread_spin_lock (&gLock);

    va_start (ap, fmt);
    iret = vsprintf (buf, fmt, ap);
    va_end (ap);

    time (&timep);

    strcat (buf, asctime(gmtime(&timep)) );

    if (gLogFD == -1) {
        gLogFD = open (gPath, O_WRONLY | O_APPEND);
        if (-1 == gLogFD) {
                pthread_spin_unlock (&gLock);
                return -1;
        }
    }

    iret = write (gLogFD, buf, strlen(buf));

    if (-1 == iret) {
        pthread_spin_unlock (&gLock);
        return -1;
    } else {
        pthread_spin_unlock (&gLock);
        return iret;
    }
}

