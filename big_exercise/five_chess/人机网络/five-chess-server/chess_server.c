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

int win_flag = 0;
chess_t chess_item;

int ptable[CHESS_X_NUM][CHESS_Y_NUM][WIN_SUM];
int ctable[CHESS_X_NUM][CHESS_Y_NUM][WIN_SUM];
int cgrades[CHESS_X_NUM][CHESS_Y_NUM];
int pgrades[CHESS_X_NUM][CHESS_Y_NUM];
int cgrade;
int pgrade;
int win[2][WIN_SUM];
int chess[CHESS_X_NUM][CHESS_Y_NUM];

void init_game(void)
{
    int iloop; 
    int jloop;
    int kloop;
    int win_count = 0; 
			
    for (iloop = 0; iloop < CHESS_X_NUM; iloop++)
    {
        for (jloop = 0; jloop < CHESS_Y_NUM; jloop++)
        {
            pgrades[iloop][jloop] = 0;
            cgrades[iloop][jloop] = 0;
            chess[iloop][jloop] = 0;
        }
    }
			
    for (iloop = 0; iloop < CHESS_Y_NUM; iloop++)
    {
        for (jloop = 0; jloop < CHESS_X_NUM - GAME_CHESS_NUM + 1; jloop++)
        {
            for (kloop = 0; kloop < GAME_CHESS_NUM; kloop++)
            {
                ptable[jloop + kloop][iloop][win_count] = 1;
                ctable[jloop + kloop][iloop][win_count] = 1;
            }
            win_count++;
        }
    }
			
    for (iloop = 0; iloop < CHESS_X_NUM; iloop++)
    {
        for (jloop = 0;jloop < CHESS_Y_NUM - GAME_CHESS_NUM + 1; jloop++)
        {
            for (kloop = 0; kloop < GAME_CHESS_NUM; kloop++)
            {
                ptable[iloop][jloop + kloop][win_count] = 1;
                ctable[iloop][jloop + kloop][win_count] = 1;
            }
            win_count++;
        }
    }	
		
    for (iloop = 0; iloop < CHESS_Y_NUM - GAME_CHESS_NUM + 1; iloop++)
    {
        for (jloop = 0; jloop < CHESS_X_NUM - GAME_CHESS_NUM + 1; jloop++)
        {
            for(kloop = 0; kloop < GAME_CHESS_NUM; kloop++)
            {
                ptable[jloop + kloop][iloop + kloop][win_count] = 1;
                ctable[jloop + kloop][iloop + kloop][win_count] = 1;
            }
            win_count++;
        }
    }	
		
    for (iloop = 0; iloop < CHESS_Y_NUM - GAME_CHESS_NUM + 1; iloop++)
    {
        for (jloop = CHESS_X_NUM - 1; jloop >= GAME_CHESS_NUM - 1; jloop--)
        {
            for (kloop = 0; kloop < GAME_CHESS_NUM; kloop++)
            {
                ptable[jloop - kloop][iloop + kloop][win_count] = 1;
                ctable[jloop - kloop][iloop + kloop][win_count] = 1;
            }
            win_count++;
        }
    }

    for (iloop = 0;iloop <= 1; iloop++)  
    {
        for (jloop = 0; jloop < WIN_SUM; jloop++)
        {
            win[iloop][jloop] = 0;
        }
    }
}


chess_t c_get_chess_item(void)
{
    int iloop;
    int jloop;
    int kloop;
    int cx_max = -1;
    int cy_max = -1;
    int px_max = -1;
    int py_max = -1;
    chess_t chessitem;

    cgrade = 0;		
    pgrade = 0;
  
    for (iloop = 0; iloop < CHESS_X_NUM; iloop++)
    {     
        for (jloop = 0; jloop < CHESS_Y_NUM; jloop++)
        {               
            if (chess[iloop][jloop] == 0)  
            {
                pgrades[iloop][jloop] = 0; 
                cgrades[iloop][jloop] = 0; 
                for (kloop = 0; kloop < WIN_SUM; kloop++)
                {   
                    if (ptable[iloop][jloop][kloop] == 1)
                    {
                        switch(win[0][kloop])
                        {   
                            case 1: 
                                pgrades[iloop][jloop] += 5;
                                break;

                            case 2: 
                                pgrades[iloop][jloop] += 50;
                                break;

                            case 3: 
                                pgrades[iloop][jloop] += 180;
                                break;

                            case 4: 
                                pgrades[iloop][jloop] += 400;
                                break;
                        }
                    }
            
                    if(ctable[iloop][jloop][kloop] == 1)
                    {
                        switch(win[1][kloop])
                        {  
                            case 1:  
                                cgrades[iloop][jloop] += 5;
                                break;

                            case 2:  
                                cgrades[iloop][jloop] += 50;
                                break;

                            case 3: 
                                cgrades[iloop][jloop] += 180;
                                break;

                            case 4:  
                                cgrades[iloop][jloop] += 400;
                                break;
                        }
                    }
                }
            }
        }
    }
			
    for (iloop = 0; iloop < CHESS_X_NUM; iloop++)
    {
        for (jloop = 0; jloop < CHESS_Y_NUM; jloop++)
        {
            if (chess[iloop][jloop] == 0)
            {  
                if (cgrades[iloop][jloop] >= cgrade)
                {
                    cgrade = cgrades[iloop][jloop];   
                    cx_max = iloop;
                    cy_max = jloop;
                }
                if(pgrades[iloop][jloop] >= pgrade)
                {
                    pgrade = pgrades[iloop][jloop];   
                    px_max = iloop;
                    py_max = jloop;
                }
            }
        }
    }

    if (cgrade >= pgrade)
    {   
        chessitem.x = cx_max;
        chessitem.y = cy_max;
    }
    else
    {
        chessitem.x = px_max;
        chessitem.y = py_max;
    }

    return chessitem;
} 

