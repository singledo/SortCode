#include "process.h"

#define NAMEPIPE "/home/z/resource/SortCode/IPC/process/channel1"

int main (int argc, char *argv[])
{
    int ret = 0;
    int wFd = 0;
    char string[] = "zzzzz";

    if (access (NAMEPIPE, O_WRONLY) == -1) {
        printf ("[%s] can't access \r\n", NAMEPIPE);
        return -1;
    }

    wFd = open (NAMEPIPE, O_WRONLY);
    if (-1 == wFd) {
        printf ("open [%s]  failed\n", NAMEPIPE);
        return -1;
    }

    ret = write (wFd, string, strlen(string));
    if (-1 == ret) {
        printf ("write failed \r\n");
        goto clean;
    }
    
    close(wFd);
    return 0;

clean:
    
    close(wFd);
    return -1;
}
