#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t result;
	result = fork();
	if(result == -1)
	{
		perror("fork");
		exit;
	}
	else if(result == 0)
	{
		printf("The return value is %d\n In child process!!\n My PID is %d\n",result,getpid());
	}
	else
	{
		printf("The return value is %d\n In father process!!\n My PID is %d\n",result,getpid());
	}
}

