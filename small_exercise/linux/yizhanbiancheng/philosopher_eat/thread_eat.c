/* thread-eat.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define N 5
#define L(x) x
#define R(x) ((x + 1) % N)

pthread_mutex_t chopstick[N];

/* pick up chopstick */
void pickup(int me)
{
    if (me == 0)
    {
        pthread_mutex_lock(&chopstick[R(me)]);
        pthread_mutex_lock(&chopstick[L(me)]);
    }
    else
    {
        pthread_mutex_lock(&chopstick[L(me)]);
        pthread_mutex_lock(&chopstick[R(me)]);
    }
}

/* put down chopstick */
void putdown(int me)
{
    pthread_mutex_unlock(&chopstick[L(me)]);
    pthread_mutex_unlock(&chopstick[R(me)]);
}

/* action of philosopher */
void *func(void *arg)
{
    int i = (int)arg;

    srand(time(NULL));
    while (1)
    {
        printf("philosopher %d thinking...\n", i);
        usleep(rand() % 10);
        pickup(i);
        printf("philosopher %d eating...\n", i);
        usleep(rand() % 10);
        putdown(i); 
    }

    return NULL;
}

/* main */
int main(void)
{
    int i;
    pthread_t tid[N];

    for (i = 0; i < N; i++)
    {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    for (i = 0; i < N - 1; i++)
    {
        pthread_create(&tid[i], NULL, func, (void *)i);
    }

    func((void *)i);

    for (i = 0; i < N - 1; i++)
    {
        pthread_join(tid[i], NULL);
    }

    return 0;
}
