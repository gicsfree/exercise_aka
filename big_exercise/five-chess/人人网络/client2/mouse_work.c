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

extern chess_t recv_chessitem;
extern int recv_flag;
extern int draw_chess_flag;
extern int is_p_win;
extern int is_c_win;
extern int mouse_work_flag;

int m_x = 0;
int m_y = 0;
int p_x = 0;
int p_y = 0;

int chess[CHESS_X_NUM][CHESS_Y_NUM];
chess_t chess_item;
int send_flag = 0;
int win_flag = 0;

/* response of left button's work, get the mouse position */
chess_t p_get_chess_item(fb_info fb_inf, int x_start, int y_start)
{
    int iloop;
    int jloop;
    chess_t chessitem;

    chessitem.x = -1;
    chessitem.y = -1;

    for (iloop = 0; iloop < CHESS_Y_NUM; iloop++)
    {
        for (jloop = 0; jloop < CHESS_X_NUM; jloop++)
        {
            if ((m_x >= x_start + iloop * GRID_SIZE - CHESS_SIZE) && (m_x < x_start + iloop * GRID_SIZE + CHESS_SIZE)
               && (m_y >= y_start + jloop * GRID_SIZE - CHESS_SIZE) && (m_y < y_start + jloop * GRID_SIZE + CHESS_SIZE))
            {
                chessitem.x = jloop;
                chessitem.y = iloop;
                return chessitem; 
            }
        }
    }

    return chess_item;
}

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

/* mouse_work */
int mouse_work(fb_info fb_inf, int x_start, int y_start)
{
    int mfd = -1;
    u8_t buf[8];
    mouse_event_t mevent;

again:
    fb_draw_board(fb_inf, x_start, y_start);
    init_chess();

    m_x = fb_inf.w / 2;
    m_y = fb_inf.h / 2;
        
    mouse_open(NULL, &mfd);

    fb_save_cursor(fb_inf, m_x, m_y);
    p_x = m_x;   
    p_y = m_y;  
    fb_draw_cursor(fb_inf, m_x, m_y);
        
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

            switch (mevent.button)
            {
                case 1:
                    if ((win_flag == 0) && (mouse_work_flag == 1))
                    {
                        chess_item = p_get_chess_item(fb_inf, x_start, y_start);
                        if ((chess_item.x != -1) && (chess_item.y != -1) && (chess[chess_item.x][chess_item.y] == 0))
                        {
                            fb_draw_chess(fb_inf, x_start + chess_item.y * GRID_SIZE, y_start + chess_item.x * GRID_SIZE, CHESS_SIZE, WHITE_CHESS_COLOR);
                            fb_save_cursor(fb_inf, m_x, m_y); 
                            p_x = m_x;   
                            p_y = m_y;
                            send_flag = 1;
                        }
                    }
                    break;

                case 2:
                    if (win_flag == 1)
                     {
                        win_flag = 0;
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

        if (draw_chess_flag == 1)
        {
            draw_chess_flag = 0;
            fb_restore_cursor(fb_inf, p_x, p_y);
            fb_draw_chess(fb_inf, x_start + recv_chessitem.y * GRID_SIZE, y_start + recv_chessitem.x * GRID_SIZE, CHESS_SIZE, BLACK_CHESS_COLOR);
            if (is_p_win == 1)
            {
                is_p_win = 0;
                display_string_ch("你输了！", fb_inf.w / 3, fb_inf.h / 2, fb_inf, 0x0000FF00);
                win_flag = 1;
            }
            fb_save_cursor(fb_inf, m_x, m_y); 
            p_x = m_x;   
            p_y = m_y;
            fb_draw_cursor(fb_inf, m_x, m_y);
        }

        if (is_c_win == 1)
        {
            is_c_win = 0;
            display_string_ch("你赢了！", fb_inf.w / 3, fb_inf.h / 2, fb_inf, 0x0000FF00);
            fb_save_cursor(fb_inf, m_x, m_y); 
            p_x = m_x;   
            p_y = m_y;
            fb_draw_cursor(fb_inf, m_x, m_y);
            win_flag = 1;
        }
        usleep(30000);	
    }

    return 0;
}
