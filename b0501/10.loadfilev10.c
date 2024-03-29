/*
    Task: Считывает csv файл, сортирует по выбранному столбцу, сохраняет в другой csv файл.
    Загрузка построчно (массив в динамической памяти)(выведение сортировки в функцию)(вначале ввод)
    Загрузка данных либо из базы данных либо из файла
    Связанный список (нахождение среднего возраста)
    Дополнены исправления от преподавателя(структура через массив...)
    Расширен диапазон до unsign long int
    Cортировки !!!указателей на структуру - работает

    Добавлены типы
    Добавлена база данных
    Добавлена сортировка !указателей

    Добавлен связанный список
    Структура через динамическую память
    Работает под нагрузкой, где массив переменной длины не справляется
    
    заменили массивы на указатели в структуре для сохранения памяти - работает
    работает для русских символов - выделяется char два байта
    Версия 2.1 - работает
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#define FILE_PATH_SOURCE "../10.generator.csv"
#define FILE_PATH_TARGET "./wtest.csv"
#define SIZEOFBUFF 1024 // размер строки для выборки fgets из файла
#define DATABASE_PATH_SOURCE "./test.db"
#define NUMOFCASES 5 // Количество столбцов для сортировки
#define NUMSOURCEOFDATA 2 // количество источников данных

struct person
{
    unsigned long int id;
    char *name;
    unsigned short int age;
    char *address;
    unsigned long int zipcode;
    struct person *link;
    // struct person *backlink;
};

// сколько строк в файле
unsigned long int getFileLineSize(char*);

// сортировка структур
void xchange(struct person**, unsigned long int, unsigned long int);

// подсчет строк в базе данных (функция обратного вызова)
int callbackNumOfRows(void*, int, char**, char**);

// получение данных из базы данных (функция обратного вызова)
int callbackData(void*, int, char**, char**);

// расчет длины строки name, address
unsigned short int lenChar(char*);

// копирование строки
void copyStr(char*, char*);




int main(int argc, char *argv[])
{
//Выбор источника данных
    short int sourceOfData;
    puts("Нажмите 1 для выбора базы данных, нажмите 2 для файла, нажмите ноль для выхода");
    for(;;)
    {
        scanf("%hd", &sourceOfData);
        if(sourceOfData >=0 && sourceOfData <= NUMSOURCEOFDATA) break;
        if(sourceOfData < 0 || sourceOfData > NUMSOURCEOFDATA) puts("Пункт не выбран, выберите пункт, или ноль для выхода");
    }
    // Выход, если выбран ноль
    if(sourceOfData == 0) exit(0);

//Выбор поля для сортировки
    short int cases;
    puts("Введите цифру для сортировки поля");
    puts("1 - id, 2 - name, 3 - age, 4 - address, 5 - zipcode, 0 - выход");
    for(;;)
    {
        scanf("%hd", &cases);
        if(cases >= 0 && cases <= NUMOFCASES) break;
        if(cases < 1 || cases > NUMOFCASES) puts("Пункт не выбран, выберите пункт, или ноль для выхода");
    }

    switch(cases)
    {
        case 1: 
            puts("Выбран id");
            break;
        case 2: 
            puts("Выбран name");
            break;
        case 3:
            puts("Выбран age");
            break;
        case 4: 
            puts("Выбран address");
            break;
        case 5: 
            puts("Выбран zipcode");
            break;
        default: 
            puts("Пункт не выбран");
            break;
    }
    // Выход, если выбран ноль
    if(cases == 0) exit(0);

// запуск расчета времени работы программы
    clock_t begin = clock();

// подсчет строк
    unsigned long int sumOfRows; //количество строк
    // из базы
    if(sourceOfData == 1)
    {
        sqlite3 *db;    // указатель на базу данных
        // открываем подключение к базе данных, открываем поток, заполняем структуру по работе с файлом
        int result  = sqlite3_open(DATABASE_PATH_SOURCE, &db);
        // если подключение успешно установлено
        if(result == SQLITE_OK) 
        {
            puts("Connection with database established");
        }
        else
        {
            // выводим сообщение об ошибке
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }
        
        char *err_msg = 0; // указатель на сообщение об ошибки
        char *sqlNumOfRows = "SELECT Count(*) as rowsnum FROM persons"; // команда запроса в базу данных
        // Основная функция запроса
        result = sqlite3_exec(db, sqlNumOfRows, callbackNumOfRows, &sumOfRows, &err_msg);  //sumOfRows передается в функцию обратного вызова в качестве параметра
        if (result != SQLITE_OK)
        {
            printf("SQL error: %s\n", err_msg);
            sqlite3_free(err_msg); // очистка указателя на строку с ошибкой
            sqlite3_close(db);
            exit(1);
        }
        // закрываем подключение
        sqlite3_close(db);
        db = NULL;
    }

    // из файла
    if(sourceOfData == 2)
    {
        sumOfRows = getFileLineSize(FILE_PATH_SOURCE);
    }

    // выход если ноль строк
    if(sumOfRows == 0) 
    {
        puts("Внимание: ноль строк в файле/базе");
        exit(0);
    }


// создание массива структур
    // struct person persons[sumOfRows];
    struct person *persons = (struct person *) malloc(sizeof(struct person) * sumOfRows);
    if (persons == NULL) {
        puts("Память не выделена, ошибка");
        exit(1);
    }

// создание указателей на массив структур для сортировки
    // struct person *personsForSort[sumOfRows];
    struct person **personsForSort = (struct person **) malloc(sizeof(struct person *) * sumOfRows);
    if (personsForSort == NULL) {
        puts("Память не выделена, ошибка");
        exit(1);
    }

    for(unsigned long int i = 0; i < sumOfRows; i++)
    {
        *(personsForSort + i) = (persons + i);
    }



// считывание данных в массив структур
    // считывание из базы
    if(sourceOfData == 1)
    {
        sqlite3 *db;    // указатель на базу данных
        // открываем подключение к базе данных
        int getData  = sqlite3_open(DATABASE_PATH_SOURCE, &db);
        // если подключение успешно установлено
        if(getData == SQLITE_OK) 
        {
            puts("Connection with database established");
        }
        else
        {
            // выводим сообщение об ошибке
            fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }
        
        char *err_msg = 0;  // указатель на сообщение об ошибки
        char *sqlData = "SELECT * FROM persons";  // команда запроса в базу данных
        // Основная функция запроса
        getData = sqlite3_exec(db, sqlData, callbackData, persons, &err_msg); // структура persons передается в функцию обратного вызова в качестве параметра
        if (getData != SQLITE_OK)
        {
            printf("SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(1);
        }
        // закрываем подключение
        sqlite3_close(db);
        db = NULL;
    }

    // считывание из файла
    if(sourceOfData == 2)
    {
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

        char buff[SIZEOFBUFF]; // размер считываемой строки
        unsigned long int i = 0; // счетчик количества строк
        unsigned short int row_count = 0; // переменная определяющая первую строку для её пропуска
        unsigned short int field_count = 0; // счетчик для перебора столбцов
        while(fgets(buff, sizeof(buff), fp)) // перебор строк
        {
            field_count = 0;
            if(row_count < 2) row_count++;
            if(row_count == 1) continue;
            char *field = strtok(buff, ","); // выбор первого столбца
            while(field)
            {
                if(field_count == 0) (persons + i)->id = strtol(field, NULL, 10); // т.к. мы обращаемся к указателю через индексацию массива, то точка, а не стрелка
                if(field_count == 1) 
                {
                    (persons + i)->name = (char *) malloc(sizeof(char) * lenChar(field));
                    copyStr((persons + i)->name, field);
                }
                if(field_count == 2) (persons + i)->age = strtol(field, NULL, 10);
                if(field_count == 3)
                {
                    (persons + i)->address = (char *) malloc(sizeof(char) * lenChar(field));
                    copyStr((persons + i)->address, field);
                }
                if(field_count == 4) (persons + i)->zipcode = strtol(field, NULL, 10);
                
                field = strtok(NULL, ","); // выбор последующего столбца
                field_count++;
            }
            i++;
        }
        fclose(fp);
        fp = NULL;
    }

// Список - start
// Связывание структур для организации списка
    for(unsigned long int i = 0; i < sumOfRows - 1; i++)
    {
        (persons + i)->link = (persons + i + 1);
    }
    (persons + sumOfRows - 1)->link = NULL; // для последней структуры устанавливаем указатель NULL
    
    // for(unsigned long int i = sumOfRows-1; i > 0 ; i--) // двусвязанный список
    // {
    //     persons[i].backlink = &persons[i-1];
    // }
    // persons[0].backlink = NULL;

// поиск среднего возраста через связанный список в любом месте программы
    struct person *personsPointer = persons;
    unsigned long long int sum = 0;

    while(personsPointer != NULL)
    {
        sum += personsPointer->age;
        personsPointer = personsPointer->link;
    }
    float middleAge = sum / (double)sumOfRows;
    // middleAge =378/12.0;
    printf("Средний возраст(лет): %.2f \n", middleAge);

//добавление еще одной структуры и поиск среднего
    struct person personsForLink = {40, "Kate", 80, "Bakuninskaya", 112460};
    (persons + 1)->link = &personsForLink;
    personsForLink.link = (persons + 2);
    
    // вторая
    struct person *personForLinkPointer;
    personForLinkPointer = (struct person*) malloc(sizeof(struct person));
    personForLinkPointer->id = 41;

    personForLinkPointer->name = (char *) malloc(sizeof(char) * lenChar("Ellen"));
    copyStr(personForLinkPointer->name, "Ellen");

    personForLinkPointer->age = 50;

    personForLinkPointer->address = (char *) malloc(sizeof(char) * lenChar("Volhovo"));
    copyStr(personForLinkPointer->address, "Volhovo");

    personForLinkPointer->zipcode = 634874;
    (persons + 5)->link = personForLinkPointer;
    personForLinkPointer->link = (persons + 6);

    //третья
    (persons + sumOfRows - 1)->link = (struct person*) malloc(sizeof(struct person));
    (persons + sumOfRows - 1)->link->id = 42;

    (persons + sumOfRows - 1)->link->name = (char *) malloc(sizeof(char) * lenChar("Tomas"));
    copyStr((persons + sumOfRows - 1)->link->name, "Tomas");

    (persons + sumOfRows - 1)->link->age = 60;
    
    (persons + sumOfRows - 1)->link->address = (char *) malloc(sizeof(char) * lenChar("Bocharovo"));
    copyStr((persons + sumOfRows - 1)->link->address, "Bocharovo");

    (persons + sumOfRows - 1)->link->zipcode = 464732;
    (persons + sumOfRows - 1)->link->link = NULL;

    //расчет среднего возраста
    personsPointer = persons;
    sum = 0;
    while(personsPointer != NULL)
    {
        sum += personsPointer->age;
        personsPointer = personsPointer->link;
    }
    middleAge = sum / ((double)sumOfRows + 3);
    printf("Средний возраст(лет): %.2f \n", middleAge);

    // очистка
    free(personForLinkPointer->name);
    personForLinkPointer->name = NULL;
    free(personForLinkPointer->address);
    personForLinkPointer->address = NULL;
    free(personForLinkPointer);
    personForLinkPointer = NULL;

    free((persons + sumOfRows - 1)->link->name);
    (persons + sumOfRows - 1)->link->name = NULL;
    free((persons + sumOfRows - 1)->link->address);
    (persons + sumOfRows - 1)->link->address = NULL;
    free((persons + sumOfRows - 1)->link);
    (persons + sumOfRows - 1)->link = NULL;
// Список - end


//сортировка
    for(unsigned long int i = 0; i < sumOfRows-1; i++)
    {
        for(unsigned long int j = i + 1; j < sumOfRows; j++)
        {
            if(((*(personsForSort + i))->id > (*(personsForSort + j))->id) && cases == 1)
            {
                xchange(personsForSort, i, j);
                // struct person *personVar;
                // personVar = *(personsForSort + i);
                // *(personsForSort + i) = *(personsForSort + j);
                // *(personsForSort + j) = personVar;  
            }
            if((strcmp((*(personsForSort + i))->name, (*(personsForSort+j))->name) > 0) && cases == 2)
            {
                xchange(personsForSort, i, j);
            }
            if(((*(personsForSort + i))->age > (*(personsForSort + j))->age) && cases == 3)
            {
                xchange(personsForSort, i, j);
            }
            if((strcmp((*(personsForSort + i))->address, (*(personsForSort + j))->address) > 0) && cases == 4)
            {
                xchange(personsForSort, i, j);
            }
            if(((*(personsForSort + i))->zipcode > (*(personsForSort + j))->zipcode) && cases == 5)
            {
                xchange(personsForSort, i, j);
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
        puts("fwopen opened");
    }

    for(unsigned long int i = 0; i < sumOfRows; i++)
    {   
        if(i == 0) fprintf(fpw,"id,name,age,address,zipcode\n");

        if(i != (sumOfRows - 1)) fprintf(fpw,"%lu,%s,%hu,%s,%lu\n", (*(personsForSort + i))->id, (*(personsForSort + i))->name, (*(personsForSort + i))->age, (*(personsForSort + i))->address, (*(personsForSort + i))->zipcode);
        if(i == (sumOfRows - 1)) fprintf(fpw,"%lu,%s,%hu,%s,%lu", (*(personsForSort + i))->id, (*(personsForSort + i))->name, (*(personsForSort + i))->age, (*(personsForSort + i))->address, (*(personsForSort + i))->zipcode);
    }

    fclose(fpw);
    fpw = NULL;

// очистка
    free(personsForSort);
    personsForSort = NULL;

    for(unsigned long int i = 0; i < sumOfRows; i++)
    {
        free((persons + i)->name);
        free((persons + i)->address);
    }

    free(persons);
    persons = NULL;


//время работы программы
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds \n", time_spent);

// завершение
    return 0;
}





// Подсчет количества строк в файле
unsigned long int getFileLineSize(char *file_name)
{
    unsigned long int sumOfRows = 0; // количество строк
    char ch; // перебор символов для поиска конца строки
	
    FILE *fd = fopen(file_name, "r");
	
    if(fd == NULL)
    {
        puts("Файл для подсчета строк не открылся");
        exit(1);
    } else {
        puts("frLineOpen opened");
        while((ch = getc(fd)) != EOF)
        {
            if (ch == '\n') sumOfRows++;
        }
        fclose(fd);
        fd = NULL;
    }
    return sumOfRows;
}

// Повторяющийся код сортировки указателей
void xchange(struct person **personsForSort, unsigned long int i, unsigned long int j)
{
    struct person *personVar;
    personVar = *(personsForSort + i);
    *(personsForSort + i) = *(personsForSort + j);
    *(personsForSort + j) = personVar;
}

// Вывод количества строк в базе
int callbackNumOfRows(void *sumOfRows, int colCount, char **columns, char **colNames)
{
    *((unsigned long int *)sumOfRows) = strtol(columns[0], NULL, 10);
    return 0;
}

// Получение данных из базы в структуру, построчно. Функция запускается для каждой строки.
int callbackData(void *persons, int colCount, char **columns, char **colNames)
{
    struct person *personsInside = (struct person *) persons; // ссылка на структуру persons, нужна для преобразования void в struct
    static unsigned long int rowCount = 0; // счетчик строк для выборки в структуру из базы данных
    for (int j = 0; j < colCount; j++)
    {
        if(j == 0)
        {
            (personsInside + rowCount)->id = strtol(*(columns + j), NULL, 10);
        }
        if(j == 1)
        {
            (personsInside + rowCount)->name = (char *) malloc(sizeof(char) * lenChar(*(columns + j)));
            copyStr((personsInside + rowCount)->name, *(columns + j));
        }
        if(j == 2)
        {
            (personsInside + rowCount)->age = strtol(*(columns + j), NULL, 10);
        }
        if(j == 3)
        {
            (personsInside + rowCount)->address = (char *) malloc(sizeof(char) * lenChar(*(columns + j)));
            copyStr((personsInside + rowCount)->address, *(columns + j));
        }
        if(j == 4)
        {
            (personsInside + rowCount)->zipcode = strtol(*(columns + j), NULL, 10);
        }
    }
    rowCount++;
    return 0;
}

// расчет длины строки name, address
unsigned short int lenChar(char *from)
{
    int i = 0;
    while(*(from + i) != '\0')
    {
        i++;
    }
    return i + 1;
}

// копирование строки
void copyStr(char *to, char *from)
{
    int i = 0;
    while((*(to + i) = *(from + i)) != '\0')
    {
        i++;
    }
}

