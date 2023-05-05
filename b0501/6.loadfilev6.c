/*
    Task: Считывает csv файл, сортирует по выбранному столбцу, сохраняет в другой csv файл.
    Загрузка построчно (массив в динамической памяти)(выведение сортировки в функцию)(вначале ввод)
    Загрузка данных либо из базы данных либо из файла - работает
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define FILE_PATH_SOURCE "./testv1.csv"
#define FILE_PATH_TARGET "./wtest.csv"
#define SIZEOFBUFF 1024

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
void xchange(struct person *, long int, long int, struct person *);

// подсчет строк в базе данных
int callbackNumOfRows(void*, int, char**, char**);

// получение данных из базы данных
int callbackData(void*, int, char**, char**);
long int iii = 0; // счетчик строк для выборки в структуру из базы данных


int main(int argc, char *argv[])
{
//Выбор источника данных
    int soureOfData = 0;
    printf("Нажмите 1 для выбора базы данных, нажмите 2 для файла, нажмите ноль для выхода \n");
    for(;;)
    {
        scanf("%d", &soureOfData);
        if(soureOfData >=0 && soureOfData <= 2) break;
        if(soureOfData < 0 || soureOfData > 2) printf("Пункт не выбран, выберите пункт, или ноль для выхода \n");
    }
        // Выход, если выбран ноль
    if(soureOfData == 0) exit(0);

//Выбор поля для сортировки
    int cases= 0;
    printf("Введите цифру для сортировки поля \n");
    printf("1 - id, 2 - name, 3 - age, 4 - address, 5 - zipcode, 0 - выход\n");
    for(;;)
    {
        scanf("%d", &cases);
        if(cases >= 0 && cases <= 5) break;
        if(cases < 1 || cases > 5) printf("Пункт не выбран, выберите пункт, или ноль для выхода \n");
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
    long int sumOfRows; //количество строк
    // из базы
    if(soureOfData == 1)
    {
        sqlite3 *db;    // указатель на базу данных
        // открываем подключение к базе данных
        int result  = sqlite3_open("test.db", &db);
        // если подключение успешно установлено
        if(result == SQLITE_OK) 
        {
            printf("Connection with database established\n");
        }
        else
        {
            // выводим сообщение об ошибке
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }
        
        char *err_msg = 0;
        char *sqlNumOfRows = "SELECT Count(*) as rowsnum FROM persons";
        result = sqlite3_exec(db, sqlNumOfRows, callbackNumOfRows, &sumOfRows, &err_msg);
        if (result != SQLITE_OK )
        {
            printf("SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(1);
        }
        //printf("%ld \n", sumOfRows);
        // закрываем подключение
        sqlite3_close(db);
    }

    // из файла
    if(soureOfData == 2)
    {
        sumOfRows = getFileLineSize(FILE_PATH_SOURCE);
        if(sumOfRows == -1) 
        {
            printf("Файл для подсчета строк не открылся");
            exit(1);
        }
    }
    
    

// создание структур
    struct person *persons = (struct person *) malloc(sizeof(struct person)*sumOfRows);
    if (persons == NULL) {
        printf("Память не выделена, ошибка");
        exit(1);
    }

// считывание данных в массив структур
    // считывание из базы
    if(soureOfData == 1)
    {
        sqlite3 *db;    // указатель на базу данных
        // открываем подключение к базе данных
        int getData  = sqlite3_open("test.db", &db);
        // если подключение успешно установлено
        if(getData == SQLITE_OK) 
        {
            printf("Connection with database established\n");
        }
        else
        {
            // выводим сообщение об ошибке
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }
        
        char *err_msg = 0;
        char *sqlData = "SELECT * FROM persons";
        getData = sqlite3_exec(db, sqlData, callbackData, persons, &err_msg);
        if (getData != SQLITE_OK )
        {
            printf("SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(1);
        }
        // закрываем подключение
        sqlite3_close(db);
    }

    // считывание из файла
    if(soureOfData == 2)
    {
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

        char buff[SIZEOFBUFF];
        int i = 0;
        int row_count = 0;
        int field_count = 0;
        while(fgets(buff, sizeof(buff), fp))
        {
            field_count = 0;
            row_count++;
            if(row_count == 1) continue;

            char *field = strtok(buff, ",");
            while(field)
            {
                if(field_count == 0) persons[i].id = strtol(field, NULL, 10); // т.к. мы обращаемся к указателю через индексацию массива, то точка, а не стрелка
                if(field_count == 1) strcpy(persons[i].name, field);
                if(field_count == 2) persons[i].age = strtol(field, NULL, 10);
                if(field_count == 3) strcpy(persons[i].address, field);
                if(field_count == 4) persons[i].zipcode = strtol(field, NULL, 10);

                field = strtok(NULL, ",");
                field_count++;
            }
            i++;
        }
        fclose(fp);
        fp = NULL;
    }



//сортировка
    struct person personVar; // промежуточная структура
    for(long int i = 0; i < sumOfRows-1; i++)
    {
        for(long int j = i + 1; j < sumOfRows; j++)
        {
            if((persons[i].id > persons[j].id) && cases == 1)
            {
                xchange(persons, i, j, &personVar);
            }
            if((strcmp(persons[i].name, persons[j].name) > 0) && cases == 2)
            {
                xchange(persons, i, j, &personVar);
            }
            if((persons[i].age > persons[j].age) && cases == 3)
            {
                xchange(persons, i, j, &personVar);
            }
            if((strcmp(persons[i].address, persons[j].address) > 0) && cases == 4)
            {
                xchange(persons, i, j, &personVar);
            }
            if((persons[i].zipcode > persons[j].zipcode) && cases == 5)
            {
                xchange(persons, i, j, &personVar);
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

// очистка
    free(persons);
    persons = NULL;

// завершение
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

void xchange(struct person *persons, long int i, long int j, struct person *personVar)
{
    *personVar = persons[i];
    persons[i] = persons[j];
    persons[j] = *personVar;
}

int callbackNumOfRows(void *sumOfRows, int colCount, char **columns, char **colNames)
{
    *((long int *)sumOfRows) = strtol(columns[0], NULL, 10);
    return 0;
}

int callbackData(void *persons, int colCount, char **columns, char **colNames)
{
    struct person *personsInside = (struct person *)persons;

    for (int j = 0; j < colCount; j++)
    {
        if(j == 0)
        {
            personsInside[iii].id = strtol(columns[j], NULL, 10);
        }
        if(j == 1)
        {
            strcpy(personsInside[iii].name, columns[j]);
        }
        if(j == 2)
        {
            personsInside[iii].age = strtol(columns[j], NULL, 10);
        }
        if(j == 3)
        {
            strcpy(personsInside[iii].address, columns[j]);
        }
        if(j == 4)
        {
            personsInside[iii].zipcode = strtol(columns[j], NULL, 10);
        }
    }
    iii++;
    return 0;
}