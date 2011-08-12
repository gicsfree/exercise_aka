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
#include "frame.h"

#define DEFAULT_PORT_TCP 5050

extern int chess[CHESS_X_NUM][CHESS_Y_NUM];
extern chess_t chess_item;
extern int send_flag;

extern int is_win(int who);

int mouse_work_flag = 0;
int draw_chess_flag = 0;
chess_t recv_chessitem;
int recv_flag = 0;
int is_p_win = 0;
int is_c_win = 0;

/* the client send and receive chessitem */
int tcp_send_chessitem(const char *addr)
{   
    int cPort = DEFAULT_PORT_TCP;
    int cClient;
    struct sockaddr_in cli;
   
    cli.sin_family = AF_INET;
    cli.sin_port = htons(cPort);
    cli.sin_addr.s_addr = inet_addr(addr);
   
    cClient = Socket(AF_INET, SOCK_STREAM, 0);
    if(cClient < 0)
    {
        printf("socket() failure!\n");
        return -1;
    }
   
    Connect(cClient, (struct sockaddr*)&cli, sizeof(cli));

again:
    while (1)
    {   
        Recv(cClient, &recv_chessitem, sizeof(recv_chessitem), 0);
        chess[recv_chessitem.x][recv_chessitem.y] = 1;
        draw_chess_flag = 1;
        if (is_win(1) == 1)
        {
            is_p_win = 1;
            mouse_work_flag = 0;
            goto again;
        }
        mouse_work_flag = 1;

        while (send_flag == 0)
        {
            ;
        }
        mouse_work_flag = 0;
        send_flag = 0;
        Send(cClient, &chess_item, sizeof(chess_item), 0);
        chess[chess_item.x][chess_item.y] = 2;
        if (is_win(2) == 1)
        {
            is_c_win = 1;
            mouse_work_flag = 0;
            goto again;
        }
    }
    
    Close(cClient);   

    return 0;
}
























