#include <pthread.h>
#include <stdio.h>
 
void* some_work(void* arg) 
{
    for(int i = 0; i < 5; ++i) 
    {
        puts(arg);
    }
    return NULL;
}
int main(void) 
{ 
    pthread_t thread[2];
    // создаем потоки
    pthread_create(&thread[0], NULL, some_work, "Hello World" );
    pthread_create(&thread[1], NULL, some_work, "Hello METANIT.COM" );
 
    // pthread_exit(NULL);
    for(int i = 0; i < 2; i++)
    {
        pthread_join(thread[i], NULL);
    }
    
    printf("End...\n");
    return 0;
}