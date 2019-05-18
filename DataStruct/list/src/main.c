#include "list.h"

#define LEN (20)
#define MAX (50)

int main(int argc, char *argv[])
{
	printf ("list test routine \r\n");
	u4 arry[LEN] ;
	
	RandomArry(arry, LEN, MAX);
	ShowArry(arry, LEN);

	tListNode head;
	u4 index = 0;

	head.next = NULL;
	head.data = -1;

	for (index=0; index<LEN; index++)
	{
		ListInsert(&head, arry[index]);
	}
	
	ListTraver(&head);

	return 0;
}
