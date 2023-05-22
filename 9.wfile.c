// печать русских символов
#include <stdio.h>
#include <stdlib.h>

struct person
{
    int age;
    char *name;
};

int main(void) 
{
    FILE *fp;
    fp = fopen("9.F0.csv", "r");
    char ch;
    char buff[1000]; 
    if(fp == NULL)
    {
        printf("Файл для подсчета строк не открылся\n");
        exit(1);
    } else {
        printf("frLineOpen opened\n");
        // while((ch = getc(fp)) != EOF)
        // {
        //     printf("%c", ch);
        // }
        while(fgets(buff, sizeof(buff), fp))
        {
            printf("%s", buff);
        }
        fclose(fp);
        fp = NULL;
    }

    struct person tom;
    // tom.name = "Tom";
    tom.age = 22;
    char str[] = "nom";
    // tom.age = (char *) malloc(sizeof(char)*strlen);
    // strcpy(tom.name, "Tom"); //segmentation fault
    printf("Name:%s Age: %d , %d", tom.name, tom.age, sizeof(str));


    return 0;
}
