#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Задание:
Написать API:
1)Добавление в коненц
2)Вывод на печать
*/

//базовая структура 
struct books 
{
    int id;
    char title[30];
    float price;
    struct books *next;
    struct books *previous;
}; 
typedef  struct books books;

//функции
int add_book_end(books ** head); //добавление в конец
void print_books(books ** head); //вывод книг на печать

//main
int main()
{
    books *head; 
    printf("1");
    books one = {1, "new", 20.9, NULL, NULL};
    head = &one;

    add_book_end(&head);
    add_book_end(&head);

    // books *g = head->next;
    
    printf("%s \n", head->title);
    printf("%f \n", head->price);
    printf("%s \n", (head->previous)->title);
    printf("%f \n", (head->previous)->price);
    
    // printf("%s", g->title);
    // printf("%f", g->price);
    
    return 0;
}



int add_book_end(books ** head)
{
    int id_cycle = 1; //id альбома 
    float price_book;
    char title_book[30];
    books *curs = *head;
    
    while (curs->next != NULL) // находим конец списка 
    {
        curs = curs->next;
        id_cycle += 1;
    }
    
    curs->next = (books*)malloc(sizeof(books));
        if (curs->next ==NULL) //проверка выделения памяти
        {
            return 1;
        }
    
    printf("Write title for book: ");
    scanf("%s", title_book);
    printf("Write price for book: ");
    scanf("%f", &price_book);

    curs->next->id=id_cycle;    
    curs->next->price = price_book;
    strcpy(curs->next->title,title_book); //функция добавления массива в массив
    curs->next->next = NULL;
    curs->next->previous = curs;

    (*head) = curs->next; 
}

void print_books(books **head)
{
    printf("go");
    while ((*head)->next != NULL)
    {
        *head = (*head)->next;
        printf("id = %d, title = %s, price = %f \n", (*head)->id, (*head)->title, (*head)->price);
    }
}

