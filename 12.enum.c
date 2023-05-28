// enum, union
#include <stdio.h>

enum operation // арифметическая операция
{
    ADD,        // сложение
    SUBTRACT,   // вычитание
    MULTIPLY    // умножение
};

union tag
{
    int x;
    double y;
    char z;
};


int main(void)
{
    enum operation op;  // определяем переменную перечисления
    op = SUBTRACT;           // присваиваем ей одну из констант перечисления
    printf("Operation: %d\n", op);
    if(op == SUBTRACT || op == 1) puts("True");
    op = ADD;
    printf("Op: %d \n", op);

    union tag funion;
    funion.z = 'f';
    printf("%c \n", funion.z);
    funion.y = 0.5;
    printf("%.2f \n", funion.y);

    
    return 0;
}