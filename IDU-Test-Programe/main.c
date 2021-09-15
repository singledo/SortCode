#include "com.h"
#include "arinc.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>



int main (int argc, char *argv[])
{
    printf ("IDU ARINC429 TEST PROGRAME \n");

    int ret = 0;
    u32 nRecv = 0;
    pthread_t wPID = 0, rPID = 0;
    pthread_attr_t attr;
    int status;

    if (argc != 2) {
        printf ("wrong cmd \n");
        return -1;
    }

    ret = arincInit ();
    if (-1 == ret) {
        printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)); \
        return -1;
    }
    if (memcmp (argv[1], "recv", 4) == 0) {
        pthread_attr_init(&attr);
        ret = pthread_create (&rPID, &attr, arincReadLoop, NULL);
        if (-1 == ret) {
            printf ("creat arincWriteLoop failed \n");
            return 1;
        }
    } else if (memcmp (argv[1], "send", 4) == 0) {
        pthread_attr_init(&attr);
        ret = pthread_create (&wPID, &attr, arincWriteLoop, NULL);
        if (-1 == ret) {
            printf ("creat arincWriteLoop failed \n");
            return 1;
        }
    }
    while (1) {
        sleep (1);
    }

    return 0;
}
