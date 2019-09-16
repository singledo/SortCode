#include "simple.h"

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
char *SimpleMatch (char *dest, char *pattern)
{
    if (dest == NULL || pattern == NULL)
    {
        return NULL;
    }

    u4 u4DestLen = strlen (dest);
    u4 u4PatternLen = strlen (pattern);
    u4 u4DestIndex = 0, u4PatternIndex = 0;
    char *p = NULL;
    
    if (u4PatternLen > u4DestLen)
    {
        return NULL;
    }

    while ( *(dest + u4DestIndex) != 0 )
    {
        if ((u4DestLen - u4DestIndex) >= u4PatternLen)
        {
            if (memcmp (dest + u4DestIndex, pattern, u4PatternLen) == 0)
            {
                return dest + u4DestIndex;
            }
        }
        u4DestIndex += 1;
    }
    return NULL;
}
