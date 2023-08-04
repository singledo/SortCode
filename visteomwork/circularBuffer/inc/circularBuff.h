#ifndef _circularBuff_h
#define _circularBuff_h

#include "com.h"
#include <pthread.h>

#define DATA_MAX (215)

struct cb_entry
{
    u8 *data;
    int s_index;
    int e_index;
    int len;
    bool full;
    pthread_mutex_t mutex;
};

typedef struct cb_entry cb_entry_t;

cb_entry_t * CBEntry_create (int data_len);

void CBEntry_free (cb_entry_t *entry);

u32 CBEntry_write (cb_entry_t * entry, u8 *w_data, u32 len);

u32 CBEnret_read (cb_entry_t * entry, u8 *r_data, u32 len);

u32 CBEntry_vaild_w (cb_entry_t * entry);

u32 CBEntry_vaild_r (cb_entry_t * entry);

#endif
