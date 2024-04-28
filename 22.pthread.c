#define _GNU_SOURCE 
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
 
void* some_work(void* arg) 
{
    for(int i = 0; i < 2; ++i) 
    {
        puts(arg);
    }
    printf("%d \n", gettid());
    return NULL;
}
int main(void) 
{ 
    pthread_t thread;
    // создаем потоки
    int i = 0;
    while(i<3)
    {
        pthread_create(&thread, NULL, some_work, "Hello World" );
        i++;
    }
    // pthread_create(&thread[0], NULL, some_work, "Hello World" );
    // pthread_create(&thread[1], NULL, some_work, "Hello METANIT.COM" );
 
    // pthread_exit(NULL);
    i=0;
    while(i<3)
    {
        pthread_join(thread, NULL);
        i++;
    }
        

    
    printf("End...\n");
    return 0;
}