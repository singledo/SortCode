#include "cShm.h"

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
cShmDev_t* cShmDevInit (char *name, int oflag, mode_t mode)
{
    int shm_fd = -1;
    void* map_addr = 0;
    int max_size = -1;
    cShmDev_t *p_dev = NULL;
    int i_ret = 0;
    bool first_flag = false;
    char shm_path[SHMPATH_MAX];
    /* if the shm have been exist */
    if ((strlen(name) + strlen(SHMPATH_PRE)) > SHMPATH_MAX)
    {
        printf ("[%s@%d] \n", __FUNCTION__, __LINE__);
        return NULL;
    }
    else
    {
        memset (shm_path, 0, SHMPATH_MAX);
        sprintf (shm_path, "%s%s", SHMPATH_PRE, name);
        if (0 == access (shm_path, F_OK))
        {
            /* shm is been exist*/
            first_flag = false;
            oflag &= (O_RDWR | O_RDONLY);
        }
        else
        {
            /* shm is not been exist */
            first_flag = true;
        }
    }

    /*open shm object*/
    shm_fd = shm_open (name, oflag, mode);
    if (-1 == shm_fd)
    {
        printf ("[%s@%d] \n", __FUNCTION__, __LINE__);
        return NULL;
    }
    else
    {
    }
    max_size = SHMMEM_SIZE + STRUCT_SIZE;
    if (-1 == ftruncate (shm_fd, max_size))
    {
        shm_unlink (name);
        printf ("[%s@%d] \n", __FUNCTION__, __LINE__);
        return NULL;
    }
    else
    {
    }

    map_addr = mmap (0, max_size, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (MAP_FAILED == map_addr)
    {
        printf ("[%s@%d] \n", __FUNCTION__, __LINE__);
        shm_unlink (name);
        return NULL;
    }
    else
    {
    }
    if (false == first_flag)
    {
        p_dev = (cShmDev_t *)map_addr;
        printf ("[%s@%d] \n", __FUNCTION__, __LINE__);
        return p_dev;
    }
    else
    {
        memset ((char *)map_addr, 0, max_size);
        p_dev = (cShmDev_t *)map_addr;
        /*copy the shm's attritube to dev*/
        i_ret = pthread_mutex_init (&p_dev->mutex, NULL);
        if (EOK != i_ret)
        {
            munmap (map_addr, max_size);
            shm_unlink (name);

            printf ("[%s@%d] \n", __FUNCTION__, __LINE__);
            return NULL;
        }
        else
        {
        }
        /* 0                       buf_soff
         * /\                      /\
         * |                        |
         * |                        |
         * |________________________|--------------------------------|
         * |<------ struct -------->|<--------- data buf ----------->|
         * struct: [0,buf_soff)
         * data: (buf_soff, buf_soff+buf_len]
         * */

        /* initialize the struct*/
        memcpy (p_dev->name, name, strlen (name));
        p_dev->state    = CSHM_IDEL;
        p_dev->is_full  = false;
        p_dev->shm_fd   = shm_fd;
        p_dev->oflag    = oflag;
        p_dev->mode     = mode;
        p_dev->map_addr = map_addr;
        p_dev->shm_len  = max_size;
        p_dev->buf_soff = STRUCT_SIZE;
        p_dev->buf_len  = SHMMEM_SIZE;
        p_dev->buf_info.s_index   = 0;
        p_dev->buf_info.e_index   = 0;
        p_dev->buf_info.max_index = p_dev->buf_len - 1;

        p_dev->buf_addr = p_dev->map_addr + p_dev->buf_soff;
        memset (p_dev->buf_addr, 0, p_dev->buf_len);
        return p_dev;
    }
}

/*
 * By zhangjun on 22.02.22.
 * function: cShmWriteVaild
 *
 * description: get vaild buf's number in byte
 * input arg:
 * output:
 * return:
 */
int cShmWriteVaild (cShmDev_t* p_dev)
{
    /*
     * |____________|--------------------------|
     * |<--struct-->|<------- data buf  ------>|
     *
     * */
    bufInfo_t *p_info = &p_dev->buf_info;
    int v_len = 0;
    if (p_info->e_index > p_info->s_index)
    {
        /*        s_index          e_index
         *         /\               /\
         *          |                |
         *  --------xxxxxxxxxxxxxxxxx-------------
         *  |_______|________________|___________|
         *  0                                    max_index
         *  vaild buf for write:
         *     [e_index, max_index] + [0,s_index)
         * */
        v_len = (p_info->max_index- p_info->e_index + 1) \
                + (p_info->s_index);
    }
    else if (p_info->e_index < p_info->s_index)
    {
        /*        e_index          s_index
         *         /\               /\
         *          |                |
         *  xxxxxxxx-----------------xxxxxxxxxxxxx
         *  |_______|________________|___________|
         *  0                                    max_index
         *  vaild buf for write:
         *   [e_index, s_index)
         * */
        v_len = p_info->s_index - p_info->e_index;
    } else {
        if (p_dev->is_full == false)
        {
            v_len = p_dev->buf_len;
        }
        else
        {
            v_len = 0;
        }
    }
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
int cShmWrite (cShmDev_t* p_dev,char *buf, int len)
{
    int wv_len = 0; /*vaile buf for write*/
    int wr_len = 0; /*really write len*/
    int rl_len = 0; /* [e_index, max_index] length*/
    bufInfo_t *p_info = NULL;
    char *p_buf       = NULL;
    pthread_mutex_t *p_mutex = &p_dev->mutex;
    int i_ret = 0;
    i_ret = pthread_mutex_lock (p_mutex);
    if (EOK != i_ret)
    {
        return 0;
    }
    else
    {
    }


    wv_len = cShmWriteVaild (p_dev);
    if ((0 == wv_len) || (0 == len))
    {

        pthread_mutex_unlock (p_mutex);
        /*there are no vaild buf for write, return with 0*/
        return 0;
    }
    else
    {
    }

    /* buf [0, len)
     * if len > wv_len:
     *    mv [0, wv_len) to shm buf
     * else:
     *    mv [0, len) to shm buf
     * */
    if (wv_len > len)
    {
        wr_len = len;
    }
    else
    {
        wr_len = wv_len;
    }

    p_info = &p_dev->buf_info;
    p_buf  = p_dev->buf_addr;

    printf ("[1]s_index: %d e_index: %d write len: %d \n", \
            p_info->s_index, p_info->e_index, wr_len);

    if (p_info->e_index >= p_info->s_index)
    {
        /*        s_index          e_index
         *         /\               /\
         *          |                |
         *  --------xxxxxxxxxxxxxxxxx-------------
         *  |_______|________________|___________|
         *  0                                    max_index
         *  vaild buf for write:
         *     [e_index, max_index] + [0,s_index)
         *     rl_len: [e_index, max_index]
         * */
        rl_len = (p_info->max_index - p_info->e_index + 1);
        if (rl_len > wr_len)
        {
            memcpy ((p_buf+p_info->e_index), buf, wr_len);
            p_info->e_index += wr_len;
        }
        else if (rl_len <= wr_len)
        {
            memcpy ((p_buf+p_info->e_index), buf, rl_len);
            if (0 == (wr_len-rl_len))
            {
            }
            else
            {
                memcpy (p_buf, buf+rl_len, wr_len - rl_len);
            }
            p_info->e_index = wr_len - rl_len;
        }
    }

    else
    {
        /*            e_index      s_index
         *                /\        /\
         *                 |         |
         *  xxxxxxxxaaaaaaa----------xxxxxxxxxxxxx
         *  |_______|________________|___________|
         *  0                                    max_index
         * */

        memcpy ((p_buf+p_info->e_index), buf, wr_len);
        p_info->e_index += wr_len;
    }
    if (p_info->e_index == p_info->s_index)
    {
        p_dev->is_full = true;
    }
    else
    {
        p_dev->is_full = false;
    }
    printf ("[2]s_index: %d e_index: %d write len: %d \n", \
            p_info->s_index, p_info->e_index, wr_len);

    pthread_mutex_unlock (p_mutex);
    return wr_len;
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
int cShmReadVaild (cShmDev_t* p_dev)
{
    /*
     * |____________|--------------------------|
     * |<--struct-->|<------- data buf  ------>|
     *
     * */
    bufInfo_t *p_info = &p_dev->buf_info;
    int v_len = 0;
    printf ("1-rv: s_index: %d e_index: %d v_len:%d \n",\
            p_info->s_index, p_info->e_index, v_len);

    if (p_info->e_index > p_info->s_index)
    {
        /*        s_index          e_index
         *         /\               /\
         *          |                |
         *  --------xxxxxxxxxxxxxxxxx-------------
         *  |_______|________________|___________|
         *  0                                    max_index
         *  vaild buf for read:
         *     [s_index, e_index)
         * */
        v_len = p_info->e_index- p_info->s_index ;
        printf ("2-rv: s_index: %d e_index: %d v_len:%d \n",\
                p_info->s_index, p_info->e_index, v_len);
    }
    else if (p_info->e_index < p_info->s_index)
    {
        /*        e_index          s_index
         *         /\               /\
         *          |                |
         *  xxxxxxxx-----------------xxxxxxxxxxxxx
         *  |_______|________________|___________|
         *  0                                    max_index
         *  vaild buf for read:
         *   [s_index, max_index] + [0, e_index)
         * */

        v_len = (p_info->max_index-p_info->s_index+1) + \
                (p_info->e_index) ;
        printf ("2-rv: s_index: %d e_index: %d v_len:%d \n",\
                p_info->s_index, p_info->e_index, v_len);

    } else {
        if (p_dev->is_full == false)
        {
            v_len = 0;
        }
        else
        {
            v_len = p_dev->buf_len;
        }
    }
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
int cShmRead (cShmDev_t* p_dev, char *buf, int len)
{
    int v_len = 0;
    int nr_len = 0;
    bufInfo_t *p_info = NULL;
    char *p_buf       = NULL;
    int lr_len = 0;
    int i_ret = 0;
    i_ret = pthread_mutex_lock (&p_dev->mutex);
    if (EOK != i_ret)
    {
        return 0;
    }
    else
    {
    }

    p_info = &p_dev->buf_info;
    p_buf  = p_dev->buf_addr;

    v_len = cShmReadVaild (p_dev);
    if ((0 == v_len) || (len == 0))
    {
        pthread_mutex_unlock (&p_dev->mutex);
        return 0;
    }
    else
    {
    }

    /* buf: [0, len)
     * if len > v_len:
     *     mv shm buf [x, x+v_len) to buf
     * else
     *     mv shm buf [x, x+len) to buf
     * */
    if (len > v_len)
    {
        nr_len = v_len;
    }
    else
    {
        nr_len = len;
    }

    printf ("[1] shm read: s_index: %d e_index: %d, read len: %d \n", \
            p_info->s_index, p_info->e_index, nr_len);


    if (p_info->s_index < p_info->e_index)
    {
        /*          s_index       e_index
         *              /\         /\
         *               |          |
         *  --------rrrrrxxxxxxxxxxxx-------------
         *  |_______|________________|___________|
         *  0                                    max_index
         *  vaild buf for read:
         *     [e_index, max_index] + [0,s_index)
         * */
        memcpy (buf, (p_buf+p_info->s_index), nr_len);
        p_info->s_index += nr_len - 1;
    }
    else if (p_info->s_index >= p_info->e_index)
    {
        /*        e_index       s_index
         *         /\               /\
         *          |                |
         *  xxxxxxxx-----------------xxxxxxxxxxxxx
         *  |_______|________________|___________|
         *  0                                    max_index
         *  vaild buf for read:
         *   [s_index, max_index] + [0, e_index)
         * */

        lr_len = p_info->max_index - p_info->s_index + 1;
        if (lr_len > nr_len)
        {
            memcpy (buf, (p_buf+p_info->s_index), nr_len);
            p_info->s_index += nr_len - 1;
        }
        else if (lr_len == nr_len)
        {
            memcpy (buf, (p_buf+p_info->s_index), nr_len);
            p_info->s_index = 0;
        }
        else
        {
            memcpy (buf, (p_buf+p_info->s_index), lr_len);
            memcpy (buf+lr_len, p_buf, nr_len - lr_len);
            p_info->s_index = nr_len - lr_len;
        }
    }
    printf ("[2] shm read: s_index: %d e_index: %d, read len: %d \n", \
            p_info->s_index, p_info->e_index, nr_len);


    p_dev->is_full = false;

    pthread_mutex_unlock (&p_dev->mutex);
    return nr_len;
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
void cShmDevFree (cShmDev_t *p_dev)
{

}



