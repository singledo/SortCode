#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

#define UPPER (x) (x - 32)
void KeyReset (char *pIn, u32 InLen, char *pOut, u32 k);
char * licenseKeyFormatting(char * S, int K);

int main (int argc, char *argv[])
{
	char In[] = "5-F3Z-2e-9-w";
	char *pRes = NULL;
	u32 k = 3;
#if 0
	char *pOut = (char *)malloc(sizeof(In));
	if (pOut == NULL)
	{
		printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
		return 1;
	}

	KeyReset (In, sizeof(In), pOut, k);
	
	printf ("In [%s] \r\nOut [%s] \r\n", In, pOut);
#endif
	pRes = licenseKeyFormatting (In, k);
	
	if (pRes != NULL)
	{
		printf ("In [%s] \r\nOut [%s] \r\n", In, pRes);
	}
	else
	{
		printf ("licenseKeyFormatting [failed]");
	}

	return 0;
}

void KeyReset (char *pIn, u32 InLen, char *pOut, u32 k)
{
	u32 RmDashLen = 0;
	u32 Index     = 0;
	u32 Parts     = 0;
	u32 FirstPart = 0;
	u32 offset    = 0;

	char *pTemp = (char *)malloc(InLen);

	if (pTemp == NULL)
	{
		printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
		return;
	}
	
	memset (pTemp, 0, InLen);
	/*1. key len after remove '-'*/
	for (Index=0; Index<InLen; Index++)
	{
		if (*(pIn+Index) != '-')
		{
			*(pTemp+RmDashLen) = *(pIn+Index);
			RmDashLen += 1;
		}
	}
	RmDashLen -= 1;

	Parts = (RmDashLen-1)/k + 1;
	FirstPart = 1 + (RmDashLen-1)%k;
	
	strncpy (pOut, pTemp, FirstPart);
	strcat (pOut, "-");

	for (Index=1; Index<Parts; Index++)
	{
		offset = FirstPart + k * (Index - 1);
		strncat (pOut, pTemp+offset, k);
		(Index==Parts-1)? :strcat (pOut, "-");
	}
}


char * licenseKeyFormatting(char * S, int K)
{
	assert (S != NULL || K != 0);

	int i4Len = strlen (S);
	int RmDashLen = 0;
	int Index = 0;
	int FirstPart = 0;
	int Parts = 0;
	int Offset = 0;

	assert (i4Len != 0);

	char *pTemp = (char *)malloc (i4Len);
	char *pRes  = (char *)malloc (i4Len);
	if (pTemp == NULL || pRes == NULL)
	{
		return NULL;
	}
	
	memset (pTemp, 0, i4Len);
	for (Index=0; Index<i4Len; Index++)
	{
		if (*(S + Index) != '-')
		{
			*(pTemp + RmDashLen) = *(S + Index);
			RmDashLen += 1;
		}
	}
	
	Parts = (i4Len - 1)/K ;
	FirstPart = (i4Len - 1)%K + 1;
	
	memset (pRes, 0, i4Len);
	strncpy (pRes, pTemp, FirstPart);
	if (Parts != 1)
		strcat (pRes, "-");
	
	for (Index=1; Index<Parts; Index++)
	{
		Offset = FirstPart + K * (Index - 1);
		strncat (pRes, pTemp + Offset, K);
		if (Index != Parts - 1)
		{
			strcat (pRes, "-");
		}
	}
	free (pTemp);
	return pRes;
}
