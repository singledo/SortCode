#include "queue.h"

#define LEN (20)
#define MAX (500)

int main(int argc, char *argv[])
{
	printf ("queue data strcut ..... \r\n");
	u4 u4RandomArry[LEN] = {0};
	RandomArry(u4RandomArry, LEN, MAX);
	ShowArry(u4RandomArry, LEN);

	Queue queue;

	return 0;
}
