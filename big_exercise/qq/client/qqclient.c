/* client.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

/* send qq message */
void qq_send_msg(void *sockfd)
{
    char buf[MAXLINE];

    while (fgets(buf, MAXLINE, stdin) != NULL) 
    {
        Write(*(int *)sockfd, buf, strlen(buf));
    }
}

/* communicate betwen two clients */
void communicate(int sockfd)
{
    char buf[MAXLINE];
    int n;
    int ret;
    pthread_t qqsend;

    ret = pthread_create(&qqsend, NULL, (void *)qq_send_msg, (void *)&sockfd);
    if (ret != 0) 
    {
        fprintf(stderr, "can't create thread: %s\n", strerror(ret));
        exit(1);
    }

    while (1) 
    {
        n = Read(sockfd, buf, MAXLINE);
        if (n == 0)
        {
            printf("the other side has been closed.\n");
            return;
        }
        else
        {
            Write(STDOUT_FILENO, buf, n);
        }
    }

    pthread_join(qqsend, NULL);
}

/* main */
int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    int sockfd;

    if (argc != 2)
    {
        printf("Usage: ./qqclient server_address\n");
        return -1;
    }
    
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);
    
    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    communicate(sockfd);
    Close(sockfd);

    return 0;
}

#if 0
int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd, n;
    
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);
    
    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (fgets(buf, MAXLINE, stdin) != NULL) 
    {
        Write(sockfd, buf, strlen(buf));
        n = Read(sockfd, buf, MAXLINE);
        if (n == 0)
        {
            printf("the other side has been closed.\n");
        }
        else
        {
            Write(STDOUT_FILENO, buf, n);
        }
    }

    Close(sockfd);

    return 0;
}
#endif
