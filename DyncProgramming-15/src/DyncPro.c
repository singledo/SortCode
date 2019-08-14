#include "DyncPro.h"

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void ShowMatrixSize (u4 *p, u4 u4Len)
{
    u4 u4Index = 0;
    for (u4Index = 0; u4Index < u4Len/2; u4Index++)
    {
        if (u4Index != u4Len/2 - 1)
        {
            printf ("[%d,%d]*", *(p+u4Index*2), *(p+u4Index*2+1));
        }
        else
        {
            printf ("[%d,%d] \n", *(p+u4Index*2), *(p+u4Index*2+1));
        }
    }
}

/****************************************************
 *  Function Name : ShowMatrix 
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void ShowMatrix (u4 *p, u4 col, u4 row)
{
    u4 i = 0, j = 0;
    printf ("#");
    for (i=1; i<row; i++)
    {
        printf ("    ");
    }
    printf ("#\n\n");
    for (i=0; i<row; i++)
    {
        for (j=0; j<col; j++)
        {
            printf ("%02d  ", *(p+i*col+j)); 
        }       
        printf ("\n\n");
    }
    printf ("#");
    for (i=1; i<row; i++)
    {
        printf ("    ");
    }
    printf ("#\n");

}

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
u4 CalculateTimes (u4 *pSou, u4 u4Start, u4 u4Middle, u4 u4End)
{
    if (u4End <= u4Start)
    {
        return 0;
    }
    assert (!(u4Middle<u4Start || u4Middle > u4End));

    u4 u4HeadTime = 0, u4TailTime = 0, u4Merger;
    u4 i = 0, j = 0;
    u4 u4Multi = 0, u4Add = 0;
    u4 *pArry1 = NULL, *pArry2 = NULL;

    for (i=u4Start; i<u4Middle; i++)
    {
        pArry1 = pSou + u4Start * 2 ;
        pArry2 = pSou + u4Start * 2  + 2;
        u4Multi = *pArry1 * *(pArry1+1) * *(pArry2 + 1);
        u4Add   = *pArry1 * *(pArry2+1) * ( *(pArry1+1) * *(pArry1+1) - 1);
        u4HeadTime += u4Multi + u4Add;
    }

    u4Multi = 0;
    u4Add = 0;
    for (j=u4Middle; j<u4End; j++)
    {
        pArry1 = pSou + u4Middle* 2 ;
        pArry2 = pSou + u4Middle* 2  + 2;
        u4Multi = *pArry1 * *(pArry1+1) * *(pArry2 + 1);
        u4Add   = *pArry1 * *(pArry2+1) * ( *(pArry1+1) * *(pArry1+1) - 1);
        u4TailTime += u4Multi + u4Add;
    }

    u4Multi = 0;
    u4Add = 0;
    if (u4Middle != u4Start)
    {
        u4Multi = *(pSou + u4Start*2) * *(pSou + u4Middle*2) * *(pSou + u4End*2 + 1);
        u4Add   = *(pSou + u4Start*2) * *(pSou + u4End*2 + 1) * \
                  (*(pSou + u4Middle*2) * *(pSou + u4Middle*2) - 1);
        u4Merger = u4Multi + u4Add;
    }
    return u4HeadTime + u4TailTime + u4Merger;
}

/****************************************************
 *  Function Name :
 *  Description   :
 *  Input         :
 *  Output        :
 *  Returns       :
 ****************************************************/
void DyncProgramming (u4 *pSou, u4 u4SouRow, u4 *pRes, u4 u4DesRow)
{
    /*ShowMatrix (pSou, 2, u4SouRow);*/
    u4 i = 0, j = 0, k = 0;
    u4 u4CalTimes = 0, u4LeastTime = 0;
    
    memset (pRes, 0, sizeof(u4)*u4DesRow*u4DesRow);
    for (i=0; i<u4DesRow; i++)
    {
        *(pRes+i*u4DesRow+i) = 0;
    }
    
    for (i=0; i<u4DesRow; i++)
    {
        for (j=i+1; j<u4DesRow; j++)
        {
            k = i;
            u4CalTimes   = 0;
            u4LeastTime  = CalculateTimes (pSou, i, k, j);
            k += 1;

            while (k<j)
            {
                u4CalTimes = CalculateTimes (pSou, i, k, j);        
                if (u4CalTimes < u4LeastTime)
                {
                    u4LeastTime = u4CalTimes;
                }
                k += 1;
            }
            *(pRes + j*u4DesRow + i) = u4LeastTime;
        }           
    }
    ShowMatrix (pRes, u4DesRow, u4DesRow);
}

