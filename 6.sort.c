// сортировка линейная и пузырьком, сортировка строк
#include <stdio.h>
#include <string.h>

int main(void) 
{
// линейная
    int x[7] = {7, 4, 8, 5, 1, 6, 3};
    size_t len = sizeof(x)/ sizeof(x[0]);
    for(int i = 0; i < len-1; i++)
    {
        for(int j = i + 1; j < len; j++)
        {
            if(x[i] > x[j])
            {
                int d = x[i];
                x[i] = x[j];
                x[j] = d;
            }
        }
    }
    for(int i = 0; i < len; i++)
    {
        printf("%d \t", x[i]);
    }
    //printf("%ld \n", len);
    printf("\n");
// пузырьком 
    int y[7] = {7, 4, 8, 5, 1, 6, 3};
    len = sizeof(y)/ sizeof(y[0]);
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len-1; j++)
        {
            if(y[j] > y[j+1])
            {
                int d = y[j];
                y[j] = y[j+1];
                y[j+1] = d;
            }
        }
    }
    for(int i = 0; i < len; i++)
    {
        printf("%d \t", x[i]);
    }

    printf("\n");


// сортировка строк линейная
    char *str[4] = {"peter", "alan", "mike", "pete"};

    for(int i = 0; i < 3; i++)
    {
        for(int j = i + 1; j < 4; j++)
        {
            if(strcmp(str[i], str[j]) > 0)
            {
                char *d = str[i];
                str[i] = str[j];
                str[j] = d;
            }
        }
    }
    for(int i = 0; i < 4; i++)
    {
        printf("%s \n", str[i]);
    }

// массивы и указатели

char *xx = "String"; //размер не считает
char yy[] = "String22"; //размер считает

printf("%ld \n", sizeof(*xx));

    return 0;
}
