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

void addClientEnd(struct clients **); // инициализация списка
void printClients(struct clients **); // печать списка

void addClient(struct clients **, unsigned long int); //  добавление в середину или конец
void deleteClient(struct clients **, unsigned long int); 
void addClientfFirst(struct clients **); // добавление первым элементом

int main(void)
{
    setlocale(LC_ALL, "");
    struct clients *head = NULL;
    wchar_t simbolOne, simbolTwo;
    for(;;)
    {
        puts("|.1.Для добавления новой структуры или добавления в конец");
        puts("  2.для добавления в середину или конец");
        puts("  3.для добавления в начало");
        puts("  4.для удаления");
        puts("  5.для печати");
        puts("  0.для выхода");
        scanf(" %lc", &simbolOne);
        if(simbolOne == '1')
        {
            for(;;)
            {
                puts("||.Для ввода текущей структуры нажмите любую клавишу. Выход - 0");
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
            puts("После какого id добавить элемент? Выход - 0");
            scanf("%ld", &n);
            if(n == 0) continue;
            addClient(&head, n);
        } else if(simbolOne == '3')
        {
            addClientfFirst(&head);
        } else if(simbolOne == '4')
        {
            unsigned long int n;
            puts("Какой id удалить? Выход - 0");
            scanf("%ld", &n);
            if(n == 0) continue;
            deleteClient(&head, n);
        } else if(simbolOne == '5')
        {   
            printClients(&head);
        } else if(simbolOne == '0')
        {
            break;
        }
    }
    return 0;
}


// инициализация списка
void addClientEnd(struct clients **head)
{
    struct clients *current = *head;
    unsigned long int tmpId = 1;
    if(*head == NULL) // добавление первого элемента
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
        while(current->next != NULL) // поиск последнего элемента в списке
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

// печать списка
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

// добавление клиентов в середину или конец
void addClient(struct clients **head, unsigned long int lastNumber)
{
    struct clients *current = *head;
    unsigned long int tmpId = 1; // новый индекс
    bool check = false; // проверка на существование индекса
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
    while(current->id != lastNumber) // получили номер по списку, за которым будем добавлять
    {
        current = current->next;
    }
     // добавление 
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

// добавление первого клиента
void addClientfFirst(struct clients **head) // добавление первым элементом
{
    struct clients *current = *head;
    unsigned long int tmpId = 1; // новый индекс
    while(current != NULL) // поиск максимального id
    {
        if(current->id > tmpId) tmpId = current->id;
        current = current->next;
    }
    tmpId++;

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
}

// удаление клиентов
void deleteClient(struct clients **head, unsigned long int dellNumber)
{
    struct clients *current = *head;
    bool check = false; // проверка на существование индекса
    unsigned long int lastNumber; // вычисление последнего номера в списке
    while(current != NULL) // поиск максимального id, и проверка на существование индекса, поиск последнего id
    {
        if(current->id == dellNumber) check = true;
        lastNumber = current->id;
        current = current->next;
    }
    if(check == false)
    {
        puts("Такого элемента нет");
        return;
    }

    current = *head; 
    if(dellNumber == current->id) // удаление первого элемента
    {
        *head = current->next;
        free(current);
        return;
    } else if(dellNumber == lastNumber) // удаление последнего элемента
    {
        while(current->next->next != NULL) // поиск предпоследнего
        {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
        return;
    } else {
        while(current->next->id != dellNumber) // удаление по номеру, поиск предыдущего по номеру клиента
        {
            current = current->next;
        }
        struct clients *tmp = current->next->next;
        free(current->next);
        current->next = tmp;
    }
}
