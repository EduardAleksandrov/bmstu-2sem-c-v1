// enum, union
#include <stdio.h>
#include <locale.h>
#include <uchar.h>


int main(void)
{
    setlocale(LC_ALL, "");

    //uchar
    char32_t one[] = U"привет";
    printf("%ld байт %ls \n", sizeof(one), one);
    
    return 0;
}