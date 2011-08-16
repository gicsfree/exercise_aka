/* fcntl_lock.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

volatile sig_atomic_t sigflag;
int pfd1[2], pfd2[2];
sigset_t newmask, oldmask, zeromask;

void err_doit(int errnoflag, const char *fmt, va_list ap)
{
    int errno_save;
    char buf[4096];

    errno_save = errno;
    vsprintf(buf, fmt, ap);

    if (errnoflag)
        sprintf(buf + strlen(buf), ": %s", strerror(errno_save));

    strcat(buf, "\n");

    fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);

    return;
}

void err_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);

    exit(1);
}

void sig_usr(int signo)
{
    sigflag = 1;

    return;
}

TELL_WAIT()
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)    /* SIGUSR1 为用户自定义信号 */
        err_sys("signal(SIGINT) error");

    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("signal(SIGQUIT) error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    /* 阻塞 SIGUSR1 和 SIGUSR2 并且保存当前信号掩码 */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("SIG_BLOCK error");
}    

void WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);    /* suspend()取消了所有信号屏蔽,等待父进程发来信号 */

    sigflag = 0;

    /* 恢复信号掩码 */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");
}

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return( fcntl(fd, cmd, &lock) );
}

void set_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        err_sys("fcntl F_GETFL error");

    val |= flags;    /* 置标志 */

    if (fcntl(fd, F_SETFL, val) < 0)
        err_sys("fcntl F_SETFL error");
}

void err_ret(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);

    return;
}

int main(void)
{
    int fd;
    pid_t pid;
    char buff[5];
    struct stat statbuf;

    if ((fd = open("templock", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
        err_sys("open error", buff);

    if (write(fd, "abcdef", 6) != 6)
        err_sys("write error");

    /* 打开 set-group-ID(s-gid), 并关闭组执行权限 */
    if (fstat(fd, &statbuf) < 0)
        err_sys("fstat error");

    if (fchmod(fd, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        err_sys("fork error");

    TELL_WAIT();
    if ( (pid = fork()) < 0) 
    {
        err_sys("fork error");
    }
    else if (pid > 0)    /* 父进程 */ 
    {
         /* 整个文件写锁 */
        if (lock_reg(fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0) < 0)
            err_sys("write_lock error");
            kill(pid, SIGUSR1);    /* 给子进程发送信号告知锁完成 */

        if (waitpid(pid, NULL, 0) < 0)
            err_sys("waitpid error");
    } 
    else 
    {
        WAIT_PARENT();    /* 等待父进程设置锁 */
        set_fl(fd, O_NONBLOCK);    
        if (lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) != -1)
            err_sys("child: read_lock succeeded");
        printf("read_lock of already-locked region return %d\n", errno);

        if (lseek(fd, 0, SEEK_SET) == -1)
            err_sys("lseek, error");

        if (read(fd, buff, 2) < 0)
            err_ret("read failed (mandatory locking wroks)");
        else
            printf("read OK (no mandatory locking), buff = %2.2s\n", buff);
    }

    exit(0);
}


