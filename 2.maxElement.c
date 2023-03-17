#include <stdio.h>

int max(short int*, short int);
int min(short int*, short int);


int main(void)
{
// input
    unsigned short int item;
    printf("Введите количество элементов в массиве: ");
    scanf("%hd", &item);
    short int elements[item]; // массив переменной длины, в с++ нет
    short int arrLength = sizeof(elements)/sizeof(*elements); // разыменование
    printf("Введите элементы: \n");
    for (int i = 0; i < arrLength; i++) 
    {
        scanf("%hu", &elements[i]);
    }

    printf("max = %d \n", max(elements, arrLength));
    printf("min = %d \n", min(elements, arrLength));
    
    return 0;
}

int max(short int *y, short int arrLength)
{
    int z = 0;
    for(int i = 0; i < arrLength; i++)
    {
        if(z<*(y+i)) z=*(y+i);
    }
    return z;
}

int min(short int *y, short int arrLength)
{
    int z = 0;
    for(int i = 0; i < arrLength; i++)
    {
        if(z>*(y+i)) z=*(y+i);
    }
    return z;
}