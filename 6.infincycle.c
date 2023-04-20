// бесконечное считывание символов
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
// считование чисел
    // int *x = (int *) malloc(sizeof(int));
    // int num;
    // int count = 0;
    // //*x = 1;
    // for(;;)
    // {
    //     count++;
    //     scanf("%d", &num);
    //     x = (int *) realloc(x,sizeof(int)*count);
    //     *(x+count-1) = num;

    //     for(int i = 0; i< count; i++)
    //     {
    //         printf("%d",*(x+i));
    //     }
    //     printf("\n");

    //     if(num == 0) break;
    // }
    // free(x);

// считование символов
    char *x = (char *) malloc(sizeof(char));
    char num;
    int count = 0;
    for(;;)
    {
        count++;
        scanf(" %c", &num); //нужен пробел, чтобы не считывался символ enter "\n"
        x = (char *) realloc(x, sizeof(char)*count);
        *(x + count - 1) = num;
        //*(x+count) = '\0';

        printf("%s \n", x);

        if(num == 'q') break;
    }
    free(x);
    return 0;
}