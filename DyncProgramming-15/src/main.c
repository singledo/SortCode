#include "DyncPro.h"

#define MatrixLen (10)
u4 MatrixSize[MatrixLen][2] = {0};
u4 MatrixRes[MatrixLen][MatrixLen] = {0};
u4 MatrixDivRes[MatrixLen][MatrixLen] = {0};

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
        /*MatrixSize[u4Index][1] = u4Index;*/
        if (u4Index+1<MatrixLen)
        {
            MatrixSize[u4Index+1][0] = MatrixSize[u4Index][1];
        }
    }
#if 1
    for (u4Index=0; u4Index<MatrixLen; u4Index++)
    {
        printf ("[%02d, %02d] \n", MatrixSize[u4Index][0], MatrixSize[u4Index][1]);
    }
#endif
    DyncProgramming ((u4 *)&MatrixSize[0], MatrixLen, \
                     (u4 *)&MatrixRes[0], (u4 *)&MatrixDivRes, MatrixLen);
#if 0
    ShorestPath ((u4*)&MatrixSize[0], (u4*)&MatrixRes[0], (u4*)&MatrixDivRes, \
                 0, MatrixLen, MatrixLen);
#endif
    return 0;
}
