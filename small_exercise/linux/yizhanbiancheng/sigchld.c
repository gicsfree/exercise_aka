/* sigchld.c */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/* action when receive SIGCHLD */
void sigchld_handler(int signo)
{
    wait(NULL);
    printf("child process exited\n");
    exit(0);
}

/* main */
int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    } 
    if (pid == 0)
    {
        sleep(3);
        exit(2);
    }
    else
    {
        struct sigaction act;

        act.sa_handler = sigchld_handler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGCHLD, &act, NULL);  

        while (1)
        {
            printf("child process is not exit\n");
            sleep(1);
        }     
    }

    return 0;
}

