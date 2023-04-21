// загрузка в буфер
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PATH_SOURCE "./testv1.csv"
#define FILE_PATH_TARGET "./wtest.csv"

long long int getFileSize(char*, int*);

struct person
{
    int id;
    char *name;
    int age;
    char *address;
    long int zipcode;
};

/*

 sumOfRows
 buffer

*/



int main(int argc, char *argv[])
{
// создаем буфер
    int sumOfRows = 0; //считаем количество строк
    long long int file_size = getFileSize(FILE_PATH_SOURCE, &sumOfRows);
    char *buffer = (char *) malloc(file_size);
    if (buffer == NULL) {
         printf("Память не выделена, ошибка");
         exit(1);
    } else {
         printf("Память выделена \n");
    }

// from file to buffer
    FILE *fp;
    fp = fopen(FILE_PATH_SOURCE, "r");
    
    if (fp == NULL)
    {
        printf("fopen failed\n");
    } else {
        printf("fopen opened\n");
    }

    fread(buffer, file_size, 1, fp); // file_size количество элементов по 1 байту
    fclose(fp);
// ---


    struct person persons[sumOfRows];

    long int charsSize = 1; // перебор символов
    int countStrs = 0;

    char buffStr[3][50];
    int counter = 0;
    while(charsSize <= file_size)
    {
        
        
        if( countStrs > 0 ) 
        {   
            counter++;
            strcpy(buffStr[countStrs-1], (buffer+counter-1));
        }
        
        if(*(buffer+charsSize-1) == '\n') \
        {
            countStrs++;
            counter = 0;
            buffer = buffer+charsSize-1;

        }
        // if(countStrs == 0) {
        //     charsSize++;
        //     continue;
        // };
        // while(countStrs == 1){
            
        //     strcat(ids, (buffer+charsSize-1));
        //     if(*(buffer+charsSize-1) == ',')
        //     {
                
        //     }
        // }




        charsSize++;
    }
    printf("%s", buffStr[4]);


// from buffer to file
    fp = fopen(FILE_PATH_TARGET, "w");
    fwrite(buffer, file_size, 1, fp);
    fclose(fp);

    free(buffer);
    buffer = NULL;
// ---

    return 0;
}

long long int getFileSize(char* file_name, int* sumOfRows){
	long long int _file_size = 0;
    char ch;
	FILE* fd = fopen(file_name, "rb");
	if(fd == NULL){
		_file_size = -1;
	} else {
		while((ch=getc(fd)) != EOF){
            if (ch == '\n') (*sumOfRows)++;
            _file_size++;
        }
		fclose(fd);
	}
    //printf("%d", *sumOfRows);
	return _file_size;
}