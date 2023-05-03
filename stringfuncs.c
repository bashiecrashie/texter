#include<string.h>

char * clearstring(const char *str)
{

    char *ClearString, ch;

    int counter = 0, dec = 0;

    for(counter = 1; counter < strlen(str) - 1; ++counter)
            ClearString[counter] = str[counter];


    return ClearString;

}