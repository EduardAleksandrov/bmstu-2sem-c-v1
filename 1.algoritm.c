/*
    Создаем массив
    Вводим число, на которое должен делиться без остатка элемент массива
    Находим сумму этих элементов
    Находим корень из полученной суммы
*/
#include <stdio.h>
#include <math.h>

//прототипы функций
void printElements(unsigned short int*, unsigned short int);
float computeSqrt(unsigned short int*, unsigned short int, unsigned short int);

int main(void)
{
    // input
    unsigned short int item;
    printf("Введите количество элементов в массиве: ");
    scanf("%hd", &item);
    unsigned short int elements[item]; // массив переменной длины, в с++ нет
    unsigned short int arrLength = sizeof(elements)/sizeof(*elements); // разыменование
    printf("Введите элементы: ");
    for (int i = 0; i < arrLength; i++) 
    {
        scanf("%hu", &elements[i]);
    }
    unsigned short int divEl;
    printf("Введите на сколько должно делиться без остатка число: ");
    scanf("%hd", &divEl);
    
    // print array
    printElements(elements, arrLength);

    // print result
    float result = computeSqrt(elements, divEl, arrLength);
    result == 0 ? printf("Нет подходящих элементов \n"): printf("Результат равен: %f \n", result);

    return 0;
}

float computeSqrt(unsigned short int *elem, unsigned short int divEl, unsigned short int arrayLength) 
{
    unsigned long int sum = 0;
    float root = 0.0;
    for (int i = 0; i < arrayLength; i++) 
    {
        if (elem[i] % divEl == 0) 
        {
            sum += elem[i];
        }
    }
    if (sum >= 0) root = sqrt(sum);
    return root;
}

void printElements(unsigned short int *elem, unsigned short int arrayLength) 
{
    // print
    for (int i = 0; i < arrayLength; i++) 
    {
        printf("%d ", elem[i]); // Массив - адрес, по шине адреса запрашиваются данные, по шине данных их получаем.
    }
    printf("\n");
    return;
}