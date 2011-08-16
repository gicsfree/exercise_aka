#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    char *const ps_argv[] ={"ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL};
    char *const ps_envp[] ={"PATH=/bin:/usr/bin", "TERM=console", NULL};

    if (fork() == 0)
    {
        execl("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
        perror("execl ps");
        exit(0);
    }
    if (fork() == 0)
    {
        execv("/bin/ps", ps_argv);
        perror("execv ps");
        exit(0);
    }
    if (fork() == 0)
    {
        execle("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL, ps_envp);
        perror("execle ps");
        exit(0);
    }

    if (fork() == 0)
    {
        execve("/bin/ps", ps_argv, ps_envp);
        perror("execve ps");
        exit(0);
    }
    if (fork() == 0)
    {
        execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
        perror("execlp ps");
        exit(0);
    }
    if (fork() == 0)
    {
        execvp("ps", ps_argv);
        perror("execvp ps");
        exit(0);
    }

    sleep(1);

    return 0;
}
