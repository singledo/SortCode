#include "rabin-karp.h"

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
char * RKMatch (char *pTarget, char *pPattern)
{
    if (pTarget == NULL || pPattern == NULL)
    {
        return NULL;
    }
    u32 TargetLen = strlen (pTarget);
    u32 PatternLen = strlen (pPattern);
    u32 ArryLen = 0;
    u32 start = 0;
    u32 *pArry = NULL;
    u32 index = 0;
    u32 PatternHash = 0;

    if (TargetLen < PatternLen)
    {
        return NULL;
    }
    
    ArryLen = TargetLen - PatternLen;
    pArry = (u32*)malloc(sizeof(u32)*ArryLen);
    if (pArry == NULL)
    {
        return NULL;
    }
    
    /*hash arry*/
    memset (pArry, 0, ArryLen*sizeof(u32));
    for (start=0; start<ArryLen; start++)
    {
        *(pArry+start) = 0;
        index = 0;
        while (index < PatternLen)
        {
            *(pArry+start) += *(pTarget+start+index);
            index += 1;
        }
        *(pArry+start) %= HASHSEED;
        printf ("%02d ", *(pArry+start));
    }
    
    /*calculate the pattern's hash*/
    index = 0;
    while (index < PatternLen)
    {
        PatternHash += *(pPattern + index);
        index += 1;
    }
    PatternHash %= HASHSEED;
    for (index=0; index<(TargetLen-PatternLen); index++)
    {
        if (*(pArry+index) == PatternHash && memcmp (pTarget+index, pPattern, PatternLen) == 0)
        {
            return pTarget+index;
        }
    }
    return NULL;
}
