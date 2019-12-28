#include "robot.h"

int main(int argc, char *argv[])
{
	printf ("rebot programable routine \r\n");
	
	u32 CorrdPointer[][2] = {{3,1}, {5,2}};
	u32 Dest[2] = {5,5};
	char Cmd[] = "UR";
	u32 CorrdPointerNum = sizeof(CorrdPointer)/sizeof(CorrdPointer[0]);
	
	if (RobotIsArrive (Cmd, CorrdPointer, CorrdPointerNum, Dest) == false)
	{
		printf ("cann't arrived \r\n");
	}
	else
	{
		printf ("can arrived \r\n");
	}
	return 0;
}
