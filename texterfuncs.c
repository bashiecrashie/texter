#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringfuncs.h"

#define MAX_LINE_LENGTH 512
#define COLUMN_WIDTH 20
#define C_FILE_BEGIN "#include<stdio.h>\nint main()\n{\nchar *content=\""
#define C_FILE_END "\";\nprintf(\"%s\", content);\nreturn 0;\n}"

void cout(const char *in, const char *out)
{

    int ch = 0;

    FILE *FileInput = fopen(in, "r"), *FileOutput = fopen(out, "w");

    fputs(C_FILE_BEGIN, FileOutput);

    while ((ch = fgetc(FileInput)) != EOF)
    {

        if (ch == 34)
            ch = 1;

        if (ch == '\n')
        {
            ch = 34;
            fputs("\\n", FileOutput);
            fputc(ch, FileOutput);
            fputc('\n', FileOutput);
        }

        fputc(ch, FileOutput);
    }

    fputs(C_FILE_END, FileOutput);

    fclose(FileOutput);

    fclose(FileInput);
}

void txtout(const char *in, const char *out)
{

    FILE *InputFile = fopen(in, "r");
    FILE *OutputFile = fopen(out, "w");

    int word_len = 0, len = 0, counter = 0, ch = 0;

    const int BUFF_SIZE = 512;

    char line[BUFF_SIZE], clrline[BUFF_SIZE];

    char *word;

    while((fgets(line, BUFF_SIZE, InputFile)))
    {

        word = strtok(line, ",");

        while(word)
        {

            word_len = strlen(word);
            fprintf(OutputFile, "%-*s", 20, word);
            word = strtok(NULL, ",");
        }
        fprintf(OutputFile, "%s", "\n");
    }

    fclose(InputFile);
    fclose(OutputFile);
}

void htmlout(const char *in, const char *out)
{
    ;
}