/* process_eat_shmget.c */

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
    pid_t pid;
    int shmid;

    if ((shmid = shmget(IPC_PRIVATE, sizeof(sem_t) * N, 0666)) == -1)
    {
        printf("fail to share memory shmid\n");
        exit(1);
    }

    chopstick = shmat(shmid, 0, 0);
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
    shmdt(chopstick);

    return 0;
}
