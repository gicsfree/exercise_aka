/* display-jpegs.c */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "frame.h"

#define JPEG_X_NUM 3
#define JPEG_Y_NUM 2

char jpegs[JPEG_X_NUM * JPEG_Y_NUM + 1][8] = {"2.jpg", "3.jpg", "4.jpg","5.jpg", "6.jpg", "7.jpg", "8.jpg"};

static int m_x;
static int m_y;
static int p_x;
static int p_y;
static int flag_p_left = -1;
static int flag_n_left = -1;
static int flag_is_big = 0;
static int flag_big_times = 0;

#ifdef FRAME_SUPPORT_JPEG
////////////////////////////////////////////////////////////////

#if 1
/* display jpegs when mouse work */
int display_jpeg_mouse(fb_info fb_inf)
{
    int mfd = -1;
    u8_t buf[8];
    mouse_event_t mevent;

    fb_info size_inf;
    fb_info bigger_size_inf;

    m_x = fb_inf.w / 2;
    m_y = fb_inf.h / 2;

    size_inf.w = fb_inf.w / (JPEG_X_NUM + 1);
    size_inf.h = fb_inf.h / (JPEG_Y_NUM + 1);

    bigger_size_inf.w = fb_inf.w / (JPEG_X_NUM );
    bigger_size_inf.h = fb_inf.h / (JPEG_Y_NUM );

    display_jpegs(fb_inf, size_inf);
        
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
	         fb_draw_cursor(fb_inf, m_x, m_y);
              }
            else
             {
	         m_x -= mevent.x;
	         m_y -= mevent.y;
             }

            jpeg_bigger(bigger_size_inf, size_inf, fb_inf);

	     switch (mevent.button)
              {
	         case 1:
                    mevent_button_left(size_inf, fb_inf);
		      break;

		  case 2:
		      break;
                     
		  case 3:
//		      printf("middle\n");
		      break;

		  default:
		      break;
	     }
	 }	
        usleep(5000);
     }

    return 0;
}
#endif

#if 1
int jpeg_bigger(fb_info bigger_size_inf, fb_info size_inf, fb_info fb_inf)
{
    int num;
    int iloop;
    int jloop;

    if (flag_is_big == 0)
    {
        for (jloop = 1; jloop < 2 * JPEG_Y_NUM; jloop += 2)
        {
            for (iloop = 1; iloop < 2 * JPEG_X_NUM; iloop += 2)
             {
                if ((m_x >= iloop * (fb_inf.w / (2 * JPEG_X_NUM)) - size_inf.w / 2) && m_x <= (iloop * (fb_inf.w / (2 * JPEG_X_NUM)) + size_inf.w / 2)
                    && (m_y >= jloop * (fb_inf.h / (2 * JPEG_Y_NUM)) - size_inf.h / 2) && (m_y <= jloop * (fb_inf.h / (2 * JPEG_Y_NUM)) + size_inf.h / 2))
                  {
                        num = iloop / 2 + JPEG_X_NUM * (jloop / 2);
                        display_jpeg_inner(jpegs[num], iloop * (fb_inf.w / (2 * JPEG_X_NUM)), jloop * (fb_inf.h / (2 * JPEG_Y_NUM)), bigger_size_inf, fb_inf);

                        fb_save_cursor(fb_inf, m_x, m_y); 
                        p_x = m_x;   
                        p_y = m_y;
                        fb_draw_cursor(fb_inf, m_x, m_y);

                } 
            }
        }
    }

    return 0;
}
#endif

#if 1
int mevent_button_left(fb_info size_inf, fb_info fb_inf)
{

    int iloop;
    int jloop;

    if (flag_is_big == 1)
    {
        flag_big_times++;
        if (flag_big_times == 2)
         {
            display_jpegs(fb_inf, size_inf);
 
            fb_save_cursor(fb_inf, m_x, m_y); 
            p_x = m_x;   
            p_y = m_y;
            fb_draw_cursor(fb_inf, m_x, m_y);

            flag_big_times = 0;
            flag_is_big = 0; 
        }  
    }
    else
    {
        for (jloop = 1; jloop < 2 * JPEG_Y_NUM; jloop += 2)
        {
            for (iloop = 1; iloop < 2 * JPEG_X_NUM; iloop += 2)
             {
                if ((m_x >= iloop * (fb_inf.w / (2 * JPEG_X_NUM)) - size_inf.w / 2) && m_x <= (iloop * (fb_inf.w / (2 * JPEG_X_NUM)) + size_inf.w / 2)
                    && (m_y >= jloop * (fb_inf.h / (2 * JPEG_Y_NUM)) - size_inf.h / 2) && (m_y <= jloop * (fb_inf.h / (2 * JPEG_Y_NUM)) + size_inf.h / 2))
                  {
                    flag_n_left = iloop / 2 + JPEG_X_NUM * (jloop / 2);
                    if (flag_p_left == flag_n_left)
                      {
                        display_jpeg(jpegs[flag_n_left], fb_inf);

                        fb_save_cursor(fb_inf, m_x, m_y); 
                        p_x = m_x;   
                        p_y = m_y;
                        fb_draw_cursor(fb_inf, m_x, m_y);

                        flag_is_big = 1;

                        flag_n_left = -1;
                        flag_p_left = -1;
                        }
                    else 
                      {
                        flag_p_left = flag_n_left;
                        flag_n_left = -1;
                      }
                } 
            }
        }
    }

    return 0;
}
#endif

#if 1
/* display jpegs */
int display_jpegs(fb_info fb_inf, fb_info size_inf)
{
    int num;
    int iloop;
    int jloop;

    display_jpeg(jpegs[JPEG_X_NUM * JPEG_Y_NUM], fb_inf);

    for (jloop = 1; jloop < 2 * JPEG_Y_NUM; jloop += 2)
    {
        for (iloop = 1; iloop < 2 * JPEG_X_NUM; iloop += 2)
        {
            num = iloop / 2 + JPEG_X_NUM * (jloop / 2);
            display_jpeg_inner(jpegs[num], iloop * (fb_inf.w / (2 * JPEG_X_NUM)), jloop * (fb_inf.h / (2 * JPEG_Y_NUM)), size_inf, fb_inf);
        }
    }

    return 0;
}
#endif

#if 1
/* display jpeg inner */
int display_jpeg_inner(const char *jpegname, int x, int y, fb_info size_inf, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int yloop;

    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, size_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, size_inf);
    
    for (yloop = 0; yloop < size_inf.h; yloop++)
    {
        for (xloop = 0; xloop < size_inf.w; xloop++)
        {
            xres = x - size_inf.w / 2 + xloop;
            yres = y - size_inf.h / 2 + yloop;

            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
             {
                fb_pixel(fb_inf, xres, yres, buf32[xloop + yloop * size_inf.w]);
             }
        }
    }
        
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#endif
