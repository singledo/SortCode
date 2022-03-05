#include "cShm.h"
#include "HsaeShm.h"

/*
 * By zhangjun on 22.02.22.
 * function: cShmWriteVaild
 *
 * description: get vaild buf's number in byte
 * input arg:
 * output:
 * return:
 */
static int cShmWriteVaild (bufInfo_t *p_info)
{
    int v_len = 0;
    if (p_info->s_index == p_info->e_index)
    {
        /*            s/e
         *  0          |          m
         * |___________|___________|
         * */
        if (p_info->is_full == false)
        {
            v_len = p_info->max_index + 1;
        }
        else
        {
            v_len = 0;
        }
    }
    else if (p_info->s_index < p_info->e_index)
    {
        /*       s     e
         *  0    |     |          m
         * |_____xxxxxx|___________|
         * vaild range for write:
         * [e,m] + [0,s)
         * */
        v_len = (p_info->max_index - p_info->e_index  + 1) + \
                 p_info->s_index ;

    }
    else if (p_info->s_index > p_info->e_index)
    {
        /*       e     s
         *  0    |     |          m
         * xxxxxx|_____xxxxxxxxxxxxx
         * vaild range for write:
         * [e,s)
         * */
        v_len = (p_info->s_index - p_info->e_index);
    }
#if 0
    if (0 != v_len)
    {
        printf ("w2-s:%d e:%d v:%d \n", \
                p_info->s_index, p_info->e_index, v_len);
    }
    else
    {

    }
#endif
    return v_len;
}


/*
 * By zhangjun on 22.02.22.
 * function:
 *
 * description:
 *
 * input arg:
 *
 * output:
 *
 * return:
 */
static int cShmReadVaild (bufInfo_t *p_info)
{
    int v_len = 0;

    /*printf ("r1-s:%d e:%d v:%d \n", p_info->s_index, p_info->e_index, v_len);*/
    if (p_info->s_index == p_info->e_index)
    {
        /*            s/e
         *  0          |          m
         * |___________|___________|
         * */
        if (p_info->is_full == false)
        {
            v_len = 0;
        }
        else
        {
            v_len = p_info->max_index+1;
        }
    }
    else if (p_info->s_index < p_info->e_index)
    {
        /*       s     e
         *  0    |     |          m
         * |_____xxxxxx|___________|
         * vaild range for read:
         * [s,e)
         * */
        v_len = p_info->e_index - p_info->s_index;
    }
    else if (p_info->s_index > p_info->e_index)
    {
        /*        e     s
         *  0     |     |           m
         * |xxxxxx|_____xxxxxxxxxxxxx|
         * vaild range for read:
         * [s,m]+[0,e)
         * */
        v_len = (p_info->max_index-p_info->s_index + 1) +\
                (p_info->e_index);
    }
#if 0
    if (0 != v_len)
    {
        printf ("r2-s:%d e:%d v:%d \n", p_info->s_index, p_info->e_index, v_len);
    }
    else
    {

    }
#endif
    return v_len;
}

static cShmOff_t cshm_off[] = {
    { SHM_RS485_R2,  0x0,},
    { SHM_RS232_R2,  0x1024*6+1,},
    { SHM_RS232_R3,  0x1024*12+1,},
};

/*
 * By zhangjun on 18.02.22.
 * function: cShmDevInit
 * description: create and initilize the cShmDev
 * input arg:
 *    name: share memory's name
 *    oflag:
 *    mode:
 * output:
 *    none
 * return:
 *    NULL: failed
 *    Other: pointer the dev
 */
