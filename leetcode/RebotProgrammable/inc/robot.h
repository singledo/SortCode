#ifndef _robot_h
#define _robot_h

#include "com.h"
typedef u32 u4;
typedef u16 u2;
typedef u8  u1;

typedef enum
{
	CONTINUE = 0,
	MEET, 
	EXCEED,
	COMPELTE
}FIND_ST;

bool RobotIsArrive (char *pCmd, u32 u4Obstacle[][2], \
                    u32 u4ObstacleNum, u32 Dest[2]);

bool IsIn (u32 u4Curr[2], u32 u4ObstList[][2], u32 u4Num);

#endif
