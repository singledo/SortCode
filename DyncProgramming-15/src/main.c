#include "DyncPro.h"

#define MatrixLen (20)
u4 MatrixSize[MatrixLen][2] = {0};
u4 MatrixRes[MatrixLen][MatrixLen] = {0};

int main(int argc, char *argv[])
{
#define MAX 50

    printf ("Dyncmic Programming ..... \r\n");

    u4 u4Index = 0;
    u4 u4Size = 0;

    /*create the martix*/
    RandomArry (MatrixSize[0], 2, MAX);
    MatrixSize[1][0] = MatrixSize[0][1];

    for (u4Index=1; u4Index<MatrixLen; u4Index++)
    {
        RandomArry (&MatrixSize[u4Index][1], 1, MAX);
        if (u4Index+1<MatrixLen)
        {
            MatrixSize[u4Index+1][0] = MatrixSize[u4Index][1];
        }
    }
#if 0
    for (u4Index=0; u4Index<MatrixLen; u4Index++)
    {
        printf ("[%02d, %02d] \n", MatrixSize[u4Index][0], MatrixSize[u4Index][1]);
    }
#endif
    DyncProgramming ((u4 *)&MatrixSize[0], MatrixLen, \
                     (u4 *)&MatrixRes[0], MatrixLen);

    return 0;
}