cShmDev_t* cShmDevOpen (char *name, SHM_TYPE type)
{
    cShmDev_t *p_dev = NULL;
    int shm_oflag = 0;
    mode_t shm_mode = 0;
    int shm_fd = 0;
    unsigned char *map_addr = NULL;
    unsigned int shm_len = 0;
    shmMutex_t *p_shm_mutex = NULL;
    int i_ret = 0;
    bufInfo_t *p_info = NULL;
    int port_flag = 0;

    printf ("arg: [name:%s t:%d] \n", name, type);

    if (HSAE_SHM_R == type)
    {
        shm_oflag = O_RDWR;
        port_flag = PROT_READ | PROT_WRITE;
        shm_mode = 0666;
    }
    else if (HSAE_SHM_W == type)
    {
        shm_unlink (name);
        shm_oflag = O_CREAT | O_RDWR;
        port_flag = PROT_READ | PROT_WRITE;
        shm_mode = 0777;
    }
    else
    {
        printf ("[%s@%d] [%s]\n", __FUNCTION__, __LINE__, strerror (errno));
        return NULL;
    }
    shm_fd = shm_open (name, shm_oflag, shm_mode);
    if (-1 == shm_fd)
    {
        printf ("[%s@%d] [%s]\n", __FUNCTION__, __LINE__, strerror (errno));
        return NULL;
    }
    else
    {
    }

    shm_len = STRUCT_SIZE+SHMMEM_SIZE;
    if (HSAE_SHM_R == type)
    {
#if 0
        if (-1 == ftruncate(shm_fd, shm_len))
        {
            printf ("[%s@%d] [%s]\n", __FUNCTION__, __LINE__, strerror (errno));
            close (shm_fd);
            return NULL;
        }
        else
        {
        }
#endif
    }
    else if (HSAE_SHM_W == type)
    {
        if (-1 == ftruncate(shm_fd, shm_len))
        {
            printf ("[%s@%d] [%s]\n", __FUNCTION__, __LINE__, strerror (errno));
            close (shm_fd);
            return NULL;
        }
        else
        {
        }
    }

    map_addr = (unsigned char *)mmap (NULL, shm_len, port_flag,\
                                      MAP_SHARED, shm_fd, 0);
    if (MAP_FAILED == map_addr)
    {
        printf ("[%s@%d] [%s]\n", __FUNCTION__, __LINE__, strerror (errno));
        printf ("[name:%s][map: 0x%x] [fd: %d] \n", name, (unsigned int)map_addr, shm_fd);
        close (shm_fd);
        return NULL;
    }
    else
    {
        printf ("[name:%s][map: 0x%x] [fd: %d] \n", name, (unsigned int)map_addr, shm_fd);
    }
    if (HSAE_SHM_R == type)
    {
        p_dev = (cShmDev_t *)map_addr;
    }
    else if (HSAE_SHM_W == type)
    {
        p_dev = (cShmDev_t *)map_addr;
        p_shm_mutex = &p_dev->shm_mutex;

        /*initialize the mutex for multiple progress*/
        i_ret = pthread_mutexattr_init (&p_shm_mutex->mutex_attr);
        if (EOK != i_ret)
        {
            close (shm_fd);
            shm_unlink (name);
            return NULL;
        }
        else
        {
        }

        i_ret = pthread_mutexattr_setpshared (&p_shm_mutex->mutex_attr, PTHREAD_PROCESS_SHARED);
        if (EOK != i_ret)
        {
            close (shm_fd);
            shm_unlink (name);
            return NULL;
        }
        else
        {
        }

        i_ret = pthread_mutex_init (&p_shm_mutex->mutex, &p_shm_mutex->mutex_attr);
        if (EOK != i_ret)
        {
            close (shm_fd);
            shm_unlink (name);
            return NULL;
        }
        else
        {
        }
        p_dev->shm_fd = shm_fd;
        p_dev->shm_len = shm_len;
        p_dev->buf_len = SHMMEM_SIZE;
        p_dev->buf_soff = STRUCT_SIZE;
        p_dev->map_addr = (unsigned char *)map_addr;
        memset (p_dev->name, 0, SHMNAME_MAX);
        memcpy (p_dev->name, name ,strlen (name));

        p_info = &p_dev->buf_info;
        p_info->s_index = 0;
        p_info->e_index = 0;
        p_info->max_index = p_dev->buf_len - 1;
        p_info->is_full = false;
        p_info->buf_addr = p_dev->map_addr+p_dev->buf_len;
    }
    return p_dev;
}


