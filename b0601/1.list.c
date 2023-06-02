// работа со связанным списком, + локализация языка
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <wchar.h>
#include <locale.h>

struct clients
{
    unsigned long int id;
    wchar_t name[50];
    unsigned short int age;
    struct clients *next;
};

void addClientEnd(struct clients **);
void printClients(struct clients **);

void addClientMiddle(struct clients **, unsigned long int);
void dellClient(struct clients **, unsigned long int);


int main(void)
{
    setlocale(LC_ALL, "");
    struct clients *head = NULL;
    wchar_t simbolOne, simbolTwo;
    for(;;)
    {
        puts("|.1.Для добавления новой структуры или добавления в конец");
        puts("  2.для добавления в начало, середину или конец");
        puts("  3.для удаления");
        puts("  4.для печати");
        puts("  0.для выхода ноль");
        scanf(" %lc", &simbolOne);
        if(simbolOne == '1')
        {
            for(;;)
            {
                puts("||.Для ввода текущей структуры нажмите любую клавишу или ноль для выхода");
                scanf(" %lc", &simbolTwo);
                if(simbolTwo == '0')
                {
                    break;
                } else {
                    addClientEnd(&head);
                }
            }
        } else if(simbolOne == '2')
        {
            unsigned long int n;
            puts("После какого id добавить элемент или первый id?");
            scanf("%ld", &n);
            addClientMiddle(&head, n);
        } else if(simbolOne == '3')
        {
            unsigned long int n;
            puts("Какой id удалить?");
            scanf("%ld", &n);
            dellClient(&head, n);
        } else if(simbolOne == '4')
        {   
            printClients(&head);
        } else if(simbolOne == '0')
        {
            break;
        }
    }
    return 0;
}

void addClientEnd(struct clients **head)
{
    struct clients *current = *head;
    unsigned long int tmpId = 1;
    if(*head == NULL)
    {   
        current = (struct clients *) malloc(sizeof(struct clients));
        printf("Введите имя: ");
        scanf(" %ls", current->name);
        printf("Введите возраст: ");
        scanf(" %hd", &(current->age));
        puts("Структура добавлена");
        current->id = 1;
        current->next = NULL;
        *head = current; // !чтобы изменять указатель в функции требуется передавать его адрес
    } else {
        while(current->next != NULL)
        {
            current = current->next;
            if(current->id > tmpId) tmpId = current->id;
        }
        current->next = (struct clients*) malloc(sizeof(struct clients));
        current->next->id = ++tmpId;
        printf("Введите имя: ");
        scanf(" %ls", current->next->name);
        printf("Введите возраст: ");
        scanf(" %hd", &(current->next->age));
        puts("Структура добавлена");
        current->next->next = NULL;
    }
}

void printClients(struct clients **head)
{
    struct clients *current = *head;
    if(*head == NULL) puts("Нет данных");
    while(current != NULL)
    {
        printf("id: %ld, name: %ls, age: %hd \n", current->id, current->name, current->age);
        current = current->next;
    }
}

void addClientMiddle(struct clients **head, unsigned long int lastNumber)
{
    struct clients *current = *head;
    unsigned long int tmpId = 1; // индекс
    bool check = false; // проверка на существование
    while(current != NULL) // поиск максимального id, и проверка на существование индекса
    {
        if(current->id > tmpId) tmpId = current->id;
        if(current->id == lastNumber) check = true;
        current = current->next;
    }
    if(check == false)
    {
        puts("Такого элемента нет");
        return;
    }
    tmpId++;
    current = *head;
    while(current->id != lastNumber)
    {
        current = current->next;
    }
    if(current == *head) // добавление первой
    {
        current = NULL;
        current = (struct clients*) malloc(sizeof(struct clients));
        current->id = tmpId;
        printf("Введите имя: ");
        scanf(" %ls", current->name);
        printf("Введите возраст: ");
        scanf(" %hd", &(current->age));
        puts("Структура добавлена");
        current->next = *head;
        *head = current;
    } else { // добавление всех кроме первой
        struct clients *tmp = current->next;
        current->next = NULL;
        current->next = (struct clients*) malloc(sizeof(struct clients));
        current->next->id = tmpId;
        printf("Введите имя: ");
        scanf(" %ls", current->next->name);
        printf("Введите возраст: ");
        scanf(" %hd", &(current->next->age));
        puts("Структура добавлена");
        current->next->next = tmp;
    }
    
}

void dellClient(struct clients **head, unsigned long int dellNumber)
{
    // if(dell)
}
