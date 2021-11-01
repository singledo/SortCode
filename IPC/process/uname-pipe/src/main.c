#include "process.h"


int main (int argc, char *argv[])
{
    printf ("Demo for process IPC \r\n");
    pid_t pid = 0;
    int   sta = 0, ret;
    int   fd[2];
    
    // fd[0] - read
    // fd[1] - write
    ret = pipe (fd);
    if (-1 == ret) {
        perror ("pipe init failed \r\n");
        return -1;
    }


    pid = fork ();

    if (-1 == pid) {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        return -1;
    }

    if (pid == 0) {
        int time = 3;
        char ch;
        char buf[25];
        int  index = 0;

        printf ("i am the parent process \r\n");
        printf ("my pid: [%d] \r\n", getpid());
        
        close (fd[1]);

        while (read(fd[0], &ch, 1) > 0 && index < 25) {
            buf[index] = ch;
            index += 1;
        }

        printf ("receive string from parent: [%s] \r\n", buf);
        
        close (fd[0]);


    } else if (pid > 0) {
        printf ("i am the child process \r\n");
        char string[] = "zhanjgun shuai";
        
        close (fd[0]);
        write (fd[1], string, strlen(string));
        close (fd[1]);


        ret = waitpid (pid, &sta,WUNTRACED | WCONTINUED);
        if (ret <= -1) {
            perror ("waitpid failed \r\n");
            return -1;
        }

        printf ("parent waitfor children compelete \r\n");
    }

    return 0;
}
