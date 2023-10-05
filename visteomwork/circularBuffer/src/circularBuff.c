#include "circularBuff.h"


/* function:
 * argument:
 * return:
 * */

cb_entry_t * CBEntry_create (int data_len)
{
    cb_entry_t *p_entry = (cb_entry_t *)malloc(sizeof(cb_entry_t));
    if (NULL == p_entry)
    {
        CB_DEBUG ("malloc failed -  cb_entry_t ");
        return NULL;
    }
    p_entry->data    = NULL;
    p_entry->s_index = 0;
    p_entry->e_index = 0;
    p_entry->len     = 0;
    p_entry->full    = false;

    p_entry->data = (u8 *) malloc(data_len);
    if (NULL == p_entry->data)
    {
        CB_DEBUG("malloc failed -  p_entry->data");
        free (p_entry);
        return NULL;
    }
    p_entry->len = data_len;

    pthread_mutex_init (&p_entry->mutex, NULL);

    return p_entry;
}

/* function:
 * argument:
 * return:
 * */

void CBEntry_free (cb_entry_t *entry)
{
    assert (NULL != entry);
    assert (NULL != entry->data);

    cb_entry_t *p_entry = entry;
    pthread_mutex_destroy (&p_entry->mutex);
    free (p_entry->data);
    free (p_entry);
}
/* function:
 * argument:
 * return:
 * */

u32 CBEntry_vaild_r (cb_entry_t * entry)
{
    u32 vaild_r = 0;
    cb_entry_t * p_entry = entry;

    if (p_entry->s_index > p_entry->e_index)
    {
        vaild_r = p_entry->s_index - p_entry->e_index;
    }
    else if (p_entry->s_index < p_entry->e_index)
    {
        vaild_r = p_entry->len - (p_entry->e_index - p_entry->s_index);
    }
    else if ((p_entry->s_index == p_entry->e_index) && \
             (p_entry->full == false)) 
    {
        vaild_r = 0;
    }
    else if ((p_entry->s_index == p_entry->e_index) && \
             (p_entry->full == true)) 
    {
        vaild_r = p_entry->len;
    }

    return  vaild_r;
}

/* function:
 * argument:
 * return:
 * */

u32 CBEntry_vaild_w (cb_entry_t * entry)
{
    u32 vaild_w = 0;
    cb_entry_t * p_entry = entry;

    if (p_entry->s_index > p_entry->e_index)
    {
        vaild_w = p_entry->len - (p_entry->s_index - p_entry->e_index);
    }
    else if (p_entry->s_index < p_entry->e_index)
    {
        vaild_w =  p_entry->e_index - p_entry->s_index;
    }
    else if ((p_entry->s_index == p_entry->e_index) && \
             (p_entry->full == false)) 
    {
        vaild_w = p_entry->len;
    }
    else if ((p_entry->s_index == p_entry->e_index) && \
             (p_entry->full == true)) 
    {
        vaild_w = 0;
    }
    return  vaild_w;
}

/* function:
 * argument:
 * return:
 * */
u32 CBEntry_write (cb_entry_t * entry, u8 *w_data, u32 len)
{
    u32 nwrite  = 0;
    u32 w_vaild = 0;
    cb_entry_t * p_entry = entry;

    assert (entry != NULL);
    assert (w_data != NULL);

    w_vaild =  CBEntry_vaild_w (p_entry);
    if (0 == w_vaild)
    {
        /*there no free data space to store the w_data*/
        nwrite = 0;
        return nwrite;
    }

    if (w_vaild < len)
    {
        /*only keep the [0:w_vaild]*/
        nwrite = w_vaild;
    }
    else 
    {
        nwrite = len;
    }
#if 0
    printf ("1-e:[%d] s:[%d] len:[%d] vaild:[%d] nwrite:[%d]\n", \
            p_entry->e_index, p_entry->s_index, p_entry->len, w_vaild, nwrite);
#endif

    pthread_mutex_lock (&p_entry->mutex);

    if ((p_entry->s_index + nwrite) <= (p_entry->len - 1))
    {
        memcpy (p_entry->data+p_entry->s_index, w_data, nwrite );
    }
    else
    {
        memcpy (p_entry->data+p_entry->s_index, w_data, \
                p_entry->len - p_entry->s_index);
        memcpy (p_entry->data, w_data + (p_entry->len - p_entry->s_index), \
                nwrite - (p_entry->len - p_entry->s_index));
    }

    p_entry->s_index = (p_entry->s_index+nwrite)%(p_entry->len);
    if (p_entry->s_index == p_entry->e_index)
    {
        p_entry->full = true;
    }

    pthread_mutex_unlock (&p_entry->mutex);

    return  nwrite;
}
#define READ_DEBUG 0
/* function:
 * argument:
 * return:
 * */
u32 CBEnret_read (cb_entry_t * entry, u8 *r_data, u32 len)
{
    u32 nread           = 0;
    u32 r_vaild         = 0;
    cb_entry_t *p_entry = entry;

    assert (entry  != NULL);
    assert (r_data != NULL);
    r_vaild = CBEntry_vaild_r (p_entry);
    if (r_vaild == 0)
    {
        nread = 0;
        return nread;
    }

    if (len <= r_vaild)
    {
        nread = len;
    }
    else
    {
        nread = r_vaild;
    }
#if (READ_DEBUG == 1)
    printf ("1-e:[%d] s:[%d] len:[%d] vaild:[%d] nread:[%d]\n", \
            p_entry->e_index, p_entry->s_index, p_entry->len, r_vaild, nread);
#endif

    pthread_mutex_lock (&p_entry->mutex);

    if ((p_entry->e_index + nread) <= (p_entry->len - 1))
    {
        memcpy (r_data, p_entry->data+p_entry->e_index, nread);
    }
    else
    {
        memcpy (r_data, p_entry->data+p_entry->e_index,\
                p_entry->len - p_entry->e_index);

        memcpy (r_data+(p_entry->len - p_entry->e_index),\
                p_entry->data, nread-(p_entry->len - p_entry->e_index));

    }
    p_entry->e_index = (p_entry->e_index + nread)%p_entry->len;
#if (READ_DEBUG == 1)
    printf ("1-e:[%d] s:[%d] len:[%d] vaild:[%d] nread:[%d]\n", \
            p_entry->e_index, p_entry->s_index, p_entry->len, r_vaild, nread);
#endif

    p_entry->full = false;

    pthread_mutex_unlock (&p_entry->mutex);

    return nread;
}

int l_save (char *fmt, ...)
{
    char buf[1024];
    memset (buf, 0, 1024);
    int len = 0;

    va_list ap;
    va_start (ap, fmt);
    len = vsnprintf (buf, 1024, fmt, ap);
    va_end (ap);
    
    printf ("len:%d [%s]", len, buf);
    return len;
}
