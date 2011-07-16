/* frame_client.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "wrap.h"

#define DEFAULT_PORT_TCP 5050
#define RECV_BUF_LEN 128
#define SEND_BUF_LEN 128
#define FRAME_NAME "frame.tar.gz"

/* the client send frame */
int main(int argc, const char *argv[])
{   
    int cPort = DEFAULT_PORT_TCP;
    int cClient;
    int cSend;
    int len;
    int frame_fd;
    char recv_buf[RECV_BUF_LEN];
    char send_buf[SEND_BUF_LEN];
    struct sockaddr_in cli;

    if (argc != 2)
    {
        printf("Usage: ./main 127.0.0.1\n");
        return -1;
    }
   
    memset(recv_buf, 0, sizeof(recv_buf));
    memset(send_buf, 0, sizeof(send_buf));
   
    cli.sin_family = AF_INET;
    cli.sin_port = htons(cPort);
    cli.sin_addr.s_addr = inet_addr(argv[1]);
   
    cClient = Socket(AF_INET, SOCK_STREAM, 0);
    if(cClient < 0)
    {
        printf("socket() failure!\n");
        return -1;
    }
   
    Connect(cClient, (struct sockaddr*)&cli, sizeof(cli)); 

    cSend = Send(cClient, FRAME_NAME, 20, 0);

    frame_fd = open(FRAME_NAME, O_RDONLY);
    if (frame_fd == -1)
    {
        perror("open frame");
        return -1;
    }

#if 1
    while (1)
    {   
        len = read(frame_fd, send_buf, sizeof(send_buf));
        Send(cClient, send_buf, len, 0);
        if (len == 0)
        {
            break;
        }
    }
#endif
    
    printf("update frame successfully !\n");
    close(frame_fd);
    Close(cClient);   

    return 0;
}
























