#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct clients
{
    unsigned long int id;
    char name[50];
    unsigned short int age;
    struct clients *next;
};

void addClientEnd(struct clients **);
void printClients(struct clients **);

void addClientMiddle(struct clients **, unsigned long int);
void dellClient(struct clients **, unsigned long int);


int main(void)
{
    struct clients *head = NULL;
    char simbolOne, simbolTwo;
    for(;;)
    {
        puts("|.Для добавления новой структуры - 1, для добавления в середину - 2, для удаления - 3, для печати - 4, для выхода ноль - 0");
        scanf(" %c", &simbolOne);
        if(simbolOne == '1')
        {
            for(;;)
            {
                puts("||.Для ввода текущей структуры нажмите любую клавишу или ноль для выхода");
                scanf(" %c", &simbolTwo);
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
            puts("После какого id добавить элемент?");
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
        scanf(" %s", current->name);
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
        scanf(" %s", current->next->name);
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
        printf("id: %ld, name: %s, age: %hd \n", current->id, current->name, current->age);
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
    struct clients *tmp = current->next;
    current->next = NULL;
    current->next = (struct clients*) malloc(sizeof(struct clients));
    current->next->id = tmpId;
    printf("Введите имя: ");
    scanf(" %s", current->next->name);
    printf("Введите возраст: ");
    scanf(" %hd", &(current->next->age));
    puts("Структура добавлена");
    current->next->next = tmp;
}

void dellClient(struct clients **head, unsigned long int dellNumber)
{
    // if(dell)
}
