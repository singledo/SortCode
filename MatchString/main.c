#include "kmp.h"
#include "rabin-karp.h"
#include "simple.h"

#define SIMPLEMATCH 0
#define RABINMATCH 0
#define KMP 1
int main (int argc, char *argv[])
{
    printf ("Match String programe ..... \r\n");

#if SIMPLEMATCH 
    char simple_dest[] = "break down these walls and come on in";
    char simple_pantter[] = "come";
    char *token_pointer = SimpleMatch (simple_dest, simple_pantter);

    printf ("dest [%s] pattern [%s] \r\n", simple_dest, simple_pantter);
    if (token_pointer != NULL)
    {
        printf ("token [%s] \r\n", token_pointer);
    }
    else
    {
        printf ("not find \r\n");
    }
#endif

#if RABINMATCH 
    char rk_target[] = "a thing of beauty is joy forever" ;
    char rk_pattern[] = "thing";
    char *rk_pointer  = NULL;
    rk_pointer = RKMatch (rk_target, rk_pattern);
    if (rk_pointer != NULL)
    {
        printf ("target [%s] \r\n", rk_target);
        printf ("pattern [%s] \r\n", rk_pattern);
        printf ("[%s] \r\n", rk_pointer);
    }
    else
    {
        printf("[%s],[%d]\n",__FUNCTION__,__LINE__);
    }

#endif
    
#if KMP
    char target[] = "abcdeabandmabcdabcf";
    char pattern[] = "abcf";
    char *pToken = KMP_MatchString (target, pattern);
    if (pToken != NULL)
    {
        printf ("success [%s] \r\n", pToken);
    }
    else
    {
        printf ("failed \r\n");
    }
#endif
    return 0;
}
