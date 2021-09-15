#include "hsaeDecrypt.h"

bool fileToKey (char *keyFile, unsigned char *key, unsigned char *iv)
{
    assert (keyFile != NULL);
    assert (key != NULL);
    assert (iv != NULL);

    char keyStr[PASSWDLEN];
	int keyLen = 0;
    int i = 0;
    EVP_CIPHER *cipher = NULL;
	EVP_MD *dgst = NULL;
	unsigned char salt[PKCS5_SALT_LEN] = "Salted__";

    OpenSSL_add_all_ciphers();
    OpenSSL_add_all_digests();

    BIO *keyIo = BIO_new_file(keyFile, "r");
    if (NULL == keyIo) {
        return false;
    }

	memset (keyStr, 0, PASSWDLEN);
    /* read string from file*/
    i = BIO_gets(keyIo, keyStr, PASSWDLEN);
    if (0 >= i) {
		printf("[%s],[%d] [%s] \n",__FUNCTION__,__LINE__, strerror(errno));
        return false;
    }
	keyLen = strlen(keyStr) - 1;

    cipher = (EVP_CIPHER *)EVP_get_cipherbyname("aes-256-cbc");
    if (NULL == cipher) {
		printf("[%s],[%d] [%s] \n",__FUNCTION__,__LINE__, strerror(errno));
        return false;
    }


	dgst = (EVP_MD *)EVP_sha256();
	i = EVP_BytesToKey(cipher, dgst, NULL, (unsigned char *)keyStr, keyLen,
					   1, key, iv);
	if (i == 0) {
		return false;
	}

	int len1 = 0;
	int len2 = 0;

	len1 = EVP_CIPHER_iv_length (cipher);
	len2 = EVP_CIPHER_key_length (cipher);

	printf ("key=");
	for (i=0; i<len2; i++) {
		printf ("%02x", *(key+i));
	}
	printf ("\n");

	printf ("iv =");
	for (i=0; i<len1; i++) {
		printf ("%02x", *(iv+i));
	}
	printf ("\n");

    // cipher
	BIO_free (keyIo);
    return true;
}


bool aesDecrypt (char* inFile, char* keyFile, char* outFile)
{
#define AESPRESIZE (1024)

    AES_KEY aes;
	bool bret = false;
	unsigned char key[PASSWDLEN], iv[PASSWDLEN];
	EVP_CIPHER_CTX  *ctx;
	int rFd, wFd;
	int rSize, wSize;
	int wSizeDone = 0;
	char *cipherBuf = NULL;
	char *plainBuf  = NULL;
	char magic[] = "Salted__";
	int i = 0;

	cipherBuf = (char *) malloc(sizeof(char) * AESPRESIZE + 4) ;
	if (NULL == cipherBuf) {
		return false;
	}

	plainBuf = (char *) malloc(sizeof(char) * AESPRESIZE + 4) ;
	if (NULL == plainBuf) {
		return false;
	}

	// file to key and iv
	memset (key, 0, PASSWDLEN);
	memset (iv, 0, PASSWDLEN);
	bret = fileToKey (keyFile, key, iv);
	if (false == bret) {
		return false;
	}
	ctx = EVP_CIPHER_CTX_new ();

	EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
	EVP_CIPHER_CTX_set_key_length(ctx, EVP_MAX_KEY_LENGTH);
	rFd = open(inFile, O_RDONLY);
	if (-1 == rFd) {
		return false;
	}
	wFd = open (outFile, O_WRONLY|O_CREAT);
	if (NULL == wFd) {
		return false;
	}
	memset (cipherBuf, 0, AESPRESIZE);
	memset (plainBuf, 0, AESPRESIZE);
	while ((rSize = read (rFd, cipherBuf, AESPRESIZE)) && (rSize > 0)) {
		if (0 == EVP_DecryptUpdate(ctx, plainBuf, &wSize, cipherBuf, rSize)) {
			printf("[%s],[%d] [%s] \n",__FUNCTION__,__LINE__, strerror(errno));
		} else {
			printf ("wsize: [%d] \n", wSize);
			printf ("%s", plainBuf);

			write (wFd, plainBuf, wSize);
		}
		memset (cipherBuf, 0, AESPRESIZE);
		memset (plainBuf, 0, AESPRESIZE);
	}
	EVP_CIPHER_CTX_free(ctx);
	close (rFd);
	close (wFd);
    return true;
}


