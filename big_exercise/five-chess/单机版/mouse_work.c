/* mouse_work.c */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "frame.h"

int m_x = 0;
int m_y = 0;
int p_x = 0;
int p_y = 0;
int win_flag = 0;

typedef struct chess 
{
    int x;
    int y;
} chess_t;

int ptable[CHESS_X_NUM][CHESS_Y_NUM][WIN_SUM];
int ctable[CHESS_X_NUM][CHESS_Y_NUM][WIN_SUM];
int cgrades[CHESS_X_NUM][CHESS_Y_NUM];
int pgrades[CHESS_X_NUM][CHESS_Y_NUM];
int cgrade;
int pgrade;
int win[2][WIN_SUM];
int chess[CHESS_X_NUM][CHESS_Y_NUM];

/* init the game */
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

/* computer get chessitem */
chess_t c_get_chess_item(void)
{
    int iloop;
    int jloop;
    int kloop;
    int cx_max = -1;
    int cy_max = -1;
    int px_max = -1;
    int py_max = -1;
    chess_t chess_item;

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
        chess_item.x = cx_max;
        chess_item.y = cy_max;
    }
    else
    {
        chess_item.x = px_max;
        chess_item.y = py_max;
    }

    return chess_item;
} 

/* change chess array */
void change_chess(chess_t chess_item, int chess_value)
{
    int kloop;
    
    if (chess_value == 1)
    {
        chess[chess_item.x][chess_item.y] = 1;
        for (kloop = 0; kloop < WIN_SUM; kloop++)
        {
            if ((ptable[chess_item.x][chess_item.y][kloop] == 1) && win[0][kloop] != 7)
            {
                win[0][kloop]++;     
            }
            if (ctable[chess_item.x][chess_item.y][kloop] == 1)
            {
                ctable[chess_item.x][chess_item.y][kloop] = 0;
                win[1][kloop] = 7;
            }
        }
    }
    else
    {
        chess[chess_item.x][chess_item.y] = 2;
        for (kloop = 0; kloop < WIN_SUM; kloop++)
        {
            if ((ctable[chess_item.x][chess_item.y][kloop] == 1) && win[1][kloop] != 7)
            {
                win[1][kloop]++;     
            }
            if (ptable[chess_item.x][chess_item.y][kloop] == 1)
            {
                ptable[chess_item.x][chess_item.y][kloop] = 0;
                win[0][kloop] = 7;
            }
        }
    }
}

/* response of left button's work, get the mouse position */
chess_t p_get_chess_item(fb_info fb_inf, int x_start, int y_start)
{
    int iloop;
    int jloop;
    chess_t chess_item;

    chess_item.x = -1;
    chess_item.y = -1;

    for (iloop = 0; iloop < CHESS_Y_NUM; iloop++)
    {
        for (jloop = 0; jloop < CHESS_X_NUM; jloop++)
        {
            if ((m_x >= x_start + iloop * GRID_SIZE - CHESS_SIZE) && (m_x < x_start + iloop * GRID_SIZE + CHESS_SIZE)
               && (m_y >= y_start + jloop * GRID_SIZE - CHESS_SIZE) && (m_y < y_start + jloop * GRID_SIZE + CHESS_SIZE))
            {
                chess_item.x = jloop;
                chess_item.y = iloop;
                return chess_item; 
            }
        }
    }

    return chess_item;
}

/* judge who win */
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

/* mouse_work */
int mouse_work(fb_info fb_inf, int x_start, int y_start)
{
    int mfd = -1;
    u8_t buf[8];
    mouse_event_t mevent;

    int play_flag = 0;
    chess_t chess_item;

again:
    fb_draw_board(fb_inf, x_start, y_start);
    m_x = fb_inf.w / 2;
    m_y = fb_inf.h / 2;
        
    mouse_open(NULL, &mfd);

    fb_save_cursor(fb_inf, m_x, m_y);
    p_x = m_x;   
    p_y = m_y;  
    fb_draw_cursor(fb_inf, m_x, m_y);

    init_game();
        
    for(;;)
     {
        if (read(mfd, buf, sizeof(buf)) != -1)
         {
            mouse_parse(buf, &mevent);

            m_x += mevent.x;
            m_y += mevent.y;
                           
            if((m_x >= 0) && (m_x < fb_inf.w - C_WIDTH) && (m_y >= 0) && (m_y < fb_inf.h - C_HEIGHT))
              {
                fb_restore_cursor(fb_inf, p_x, p_y);
                fb_save_cursor(fb_inf, m_x, m_y); 
                p_x = m_x;   
                p_y = m_y;
//                fb_draw_cursor(fb_inf, m_x, m_y);
              }
            else
             {
                m_x -= mevent.x;
                m_y -= mevent.y;
             }

            if (play_flag == 1)
            {
                chess_item = c_get_chess_item();
                change_chess(chess_item, 2);
                play_flag = 0;
                fb_draw_chess(fb_inf, x_start + chess_item.y * GRID_SIZE, y_start + chess_item.x * GRID_SIZE, CHESS_SIZE, WHITE_CHESS_COLOR);
                fb_save_cursor(fb_inf, m_x, m_y); 
                p_x = m_x;   
                p_y = m_y;	
                if (is_win(1) == 1)
                {
                    display_string_ch("你输了！", fb_inf.w / 3, fb_inf.h / 2, fb_inf, 0x0000FF00);
                    fb_save_cursor(fb_inf, m_x, m_y); 
                    p_x = m_x;   
                    p_y = m_y;
                    play_flag = -1;
                }							
            }

            switch (mevent.button)
            {
                case 1:
                    if (play_flag == 0)
                     {
                        chess_item = p_get_chess_item(fb_inf, x_start, y_start);
                        if ((chess_item.x != -1) && (chess_item.y != -1) && (chess[chess_item.x][chess_item.y] == 0))
                          {
                            change_chess(chess_item, 1);
                            play_flag = 1;
                            fb_draw_chess(fb_inf, x_start + chess_item.y * GRID_SIZE, y_start + chess_item.x * GRID_SIZE, CHESS_SIZE, BLACK_CHESS_COLOR);
                            if (is_win(0) == 1)
                              {
                                display_string_ch("你赢了！", fb_inf.w / 3, fb_inf.h / 2, fb_inf, 0x0000FF00);
                                play_flag = -1;
                              }
                            fb_save_cursor(fb_inf, m_x, m_y); 
                            p_x = m_x;   
                            p_y = m_y;
                          }
                      }
                    break;

                case 2:
                    if (win_flag == 1)
                    {
                        win_flag = 0;
                        play_flag = 0;
                        goto again;
                    }
                    break;
                     
                case 3:
                    break;

                default:
                    break;
            }
        fb_draw_cursor(fb_inf, m_x, m_y);
        }	
    usleep(30000);
    }

    return 0;
}
