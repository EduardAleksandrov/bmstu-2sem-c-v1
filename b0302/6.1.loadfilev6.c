/*
    Task: Считывает csv файл, сортирует по выбранному столбцу, сохраняет в другой csv файл.
    Загрузка построчно (массив в динамической памяти)(выведение сортировки в функцию)(вначале ввод)
    Дополнены исправления от преподавателя (структура через массив...) - работает
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PATH_SOURCE "./testv1.csv"
#define FILE_PATH_TARGET "./wtest.csv"
#define SIZEOFBUFF 1024 // размер строки для выборки fgets из файла
#define NUMOFCASES 5 // Количество столбцов для сортировки

struct person
{
    int id;
    char name[50];
    int age;
    char address[50];
    long int zipcode;
};

// сколько строк в файле
long int getFileLineSize(char*);

// сортировка структур
void xchange(struct person *, long int, long int);



int main(int argc, char *argv[])
{
//Выбор поля для сортировки
    int cases;
    printf("Введите цифру для сортировки поля \n");
    printf("1 - id, 2 - name, 3 - age, 4 - address, 5 - zipcode, 0 - выход \n");
    for(;;)
    {
        scanf("%d", &cases);
        if(cases >= 0 && cases <= NUMOFCASES) break;
        if(cases < 1 || cases > NUMOFCASES) printf("Пункт не выбран, выберите пункт, или ноль для выхода \n");
    }

    switch(cases)
    {
        case 1: 
            printf("Выбран id \n");
            break;
        case 2: 
            printf("Выбран name \n");
            break;
        case 3:
            printf("Выбран age \n");
            break;
        case 4: 
            printf("Выбран address \n");
            break;
        case 5: 
            printf("Выбран zipcode \n");
            break;
        default: 
            printf("Пункт не выбран \n");
            break;
    }
// Выход, если выбран ноль
    if(cases == 0) exit(0);
    
    
    
// подсчет строк
    long int sumOfRows = getFileLineSize(FILE_PATH_SOURCE);
    if(sumOfRows == -1) 
    {
        printf("Файл для подсчета строк не открылся");
        exit(1);
    }

// создание структур
    struct person persons[sumOfRows];

// считывание данных из файла в массив структур
    FILE *fp;
    fp = fopen(FILE_PATH_SOURCE, "r");
    
    if (fp == NULL)
    {
        //printf("fropen failed\n");
        perror("fropen failed ");
        exit(1);
    } else {
        printf("fropen opened\n");
    }

    char buff[SIZEOFBUFF]; // размер считываемой строки
    int i = 0; // счетчик количества строк
    int row_count = 0; // переменная определяющая первую строку для её пропуска
    int field_count = 0; // счетчик для перебора столбцов
    while(fgets(buff, sizeof(buff), fp)) // перебор строк
    {
        field_count = 0;
        row_count++;
        if(row_count == 1) continue;

        char *field = strtok(buff, ","); // выбор первого столбца
        while(field)
        {
            if(field_count == 0) persons[i].id = strtol(field, NULL, 10); // т.к. мы обращаемся к указателю через индексацию массива, то точка, а не стрелка
            if(field_count == 1) strcpy(persons[i].name, field);
            if(field_count == 2) persons[i].age = strtol(field, NULL, 10);
            if(field_count == 3) strcpy(persons[i].address, field);
            if(field_count == 4) persons[i].zipcode = strtol(field, NULL, 10);

            field = strtok(NULL, ","); // выбор последующего столбца
            field_count++;
        }
        i++;
    }
    fclose(fp);
    fp = NULL;
    

//сортировка линейная
    for(long int i = 0; i < sumOfRows-1; i++)
    {
        for(long int j = i + 1; j < sumOfRows; j++)
        {
            if((persons[i].id > persons[j].id) && cases == 1)
            {
                xchange(persons, i, j);
            }
            if((strcmp(persons[i].name, persons[j].name) > 0) && cases == 2)
            {
                xchange(persons, i, j);
            }
            if((persons[i].age > persons[j].age) && cases == 3)
            {
                xchange(persons, i, j);
            }
            if((strcmp(persons[i].address, persons[j].address) > 0) && cases == 4)
            {
                xchange(persons, i, j);
            }
            if((persons[i].zipcode > persons[j].zipcode) && cases == 5)
            {
                xchange(persons, i, j);
            }
        }
    }

// запись в файл
    FILE *fpw;
    fpw = fopen(FILE_PATH_TARGET, "w");
    
    if (fpw == NULL)
    {
        //printf("fwopen failed\n");
        perror("fwopen failed ");
        exit(1);
    } else {
        printf("fwopen opened\n");
    }

    for(long int i = 0; i < sumOfRows; i++)
    {   
        if(i == 0) fprintf(fpw,"id,name,age,address,zipcode\n");

        if(i != (sumOfRows - 1)) fprintf(fpw,"%d,%s,%d,%s,%ld\n", persons[i].id, persons[i].name, persons[i].age, persons[i].address, persons[i].zipcode);
        if(i == (sumOfRows - 1)) fprintf(fpw,"%d,%s,%d,%s,%ld", persons[i].id, persons[i].name, persons[i].age, persons[i].address, persons[i].zipcode);
    }

    fclose(fpw);
    fpw = NULL;

// завершение работы
    return 0;
}

long int getFileLineSize(char* file_name)
{
    long int sumOfRows = 0;
    char ch;
	
    FILE* fd = fopen(file_name, "r");
	
    if(fd == NULL)
    {
        printf("frLineOpen failed\n");
        sumOfRows = -1;
    } else {
        printf("frLineOpen opened\n");
        while((ch = getc(fd)) != EOF)
        {
            if (ch == '\n') sumOfRows++;
        }
        fclose(fd);
        fd = NULL;
    }
    return sumOfRows;
}

void xchange(struct person *persons, long int i, long int j)
{
    struct person personVar;
    personVar = persons[i];
    persons[i] = persons[j];
    persons[j] = personVar;
}