// bitwise operation
#include <stdio.h>
#include <stdlib.h>

int convert(int a) {
    a = ~(a) + 1;
    return a;
}

int main(void)
{
    int x = 12;
    int y = ~x;
    y += 1;
    printf("%d \n", y);

    int a = 2 << 2;  // 2^(1 + 2)
    int b = 256 >> 7;  // 2^(8 - 7) 
    printf("%d, %d\n", a, b);

    printf("%d\n", convert(5));
    puts("");


//перевод из десятичной системы в любую другую
    int decimalNumber; // число
    puts("Введите число: ");
    scanf("%d", &decimalNumber);
    short int system; // система счисления
    puts("Введите систему счисления: ");
    scanf("%hd", &system);

    int ostatok, sled;
    sled = decimalNumber;

    int num = 1;
    short int *convert = (short int *) calloc(num, sizeof(short int));
    do
    {
        ostatok = sled % system;
        // printf("%d", ostatok);
        *(convert + num - 1) = ostatok;
        
        sled = sled / system;
        if(sled == 0) break;
        
        num++;
        convert = (short int *) realloc(convert, sizeof(short int)*num);
    // } while(sled != 0);
    } while(sled);
    puts("Результат: ");
    for(int i = num - 1; i >= 0; i--)
    {
        printf("%d", *(convert + i));
    }
    puts("");
    free(convert);
// end

// Преобразование символа в число, как в ассемблере
    //символ в число
    char str;
    scanf(" %c", &str);
    printf("Число из символа: %d \n", str - '0');
    //символ из числа
    int number;
    scanf(" %d", &number);
    printf("Символ из числа: %c \n", number + '0');
// end


    return 0;
}