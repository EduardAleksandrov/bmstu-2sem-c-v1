#include <stdio.h>

int elements[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

int main() 
{

    printf( "rows: %ld\n", sizeof( elements ) / sizeof( elements[0] ) );
    printf( "columns: %ld\n", sizeof( elements[0] ) / sizeof( elements[0][0] ) );

    for(int i = 0; i < sizeof( elements ) / sizeof( elements[0]); i++)
    {   
        for(int j = 0; j < sizeof( elements[0] ) / sizeof( elements[0][0]); j++)
        {
            printf("%d",elements[i][j]);
            printf(" ");
        }
        printf("\n");
    }

}