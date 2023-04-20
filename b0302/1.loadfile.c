#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[])
{
// создаем буфер
    int sumOfRows = 0;
    long long int file_size = getFileSize(FILE_PATH_SOURCE, &sumOfRows);
    char *buffer = (char *) malloc(file_size);
    if (buffer == NULL) {
        printf("Память не выделена, ошибка");
    } else {
        printf("Память выделена \n");
    }

// ---

    FILE *fp;

// from file to buffer
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
    char a;
	FILE* fd = fopen(file_name, "rb");
	if(fd == NULL){
		_file_size = -1;
	} else {
		while((a=getc(fd)) != EOF){
            if (a == '\n') (*sumOfRows)++;
            _file_size++;
        }
		fclose(fd);
	}
    printf("%d", *sumOfRows);
	return _file_size;
}