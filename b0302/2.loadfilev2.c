// загрузка построчно (переменный массив) - работает 
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

long int getFileLineSize(char*);

int main(int argc, char *argv[])
{
    long int sumOfRows = getFileLineSize(FILE_PATH_SOURCE);
    FILE *fp;
    fp = fopen(FILE_PATH_SOURCE, "r");
    
    if (fp == NULL)
    {
        printf("fopen failed\n");
    } else {
        printf("fopen opened\n");
    }

    struct person persons[sumOfRows];
    char buff[1024];

    int i = 0;
    int row_count = 0;
    int field_count = 0;
    while(fgets(buff, sizeof(buff), fp))
    {
        // printf("%s", buff);
        field_count = 0;
        row_count++;
        if(row_count == 1) continue;

        // char* pFirstN = strstr(buff, "\n");
        // *pFirstN = 'x';

        char *field = strtok(buff, ",");
        while(field)
        {
            if(field_count == 0) strcpy(persons[i].id, field);
            if(field_count == 1) strcpy(persons[i].name, field);
            if(field_count == 2) strcpy(persons[i].age, field);
            if(field_count == 3) strcpy(persons[i].address, field);
            if(field_count == 4) strcpy(persons[i].zipcode, field);

            field = strtok(NULL, ",");
            field_count++;
        }
        i++;
    }
    fclose(fp);

    fp = NULL;

    // for(int i = 0; i < sumOfRows; i++)
    // {
    //     printf("%s %s %s %s %s", persons[i].id, persons[i].name, persons[i].age, persons[i].address, persons[i].zipcode);
    // }
    
    // убрали символы конца строки
    for(long int i = 0; i < sumOfRows-1; i++)
    {
        char* pFirstN = strstr(persons[i].zipcode, "\n");
        *pFirstN = ' ';
    }


    //Выбор поля для сортировки
    int cases= 0;
    printf("Введите цифру для сортировки поля \n");
    printf("1 - id, 2 - name, 3 - age, 4 - address, 5 - zipcode \n");
    scanf("%d", &cases);

    switch(cases)
    {
        case 1: 
            printf("Выбран 1 \n");
            break;
        case 2: 
            printf("Выбран 2 \n");
            break;
        case 3:
            printf("Выбран 3 \n");
            break;
        case 4: 
            printf("Выбран 4 \n");
            break;
        case 5: 
            printf("Выбран 5 \n");
            break;
        default: 
            printf("Пункт не выбран \n");
            break;
    }

    //сортировка
    struct person personVar;
    for(long int i = 0; i < sumOfRows-1; i++)
    {
        for(int j = i + 1; j < sumOfRows; j++)
        {
            if((strcmp(persons[i].id, persons[j].id) > 0) && cases == 1)
            {
                personVar = persons[i];
                persons[i] = persons[j];
                persons[j] = personVar;
            }
            if((strcmp(persons[i].name, persons[j].name) > 0) && cases == 2)
            {
                personVar = persons[i];
                persons[i] = persons[j];
                persons[j] = personVar;
            }
            if((strcmp(persons[i].age, persons[j].age) > 0) && cases == 3)
            {
                personVar = persons[i];
                persons[i] = persons[j];
                persons[j] = personVar;
            }
            if((strcmp(persons[i].address, persons[j].address) > 0) && cases == 4)
            {
                personVar = persons[i];
                persons[i] = persons[j];
                persons[j] = personVar;
            }
            if((strcmp(persons[i].zipcode, persons[j].zipcode) > 0) && cases == 5)
            {
                personVar = persons[i];
                persons[i] = persons[j];
                persons[j] = personVar;
            }
        }
    }

    // запись в файл
    FILE *fpw;
    fpw = fopen(FILE_PATH_TARGET, "w");
    
    if (fpw == NULL)
    {
        printf("fopen failed\n");
    } else {
        printf("fopen opened\n");
    }

    for(long int i = 0; i < sumOfRows; i++)
    {
        if(i == 0) fprintf(fpw,"id,name,age,address,zipcode\n");
        fprintf(fpw,"%s,%s,%s,%s,%s\n", persons[i].id, persons[i].name, persons[i].age, persons[i].address, persons[i].zipcode);
    }

    fclose(fpw);
    fpw = NULL;

    // for(long int i = 0; i < sumOfRows; i++)
    // {
    //     printf("%s %s %s %s %s \n", persons[i].id, persons[i].name, persons[i].age, persons[i].address, persons[i].zipcode);
    // }

    // FILE *fpp;
    // fpp = fopen(FILE_PATH_TARGET, "w");
    // for(int i = 0; i<5; i++)
    //     fprintf(fp,"Строка\n");
    // fclose(fpp);

    return 0;
}

long int getFileLineSize(char* file_name){
    long int sumOfRows = 0;
    char ch;
	FILE* fd = fopen(file_name, "r");
	if(fd == NULL){
		sumOfRows = -1;
	} else {
		while((ch = getc(fd)) != EOF){
            if (ch == '\n') sumOfRows++;
        }
		fclose(fd);
	}
	return sumOfRows;
}