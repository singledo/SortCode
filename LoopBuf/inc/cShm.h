#ifndef _cShm_h
#define _cShm_h

#include "com.h"


#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

typedef struct cShmDev cShmDev_t;
typedef struct bufInfo bufInfo_t;

#define DEFAULT_OFLAG (O_CREAT | O_RDWR)
#define DEFAULT_MODE  (S_IRWXU | S_IRWXG | S_IRWXO)
#define SHMNAME_MAX (255)

#define SHMMEM_SIZE (4*1024)
#define STRUCT_SIZE (1024)

#define SHMPATH_PRE ("/dev/shmem")
#define SHMPATH_MAX (1024)

typedef enum
{
    CSHM_IDEL = 0,
    CSHM_W,
    CSHM_R,
}SHM_ST;

struct bufInfo
{
    /*start index*/
    int s_index;
    /*end index*/
    int e_index;
    int max_index;
};

struct cShmDev
{
    SHM_ST state;
    bool is_full; /*false->not full, true->buf is full with data*/
    /*name for share memory*/
    char name[SHMNAME_MAX];
    /*O_RDONLY, O_WRONLY ... */
    int oflag;
    /*The permission bits */
    mode_t mode;
    /*shm_open return*/
    int shm_fd;
    /*for read and write*/
    pthread_mutex_t mutex;

    int buf_len;  /*buf's len*/
    int buf_soff; /*start offset of buf */
    char * map_addr; /*map address*/
    char * buf_addr; /* keep receive data*/

    int shm_len; /*share memory's len*/

    bufInfo_t buf_info;
};

/*
 *  share memory distribution
 *  |<-- data struct   -->|<------ buffer for data --------->|
 *  |_____________________|----------------------------------|
 * */

int cShmWriteVaild (cShmDev_t* p_dev);

#endif
