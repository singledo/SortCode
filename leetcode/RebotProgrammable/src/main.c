#include "robot.h"

int main(int argc, char *argv[])
{
	printf ("rebot programable routine \r\n");
	
	u32 CorrdPointer[][2] = {{1,1}, {2,2}};
	char Cmd[] = "UUR";
	int x = 9, y = 9;

	printf ("corrdinate pointer size: [%d] \r\n", sizeof (CorrdPointer));
	
	if (RobotIsArrive (Cmd, CorrdPointer, x, y) == false)
	{
		printf ("cann't arrived \r\n");
	}
	else
	{
		printf ("can arrived \r\n");
	}
	return 0;
}
