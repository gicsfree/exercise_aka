/* server.c */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    int n;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    Listen(listenfd, 20);

    while (1) 
    {
        cliaddr_len = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
        while (1)
        {
            n = Read(connfd, buf, MAXLINE);
            if (n == 0) 
            {
                break; //the other side has been closed
            }
            if (strcmp(buf, "pause") == 0)
            {
                Write(STDOUT_FILENO, "p\n", 2);
            }
        }
        Close(connfd);
    }
    Close(listenfd);

    return 0;
}
