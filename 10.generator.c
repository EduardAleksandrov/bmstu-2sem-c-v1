// генератор csv файла
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_PATH_TARGET "./10.generator.csv"


int main(void) 
{
    srand(time(NULL)); // генерация множества случайных значений
    
    unsigned long long int n; // количество строк
    unsigned long long int x = 1; // счетчик

    printf("Введите цифры больше нуля или ноль для выхода \n");
    scanf("%lld", &n);
    if(n <= 0) exit(0);

    FILE *fp;
    fp = fopen(FILE_PATH_TARGET, "w");
    if (fp == NULL)
    {
        perror("fwopen failed ");
        exit(1);
    } else {
        printf("fwopen opened\n");
    }

    while(x <= n){
    // генерация имени
        int k = 4 + rand()%(25 - 4 + 1);
        char name[k];
        int i;
        for (i = 0; i < k - 1; i++)
        {
            name[i] = 'a' + rand()%26;
        } 
        name[i] = '\0';
        // printf("%s\n", s);

    // генерация адреса
        int kk = 6 + rand()%(35 - 6 + 1);
        char address[kk];
        int j;
        for (j = 0; j < kk - 1; j++)
        {
            address[j] = 'a' + rand()%26;
        } 
        address[j] = '\0';
        // printf("%s\n", ss);

    // генерация возраста
        unsigned short int age;
        age = 5 + rand()%(100 - 5 + 1);
        // printf("%d\n", age);

    // генерация индекса
        unsigned long int zipcode;
        zipcode = 100000 + rand()%(999999 - 100000 + 1);
        // printf("%ld\n", zipcode);

    // запись в файл
        if(x == 1) fprintf(fp,"id,name,age,address,zipcode\n");
        if(x != n) fprintf(fp,"%llu,%s,%hu,%s,%lu\n", x, name, age, address, zipcode);
        if(x == n) fprintf(fp,"%llu,%s,%hu,%s,%lu", x, name, age, address, zipcode);

    // счетчик строк
        x++;
    }

    fclose(fp);
    fp = NULL;

return 0;
}
