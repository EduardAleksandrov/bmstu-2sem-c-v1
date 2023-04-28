// реализация стека через структуру - работает
#include <stdio.h>
#include <stdlib.h>

#include "7.stackv2.h"

#define SIZE 50

int main(void)
{
    int *stack = (int *) calloc(SIZE, sizeof(int));
    if (stack == NULL) {
        printf("Память не выделена, ошибка");
        exit(1);
    }
    struct stacked stacks;

    int value;
    stacks.stackBase = stack;
    stacks.stackPointer = stack;
    int num;

    do
    {
        printf("Введите значение: ");
        scanf("%d", &value);
        if(value != 0) {
            push(value, &stacks);
        } else {
            num = pop(&stacks);
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

void push(int i, struct stacked *stacks)
{
    stacks->stackPointer++;
    if(stacks->stackPointer == (stacks->stackBase + SIZE)) 
    {
        printf("Stackoverflow \n");
        exit(1);
    }
    *stacks->stackPointer = i;
}

int pop(struct stacked *stacks)
{
    if(stacks->stackPointer == stacks->stackBase)
    {
        printf("Стек пуст \n");
        exit(1);
    }
    stacks->stackPointer--;
    return *(stacks->stackPointer+1);
}