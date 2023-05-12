#include<stdio.h>

int colnum(const char *file)//функция для подсчёта столбцов в файле
{
    FILE *fp = fopen(file, "r");

	int num = 0, ch = 0, quotes = 0;
	char word[10];

	while((ch = fgetc(fp)) != '\n')
	{
		if(ch == 34)
			++quotes;

        if(quotes == 2)
        {
            ++num;
            quotes = 0;
        }
	}
    fclose(fp);

    return num;
}
