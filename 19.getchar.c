#include <stdio.h>
#include <stdlib.h>



int main(void)
{
// отладка
    int y;
    scanf("%d", &y);  //считывает только числа до перевода строки
    
    char x[10];
    fgets(x, 10, stdin);  //считывает все после scanf, включая перевод строки, чтобы сработал getchar()
    printf("отладка \n");
    getchar();
    
    exit(0);
}



