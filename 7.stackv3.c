// реализация стека - работает
#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

void push(int, int*, int**);
int pop(int*, int**);

// int *stackPointer;

int main(void)
{
    int *stackBase;
    int *stackPointer;
    // int stack[SIZE];

    int *stack = (int *) calloc(SIZE, sizeof(int));
    if (stack == NULL) {
        printf("Память не выделена, ошибка");
        exit(1);
    }

    int value;
    stackBase = stack;
    stackPointer = stack;
    int num;

    do
    {
        printf("Введите значение: ");
        scanf("%d", &value);
        if(value != 0) {
            // stackPointer++; // !!! Указатель в функцию передается по значению, в функции его инкрементировать не правильно. Либо он должен быть объявлен глобальной переменной.
            push(value, stackBase, &stackPointer); //! Чтобы изменять указатель в функции нужно передавать его адрес
            // printf("%p \n", stackPointer);
        } else {
            // stackPointer--;
            num = pop(stackBase, &stackPointer);
            printf("Значение на вершине равно %d, уменьшино на единицу \n", num);
            for(int j = 0; j < SIZE; j++)
            {
                if(stack[j] != 0) printf("%d ", stack[j]);
            }
            printf("\n");
        }

    } while (value != -1);

    free(stack);
    stack = NULL;

    return 0;
}

void push(int i, int *stackBase, int **stackPointer)
{
    if(*stackPointer == (stackBase + SIZE)) 
    {
        printf("Stackoverflow \n");
        exit(1);
    }
    **stackPointer = i;
    (*stackPointer)++;
    // printf("%p \n", stackPointer);
    
}
int pop(int *stackBase, int **stackPointer)
{
    if((*stackPointer) == stackBase)
    {
        printf("Стек пуст \n");
        exit(1);
    }
    (*stackPointer)--;
    return **stackPointer;
}