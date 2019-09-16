#include "kmp.h"
#include "rabin-karp.h"
#include "simple.h"

#define SIMPLEMATCH 0
#define RABINMATCH 1
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

#endif
    return 0;
}