/*
 * By zhangjun on 01.03.22.
 * function:
 * description:
 * input arg:
 * output:
 * return:
 */
int cShmDevLen_w (cShmDev_t *p_dev)
{
    int v_len = 0;

    shmMutex_t *p_mutex = &p_dev->shm_mutex;
    if (EOK != pthread_mutex_lock (&p_mutex->mutex))
    {
        return 0;
    }
    else
    {
    }
    v_len = cShmWriteVaild (&p_dev->buf_info);
    pthread_mutex_unlock (&p_mutex->mutex);
    return v_len;
}


/*
 * By zhangjun on 18.02.22.
 * function: shmWrite
 * description: write buf to share memory
 * input arg:
 *     p_dev: point the cShmDev
 *     buf:   buffer that write data
 *     len:   buffer len
 * output:
 *     none
 * return:
 *     -1: write failed
 *     other: the length that really write to share memory
 */
int cShmWrite (cShmDev_t* p_dev,unsigned char *buf, int len)
{
    assert (p_dev != NULL);
    int nr_write = 0, wv_len = 0, lr_len = 0;
    bufInfo_t *p_info = NULL;

    shmMutex_t *p_mutex = &p_dev->shm_mutex;
    if (EOK != pthread_mutex_lock (&p_mutex->mutex))
    {
        return 0;
    }
    else
    {
    }

    p_dev->state = CSHM_W;
    p_info = &p_dev->buf_info;
    wv_len = cShmWriteVaild (p_info);
    if ((0 == wv_len) || (len == 0))
    {

        p_dev->state = CSHM_IDEL;
        pthread_mutex_unlock (&p_mutex->mutex);
        return 0;
    }
    else
    {
    }

    if (len <= wv_len)
    {
        nr_write = len;
    }
    else
    {
        nr_write = wv_len;
    }

    printf ("w-1:[name:%s] [%d~%d] [0x%x] \n", p_dev->name,\
            p_info->s_index, p_info->e_index, \
            *(p_info->buf_addr + p_info->e_index-1));

    if (p_info->s_index <= p_info->e_index)
    {
        /*        s    e
         *  0     |    |          m
         * |______xxxxx|___________|
         *  vaild range: [e,m] + [0,s)
         * */
        lr_len = p_info->max_index - p_info->e_index + 1;
        if (nr_write <= lr_len)
        {
            memcpy ((p_info->buf_addr + p_info->e_index), buf, nr_write);
        }
        else
        {
            memcpy ((p_info->buf_addr + p_info->e_index), buf, lr_len);
            memcpy (p_info->buf_addr, buf+lr_len, nr_write-lr_len);
        }
        p_info->e_index = (p_info->e_index + nr_write) % (p_info->max_index+1);
    }
    else if (p_info->s_index > p_info->e_index)
    {
        /*        e    s
         *  0     |    |          m
         * |xxxxxx|____xxxxxxxxxxxx|
         *  vaild range: [e,s)
         * */
        memcpy ((p_info->buf_addr + p_info->e_index), buf, nr_write);
        p_info->e_index += nr_write;
    }

    printf ("w-2: [%d~%d] [0x%x] \n", p_info->s_index, p_info->e_index, \
            *(p_info->buf_addr + p_info->e_index-1));
    printf ("w-3: [0x%x 0x%x] \n", *(buf), *(buf+nr_write-1));

    if (p_info->e_index == p_info->s_index)
    {
        p_info->is_full = true;
    }
    else
    {
        p_info->is_full = false;
    }

    p_dev->state = CSHM_IDEL;
    pthread_mutex_unlock (&p_mutex->mutex);
    return nr_write;
}


