#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp; //структура данных описывающая поток
    char ch;

    if(argc != 2) 
    {
        printf("File name is empty \n");
        exit(1);
    }
    //write
    fp = fopen(argv[1], "w");

    if(fp == NULL) 
    {
        printf("File open error \n");
        exit(1);
    }
    do {
        ch = getchar();
        if(ch != '$') putc(ch, fp);

    } while(ch != '$');

    fclose(fp);

    //read
    fp = fopen(argv[1], "r");

    if(fp == NULL) 
    {
        printf("File open error \n");
        exit(1);
    }
    
    ch = getc(fp);
    while(ch != EOF) {
        putchar(ch);

        ch = getc(fp);
    }

    fclose(fp);

    return 0;
}

 
// int main(void)
// {
//     FILE * fp = fopen("4.data.txt", "w");
//     fclose(fp);
//     return 0;
// }