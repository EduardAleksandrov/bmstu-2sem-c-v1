    // // вторая
    // struct person *personForLinkPointer;
    // personForLinkPointer = (struct person*) malloc(sizeof(struct person));
    // personForLinkPointer->id = 41;
    // personForLinkPointer->name = "Ellen";
    // personForLinkPointer->age = 50;
    // personForLinkPointer->address = "Volhovo";
    // personForLinkPointer->zipcode = 634874;
    // (persons + 5)->link = personForLinkPointer;
    // personForLinkPointer->link = (persons + 6);

    // //третья
    // (persons + sumOfRows - 1)->link = (struct person*) malloc(sizeof(struct person));
    // (persons + sumOfRows - 1)->link->id = 42;
    // (persons + sumOfRows - 1)->link->name = "Tomas";
    // (persons + sumOfRows - 1)->link->age = 60;
    // (persons + sumOfRows - 1)->link->address = "Bocharovo";
    // (persons + sumOfRows - 1)->link->zipcode = 464732;
    // (persons + sumOfRows - 1)->link->link = NULL;

#include <stdio.h>

int main(void)
{
    int n = malloc(sizeof(int));
    free(n);
    printf("too few \n");
    
    return 0;
}