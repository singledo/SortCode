#include "hsaeMD5.h"

#define TAG "MD5"

bool fileMD5 (const char *file, unsigned char *md)
{
	MD5_CTX md5_ctx;
	char dataBuf[MD5BUFLEN];
	int fd;
	int fdSize = 0;
    int rdSize = 0;
    int md5Size = 0;

	assert (MD5_Init(&md5_ctx) == 1);
	memset (dataBuf, 0, MD5BUFLEN);

	fd = open (file, O_RDONLY);
	if (-1 == fd) {
		printf("[%s] [%s],[%d]\n",TAG, __FUNCTION__,__LINE__);
		return false;
	}
    // get file's size
    fdSize = lseek (fd, 0L, SEEK_END);
    printf ("[%s] [size=%d] \n", file, fdSize);
    lseek (fd, 0L, SEEK_SET);

    rdSize = read (fd, dataBuf, MD5BUFLEN) ;

    while (rdSize > 0) {

        MD5_Update (&md5_ctx, dataBuf, rdSize);
        md5Size += rdSize;

        rdSize = read (fd, dataBuf, MD5BUFLEN) ;
    }

    printf ("md5 size: %d \n", md5Size);

    MD5_Final(md, &md5_ctx);

    close (fd);

	return true;
}

