#include <stdio.h>

#define MAX 100

int point(int p);

int main(void)
{
// бесконечный цикл
    // int choice;
    // for(;;) 
    // {
    //     scanf("%d", &choice);

    //     switch (choice)
    //     {
    //     case 1:
    //         printf("1");
    //         break;
        
    //     default:
    //         printf("0");
    //         break;
    //     }
    // }

// цикл без тела
    // int i;
    // for(i = 0; i < MAX; i++);
    // printf("%d", i);

// типы задания строк 4шт.
    // char str1[6] = {'h','e','l','l','o','\0'};   // символ
    // char str2[6] = "Hello";                      // строка с окончание нуль
    // char str3[3];
    // str3[0] = 'h';
    // str3[1] = 'h';
    // str3[2] = '\0';
    // char *str4 = "HELLO";

    // str3[0] = '\0'; // пустая строка, очищение строки
    // printf("%s", str4);

// передача по значению адрес разный
    // int x = 5;
    // printf("%p \n", &x);

    // point(x);

    // printf("5 \t 6 \t 8");

//указатель
    int x = 5;
    int *z = &x;
    printf("%d \n", *z);
    
    return 0;
}

int point(int p)
{
    printf("%p", &p);
}