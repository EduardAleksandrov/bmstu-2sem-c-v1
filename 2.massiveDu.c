#include <stdio.h>

void printArray(unsigned short int*, unsigned short int, unsigned short int);
void printArray_33(unsigned short int[][3]);

int main(void)
{
// input
    unsigned short int elements[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    unsigned short int newElem[3][3];

    printf( "rows: %ld\n", sizeof( elements ) / sizeof( elements[0] ) );
    printf( "columns: %ld\n", sizeof( elements[0] ) / sizeof( elements[0][0] ) );
    printf( "number of elements: %ld\n", sizeof( elements ) / sizeof( elements[0][0] ) );
    printf( "number of elements pointer: %ld\n", (&elements[2][2] - &elements[0][0])+1);


    //unsigned short int arrLength = sizeof(elements)/sizeof(*elements); // разыменование

    printArray(&elements[0][0], sizeof( elements ) / sizeof( elements[0] ), sizeof( elements[0] ) / sizeof( elements[0][0] ));

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            newElem[j][i] = elements[i][j];
        }
    }
// 1 способ
    printArray(&newElem[0][0], sizeof( elements ) / sizeof( elements[0] ), sizeof( elements[0] ) / sizeof( elements[0][0] ));
// 2 способ
    printArray_33(&newElem[0]);

// сопоставление начального адреса массива, все одинаково
    printf("%p \n", newElem);
    printf("%p \n", &newElem[0]);
    printf("%p \n", &newElem[0][0]);

    return 0;
}

void printArray(unsigned short int *y, unsigned short int rows, unsigned short int columns)
{
    for(int i = 0; i < rows; i++)
    {   
        for(int j = 0; j < columns; j++)
        {
            // printf("%u",y[i*columns+j]); // в памяти располагаются последовательно, массив превратился в одномерный
            printf("%u",*(y+i*columns+j)); // с указателем
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

void printArray_33(unsigned short int y[3][3])
{
    for(int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 3; j++)
        {
            printf("%u",y[i][j]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}