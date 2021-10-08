#ifndef _hsaeMD5_h
#define _hsaeMD5_h

#include "com.h"
#include <errno.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/ssl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<openssl/md5.h>
#include <sys/types.h>
#include <unistd.h>


#define MD5BUFLEN (4096)
#define MD5LENTH 16

bool fileMD5 (const char *file, unsigned char *md);


#endif
