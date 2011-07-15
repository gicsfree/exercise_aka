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

#if 0
#define JPEG_X_NUM 3
#define JPEG_Y_NUM 2

char jpegs[JPEG_X_NUM * JPEG_Y_NUM + 1][8] = {"2.jpg", "3.jpg", "4.jpg","5.jpg", "6.jpg", "7.jpg", "8.jpg"};
#endif

#if 1
#define JPEG_X_NUM 4
#define JPEG_Y_NUM 3

char jpegs[JPEG_X_NUM * JPEG_Y_NUM + 1][8] = {"1.jpg", "22.jpg", "3.jpg", "4.jpg","5.jpg", "6.jpg", "7.jpg", "9.jpg", "10.jpg", "11.jpg", "12.jpg", "13.jpg", "8.jpg"};
#endif

#if 0
#define JPEG_X_NUM 7
#define JPEG_Y_NUM 5
char jpegs[JPEG_X_NUM * JPEG_Y_NUM + 1][8] = {"2.jpg", "3.jpg", "4.jpg","5.jpg", "6.jpg", "7.jpg", "8.jpg","1.jpg", "9.jpg", "10.jpg","11.jpg", "12.jpg", "13.jpg", "14.jpg"
                                              , "15.jpg", "16.jpg", "17.jpg","18.jpg", "19.jpg", "20.jpg", "21.jpg","22.jpg", "21.jpg", "20.jpg","19.jpg"
                                              , "18.jpg", "17.jpg",  "16.jpg","15.jpg", "14.jpg", "13.jpg","12.jpg", "11.jpg", "10.jpg", "9.jpg", "8.jpg"}; 
#endif

static int m_x;
static int m_y;
static int p_x;
static int p_y;
static int button_left_pre_flag = -1;
static int button_left_now_flag = -1;
static int jpeg_is_big_flag = 0;
static int jpeg_big_button_left_times = 0;
static int jpeg_is_bigger_flag = 0;
static int mouse_response_time = 0;

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

    bigger_size_inf.w = fb_inf.w / JPEG_X_NUM;
    bigger_size_inf.h = fb_inf.h / JPEG_Y_NUM;

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
//	         fb_draw_cursor(fb_inf, m_x, m_y);
              }
            else
             {
	         m_x -= mevent.x;
	         m_y -= mevent.y;
             }

            jpeg_bigger(bigger_size_inf, size_inf, fb_inf);

	     fb_draw_cursor(fb_inf, m_x, m_y);

	     switch (mevent.button)
              {
	         case 1:
                    if (jpeg_is_bigger_flag == 0)
                      {
                        mevent_button_left(size_inf, size_inf, fb_inf);
                      }
                    else
                      {
                        mevent_button_left(bigger_size_inf, size_inf, fb_inf);
                      }
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
        usleep(300);
#if 1
        mouse_response_time++;
        if (mouse_response_time == 300)
        {
            mouse_response_time = 0;
            jpeg_big_button_left_times = 0;
            button_left_pre_flag = -1;
            button_left_now_flag = -1;             
        }
#endif
     }

    return 0;
}
#endif

#if 1
/* jpeg bigger */
int jpeg_bigger(fb_info bigger_size_inf, fb_info size_inf, fb_info fb_inf)
{
    int num;
    int iloop;
    int jloop;
    int flag_mouse_in_bigger;
    static int p_iloop;
    static int p_jloop;

    if (jpeg_is_big_flag == 0)
    {
        if (jpeg_is_bigger_flag == 0)
         {
            for (jloop = 1; jloop < 2 * JPEG_Y_NUM; jloop += 2)
            {
                for (iloop = 1; iloop < 2 * JPEG_X_NUM; iloop += 2)
                 {
                    if ((m_x >= iloop * (fb_inf.w / (2 * JPEG_X_NUM)) - size_inf.w / 2) && m_x <= (iloop * (fb_inf.w / (2 * JPEG_X_NUM)) + size_inf.w / 2)
                        && (m_y >= jloop * (fb_inf.h / (2 * JPEG_Y_NUM)) - size_inf.h / 2) && (m_y <= jloop * (fb_inf.h / (2 * JPEG_Y_NUM)) + size_inf.h / 2))
                      {
                        num = iloop / 2 + JPEG_X_NUM * (jloop / 2);
                        display_bigger_jpeg_inner(jpegs[num], iloop * (fb_inf.w / (2 * JPEG_X_NUM)), jloop * (fb_inf.h / (2 * JPEG_Y_NUM)), bigger_size_inf, fb_inf);

                        fb_save_cursor(fb_inf, m_x, m_y); 
                        p_x = m_x;   
                        p_y = m_y;
                        fb_draw_cursor(fb_inf, m_x, m_y);

                        p_iloop = iloop;
                        p_jloop = jloop;

                        jpeg_is_bigger_flag = 1;

                        break;
                      } 
                }
           }
     }
        else
        {
            flag_mouse_in_bigger = 0;

            if ((m_x >= p_iloop * (fb_inf.w / (2 * JPEG_X_NUM)) - bigger_size_inf.w / 2) && m_x <= (p_iloop * (fb_inf.w / (2 * JPEG_X_NUM)) + bigger_size_inf.w / 2)
                && (m_y >= p_jloop * (fb_inf.h / (2 * JPEG_Y_NUM)) - bigger_size_inf.h / 2) && (m_y <= p_jloop * (fb_inf.h / (2 * JPEG_Y_NUM)) + bigger_size_inf.h / 2))
            {
                flag_mouse_in_bigger = 1;
            }

            if (flag_mouse_in_bigger == 0)
            {
                display_jpeg_local(p_iloop, p_jloop, bigger_size_inf, fb_inf); 
                num = p_iloop / 2 + JPEG_X_NUM * (p_jloop / 2);
                display_jpeg_inner(jpegs[num], p_iloop * (fb_inf.w / (2 * JPEG_X_NUM)), p_jloop * (fb_inf.h / (2 * JPEG_Y_NUM)), size_inf, fb_inf);

                fb_save_cursor(fb_inf, m_x, m_y); 

                jpeg_is_bigger_flag = 0; 
             }
        }
    }

    return 0;
}
#endif

