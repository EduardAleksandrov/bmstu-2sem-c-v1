#include <stdio.h>
#include <math.h>
#include <stdlib.h> //юзаем динамическую память
#include <locale.h> //русскоязычная раскладка вывода файла

#include <string.h>

#define FILE_PATH_SOURCE "17.F00.csv"

//________________________________________________________________________________________________

struct File_from_Remedy{
    //Исполнитель	Группа исполнителя	№ проблемы	Приоритет	Статус	Объект сети
   char performer[150];
   char group[150];
   char number_problem[150];
   char priority[150];
   char status[150];
   char network_object[500];
};
//________________________________________________________________________________________________

int main(void)
{


//________________________________________________________________________________________________

//    char File0[100];
    char *locale = setlocale(LC_ALL, ""); //Для вывода кириллицы на консоль Win

//    FILE *Remedy;
//    Remedy = fopen("C:\\Users\\nasta\\Downloads\\New\\F0.csv", "r");
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
    // Расчёт кол-ва символов и строк для вычисления динамической памяти (КОДИРОВКА ФАЙЛА ДОЛЖНА БЫТЬ UFT8!!!!)
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
    printf("Number of lines: %d\n", Number_of_lines);

    fclose(Remedy);


//________________________________________________________________________________________________

    // 1. Задаём динамическую память под структуры (!!!Не забудь очистистить её!!!)
    // Задала под размеры одной строки ~ примерно, то есть одной структуры (почему одна строка - одна структура?)

    struct File_from_Remedy *dinam = malloc(Number_of_lines*sizeof (struct File_from_Remedy));
    if (dinam != NULL)
    {
        printf("Dinamic memory is done\n");

        // 2. Закидываем в выделенную динамическую память структуру из файла
//        while (fgets(dinam, sizeof (dinam), Remedy))
//        {
//            printf("%s", dinam);
//        }
    }

    else printf("Dinamic memory is NOT done\n");

//________________________________________________________________________________________________
   // Записываем структуру в файл (зачем нужен перевод в бинарный файл???)

    // FILE *Remedy1 = fopen("D:\\Projects Qt\\test1\\F00.csv", "wb");

    // if (Remedy1 == NULL)
    // {
    //     printf("File F0 is not open\n");
    //     exit(1);
    // }
    // else printf("File F0 is open\n");

    // char *a;
    // int i;
    // int k = Number_of_lines*sizeof (struct File_from_Remedy);
    // a = (char *)dinam; //Адрес в памяти первого байта из блока памяти, которая выделена для структуры
    // for (i=0; i< k; i++)
    // {
    //     putc(*a++, Remedy1);
    // }

    //     fclose(Remedy1);
//________________________________________________________________________________________________
    // Записываем из файла структуры

    //     FILE *Remedy2 = fopen("D:\\Projects Qt\\test1\\F00.csv", "rb");

    //     if (Remedy2 == NULL)
    //     {
    //         printf("File F0 is not open\n");
    //         exit(1);
    //     }
    //     else printf("File F0 is open\n");
    // char *c;
    // char ph;
    // c = (char *)dinam; //Настройка на начало файла
    // while((ph=getc(Remedy2)) != EOF)
    // {
    //     *c=ph;
    //     c++;
    // }

    // printf("Performer %c\nGroup %c\n", dinam->performer, dinam->group);
    // fclose(Remedy2);
    // free(dinam); // Чистим память


// parsing csv

    FILE *fp;
    fp = fopen(FILE_PATH_SOURCE, "r");
    
    if (fp == NULL)
    {
        //printf("fropen failed\n");
        perror("fropen failed ");
        exit(1);
    } else {
        puts("fropen opened");
    }

    char buff[1024]; // размер считываемой строки
    unsigned long int i = 0; // счетчик количества строк
    unsigned short int row_count = 0; // переменная определяющая первую строку для её пропуска
    unsigned short int field_count = 0; // счетчик для перебора столбцов
    while(fgets(buff, sizeof(buff), fp)) // перебор строк
    {
        field_count = 0;
        if(row_count < 2) row_count++;
        if(row_count == 1) continue;

        char *field = strtok(buff, ";"); // выбор первого столбца
        while(field)
        {
            if(field_count == 0) strcpy((dinam + i)->performer, field); // т.к. мы обращаемся к указателю через индексацию массива, то точка, а не стрелка
            if(field_count == 1) strcpy((dinam + i)->group, field);
            if(field_count == 2) strcpy((dinam + i)->number_problem, field);
            if(field_count == 3) strcpy((dinam + i)->priority, field);
            if(field_count == 4) strcpy((dinam + i)->status, field);
            if(field_count == 5) strcpy((dinam + i)->network_object, field);

            field = strtok(NULL, ";"); // выбор последующего столбца
            field_count++;
        }
        i++;
    }
    fclose(fp);
    fp = NULL;
    //print
    i = 0; //line
    printf("%s %s %s %s %s %s\n", (dinam + i)->performer, (dinam + i)->group, (dinam + i)->number_problem, (dinam + i)->priority, (dinam + i)->status, (dinam + i)->network_object);

    free(dinam);
    dinam = NULL;


}