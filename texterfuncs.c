#include<stdio.h>
#include<stdlib.h>

/*FILE *retfp(const char *file)
{

    FILE *FilePointer = fopen(file, "r");

    return FilePointer;

}*/

void quotesclear(FILE *fin, FILE *fout)
{

    int ch = 0;

    while(ch != EOF)
    {
        ch = fgetc(fin);
        if(ch != '"')
            fputc(ch, fout);
    }


}

void commasclear(FILE *fin, FILE *fout)
{

    int ch = 0;

    while(ch != EOF)
    {
        ch = fgetc(fin);
        if(ch != ',')
            fputc(ch, fout);

    }


}

int sizeoffile(FILE *file)
{

    int ch = 0, size = 0;

    while(ch != EOF)
    {
        ch = fgetc(file);
        ++size;
    }

    return size;

}

void cout(const char *in, const char *out)
{

    int *GetPointer = NULL, ch = 0;

    char *str, *clrstr, *c_file_begin = "#include<stdio.h>\nint main()\n{\nchar *content=\"", *c_file_end = "\";\nprintf(\"%s\", content);\nreturn 0;\n}";

    FILE *FileInput = fopen(in, "r"), *FileOutput = fopen(out, "w");

    int size = sizeoffile(FileInput), counter = 0;

    char content[size];

    fputs(c_file_begin, FileOutput);

    /*:-|*/

    fputs(c_file_end, FileOutput);

    fclose(FileOutput);
}

void txtout(const char *in, const char *out)
{
    ;
}

void htmlout(const char *in, const char *out)
{
    ;
}