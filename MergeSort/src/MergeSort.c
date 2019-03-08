#include "MergeSort.h"

static void swap(u32 *arry, u32 idex, u32 idex2)
{
	u32 temp 		= *(arry+idex);
	*(arry+idex) 	= *(arry+idex2);
	*(arry+idex2)  	= *(arry+idex);
}
/*
 * input: 	l - left boudary index
 * 			m - middle index
 * 			r - right boudary index
 * */
void MergeSort(u32 *arry, u32 l, u32 m, u32 r)
{
	/*printf ("[%d] [%d] [%d] \r\n", l, m, r);*/

	u32 sub_l , sub_m, sub_r, sub_len;
	u32 *u32TempArry = NULL;
	u32 i = 0, j = 0, k = 0;
	/* left sub arry: [l,m]*/
	if (m-l>=1)
	{
		sub_l	= l;
		sub_m 	= sub_l + (m-sub_l)/2;
		sub_r	= m;
		if (sub_len == 1)
		{ 
			if (*(arry+l) > *(arry+l+1))
			{
				swap(arry, l, l+1);
			}
		}
		else
		{

			MergeSort(arry, sub_l, sub_m, sub_r);
		}
	}
    /* right sub arrt: [m+1,r]*/
	if (r-m>=2)
	{
		sub_l 	= m + 1;
		sub_m	= sub_l + (r-sub_l)/2;
		sub_r	= r;
		/*[m+1,m+2]*/
		if (sub_len == 1)
		{
			if (*(arry+sub_l) > *(arry+sub_l+1))
			{
				swap(arry, sub_l, sub_l+1);
			}
		}
		else
		{
			MergeSort(arry, sub_l, sub_m, sub_r);
		}
	}

	sub_len = r - l + 1;
	u32TempArry = (u32*)malloc(sizeof(u32)*(sub_len+1));
	if (u32TempArry == NULL)
	{
		printf ("malloc failed \r\n");
		return;
	}
	memset(u32TempArry, 0, sub_len+1);
	/*printf ("### left [%d] [%d] \r\n", l, m);*/
	/*TraverArry(arry+l, m-l+1);*/
	/*printf ("### right [%d] [%d] \r\n", m+1, r);*/
	/*TraverArry(arry+m+1, r-m);*/

	for (i = l, j=m+1, k = l; k<=r; )
	{
		if (*(arry+i) >= *(arry+j))
		{
			*(u32TempArry+k-l) = *(arry+j);
			if (j+1>r)
			{
				memcpy(u32TempArry+k-l+1, arry+i, (m-i+1)*sizeof(u32));
				break;
			}
			else
			{
				j += 1;
			}
		}
		else
		{
			*(u32TempArry+k-l) = *(arry+i);
			if (i+1>m)
			{
				memcpy(u32TempArry+k-l+1, arry+j, sizeof(u32)*(r-j+1));
				break;
			}
			else
			{
				i += 1;
			}
		}
		k += 1;
	}

	/*TraverArry(u32TempArry, r-l+1);*/
	memcpy(arry+l, u32TempArry, sizeof(u32)*(r-l+1));
	free(u32TempArry);
//	printf ("## i:[%d] j:[%d] merger [%d] [%d] [%d] \r\n", i, j, l, m, r);
//	TraverArry(arry+l, r-l+1);
}

void TraverArry(u32 *arry, u32 len)
{
	u32 i = 0;
	for (i=0; i<len; i++)
	{
		printf ("%04d  ", *(arry+i));
	}
	printf ("\r\n");
}
