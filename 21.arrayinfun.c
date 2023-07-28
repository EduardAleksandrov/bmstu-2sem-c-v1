#include <stdio.h>
#include <stdlib.h>

int* fun(void);

int main(void)
{
    int* v = fun();

    printf("%d", *(v+1));

    return 0;
}

int* fun()
{
    int x[5] = {1,2,3,4,5}; // не работает т.к. массив локален
    int *z = (int *) malloc(sizeof(int)*5); //работает
    *(z+1) = 4;
    return z; 
}

