#include <stdio.h>



void func(int *p);

int main(void)
{
    // char ch;
    // ch = getchar();
    // putchar(ch);

    // printf("%x %#x", 10, 10);

    // int i, j;
    // scanf("%d%d", &i, &j);
    // printf("%d %d", i, j);

// указатель передается по ссылке
    int t = 8;
    int *p = &t;

    printf("%p \n",&p);

    func(p);

    return 0;
}

void func(int *p)
{
    printf("%p \n", &p);
}