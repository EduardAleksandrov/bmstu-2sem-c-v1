#include <stdio.h>
#include <json-c/json.h>

#define FILE_PATH_SOURCE "./b0301/test.json"
#define FILE_PATH_TARGET "./b0301/wtest.json"

int64_t getFileSize(const char*);

int main(int argc, char *argv[])
{
// создаем буфер
    int64_t file_size = getFileSize(FILE_PATH_SOURCE);
    // char buffer[file_size];
    // char *x = "{\"name\": \"Alice\", \"age\": 30, \"friends\": [\"Paula\", \"Cindy\", \"Dorothy\"]}";
    char *buffer = malloc(file_size);
// ---

    FILE *fp;
    struct json_object *parsed_json;
    struct json_object *name;
    size_t i;

// from file to buffer
    fp = fopen(FILE_PATH_SOURCE, "r");
    
    if (fp == NULL)
    {
        printf("fopen failed\n");
    } else {
        printf("fopen opened\n");
    }

    fread(buffer, 1, file_size, fp);
    fclose(fp);
// ---



    parsed_json = json_tokener_parse(buffer);
    // печать всего файла
    printf("%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_SPACED));
    
    
    //char *t = (*parsed_json).name;

    // json_object_object_get_ex(parsed_json, "name", &name);

    // printf("%s", json_object_get_string(name));




// from buffer to file
    fp = fopen(FILE_PATH_TARGET, "w");
    fwrite(buffer, 1, file_size, fp);
    fclose(fp);

    free(buffer);
    buffer = NULL;
// ---

    return 0;
}

int64_t getFileSize(const char* file_name){
	int64_t _file_size = 0;
	FILE* fd = fopen(file_name, "rb");
	if(fd == NULL){
		_file_size = -1;
	}
	else{
		while(getc(fd) != EOF)
			_file_size++;
		fclose(fd);
	}
	return _file_size;
}