/* server.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

/* send qq message */
void qq_send_msg(void *connfd)
{
    char buf[MAXLINE];
    int n;

    while (1)
    {
        n = Read(((int *)connfd)[1], buf, MAXLINE);
        if (n == 0) 
        {
            printf("the other side has been closed.\n");
            Close(((int *)connfd)[0]);
            Close(((int *)connfd)[1]);
            exit(0);
        }    
        Write(((int *)connfd)[0], buf, n);
    }
}

/* communicate betwen two clients */
void communicate(int connfd[2])
{
    char buf[MAXLINE];
    int n;
    int ret;
    pthread_t qqsend;

    ret = pthread_create(&qqsend, NULL, (void *)qq_send_msg, (void *)connfd);
    if (ret != 0) 
    {
        fprintf(stderr, "can't create thread: %s\n", strerror(ret));
        exit(1);
    }

    while (1)
    {
        n = Read(connfd[0], buf, MAXLINE);
        if (n == 0) 
        {
            printf("the other side has been closed.\n");
            Close(connfd[0]);
            Close(connfd[1]);
            exit(0);
        }    
        Write(connfd[1], buf, n);
    } 

    pthread_join(qqsend, NULL);
}

/* action when receive SIGCHLD */
void sigchld_handler(int signo)
{
    wait(NULL);
    printf("child process exited\n");
}

/* main */
int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd[2];
    int cnt = 0;
    pid_t pid;
    struct sigaction act;

    act.sa_handler = sigchld_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, NULL);

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    Listen(listenfd, 20);

    printf("Accepting connections ...\n");
    while (1) 
    {
        cliaddr_len = sizeof(cliaddr);
        connfd[cnt++] = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
        if (cnt == 2)
        {
            cnt = 0;
            pid = fork();
            if (pid < 0)
            {
                perror("fork():");
                exit(1);
            }
            if (pid > 0)
            {
                Close(connfd[0]);
                Close(connfd[1]);
            }
            else
            {
                Close(listenfd);
                communicate(connfd); 
                Close(connfd[0]);
                Close(connfd[1]);
                exit(0);  
            }
        }
    }
    Close(listenfd);

    return 0;
}

#if 0
int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    int i, n;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    Listen(listenfd, 20);

    printf("Accepting connections ...\n");
    while (1) 
    {
        cliaddr_len = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
        while (1)
        {
            n = Read(connfd, buf, MAXLINE);
            if (n == 0) 
            {
                printf("the other side has been closed.\n");
                break;
            }
            printf("received from %s at PORT %d\n",
            inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
    
            for (i = 0; i < n; i++)
            {
                buf[i] = toupper(buf[i]);
            }
            Write(connfd, buf, n);
        }
        Close(connfd);
    }
    Close(listenfd);
}
#endif
