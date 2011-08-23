/* process_eat_mmap.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
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

sem_t *chopstick;

/* pick up chopstick */
void pickup(int me)
{
    if (me == 0)
    {
        sem_wait(&chopstick[R(me)]);
        sem_wait(&chopstick[L(me)]);
    }
    else
    {
        sem_wait(&chopstick[L(me)]);
        sem_wait(&chopstick[R(me)]);
    }
}

/* put down chopstick */
void putdown(int me)
{
    sem_post(&chopstick[L(me)]);
    sem_post(&chopstick[R(me)]);
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
    if ((chopstick = mmap(NULL, sizeof(sem_t) * N, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        perror("mmap()");
        exit(1);        
    }

    for (i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 1, 1);
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
    munmap(chopstick, sizeof(sem_t) * N);
    close(fd);

    return 0;
}
