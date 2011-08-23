/* process_eat_mutex.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define N 5
#define L(x) x
#define R(x) ((x + 1) % N)

pthread_mutex_t *chopstick;  //mutex在多进程时不能解决我们的问题

/* pick up chopstick */
void pickup(int me)
{
    if (me == 10)
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
void func(int me)
{
    srand(time(NULL));
    while (1)
    {
        printf("philosopher %d thinking...\n", me);
        usleep(rand() % 10);
        pickup(me);
        printf("philosopher %d eating...\n", me);
        usleep(rand() % 10);
        putdown(me); 
    } 
}

/* main */
int main(void)
{
    int i;
    int fd;
    pid_t pid;

    if ((fd = open("/dev/zero", O_RDWR)) < 0)
    {
        perror("open()");
        exit(1);
    }
    if ((chopstick = mmap(NULL, sizeof(pthread_mutex_t) * N, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        perror("mmap()");
        exit(1);        
    }

    for (i = 0; i < N; i++)
    {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    for (i = 0; i < N - 1; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork()");
            exit(1);
        }
        if (pid == 0)
        {
            func(i);
            exit(0);
        }
    }

    func(i);
    munmap(chopstick, sizeof(pthread_mutex_t) * N);
    close(fd);

    return 0;
}
