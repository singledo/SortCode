#ifndef _DyncProc_h
#define _DyncProc_h
#include "com.h"

void DyncProgramming (u4 *pSou, u4 u4SouRow, u4 *pRes, u4 *pDivRes, u4 u4DesRow);
void ShowMatrixSize (u4 *p, u4 u4Len);
void ShowMatrix (u4 *p, u4 col, u4 row);
void ShorestPath (u4 *pSou,u4 *pArry, u4 *pDivArry, u4 u4Start, u4 u4End, u4 u4Col);
#endif
