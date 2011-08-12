/* chess_server.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <math.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "frame.h"
#include "wrap.h"

#define DEFAULT_PORT_TCP 5050

int chess[CHESS_X_NUM][CHESS_Y_NUM];

/* judge who win */
int is_win(int who)  
{  
    int iloop, jloop, kloop;  

    for (iloop = 0; iloop < CHESS_X_NUM; iloop++) 
    {  
        for (jloop = 0; jloop <  CHESS_Y_NUM; jloop++) 
        {  
            if (chess[iloop][jloop] != who) 
            {  
                continue;   
            } 
            else 
            {  
                for (kloop = 1; (chess[iloop + kloop][jloop] == who) && (iloop < CHESS_X_NUM - GAME_CHESS_NUM + 1); ) 
                {  
                    kloop++;  
                    if (kloop == GAME_CHESS_NUM)
                    {  
                        return 1;  
                    }                     
                }  
                 
                for (kloop = 1; (chess[iloop][jloop + kloop] == who) && (jloop < CHESS_Y_NUM - GAME_CHESS_NUM + 1); ) 
                {  
                    kloop++;  
                    if (kloop == GAME_CHESS_NUM)
                    {  
                        return 1;  
                    }  
                }  
  
                 
                for (kloop = 1; (chess[iloop + kloop][jloop + kloop] == who) && (iloop < CHESS_X_NUM - GAME_CHESS_NUM + 1) && (jloop < CHESS_Y_NUM - GAME_CHESS_NUM + 1); ) 
                {  
                    kloop++;  
                    if (kloop == GAME_CHESS_NUM)
                    {  
                        return 1;  
                    }  
                }  
                  
                for (kloop = 1; (chess[iloop - kloop][jloop + kloop] == who) && iloop > (GAME_CHESS_NUM - 2) && (jloop < CHESS_Y_NUM - GAME_CHESS_NUM + 1); ) 
                {  
                    kloop++;  
                    if (kloop == GAME_CHESS_NUM)
                    {  
                        return 1;  
                    }  
                }  
            }  
        }  
    } 
 
    return 0;  
}

/* init the chess array */
void init_chess(void)
{
    int iloop;
    int jloop;

    for (iloop = 0; iloop < CHESS_X_NUM; iloop++)
    {
        for (jloop = 0; jloop < CHESS_Y_NUM; jloop++)
       {
            chess[iloop][jloop] = 0;
       }
    }
}

/* tcp receive the chessitem */
int tcp_recv_chessitem(void)
{
    int sPort = DEFAULT_PORT_TCP;
    int sListen = 0;
    int sAccept[2] = {0};
    unsigned int sLen = 0;
    struct sockaddr_in ser;
    struct sockaddr_in cli;
    pid_t pid;

    int cnt = 0;
    chess_t chess_item;

    printf("Server waiting...\n");
   
    sListen = Socket(AF_INET, SOCK_STREAM, 0);
    if (sListen < 0)
    {
        printf("socket() failure!\n");
        return -1;
    }
   
    ser.sin_family = AF_INET;
    ser.sin_port = htons(sPort);
    ser.sin_addr.s_addr = htonl(INADDR_ANY);
   
    Bind(sListen, (struct sockaddr*)&ser, sizeof(ser));
    Listen(sListen, 5); 

    while(1)
    {
        sLen = sizeof(cli);
        sAccept[cnt] = Accept(sListen, (struct sockaddr*)&cli, (unsigned int*)&sLen);
        cnt++;
        if (cnt == 2)
        {
            cnt = 0;
            pid = fork();
            if (pid > 0)
            {
                Close(sAccept[0]);
                Close(sAccept[1]);
                continue;
            }
            else if(pid == 0)
            {
                Close(sListen);
again:
                init_chess();
                while (1)
                {
                    Recv(sAccept[0], &chess_item, sizeof(chess_item), 0);
                    printf("recv0: %d %d\n", chess_item.x, chess_item.y);
                    Send(sAccept[1], &chess_item, sizeof(chess_item), 0);
                    printf("send1: %d %d\n", chess_item.x, chess_item.y);
                    chess[chess_item.x][chess_item.y] = 1;
                    if (is_win(1) == 1)
                    {
                        goto again;
                    }
                    Recv(sAccept[1], &chess_item, sizeof(chess_item), 0);
                    printf("recv1: %d %d\n", chess_item.x, chess_item.y);
                    Send(sAccept[0], &chess_item, sizeof(chess_item), 0);
                    printf("send0: %d %d\n", chess_item.x, chess_item.y);
                    chess[chess_item.x][chess_item.y] = 2;
                    if (is_win(2) == 1)
                    {
                        goto again;
                    }
                }
                Close(sAccept[0]);
                Close(sAccept[1]);
            }          
            else 
            {
                perror("fork error\n");
                exit(0);
            }
        }
    }

    Close(sListen);
   
    return 0;
}