#if 0
void change_chess(chess_t chess_item, int chess_value)
{
    int kloop;
    
    if (chess_value == 1)
    {
        chess[chess_item.x][chess_item.y] = 1;
        for (kloop = 0; kloop < WIN_SUM; kloop++)
        {
            if (ptable[chess_item.x][chess_item.y][kloop] == 1)
            {
                win[0][kloop]++;     
                ctable[chess_item.x][chess_item.y][kloop] = 0;
                win[1][kloop] = 0;
            }
        }
    }
    else
    {
        chess[chess_item.x][chess_item.y] = 2;
        for (kloop = 0; kloop < WIN_SUM; kloop++)
        {
            if ((ctable[chess_item.x][chess_item.y][kloop] == 1))
            {
                win[1][kloop]++;     
                ptable[chess_item.x][chess_item.y][kloop] = 0;
                win[0][kloop] = 0;
            }
        }
    }
}

#else
void change_chess(chess_t chessitem, int chess_value)
{
    int kloop;
    
    if (chess_value == 1)
    {
        chess[chessitem.x][chessitem.y] = 1;
        for (kloop = 0; kloop < WIN_SUM; kloop++)
        {
            if ((ptable[chessitem.x][chessitem.y][kloop] == 1) && win[0][kloop] != 7)
            {
                win[0][kloop]++;     
            }
            if (ctable[chessitem.x][chessitem.y][kloop] == 1)
            {
                ctable[chessitem.x][chessitem.y][kloop] = 0;
                win[1][kloop] = 7;
            }
        }
    }
    else
    {
        chess[chessitem.x][chessitem.y] = 2;
        for (kloop = 0; kloop < WIN_SUM; kloop++)
        {
            if ((ctable[chessitem.x][chessitem.y][kloop] == 1) && win[1][kloop] != 7)
            {
                win[1][kloop]++;     
            }
            if (ptable[chessitem.x][chessitem.y][kloop] == 1)
            {
                ptable[chessitem.x][chessitem.y][kloop] = 0;
                win[0][kloop] = 7;
            }
        }
    }
}
#endif

int is_win(int who)
{
    int iloop;

    for (iloop = 0; iloop < WIN_SUM; iloop++)
    {
        if (win[who][iloop] == GAME_CHESS_NUM)
        {
            win_flag = 1;
            return 1;
        }
    }
    
    return 0;
}

/* tcp receive the chessitem */
int tcp_recv_chessitem(void)
{
    int sPort = DEFAULT_PORT_TCP;
    int sListen = 0;
    int sAccept = 0;
    unsigned int sLen = 0;
    struct sockaddr_in ser;
    struct sockaddr_in cli;
    pid_t pid;

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
        sAccept = Accept(sListen, (struct sockaddr*)&cli, (unsigned int*)&sLen);
   
//        printf("accept() client IP: [%s]\n", (char*)inet_ntoa(cli.sin_addr));
//        printf("accept() client PORT: [%d]\n", ntohs(cli.sin_port)); 

        if ((pid = fork()) > 0)
        {
            Close(sAccept);
            continue;
        }
        else if(pid == 0)
        {
            Close(sListen);
again:
            init_game();

            while (1)
            {   
                Recv(sAccept, &chess_item, sizeof(chess_item), 0);
                printf("recv: %d %d\n", chess_item.x, chess_item.y);
                change_chess(chess_item, 1);
                if (is_win(0) == 1)
                 {
                    goto again;
                 }
                chess_item = c_get_chess_item();
                change_chess(chess_item, 2);
                Send(sAccept, &chess_item, sizeof(chess_t), 0);
                printf("send: %d %d\n", chess_item.x, chess_item.y);
                if (is_win(1) == 1)
                {
                    goto again;
                }
            }
            exit(0);
        }
        else 
        {
            perror("fork error\n");
            exit(0);
        }
    }

    Close(sListen);
   
    return 0;
}



