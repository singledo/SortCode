#include "process.h"

#define NAMEPIPE "/home/z/resource/SortCode/IPC/process/channel1"

int main (int argc, char *argv[])
{
    printf ("Demo for process IPC \r\n");
    int ret = 0;
    int rFd = 0;
    char tmp[256] ;
    char tmpCh = 0;
    int  index = 0;

    ret = access (NAMEPIPE, F_OK);

    if (-1 == ret) {
        printf ("[%s] not exit, we crearte now\r\n", NAMEPIPE);
        ret = mkfifo (NAMEPIPE, O_CREAT|O_EXCL|0755);
        if (-1 == ret) {
            printf ("create [%s] failed \r\n", NAMEPIPE);
            return -1;
        } else {
            printf ("create [%s] success \r\n", NAMEPIPE);
        }
    }

    rFd = open (NAMEPIPE, O_RDONLY);
    if (-1 == rFd) {
        unlink (NAMEPIPE);
        printf ("open [%s] failed \r\n", rFd);
        return -1;
    }
    while (1) {
        if (read (rFd, tmp, 255) <= 0) {
            continue;
        }
        printf ("receive: [%s] \r\n", tmp);

        memset (tmp, 0, 256);
    }

    return 0;

clean:
    close (rFd);
    return -1;
}
