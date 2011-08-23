/* sh_memory.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <error.h>

#define MAX_LINE 1024

int shmid;

void handler(int signo)
{
    char *p_addr;

    if (signo == SIGUSR1)
    {
        p_addr = shmat(shmid, 0, 0);
        printf("parent process get: %s", p_addr);
    }
}

int main(int argc, const char *argv[])
{
    pid_t pid;	

    if ((shmid = shmget(IPC_PRIVATE, MAX_LINE, 0666)) == -1)
    {
        printf("fail to share memory shmid\n");
        exit(1);
    }

    if (signal(SIGUSR1, handler) == SIG_ERR)
    {
        perror("can't set handler for SIGUSR\n");
        exit(1);
    }

    pid = fork();	
    if (pid < 0 )
    {
        perror("fork()");
        exit(1);
    }
    if (pid == 0)
    {
        char buf[MAX_LINE] = {0};
        char *c_addr;

        c_addr = shmat(shmid, 0, 0);
        while (1)
        {
            memset(buf, MAX_LINE, 0);
            memset(c_addr, MAX_LINE, 0);
            printf("child process send: ");
            fgets(buf, MAX_LINE, stdin);
            strncpy(c_addr, buf, MAX_LINE);
            kill(getppid(), SIGUSR1);
            usleep(1);
        }
    }
    else
    {
        wait(NULL);
    }

    return 0;
}
