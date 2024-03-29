#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *wait(void* n)
{
    sleep(2);

    printf("Done.\n");
    pthread_exit((void*)5);
}

int main(void)
{
    pthread_t thread;
    int err;

    err = pthread_create(&thread, NULL, wait, NULL);

    if (err)
    {
        printf("An error occured: %d", err);
        return 1;
    }

    printf("Waiting for the thread to end...\n");

    pthread_join(thread, NULL);

    printf("Thread ended.\n");    

    return 0;
}