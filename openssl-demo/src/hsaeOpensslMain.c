#include "hsaeDecrypt.h"
#include "hsaeEncrypt.h"


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


	char inFile[] = "./out-enc";
	char outFile[] = "./out-dec";
	char keyFile[] = "./key/sym.key";

	aesDecrypt (inFile, keyFile, outFile);

	return 0;
}
