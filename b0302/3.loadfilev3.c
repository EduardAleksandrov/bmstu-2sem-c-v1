// загрузка построчно (массив в динамической памяти) - работает 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PATH_SOURCE "./testv1.csv"
#define FILE_PATH_TARGET "./wtest.csv"
#define SIZEOFBUFF 1024

struct person
{
    int id;
    char name[50];
    int age;
    char address[50];
    long int zipcode;
};

long int getFileLineSize(char*);


int main(int argc, char *argv[])
{
    // подсчет строк
    long int sumOfRows = getFileLineSize(FILE_PATH_SOURCE);
    if(sumOfRows == -1) 
    {
        printf("Файл для подсчета строк не открылся");
        exit(1);
    }

    // создание структур
    struct person *persons = (struct person *) malloc(sizeof(struct person)*sumOfRows);
    if (persons == NULL) {
        printf("Память не выделена, ошибка");
        exit(1);
    }

    // считывание данных из файла в массив структур
    FILE *fp;
    fp = fopen(FILE_PATH_SOURCE, "r");
    
    if (fp == NULL)
    {
        printf("fropen failed\n");
        exit(1);
    } else {
        printf("fropen opened\n");
    }

    char buff[SIZEOFBUFF];
    int i = 0;
    int row_count = 0;
    int field_count = 0;
    while(fgets(buff, sizeof(buff), fp))
    {
        field_count = 0;
        row_count++;
        if(row_count == 1) continue;

        char *field = strtok(buff, ",");
        while(field)
        {
            if(field_count == 0) persons[i].id = strtol(field, NULL, 10); // т.к. мы обращаемся к указателю через индексацию массива, то точка, а не стрелка
            if(field_count == 1) strcpy(persons[i].name, field);
            if(field_count == 2) persons[i].age = strtol(field, NULL, 10);
            if(field_count == 3) strcpy(persons[i].address, field);
            if(field_count == 4) persons[i].zipcode = strtol(field, NULL, 10);

            field = strtok(NULL, ",");
            field_count++;
        }
        i++;
    }
    fclose(fp);
    fp = NULL;

    //Выбор поля для сортировки
    int cases= 0;
    printf("Введите цифру для сортировки поля \n");
    printf("1 - id, 2 - name, 3 - age, 4 - address, 5 - zipcode \n");
    for(;;)
    {
        scanf("%d", &cases);
        if(cases >= 0 && cases <= 5) break;
        if(cases < 1 || cases > 5) printf("Пункт не выбран, выберите пункт, или ноль для выхода \n");
    }

    switch(cases)
    {
        case 1: 
            printf("Выбран id \n");
            break;
        case 2: 
            printf("Выбран name \n");
            break;
        case 3:
            printf("Выбран age \n");
            break;
        case 4: 
            printf("Выбран address \n");
            break;
        case 5: 
            printf("Выбран zipcode \n");
            break;
        default: 
            printf("Пункт не выбран \n");
            break;
    }
    
    if(cases >= 1 && cases <= 5)
    {
        //сортировка
        struct person personVar;
        for(long int i = 0; i < sumOfRows-1; i++)
        {
            for(long int j = i + 1; j < sumOfRows; j++)
            {
                if((persons[i].id > persons[j].id) && cases == 1)
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
                if((persons[i].age > persons[j].age) && cases == 3)
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
                if((persons[i].zipcode > persons[j].zipcode) && cases == 5)
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
            printf("fwopen failed\n");
            exit(1);
        } else {
            printf("fwopen opened\n");
        }

        for(long int i = 0; i < sumOfRows; i++)
        {   
            if(i == 0) fprintf(fpw,"id,name,age,address,zipcode\n");

            if(i != (sumOfRows - 1)) fprintf(fpw,"%d,%s,%d,%s,%ld\n", persons[i].id, persons[i].name, persons[i].age, persons[i].address, persons[i].zipcode);
            if(i == (sumOfRows - 1)) fprintf(fpw,"%d,%s,%d,%s,%ld", persons[i].id, persons[i].name, persons[i].age, persons[i].address, persons[i].zipcode);
        }

        fclose(fpw);
        fpw = NULL;
    }

    free(persons);
    persons = NULL;

    return 0;
}

long int getFileLineSize(char* file_name){
    long int sumOfRows = 0;
    char ch;
	FILE* fd = fopen(file_name, "r");
	if(fd == NULL){
        printf("frLineOpen failed\n");
		sumOfRows = -1;
	} else {
        printf("frLineOpen opened\n");
		while((ch = getc(fd)) != EOF){
            if (ch == '\n') sumOfRows++;
        }
		fclose(fd);
	}
	return sumOfRows;
}