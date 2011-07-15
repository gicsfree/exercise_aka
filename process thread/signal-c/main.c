#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#define X

#ifdef X
void child_process(char argv[])
{

    
    while(1)
    {
		kill(0, atoi(argv)); 
    	sleep(2);
    }
}
#endif





void new_op(int, siginfo_t *, void *);
int main(int argc, char **argv)
{
	struct sigaction act;
	int sig;
	sig = atoi(argv[1]);

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = new_op;




#ifdef X
    pid_t pid;

    pid = fork();
    
    if (pid == 0)
    {
        child_process(argv[1]);
    }
    else
    {
    


#endif


	if (sigaction(sig, &act, NULL) < 0) {
		printf("install sigal error\n");
	}

	while (1) {
		sleep(200);
		printf("wait for the signal\n");
	}
#ifdef X
}
#endif

}

void new_op(int signum, siginfo_t * info, void *myact)
{
	printf("receive signal %d\n", signum);
	sleep(5);
}
