// memory operation, одинаковые указатели на динамическую память
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    long int m = 1073000000;
    int *mainPointer = (int *) malloc(sizeof(int)*m);

    for(long int i = 0; i < m; i++)
    {
        *(mainPointer + i) = 1;
    }

    int *secondPointer;
    secondPointer= mainPointer;
    
    int t;
    scanf("%d", &t);

    free(secondPointer);
    secondPointer = NULL;

    scanf("%d", &t);

    // *mainPointer = 5;
    // printf("%d \n", *mainPointer);

    return 0;
}

// int *fun()
// {
//     int *mainPointer = (int *) malloc(sizeof(int));
//     *mainPointer = 10;
//     return mainpo
// }