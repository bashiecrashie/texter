#include<stdio.h>
#include<string.h>
#include"help.h"
#include"texterfuncs.h"

int main(int argc, char *argv[])
{
    //Для красоты
    char *logo = "\n"
                                     
" _____ _____ __ __ _____ _____ _____ \n"
"|_   _|   __|  |  |_   _|   __| __  |\n"
"  | | |   __|-   -| | | |   __|    -|\n"
"  |_| |_____|__|__| |_| |_____|__|__|\n"
"                          Version 0.1\n";

    printf("%s", logo);

    if(argc != 5)
    {
        printf("Неверное количество аргументов.\n");
        showhelp();
    }else if(!(strcmp(argv[4], "COUT")))
        cout(argv[1], argv[3]);
    else if(!(strcmp(argv[4], "TXTOUT")))
        txtout(argv[1], argv[3]);
    else if(!(strcmp(argv[4], "HTMLOUT")))
        htmlout(argv[1], argv[3]);

    return 0;

}