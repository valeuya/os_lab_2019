#include "revert_string.h"
#include <string.h>

void RevertString(char *str)
{
    int i, j;
    char c;

    for (i = 0, j = strlen(str)-1; i < j; i++, j--) 
    {
        c = *(str+i);
        *(str+i) = *(str+j);
        *(str+j) = c;
    }
    
}


