#include "circularBuff.h"
#if 0
void* readThread(void *arg);
void * writeThread (void *arg);

#if (CMPILE_SWITCH == RECV)
int main (int argc, char *argv[])
{
    printf ("1-circular Buffer Test programe \n");
    pthread_t  readThread_pid = 0, writeThread_pid = 0;
    int i_ret = 0;

    cb_entry_t *cb_entry = CBEntry_create (DATA_MAX);
    if (NULL == cb_entry)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        return 1 ;
    }

    printf("[%s],[%d] write thread \n",__FUNCTION__,__LINE__);
    i_ret = pthread_create (&writeThread_pid, NULL, writeThread, (void*)cb_entry);
    if (0 != i_ret)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        goto faile_exit;
    }

    printf("[%s],[%d] read thread \n",__FUNCTION__,__LINE__);
    i_ret = pthread_create (&readThread_pid, NULL, readThread, (void*)cb_entry);
    if (0 != i_ret)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        goto faile_exit;
    }

    pthread_join (writeThread_pid, NULL);
    pthread_join (readThread_pid,  NULL);

    CBEntry_free (cb_entry);
    return 0;

faile_exit:
printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
    CBEntry_free (cb_entry);
    return 1;
}

#elif (CMPILE_SWITCH == SEND)

#else
int main (int argc, char *argv[])
{
    printf ("1-circular Buffer Test programe \n");
    pthread_t  readThread_pid = 0, writeThread_pid = 0;
    int i_ret = 0;

    cb_entry_t *cb_entry = CBEntry_create (DATA_MAX);
    if (NULL == cb_entry)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        return 1 ;
    }

    printf("[%s],[%d] write thread \n",__FUNCTION__,__LINE__);
    i_ret = pthread_create (&writeThread_pid, NULL, writeThread, (void*)cb_entry);
    if (0 != i_ret)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        goto faile_exit;
    }

    printf("[%s],[%d] read thread \n",__FUNCTION__,__LINE__);
    i_ret = pthread_create (&readThread_pid, NULL, readThread, (void*)cb_entry);
    if (0 != i_ret)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        goto faile_exit;
    }

    pthread_join (writeThread_pid, NULL);
    pthread_join (readThread_pid,  NULL);

    CBEntry_free (cb_entry);
    return 0;

faile_exit:
printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
    CBEntry_free (cb_entry);
    return 1;
}

#endif

void* readThread(void *arg)
{

    cb_entry_t *p_entry = (cb_entry_t *)arg;
    char *p_str = NULL;
    u8   ndelay = 0;
    u32  nread  = 0;

    p_str = (char *) malloc(255);
    if (NULL == p_str)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        return (void*)-1;
    }


    while (1)
    {
        memset (p_str, 0, 255);
        nread = CBEnret_read (p_entry, p_str, 255); 
        if (nread > 0)
        {
            printf ("%s\n", p_str);
        }
        else
        {
            /*printf("[%s],[%d]nread: %d \n",__FUNCTION__,__LINE__, nread);*/
        }
        RandomU8(&ndelay, 250);
        usleep (1000*400);
    }
    return (void*) 0;
}

void * writeThread (void *arg)
{
#define READMAX 255

    cb_entry_t *p_entry = (cb_entry_t *)arg;
    char *p_data = NULL;
    u32 nwrite = 0;
    u8  ndelay = 0;
    u32 time = 0;

    p_data = (char *)malloc(READMAX);
    if (NULL == p_data)
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
        return (void*)-1;
    }

    while (1)
    {
        memset (p_data, 0, 255);

        sprintf (p_data, "send time: %04d#-|", time);

        nwrite = CBEntry_write (p_entry, p_data, strlen(p_data));
        if (nwrite <= 0)
        {
            printf("[%s],[%d][loss :%d ] \n",__FUNCTION__,__LINE__, time);
        }
        else if (nwrite != strlen(p_data))
        {
            printf("[%s],[%d][%u] [%u] \n",__FUNCTION__,__LINE__,\
                   nwrite, strlen(p_data));
        }
        time += 1;
        RandomU8(&ndelay, 250);
        usleep (10*ndelay);
    }

    return (void*)0;
}


#else
int main (int argc, char *argv[])
{
    l_save ("%s: %d", "zhangjun", 10);
    l_save ("sssss");
    return 0;
}
#endif
