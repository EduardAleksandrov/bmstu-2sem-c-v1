#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
 

int callbackNumOfRows(void*, int, char**, char**);

int main() {
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
    int numOfRows; //Вычисляем количество строк
    result = sqlite3_exec(db, sqlNumOfRows, callbackNumOfRows, &numOfRows, &err_msg);
    if (result != SQLITE_OK )
    {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
    //printf("%d \n", numOfRows);
    // закрываем подключение
    sqlite3_close(db);
}

int callbackNumOfRows(void *notUsed, int colCount, char **columns, char **colNames)
{
    *((int *)notUsed) = strtol(columns[0], NULL, 10);
    return 0;
}