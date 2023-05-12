#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extrafuncs.h"

void cout(const char *in, const char *out)
{

    int ch = 0;
    
    char *C_FILE_BEGIN = "#include<stdio.h>\nint main()\n{\nchar *content=\"";
    char *C_FILE_END = "\";\nprintf(\"%s\", content);\nreturn 0;\n}";

    FILE *FileInput, *FileOutput;

    if(!(FileInput = fopen(in, "r")))
    {
        perror("");
        exit(-1);
    }

    if(!(FileOutput = fopen(out, "w")))
    {
        perror("");
        exit(-1);
    }
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

    FILE *FileInput;
    FILE *FileOutput;

    if(!(FileInput = fopen(in, "r")))
    {
        perror("");
        exit(-1);
    }

    if(!(FileOutput = fopen(out, "w")))
    {
        perror("");
        exit(-1);
    }

    int word_len = 0, len = 0, counter = 0, ch = 0;
    const int BUFF_SIZE = 512;

    char line[BUFF_SIZE], clrline[BUFF_SIZE], *word;

    while((fgets(line, BUFF_SIZE, FileInput)))
    {
        word = strtok(line, ",");
        while(word)
        {
            fprintf(FileInput, "%-*s", 20, word);
            word = strtok(NULL, ",");
        }
        fprintf(FileOutput, "%s", "\n");
    }

    fclose(FileInput);
    fclose(FileOutput);
}

void htmlout(const char *in, const char *out)
{
    FILE *FileInput;
    FILE *FileOutput;

    if(!(FileInput = fopen(in, "r")))
    {
        perror("");
        exit(1);
    }

    if(!(FileOutput = fopen(out, "w")))
    {
        perror("");
        exit(1);
    }

    char *HTML_FILE_BEGIN = "<!DOCTYPE html>\n"
    "<html>\n"
    "<style>\n"
    "table, th, td {\n"
    "   border:1px solid black;\n"
    "}\n"
    "</style>\n"
    "<body>\n";
    char *HTML_TABLE_STYLE = "\n<table style=""width:100%"">\n";

    const int BUFF_SIZE = 512;
    int columns = colnum(in), counter = 0;

    char line[BUFF_SIZE], *word;

    fprintf(FileOutput, "%s", HTML_FILE_BEGIN);
    fprintf(FileOutput, "<title>%s</title>", in);
    fprintf(FileOutput, "%s", HTML_TABLE_STYLE);

    fprintf(FileOutput, "<tr>");
    fgets(line, BUFF_SIZE, FileInput);
    word = strtok(line, ",");
    while(word)
    {
        fprintf(FileOutput, "<th>%s</th>", word);
        word = strtok(NULL, ",");
    }
    fprintf(FileOutput, "</tr>");

    while((fgets(line, BUFF_SIZE, FileInput)))
    {
        for(counter = 1; counter < columns; ++counter)
            fprintf(FileOutput, "<tr>\n");

        word = strtok(line, ",");
        fprintf(FileOutput, "<td>%s</td>\n", word);

        while(word)
        {
            word = strtok(NULL, ",");
            if(word == NULL)
                continue;

            fprintf(FileOutput, "<td>%s</td>\n", word);
        }
    }
    for(counter = 1; counter < columns; ++counter)
        fprintf(FileOutput, "</tr>\n");

    fprintf(FileOutput, "\n</table>\n");
    fprintf(FileOutput, "\n</body>\n</html>\n");

    fclose(FileInput);
    fclose(FileOutput);
}
