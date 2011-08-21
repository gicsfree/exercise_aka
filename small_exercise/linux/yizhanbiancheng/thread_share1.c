/* thread_share.c */

#include <stdio.h>
#include <pthread.h>

static int a = 1;
//int a = 1;

void *create(void *arg)
{
    printf("new thread ...\n");
    printf("a = %d\n", a);
    a++;

    return (void *)0;
}

int main(void)
{
    pthread_t tidp;
    int error;

    int a = 5;
    printf("in main 1: a = %d\n", a);

    error = pthread_create(&tidp, NULL, create, NULL);
    if (error != 0)
    {
        printf("new thread is not create ... \n");
        return -1;
    }

    sleep(3);

    printf("in main 2: a = %d\n", a);
    printf("new thread is created ... \n");

    return 0;
}
