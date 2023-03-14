#include <stdio.h>

int max(unsigned short int*, unsigned short int);

int main(void)
{
// input
    unsigned short int item;
    printf("Введите количество элементов в массиве: ");
    scanf("%hd", &item);
    unsigned short int elements[item]; // массив переменной длины, в с++ нет
    unsigned short int arrLength = sizeof(elements)/sizeof(*elements); // разыменование
    printf("Введите элементы: \n");
    for (int i = 0; i < arrLength; i++) 
    {
        scanf("%hu", &elements[i]);
    }

    printf("max = %d \n", max(elements, arrLength));
    
    return 0;
}

int max(unsigned short int *y, unsigned short int arrLength)
{
    int z = 0;
    for(int i = 0; i < arrLength; i++)
    {
        if(z<*(y+i)) z=*(y+i);
    }
    return z;
}