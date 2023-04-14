#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void info() {
    int i;
    int k = 0;
    for(i = 0; i<5; i++){
        
        k += i;
    }
}

struct xcoord {
  int x, y;
  char attr, color;
};
void fun( struct xcoord * ); //передаем в функцию указатель st на структуру xcoord



int main(void) 
{
    int *restrict p, *restrict pp;
    int x = 5;
    int y = 6;

    p = &x;
    pp = &x;

    info();

// true false bool
    bool t;
    t = true;
    printf("%d \n", t);
    printf("Your boolean variable is: %s \n", t ? "true" : "false");
//
    printf("%d \n", __STDC_HOSTED__);
//
    int a[10];
    int* s = a;
    printf("%ld %ld %ld\n", sizeof(a), sizeof(*s), sizeof(s));
    char *buffer = malloc(5);
    printf("%ld \n", sizeof(buffer)); // мы не можем найти длину выделенной памяти через указатель, ее нужно знать заранее
// структура через указатель
    //1
    struct xcoord str;
    fun(&str);
    //2
    struct xcoord *mpoint;
    mpoint = malloc(sizeof(struct xcoord));
    mpoint->x = 6;
    printf("%d \n", mpoint->x);
// арифметика указателей
    int x[] = {1,2,3,4};
    int *p = x;
    p = p + 2;
    printf("%d \n", *p);

    int *pp = p;
    pp = pp + 1;
    printf("%d \n", *pp);



    return 0;
}


void fun( struct xcoord * st ) //передаем в функцию указатель st на структуру xcoord
{
  st->x = 12; //обращению к полю x структуры xcoord через указатель st
  st->y = 10;
  st->attr = 'A';
  st->color = 0;
  printf("\n%d \n", st->x);
}

