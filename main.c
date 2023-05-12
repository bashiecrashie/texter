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
        fprintf(stdout, "Неверное количество аргументов.\n");
        showhelp();
    }else if(!(strcmp(argv[4], "COUT")))
    {
        fprintf(stdout, "Выбран формат для генерации файла .c\n");
        cout(argv[1], argv[3]);
    }
    else if(!(strcmp(argv[4], "TXTOUT")))
    {
        fprintf(stdout, "Выбран формат для генерации файла .txt\n");
        txtout(argv[1], argv[3]);
    }
    else if(!(strcmp(argv[4], "HTMLOUT")))
    {
        fprintf(stdout, "Выбран формат для генерации файла .html\n");
        htmlout(argv[1], argv[3]);
    }
    return 0;

}