#include "arinc.h"
#include "com.h"

static int gSerFd = 0;
static arincDev_t arincDev;

/* @zhangjun 01.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
arincDev_t * arincGetDev (void)
{
    return &arincDev;
}

/* @zhangjun 01.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
void arincLock (void)
{
    arincDev_t *dev = arincGetDev ();
    pthread_spin_lock (&dev->lock);
}

/* @zhangjun 01.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
void arincUnlock (void)
{
    arincDev_t *dev = arincGetDev ();
    pthread_spin_unlock (&dev->lock);
}


/* @zhangjun 01.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
int arincInfo (char *fmt, ...)
{
    static char buf[1024];
    va_list ap;
    int iret ;

    arincDev_t *dev = arincGetDev ();
    pthread_spin_lock (&dev->printflock);

    va_start (ap, fmt);
    iret = vsprintf (buf, fmt, ap);
    va_end (ap);
    fputs (buf, stdout);

    if (-1 == iret) {
        pthread_spin_unlock (&dev->printflock);
        return -1;
    } else {
        pthread_spin_unlock (&dev->printflock);
        return iret;
    }

}


/* @zhangjun 01.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
int arincTrylock (void)
{
    arincDev_t *dev = arincGetDev ();
    return pthread_spin_trylock (&dev->lock);
}


/* @zhangjun 01.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
static void arryOffset (u8 arry[], u32 start, u32 end)
{
    u32 i = 0;

    for (; start<end; start++) {
        arry[i] = arry[start];
        i += 1;
    }
    for (; i<end; i++) {
        arry[i] = 0;
    }
}

static void arryShow (u8 arry[], u32 len)
{
    u32 i = 0;
    for (i=0; i<len; i++) {
        printf ("%02x ", arry[i]);
    }
    printf ("\n");
}


static int line2Data (u8 *line, u8 *data, float *speed)
{
    u8* pDivS = NULL;
    u8* pDivE = NULL;
    u8 tmp[25];
    u32 arincData;

    pDivS = strchr (line, ':');
    pDivE = strchr (line, ';');
    if ((pDivS == NULL) || (pDivE == NULL)) {
        return -1;
    }

    memset (tmp, 0, 25);
    memcpy (tmp, pDivS+2, pDivE-pDivS-3);

    *speed = atof (tmp);

    pDivS = strchr ((char*)pDivE, ':');
    if ((pDivS == NULL) || (pDivE == NULL)) {
        return -1;
    }

    memset (tmp, 0, 25);
    memcpy (tmp, (char*)pDivS+3,  strlen(line) - (pDivS-line) - 3);

    arincData = strtol (tmp, NULL, 16);

    data[0] = (0xFF << 0 & arincData) >> 0;
    data[1] = (0xFF << 8 & arincData) >> 8;
    data[2] = (0xFF << 16 & arincData) >> 16;
    data[3] = (0xFF << 24 & arincData) >> 24;
    return 0;
}

/* @zhangjun 30.06.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
int arincInit (void)
{
    int ret;
    arincDev_t *dev = NULL;

    gSerFd = open_port (SERIALDEV);
    if (-1 == gSerFd) {
        printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)) ;
        return -1;
    }

    ret = setup_port (gSerFd, SERIAL_BAUDRATE, SERIAL_DATAWIDTH, SERIAL_PARITY, SERIAL_STOP);
    if (-1 == ret) {
        printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)) ;
        return -1;
    }

    dev = arincGetDev ();

    ret = pthread_spin_init (&dev->lock, PTHREAD_PROCESS_SHARED);
    if (0 != ret) {
        printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)) ;
        return -1;
    }

    ret = pthread_spin_init (&dev->printflock, PTHREAD_PROCESS_SHARED);
    if (0 != ret) {
        printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)) ;
        return -1;
    }

    if (access(ARINC_SHM, F_OK) == -1) {
        ret = open (ARINC_SHM, O_CREAT | 0666);
        if (-1 == ret) {
            printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)) ;
            return -1;
        }
        close (ret);
    }

    dev->key = ftok (ARINC_SHM, ARINC_PRJ);
    if (-1 == dev->key) {
        printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)) ;
        return  -1;
    }

    dev->shmID = shmget (dev->key, ARINC_SHM_SIZE, IPC_CREAT|0666);
    if (-1 == dev->shmID) {
        printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)) ;
        return  -1;
    }

    dev->offset = 0;

    ret = logInit (ARINC_LOG);
    if (-1 == ret) {
        printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)) ;
        return -1;
    }

    return 0;
}

/* @zhangjun 30.06.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
int arincWrite (arincData_t pkt)
{
    u8 cmd[] = {0xaa, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    u8 nWrite = 0, total = 0, nSize = sizeof(cmd);

    memcpy (&cmd[3], &pkt, sizeof(pkt));

    while (total < nSize) {
        nWrite = write (gSerFd, &cmd[total], nSize-total);
        if (-1 == nWrite) {
            continue;
        }
        total += nWrite;
    }
    return 0;
}

/* @zhangjun 30.06.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
int arincRead (u8 *data, u32 len)
{
    int ret = 0;
    ret = read (gSerFd, data, len);
    if (-1 == ret) {
        return -1;
    }
    return ret;
}


/* @zhangjun 30.06.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
void * arincWriteLoop (void *arg)
{
    arincData_t pkt;
    u32 checkSum = 0, nSend = 0;
    int ret = 0;

    while (1) {

        RandomU8 (&pkt.label, 0xff);
        RandomU8 (&pkt.dat[0], 0xff);
        RandomU8 (&pkt.dat[1], 0xff);
        RandomU8 (&pkt.dat[2], 0xff);

        checkSum += pkt.label + pkt.dat[0] + pkt.dat[1] + pkt.dat[2];

        ret = arincWrite (pkt);
        if (0 == ret) {
            nSend += 1;
            if ((nSend % OUT_PRESIZE ) == 0) {
                arincInfo ("nSend: %d  checkSum: %x \n", nSend, checkSum);
            }
        } else {
            printf ("failed: [%x %x %x %x] \n", pkt.label, pkt.dat[0], pkt.dat[1], pkt.dat[2]);
        }
        usleep (10);
    }
}


/* @zhangjun 01.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
void *arincReadLoop (void *arg)
{
    arincDev_t *dev = arincGetDev ();
    u8 *pMapAddr = NULL;
    u8 *pReadMem = 0;
    u32 nRead = 0, nTotal = 0;
    u32 nTran = 0;
    pthread_attr_t attr;
    pthread_t revPID = 0;
    int ret = 0;

    pthread_attr_init(&attr);

    ret = pthread_create (&revPID, &attr, arincResolverLoop, NULL);
    if (-1 == ret) {
        printf ("[%s] [%d] (%s) \n", __FUNCTION__, __LINE__, strerror(errno)) ;
        return (void *) -1;
    }

    pReadMem = (u8*)malloc(ARINC_READ_MAX);
    if (NULL == pReadMem) {
        return (void *) -1;
    }

    pMapAddr = (u8*)shmat (dev->shmID, NULL, 0);
    if (NULL == pMapAddr) {
        printf ("[%s] [%d] \n", __FUNCTION__, __LINE__);
        printf ("[%s] \n", strerror(errno));
        return (void *) -1;
    }

    memset (pMapAddr, 0, ARINC_SHM_SIZE);

    nRead = 0;
    nTotal = 0;

    while (1) {

        nRead = arincRead ( pReadMem+nTotal, ARINC_READ_MAX-nTotal);
        if (-1 == nRead) {
            continue;
        }

        nTotal += nRead;
        if (-1 == arincTrylock()) {
            continue;
        }

        if ( (dev->offset + nTotal) <= ARINC_SHM_SIZE) {
            nTran = nTotal;
        } else {
            nTran = ARINC_SHM_SIZE-dev->offset;
        }

        memcpy (pMapAddr+dev->offset, pReadMem, nTran);
        dev->offset += nTran;

        if (nTran >= nTotal) {
            nTotal = 0;
            memset (pReadMem, 0, ARINC_READ_MAX);
        } else {
            arryOffset (pReadMem, nTran, nTotal);
            nTotal -= nTran;
        }

        arincUnlock ();
    }
    return (void *) -1;
}


/* @zhangjun 01.07.2021
 * function:
 * description:
 * input:
 * output:
 * return:
 */
