/* signalchild.c */

#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h>

void sigchld_handler(int signo)
{ 
    int status; 
    int pid = waitpid(-1, &status, WNOHANG); 

    if (WIFEXITED(status)) 
    { 
        printf("The child %d exit with code %d\n", pid, WEXITSTATUS(status)); 
    } 
} 

int main() 
{ 
    int pid; 
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = sigchld_handler;
//    act.sa_handler = SIG_DFL;
//    act.sa_handler = SIG_IGN;

    sigaction(SIGCHLD, &act, NULL);

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid ==  0) 
    { 
        printf("I 'm a child.\n"); 
        sleep(2); 
        exit(2); 
    } 
    else 
    { 
        int i;

        printf("The child process is %d\n", pid); 

        for (i = 0; i < 10; i++) 
        { 
            printf("Do parent things.\n"); 
            sleep(1); 
        } 
    } 

    return 0;
}
