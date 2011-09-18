/* server.c */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 7000

int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    int file_fd;
    int n;
    char filename[MAXLINE] = "../video";
    char *file = NULL;

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

        Read(connfd, buf, sizeof(buf));
        file = strrchr(buf, '/');
        strcat(filename, file);
        printf("%s\n", filename);
        file_fd = open(filename, O_WRONLY|O_CREAT, 0666);
        if (file_fd == -1)
        {
            perror("open file");
            exit(1);
        }  
        while ((n = Read(connfd, buf, sizeof(buf))) != 0)
        {
            Write(file_fd, buf, n);
        }

        Close(file_fd);             
        Close(connfd);
    }
    Close(listenfd);
}
