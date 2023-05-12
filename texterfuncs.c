#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extrafuncs.h"//файл с объявлением дополнительных функциями

void cout(const char *in, const char *out)//Функция для создания файла исходного текста на С с содержимым исходного файла
{

    int ch = 0; // Переменная для хранения получаемого символа
    
    char *C_FILE_BEGIN = "#include<stdio.h>\nint main()\n{\nchar *content=\""; //Первая часть С-файла
    char *C_FILE_END = "\";\nprintf(\"%s\", content);\nreturn 0;\n}"; //Втора часть С-файла

    FILE *FileInput, *FileOutput; //Указатели на файлы

    if(!(FileInput = fopen(in, "r")))//Проверка и открытие входящего файла для чтения
    {
        perror("");
        exit(-1);
    }

    if(!(FileOutput = fopen(out, "w"))) //Проверка и создание файла для записи
    {
        perror("");
        exit(-1);
    }
    fputs(C_FILE_BEGIN, FileOutput);//Запись первой половины С-файла

    while((ch = fgetc(FileInput)) != EOF)// Цикл для чтения файла посимвольно
    {
        if (ch == 34)//Удаление ковычек
            ch = 1;

        if (ch == '\n')//Поиск символов для перехода на следующую строку
        {              //и подстановка ковычек в конце каждой строки
            ch = 34;
            fputs("\\n", FileOutput);
            fputc(ch, FileOutput);
            fputc('\n', FileOutput);
        }
        fputc(ch, FileOutput);
    }

    fputs(C_FILE_END, FileOutput);//Запись второй половины С-файла
    fclose(FileOutput);//Закрытие файла для записи
    fclose(FileInput);//Закрытие файла для чтения
}

void txtout(const char *in, const char *out)//Функция для записи содержимого исходного файла и
                                            //с выравниванием по столбцам
{

    FILE *FileInput;//Указатель на файл чтения
    FILE *FileOutput;//Указатель на файл для записи

    if(!(FileInput = fopen(in, "r")))//Проверка и открытие входящего файла для чтения
    {
        perror("");
        exit(-1);
    }

    if(!(FileOutput = fopen(out, "w")))//Проверка и создание файла для записи
    {
        perror("");
        exit(-1);
    }

    const int BUFF_SIZE = 512;//Константа с обозначением маскимального размера входящей строки

    char line[BUFF_SIZE], *word;//Массив для хранения полученной строки, указатель
                                //на хранение слов до и после запятой

    while((fgets(line, BUFF_SIZE, FileInput)))//Цикл для чтения и записи
    {
        word = strtok(line, ",");//Получаем слова до запятой
        while(word)
        {
            fprintf(FileInput, "%-*s", 20, word);//Запис результат в файл с выравниваем по столбцам
            word = strtok(NULL, ",");//Получение слов после запятой
        }
        fprintf(FileOutput, "%s", "\n");//Запись символа для перехода на следующую строку
    }

    fclose(FileInput);//Закрытие потока файла для чтения
    fclose(FileOutput);//Закрытие потока файла для записи
}

void htmlout(const char *in, const char *out)//Функция для записи в файл в формате HTML по столбцам
{
    FILE *FileInput;//Указатель на файл для чтения
    FILE *FileOutput;//Указатель на файл для записи

    if(!(FileInput = fopen(in, "r")))//Проверка и открытие входящего файла для чтения
    {
        perror("");
        exit(1);
    }

    if(!(FileOutput = fopen(out, "w")))//Проверка и создание файла для записи
    {
        perror("");
        exit(1);
    }

    char *HTML_FILE_BEGIN = "<!DOCTYPE html>\n"//Начало файла HTML
    "<html>\n"
    "<style>\n"
    "table, th, td {\n"
    "   border:1px solid black;\n"
    "}\n"
    "</style>\n"
    "<body>\n";
    char *HTML_TABLE_STYLE = "\n<table style=""width:100%"">\n";//Стиль таблицы

    const int BUFF_SIZE = 512;//Константа для хранения границ размера получаемой строки
    int columns = colnum(in), counter = 0;//Переменная для хранения количества столбцов, переменная-счётчик

    char line[BUFF_SIZE], *word;//Массив для хранения полученной строки, указатель на слово

    fprintf(FileOutput, "%s", HTML_FILE_BEGIN);//Запись в файл начала HTML
    fprintf(FileOutput, "<title>%s</title>", in);//Запись в файл тега с заголовком исходного файла
    fprintf(FileOutput, "%s", HTML_TABLE_STYLE);//Запись в файл стиля таблицы

    fprintf(FileOutput, "<tr>");//Запись в файл тега для разметки таблицы
    fgets(line, BUFF_SIZE, FileInput);//Полчение первой строки файла
    word = strtok(line, ",");//Убираем запятую
    while(word)//Получаем слова после запятой и записываем теги с заголовками таблицы
    {
        fprintf(FileOutput, "<th>%s</th>", word);//Запись заголовков таблицы
        word = strtok(NULL, ",");
    }
    fprintf(FileOutput, "</tr>");//Запись закрытия тега таблицы

    while((fgets(line, BUFF_SIZE, FileInput)))//Цикл для полчения строк из файла
    {
        for(counter = 1; counter < columns; ++counter)//Цикл для записи открытия тегов таблицы
            fprintf(FileOutput, "<tr>\n");

        word = strtok(line, ",");
        fprintf(FileOutput, "<td>%s</td>\n", word);//Цикл для записи тегов с содержимым таблицы

        while(word)//Цикл для полчения слов до запятой
        {
            word = strtok(NULL, ",");
            if(word == NULL)
                continue;

            fprintf(FileOutput, "<td>%s</td>\n", word);//Запись тегов для содержимого таблицы
        }
    }
    for(counter = 1; counter < columns; ++counter)//Запись закрыввающих тегов таблицы
        fprintf(FileOutput, "</tr>\n");

    fprintf(FileOutput, "\n</table>\n");//Закрытия тега таблицы
    fprintf(FileOutput, "\n</body>\n</html>\n");//Запись закрывающих тегов для основной части HTML

    fclose(FileInput);//Закрытие потока файла для чтения
    fclose(FileOutput);//Закрытие потока файла для записи
}
