/* client.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cgi.h>

#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 7000

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd;
    int file_fd;
    int n;
    char filename[MAXLINE] = "../../video/";

    cgi_init();
    cgi_process_form();
    cgi_init_headers();
 
    if (cgi_param("action") && cgi_param("file"))
    {
        strcat(filename, cgi_param("file"));
        printf("%s", filename);   

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);
    
    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    Write(sockfd, filename, strlen(filename) + 1);

    file_fd = open(filename, O_RDONLY);
    if (file_fd == -1)
    {
        perror("open file");
        exit(1);
    }
 
    while ((n = Read(file_fd, buf, sizeof(buf))) != 0)
    {
        Write(sockfd, buf, n);
    }

    Close(file_fd);
    Close(sockfd);
    printf("success");
    }

    cgi_end();

    return 0;
}
