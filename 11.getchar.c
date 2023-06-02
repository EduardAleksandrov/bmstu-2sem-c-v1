// getchar, putchar
#include <stdio.h>

int main(void) 
{
    int x;
    x = EOF;
    printf("%d \n", x);

    char nc;
    while((nc = getchar()) != EOF) //считывает строку посимвольно
    // while((nc = getchar()) != '\n')
    {
        putchar(nc);
        if(nc == '0') break;
    }

return 0;
}