/*
 * By zhangjun on 01.03.22.
 * function:
 *
 * description:
 *
 * input arg:
 *
 * output:
 *
 * return:
 */

int cShmDevLen_r (cShmDev_t *p_dev)
{
    int v_len = 0;
    shmMutex_t *p_mutex = &p_dev->shm_mutex;
    if (EOK != pthread_mutex_lock (&p_mutex->mutex))
    {
        return 0;
    }
    else
    {
    }
    v_len = cShmReadVaild (&p_dev->buf_info);
    pthread_mutex_unlock (&p_mutex->mutex);
    return v_len;
}


/*
 * By zhangjun on 22.02.22.
 * function: shmRead
 * description: read buf from share memory
 * input arg:
 *       p_dev: pointer return by shmInit
 *       len:   read data's number
 * output:
 *       buf:   memory that keey read buf
 * return:
 *      realy number that read
 */
int cShmRead (cShmDev_t* p_dev, unsigned char *buf, int len)
{
    assert (p_dev != NULL);

    int rv_len = 0, lr_len = 0, nr_read = 0;

    bufInfo_t *p_info = NULL;
    shmMutex_t *p_mutex = &p_dev->shm_mutex;
    if (EOK != pthread_mutex_lock (&p_mutex->mutex))
    {
        return 0;
    }
    else
    {
    }
    p_dev->state = CSHM_R;

    p_info = &p_dev->buf_info;

    rv_len = cShmReadVaild (p_info);
    if ((0 == rv_len) || (0 == len))
    {
        p_dev->state = CSHM_IDEL;
        pthread_mutex_unlock (&p_mutex->mutex);
        return 0;
    }
    else
    {
    }

    if (len <= rv_len)
    {
        nr_read = len;
    }
    else
    {
        nr_read = rv_len;
    }
    printf ("read-1: [name:%s ][%d-%d] [0x%x] \n", p_dev->name,\
            p_info->s_index, p_info->e_index, \
            *(p_info->buf_addr + p_info->s_index));

    if (p_info->s_index >= p_info->e_index)
    {
        /*        e     s
         *  0     |     |           m
         * |xxxxxx|_____xxxxxxxxxxxxx|
         * vaild range for read:
         * [s,m]+[0,e)
         * */
        lr_len = p_info->max_index - p_info->s_index + 1;
        if (nr_read <= lr_len)
        {
            memcpy (buf, p_info->buf_addr + p_info->s_index, nr_read);
        }
        else
        {
            memcpy (buf, p_info->buf_addr + p_info->s_index, lr_len);
            memcpy (buf+lr_len, p_info->buf_addr, nr_read - lr_len);
        }
        p_info->s_index = (p_info->s_index+nr_read)%(p_info->max_index+1);
    }
    else if (p_info->s_index < p_info->e_index)
    {
        /*       s     e
         *  0    |     |          m
         * |_____xxxxxx|___________|
         * vaild range for read:
         * [s,e)
         * */
        memcpy (buf, p_info->buf_addr + p_info->s_index, nr_read);
        p_info->s_index += nr_read;
    }
    printf ("read-2: [%d-%d] [0x%x] \n", p_info->s_index, p_info->e_index, \
            *(p_info->buf_addr + p_info->s_index));
    printf ("read-3: [0x%x 0x%x] \n", *(buf), *(buf+nr_read-1));

    p_info->is_full = false;

    p_dev->state = CSHM_IDEL;
    pthread_mutex_unlock (&p_mutex->mutex);
    return nr_read;
}

/*
 * By zhangjun on 18.02.22.
 * function: cShmDevFree
 * description: free the cShmDev
 * input arg:
 *     p_dev: pointer that point cShmDev
 * output:
 *     None
 * return:
 *    None
 */
void cShmDevClose (cShmDev_t *p_dev)
{

}



