#include "hsaeDecrypt.h"
#include "hsaeEncrypt.h"
#include "hsaeMD5.h"

#define TAG "main"
int main (int argc, char *argv[])
{
	printf ("hsae Decrypt Demo \n");

#if 0
	char fileKey[] = "./key/sym.key";
	char key[PASSWDLEN];
	char iv[PASSWDLEN];
	bool bret = false;

	bret = fileToKey (fileKey, key, iv);
#endif

#if 0
	char inFile[] = "./out-enc";
	char outFile[] = "./out-dec";
	char keyFile[] = "./key/sym.key";

	aesDecrypt (inFile, keyFile, outFile);
#endif

	unsigned char md[MD5LENTH];
	char file[] = "./demo";
    int i = 0;

	memset (md, 0, MD5LENTH);

    if (false == fileMD5 (file, md)) {
        printf("[%s] [%s],[%d]\n",TAG, __FUNCTION__,__LINE__);
        return 1;
    } else {
        for (i=0; i<MD5LENTH; i++) {
            printf ("%02x", md[i]);
        }
        printf ("\n");
    }

	return 0;
}
