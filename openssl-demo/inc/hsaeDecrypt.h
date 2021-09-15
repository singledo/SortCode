#ifndef _hsaeDecrypt_h
#define _hsaeDecrypt_h

#include "com.h"
#include <errno.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/ssl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PASSWDLEN (1024)

bool fileToKey (char *keyFile, unsigned char *key, unsigned char *iv);
bool aesDecrypt (char* inFile, char* keyFile, char* outFile);

#endif