void * arincResolverLoop (void *arg)
{
    arincDev_t *dev = arincGetDev ();
    u8 *pMapAddr = NULL;
    u8 *pDiv = NULL, *pLastDiv = NULL;
    u8 tmp[255];
    float speed;
    u8 data[4];
    u32 nRecvPkt = 0, nRecvChcekSum = 0;


    pMapAddr = (u8*)shmat (dev->shmID, NULL, 0);
    if (NULL == pMapAddr) {
        printf ("[%s] [%d] \n", __FUNCTION__, __LINE__);
        printf ("[%s] \n", strerror(errno));
        return (void *) -1;
    }

    while (1) {
        if (-1 == arincTrylock()) {
            continue;
        }

        if (0 == dev->offset) {

        } else {

            pLastDiv = pMapAddr;
            pDiv = pMapAddr;

            while ((pDiv = strchr (pLastDiv, '\n'))  != NULL) {
                memset (tmp, 0, 255);
                memcpy (tmp, pLastDiv, pDiv-pLastDiv-1);

				printf ("tmp: %s \n", tmp);

                if (0 == line2Data (tmp, data, &speed)) {
				    static struct timeval tv_start;
				    static struct timeval tv_cur;

					if (nRecvPkt == 0) {
						gettimeofday (&tv_start, NULL);
					} else {
						gettimeofday (&tv_cur, NULL);
					}

                    nRecvPkt += 1;
                    nRecvChcekSum += data[0] + data[1] + data[2] +data[3] ;
                    if (nRecvPkt % OUT_PRESIZE == 0) {
						/*logInfo ("recv packet: %d , checksum: %x \n", nRecvPkt, nRecvChcekSum);*/
						printf ("recv packet: %d , checksum: %x [%ld s]\n", nRecvPkt, nRecvChcekSum, \
								tv_cur.tv_sec - tv_start.tv_sec);
                    }
					if (nRecvPkt == RES_SIZE) {
						printf ("TEST result: [%d] cheksum: %x \n", nRecvPkt, nRecvChcekSum);
					}
                }
                pLastDiv = pDiv+1;
            }

            if (pLastDiv != pMapAddr) {
                arryOffset (pMapAddr, pLastDiv-pMapAddr, dev->offset);
                dev->offset = dev->offset - (pLastDiv-pMapAddr);
            }
        }

        arincUnlock ();
    }
    return (void *) -1;
}
