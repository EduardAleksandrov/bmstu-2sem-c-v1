#include <stdio.h>
#include <math.h>
#include <stdlib.h> //юзаем динамическую память
#include <locale.h> //русскоязычная раскладка вывода файла
#include <wchar.h>
#include <string.h>

#define FILE_PATH_SOURCE "./18.F00.csv"
#define FILE_PATH_GOAL "./18.F0111.csv"


struct File_from_Remedy
{
    //Исполнитель	Группа исполнителя	№ проблемы	Приоритет	Статус	Объект сети
   char performer[150];
   char group[150];
   char number_problem[150];
   char priority[150];
   char status[150];
   char network_object[500];
};

int main(void)
{

    char *locale = setlocale(LC_ALL, ""); //Для вывода кириллицы на консоль Win

    FILE *Remedy = fopen(FILE_PATH_SOURCE, "r");
//________________________________________________________________________________________________
    // Проверка открытия файла
    if (Remedy == NULL)
    {
        printf("File F0 is not open\n");
        exit(1);
    }
    else printf("File F0 is open\n");

//________________________________________________________________________________________________
    // Расчёт кол-ва строк для вычисления динамической памяти (КОДИРОВКА ФАЙЛА ДОЛЖНА БЫТЬ UFT8!!!!)
    char cp;
//    int Numder_of_symbols = 0;
    int Number_of_lines = 0;
    ;

    while ((cp = getc(Remedy)) != EOF)
    {
//        Numder_of_symbols++;

        if (cp == '\n')
        {
            Number_of_lines++;
        }
    }
//    printf("Number of symbols: %d\n", Numder_of_symbols);
    Number_of_lines--;
    printf("Number of lines: %d\n", Number_of_lines);

    fclose(Remedy);
    Remedy = NULL;

//________________________________________________________________________________________________

    // 1. Задаём динамическую память под структуры (!!!Не забудь очистистить её!!!)
    // Задала под размеры одной строки ~ примерно, то есть одной структуры (почему одна строка - одна структура?)

    struct File_from_Remedy *dinam = malloc(Number_of_lines*sizeof (struct File_from_Remedy));
    if (dinam != NULL)
    {
        printf("Dinamic memory is done\n");
    }
    else printf("Dinamic memory is NOT done\n");

//________________________________________________________________________________________________

    // Записываем файл в массив структур

    FILE *fp;
    fp = fopen(FILE_PATH_SOURCE, "r");

    if (fp == NULL)
    {
        printf("File F0 is not open\n");
        exit(1);
    } else {
        printf("File F0 is open\n");
    }

    char buff[1024]; // размер считываемой строки
    int i = 0; // счетчик количества строк
    int row_count = 0; // переменная определяющая первую строку для её пропуска
    int field_count = 0; // счетчик для перебора столбцов
    while(fgets(buff, sizeof(buff), fp)) // перебор строк
    {
        field_count = 0;
        if(row_count < 2) row_count++;
        if(row_count == 1) continue;

        char *field = strtok(buff, ";"); // выбор первого столбца // strtok – разбиение строки на части по указанному разделителю.
        while(field != NULL)                                             // strcpy (куда, откуда) – копирование строк
        {
            if(field_count == 0)
            {
                strcpy((dinam + i)->performer, field); //слева адрес - используем стрелку.
            }

            if(field_count == 1)
            {
                strcpy((dinam + i)->group, field);
            }

            if(field_count == 2)
            {
                strcpy((dinam + i)->number_problem, field);
            }

            if(field_count == 3)
            {
                strcpy((dinam + i)->priority, field);
            }

            if(field_count == 4)
            {
                strcpy((dinam + i)->status, field);
            }

            if(field_count == 5)
            {
                strcpy((dinam + i)->network_object, field);
            }

            field = strtok(NULL, ";"); // выбор последующего столбца
            field_count++;
        }
        i++;
    }
    fclose(fp);
    fp = NULL;
    //print
//    i = 13; //line
//    printf("%s %s %s %s %s %s\n", (dinam + i)->performer, (dinam + i)->group, (dinam + i)->number_problem, (dinam + i)->priority, (dinam + i)->status, (dinam + i)->network_object);

//    free(dinam);
//    dinam = NULL;



    int j;
    struct File_from_Remedy buffer;

    for (i=0; i < Number_of_lines-1; i++)
    {
        for (j = i+1; j < Number_of_lines; j++)
        {
            if (strcmp((dinam + i)->performer, (dinam + j)->performer) > 0)
            {
                buffer = *(dinam+i);
                *(dinam+i) = *(dinam+j);
                *(dinam+j) = buffer;
            }

        }
    }


    FILE *fpw;
            fpw = fopen(FILE_PATH_GOAL, "w");

            if (fpw == NULL)
            {
                printf("File F011 is not open\n");
                exit(1);
            }
            else printf("File F011 is open\n");

            for(int i = 0; i < Number_of_lines; i++)
            {
                if(i == 0) fprintf(fpw,"performer,group,number_problem,priority,status,network_object\n");

                if(i != (Number_of_lines - 1)) fprintf(fpw,"%s %s %s %s %s %s\n", (dinam+i)->performer, dinam[i].group, dinam[i].number_problem, dinam[i].priority, dinam[i].status, dinam[i].network_object);
               if(i == (Number_of_lines - 1)) fprintf(fpw,"%s %s %s %s %s %s", dinam[i].performer, dinam[i].group, dinam[i].number_problem, dinam[i].priority, dinam[i].status, dinam[i].network_object);
//                if(i == (Number_of_lines - 1)) fprintf(fpw,"%s %s %s %s %s %s", dinam[i]->performer, dinam[i]->group, dinam[i]->number_problem, dinam[i]->priority, dinam[i]->status, dinam[i]->network_object);
            }

            fclose(fpw);
            fpw = NULL;

            free(dinam);
            dinam = NULL;


}