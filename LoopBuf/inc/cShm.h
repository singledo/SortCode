#ifndef _cShm_h
#define _cShm_h

#include "com.h"


#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

typedef struct cShmDev cShmDev_t;
typedef struct bufInfo bufInfo_t;
typedef struct shmMutex_type shmMutex_t;

#define W_OFLAG (O_CREAT | O_RDWR)
#define R_OFLAG (O_RDONLY)

#define DEFAULT_MODE  (S_IRWXU | S_IRWXG | S_IRWXO)
#define SHMNAME_MAX (255)

#define SHMMEM_SIZE (4*1024)
#define STRUCT_SIZE (1024)

#define SHMPATH_PRE ("/dev/shmem")
#define SHMPATH_MAX (1024)

typedef enum
{
    HSAE_SHM_W=0,
    HSAE_SHM_R,
}SHM_TYPE;

typedef enum
{
    CSHM_IDEL = 0,
    CSHM_W,
    CSHM_R,
}SHM_ST;

struct bufInfo
{
    bool is_full;
    int s_index;
    int e_index;
    int max_index;
    unsigned char* buf_addr;
};

struct shmMutex_type
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutex_attr;
};

struct cShmDev
{
    SHM_ST state;
    char name[SHMNAME_MAX];
    /*shm_open return*/
    int shm_fd;
    /*for read and write*/
    shmMutex_t shm_mutex;

    int buf_len;  /*buf's len*/
    int buf_soff; /*start offset of buf */
    unsigned char* map_addr; /*map address*/
    int shm_len; /*share memory's len*/

    bufInfo_t buf_info;
};

/*
 *  share memory distribution
 *  |<-- data struct   -->|<------ buffer for data --------->|
 *  |_____________________|----------------------------------|
 * */


int cShmDevLen_w (cShmDev_t *p_dev);
int cShmDevLen_r (cShmDev_t *p_dev);

cShmDev_t* cShmDevOpen (char *name, SHM_TYPE type);

int cShmRead (cShmDev_t* p_dev, unsigned char *buf, int len);

int cShmWrite (cShmDev_t* p_dev,unsigned char *buf, int len);

void cShmDevClose (cShmDev_t *p_dev);

#endif
