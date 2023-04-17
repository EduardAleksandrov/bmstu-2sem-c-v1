// maxmin значение суммы элементов строки столбца
#include <stdio.h>

int findsumrows(int*, int, int, int*);
int maxmin(int*, int);

int findsumcolumns(int*, int, int, int*);

int main(void) 
{
    int elements[4][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {9, -9, -9} };

    int rows = sizeof( elements ) / sizeof( elements[0]);
    int columns = sizeof( elements[0] ) / sizeof( elements[0][0]);

    int sumrow[rows];
    int sumcolumn[columns];

    // printf( "rows: %ld\n", sizeof( elements ) / sizeof( elements[0] ) );
    // printf( "columns: %ld\n", sizeof( elements[0] ) / sizeof( elements[0][0] ) );



    printf("Sumrows: ");
    findsumrows(&elements[0][0], rows, columns, sumrow);
    maxmin(sumrow, sizeof( sumrow )/sizeof(sumrow[0]));

    printf("Sumcolumns: ");
    findsumcolumns(&elements[0][0], rows, columns, sumcolumn);
    maxmin(sumcolumn, sizeof( sumcolumn )/sizeof(sumcolumn[0]));
    
}

int findsumrows(int *elements, int rows, int columns, int *sumrow)
{
    for(int i = 0; i < rows; i++)
    {   
        int sumrows = 0;
        for(int j = 0; j < columns; j++)
        {
            sumrows += *(elements + i*columns + j);
        }
        // printf("\n");
        sumrow[i] = sumrows;
    }
}

int findsumcolumns(int *elements, int rows, int columns, int *sumcolumn)
{
    for(int j = 0; j < columns; j++)
    {   
        int sumcolumns = 0;
        for(int i = 0; i < rows; i++)
        {
            sumcolumns += *(elements + i*columns + j);
        }
        // printf("\n");
        sumcolumn[j] = sumcolumns;
    }
}

int maxmin(int *sumrowc, int sumsize)
{
    int indexmax = sumrowc[0];
    int indexmin = sumrowc[0];
    int minrowc = 1;
    int maxrowc = 1;

    for(int i = 0; i< sumsize; i++) {
        if(indexmax < sumrowc[i]) {
            indexmax = sumrowc[i];
            maxrowc = i+1;
        }
        if(indexmin > sumrowc[i]) {
            indexmin = sumrowc[i];
            minrowc = i+1;
        }
    }
    printf("max: %d, min: %d \n", maxrowc, minrowc);

}