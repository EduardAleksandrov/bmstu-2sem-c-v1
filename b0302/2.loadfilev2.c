// загрузка построчно
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PATH_SOURCE "./testv1.csv"
#define FILE_PATH_TARGET "./wtest.csv"



struct person
{
    char id[50];
    char name[50];
    char age[50];
    char address[50];
    char zipcode[50];
};

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(FILE_PATH_SOURCE, "r");
    
    if (fp == NULL)
    {
        printf("fopen failed\n");
    } else {
        printf("fopen opened\n");
    }

    char buff[1024];

    while(fgets(buff, sizeof(buff), fp))
    {
        printf("%s", buff);
    }


    fclose(fp);


    return 0;
}