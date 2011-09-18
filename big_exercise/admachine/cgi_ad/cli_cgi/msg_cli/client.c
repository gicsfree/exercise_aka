/* client.c */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cgi.h>

#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 6000

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd, n;

    cgi_init();
    cgi_process_form();
    cgi_init_headers();
    
    if (cgi_param("action") && cgi_param("message") && cgi_param("ip"))
    {
        sockfd = Socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, cgi_param("ip"), &servaddr.sin_addr);
        servaddr.sin_port = htons(SERV_PORT);    

        Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        strcpy(buf, cgi_param("message")); 
        Write(sockfd, buf, strlen(buf) + 1);
        Close(sockfd);
    }

    cgi_end();

    return 0;
}