#if 1
/* display jpeg in local */
int display_jpeg_local(int p_iloop, int p_jloop, fb_info bigger_size_inf, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int yloop;

    u8_t *buf24 = decode_jpeg(jpegs[JPEG_X_NUM * JPEG_Y_NUM], &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (yloop = 0; yloop < bigger_size_inf.h; yloop++)
    {
        for (xloop = 0; xloop < bigger_size_inf.w; xloop++)
        {
            xres = p_iloop * (fb_inf.w / (2 * JPEG_X_NUM)) - bigger_size_inf.w / 2 + xloop;
            yres = p_jloop * (fb_inf.h / (2 * JPEG_Y_NUM)) - bigger_size_inf.h / 2 + yloop;

            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
             {
                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
             }
        }
    }
        
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
} 
#endif

#if 1
/* response of left button's work */
int mevent_button_left(fb_info size_inf, fb_info small_size_inf, fb_info fb_inf)
{

    int iloop;
    int jloop;

    mouse_response_time = 0;

    if (jpeg_is_big_flag == 1)
    {
        jpeg_big_button_left_times++;
        if (jpeg_big_button_left_times == 2)
         {
            display_jpegs(fb_inf, small_size_inf);
            jpeg_is_bigger_flag = 0;
 
            fb_save_cursor(fb_inf, m_x, m_y); 
            p_x = m_x;   
            p_y = m_y;
            fb_draw_cursor(fb_inf, m_x, m_y);

            jpeg_big_button_left_times = 0;
            jpeg_is_big_flag = 0; 
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
                    button_left_now_flag = iloop / 2 + JPEG_X_NUM * (jloop / 2);
                    if (button_left_pre_flag == button_left_now_flag)
                      {
                        display_jpeg(jpegs[button_left_now_flag], fb_inf);

                        fb_save_cursor(fb_inf, m_x, m_y); 
                        p_x = m_x;   
                        p_y = m_y;
                        fb_draw_cursor(fb_inf, m_x, m_y);

                        jpeg_is_big_flag = 1;

                        button_left_pre_flag = -1;
                        button_left_now_flag = -1;
                        }
                    else 
                      {
                        button_left_pre_flag = button_left_now_flag;
                        button_left_now_flag = -1;
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
/* display bigger jpeg inner */
int display_bigger_jpeg_inner(const char *jpegname, int x, int y, fb_info size_inf, fb_info fb_inf)
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

#if 1
/* display transparent jpeg inner */
int display_jpeg_inner(const char *jpegname, int x_center, int y_center, fb_info size_inf, fb_info fb_inf)
{
    fb_info big_jpeg_inf;
    fb_info small_jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int yloop;
    int x;
    int y;

    u8_t *buf24_big = decode_jpeg(jpegs[JPEG_X_NUM * JPEG_Y_NUM], &big_jpeg_inf);
    u8_t *scale_buf_big = scale24(buf24_big, fb_inf, big_jpeg_inf);
    u32_t *buf32_big = rgb24to32(scale_buf_big, fb_inf);
    
    u8_t *buf24_small = decode_jpeg(jpegname, &small_jpeg_inf);
    u8_t *scale_buf_small = scale24(buf24_small, size_inf, small_jpeg_inf);
    u32_t *buf32_small = rgb24to32(scale_buf_small, size_inf);
    
    for (yloop = 0; yloop < size_inf.h; yloop++)
    {
        for (xloop = 0; xloop < size_inf.w; xloop++)
        {
            x = x_center - size_inf.w / 2; 
            y = y_center - size_inf.h / 2;
            *((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 2) = (float)(*((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 2)) * 0.3 
                                                              + (float)(*((u8_t *)&buf32_small[xloop + (yloop * size_inf.w)] + 2)) * 0.7;
            *((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 1) = (float)(*((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 1)) * 0.3
                                                              + (float)(*((u8_t *)&buf32_small[xloop + (yloop * size_inf.w)] + 1)) * 0.7;
            *((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 0) = (float)(*((u8_t *)&buf32_big[x + xloop + ((y + yloop) * fb_inf.w)] + 0)) * 0.3 
                                                              + (float)(*((u8_t *)&buf32_small[xloop + (yloop * size_inf.w)] + 0)) * 0.7;

        }
    }
    
    for (yloop = 0; yloop < size_inf.h; yloop++)
    {
        for (xloop = 0; xloop < size_inf.w; xloop++)
        {
            xres = x_center - size_inf.w / 2 + xloop;
            yres = y_center - size_inf.h / 2 + yloop;

            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
             {
                fb_pixel(fb_inf, xres, yres, buf32_big[xres + yres * fb_inf.w]);
             }
        }
    }
        
    free(buf24_small);
    free(scale_buf_small);
    free(buf32_small);

    free(buf24_big);
    free(scale_buf_big);
    free(buf32_big);
    
    return 0;
}
#endif

#if 0
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
