#ifndef _arinc_h
#define _arinc_h

#include "com.h"
#include "serialport.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "log.h"

typedef struct arincData arincData_t;
typedef struct arincDev arincDev_t;

struct arincData
{
    u8 label;
    u8 dat[3];
};


struct arincDev {
    char name[250];
    key_t key;
    int shmID;
    u8 * pMap;
    u32 offset;
    pthread_spinlock_t lock;
    pthread_spinlock_t printflock;
};


int arincInit (void);
int arincWrite (arincData_t pkt);
void * arincWriteLoop (void *arg);


int arincRead (u8 *data, u32 len);
void *arincReadLoop (void *arg);

void * arincResolverLoop (void *arg);

arincDev_t * arincGetDev (void);
void arincLock (void);
void arincUnlock (void);
int arincTrylock (void);

int arincInfo (char *fmt, ...);

#define SERIALDEV "/dev/ttyUSB0"
#define SERIAL_BAUDRATE (115200)
#define SERIAL_DATAWIDTH (8)
#define SERIAL_STOP (1)
#define SERIAL_PARITY ('N')

#define ARINC_SHM "./arinc.shm"
#define ARINC_PRJ ('a')
#define ARINC_SHM_SIZE 1024*20
#define ARINC_READ_MAX (1024*5)

#define ARINC_LOG "./arinc.log"
#define OUT_PRESIZE (10000)

#define RES_SIZE (5000000/4)

#endif
