#include "kmp.h"
#define Debug 1

#if Debug 
static void showA (u32 *pArry, u32 len)
{
    u32 i = 0;
    for (i=0; i<len; i++)
    {
        printf ("%d", *(pArry + i));
    }
    printf ("\r\n");
}
#endif

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
static void KMP_Prefix (char *pPattern, u32 *pPi)
{
    u32 PatternLen = strlen (pPattern);
    u32 PatternIndex = 0;
    u32 MatchLen = 0;

    *(pPi + 0) = 0;
    
    for (PatternIndex=1; PatternIndex < PatternLen; PatternIndex++)
    {
        /*when we find next character no match, we should try to find last match sub string*/
        while (MatchLen>0 && *(pPattern+MatchLen) != *(pPattern + PatternIndex))
        {
            MatchLen = *(pPi+MatchLen);
        }

        /*if the next character match, increase the match len*/
        if (*(pPattern+ MatchLen ) == *(pPattern+ PatternIndex))
        {
            MatchLen += 1;
        }
        *(pPi + PatternIndex) = MatchLen ;
    }
}

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
char * KMP_MatchString (char *pTarget, char *pPattern)
{
    u32 patternLen = strlen (pPattern);
    u32 TargetLen  = strlen (pTarget);
    u32 TargetIndex = 0;
    u32 MatchLen = 0;
    u32 *pPi = (u32 *)malloc(sizeof(u32) *patternLen);

    if (pPi == NULL)
    {
        return NULL;
    }

    memset (pPi, 0, sizeof(u32)*patternLen);
    KMP_Prefix (pPattern, pPi);
    
#if Debug
    printf ("%s \r\n", pPattern);
    showA (pPi, patternLen);
#endif

    for (TargetIndex = 0; TargetIndex < TargetLen; TargetIndex++)
    {
        while (MatchLen > 0 && *(pPattern + MatchLen) != *(pTarget + TargetIndex))
        {
            MatchLen = *(pPi + MatchLen);
        }
        if (*(pPattern + MatchLen) == *(pTarget + TargetIndex))
        {
            MatchLen += 1;
        }
        if (MatchLen == patternLen)
        {
            return pTarget + TargetIndex - patternLen + 1;
        }
    }

    free (pPi);
    return NULL;
}



