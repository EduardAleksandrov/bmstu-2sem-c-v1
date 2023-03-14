#include <stdio.h>

int fun(int*);

int main(void)
{
    int x = 100;
    
    fun(&x);
    printf("outer = %d \n", x);
}

int fun(int *y)
    {
        int z = 150;
        *y = z;
        printf("inner = %d \n", *y);
        return 0;
    }