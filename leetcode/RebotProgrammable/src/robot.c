#include "robot.h"

bool IsIn (u32 u4Curr[2], u32 u4ObstList[][2], u32 u4Num)
{
    u4 u4Index = 0;
    for (u4Index=0; u4Index<u4Num; u4Index++)
    {
        if (u4Curr[0] == u4ObstList[u4Index][0] && \
            u4Curr[1] == u4ObstList[u4Index][1] )
        {
            return true;
        }
    }
    return false;
}


/* functionc:  RobotIsArrive 
 *
 * decription: robot can arrive the end
 *
 * argument:
 *           pCmd - command 
 *           u4Obstacle - pointer for obstacla
 *           x          - x for end pointer
 *           y          - y for end pointer
 *
 * return :
 *        false - cann't arrive
 *        true  - can arrive
 *
 * */
bool RobotIsArrive (char *pCmd, u32 u4Obstacle[][2], \
                    u32 u4ObstacleNum, u32 Dest[2])
{
    assert (pCmd != NULL);
    u4 u4CmdLen = strlen (pCmd);
    u4 u4Index = 0;
    FIND_ST findSt = CONTINUE;
    char *pNextCmd = pCmd;
    char Cmd = *pNextCmd;
    u4   u4Curr[2] = {0, 0};

    while (findSt == CONTINUE)
    {
        printf ("%c ", Cmd);
        // [x,y]
       switch (Cmd)
       {
       case 'U': // x+1
           {
               u4Curr[0] += 1;
           }
           break;
       case 'R': // y+1
           {
               u4Curr[1] += 1;
           }
           break;
       default:
           {
                printf ("WRONG CMD [%c] \r\n", Cmd);
                return false;
           }
       }
       if (u4Curr[0] > Dest[0] || u4Curr[1] > Dest[1])
       {
           findSt = EXCEED;
       }
       else if (u4Curr[0] == Dest[0] &&  u4Curr[1] == Dest[1])
       {
           findSt = COMPELTE;
       }
       else if (IsIn (u4Curr, u4Obstacle, u4ObstacleNum) == true)
       {
           findSt = MEET;
       }
       else
       {
           if (pNextCmd - pCmd < u4CmdLen - 1)
           {
               pNextCmd += 1;
           }
           else
           {
               pNextCmd = pCmd;
           }
           Cmd = *pNextCmd;
           findSt = CONTINUE;
       }
    }
    
    if (findSt == COMPELTE)
    {
        return true;
    }
    else
    {
        printf ("exit status: [%d] \r\n", findSt);
        return false;
    }
}
