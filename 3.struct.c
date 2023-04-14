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
    // for(i = 0; i < MAX; i++); // найти элемент по условию
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

    //char aa[] = {'e', 't', '\0'};

// передача по значению адрес разный
    // int x = 5;
    // printf("%p \n", &x);

    // point(x);

    // printf("5 \t 6 \t 8");

//указатель
    int x = 5;
    int *z = &x;

    int *g;
    g = NULL;
    g = &x; //  при *g=&x он берет адрес, который там хранится(мусор) и присваивает значению *p адрес &x. Если мы присвоим g=NULL,
            //  то выполнить операцию не получится т.к. указатель ссылается на нулевой участок память
    printf("%d %p  %p\n", *g, &x, g);

    //segmentation fault
    // int *ss;
    // printf("%d\n", *ss);

// при выделении памяти переменной в ней хранится мусор 
    int f;
    printf("%d \n", f);

//печать строк без нулевого символа
    char str2[3] = {'f','g','\0'};
    char str1[5] = {'a','b','c','d','e'};
    char str3[5] = {'f','g','h','i','j'};

    // printf("%p, %p \n", &str1, &str2);
    printf("%s \n", str1);

// размер функции
    printf("%ld \n", sizeof(point));

// вызов функции в if
    int n;
    if ((n = point(5)) == 1) printf("Функция сработала n = %d\n", n);
    return 0;
}   

int point(int p)
{
    printf("%p \t", &p);
    return 1;
}