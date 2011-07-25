/* display_homepage.c */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "frame.h"

#define BUTTON_AREA_WIDTH 100
#define BUTTON_AREA_HEIGHT 90

#define BUTTON_X_SUM 6
#define BUTTON_Y_SUM 4

#define HOMEPAGE "homepage.jpg"
#define JIYU "jiyu.jpg"
#define HELP "help.jpg"
#define AUTHOR "author.jpg"
#define COPYRIGHT "copyright.jpg"

#define JPEG_X_NUM 20
#define JPEG_Y_NUM 15

extern int clock_flag;

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

static int under_button_one_pic_count = -1;
static int under_button_some_pic_count = -1;
static int under_button_one_pic_flag = -1;
static int under_button_some_pic_flag = -1;
static int under_button_one_pic_start = 1;
static int under_button_some_pic_start = 1;
static show_start = 0;

static picture_t *pic;
static int count = 0;

#if 1
/* display jpegs when mouse work */
int display_jpeg_mouse(fb_info fb_inf)
{
    int mfd = -1;
    u8_t buf[8];
    mouse_event_t mevent;
    int mouse_position_flag = -1;

    picture_t *tmp;
    int iloop;

    fb_info big_pic_inf;
    fb_info small_pic_inf;
    fb_info bigger_pic_inf;
    fb_info under_light_area_inf;
    fb_info right_light_area_inf;

    big_pic_inf.w = fb_inf.w - BUTTON_AREA_WIDTH;
    big_pic_inf.h = fb_inf.h - BUTTON_AREA_HEIGHT;

    small_pic_inf.w = big_pic_inf.w / (JPEG_X_NUM + 1);
    small_pic_inf.h = big_pic_inf.h / (JPEG_Y_NUM + 1);

    bigger_pic_inf.w = big_pic_inf.w / JPEG_X_NUM;
    bigger_pic_inf.h = big_pic_inf.h / JPEG_Y_NUM;

    under_light_area_inf.w = big_pic_inf.w / (2 * BUTTON_X_SUM);
    under_light_area_inf.h = BUTTON_AREA_HEIGHT / 2;

    right_light_area_inf.h = big_pic_inf.h / (2 * BUTTON_Y_SUM);
    right_light_area_inf.w = BUTTON_AREA_WIDTH / 2;

    if (pic != NULL)
    {
        free_pic(pic);
        pic = NULL;
    }
    pic = get_pictures("./frame", pic);
    count = count_pic(pic);

    display_shutters5(HOMEPAGE, fb_inf);
//    display_jpeg_point(HOMEPAGE, fb_inf);
//    display_jpeg(HOMEPAGE, fb_inf);

    clock_flag = 1;

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
              }
            else
             {
	         m_x -= mevent.x;
	         m_y -= mevent.y;
             }

             if ((m_x >= 0) && (m_x < big_pic_inf.w) && (m_y >= 0) && (m_y < big_pic_inf.h) && (show_start == 1))
              {
                 mouse_position_flag = 0;
                 jpeg_bigger(small_pic_inf, bigger_pic_inf, big_pic_inf, fb_inf);
              }
             else
              {
                if ((m_x >= big_pic_inf.w) && (m_x < fb_inf.w) && (m_y >= 0) && (m_y < big_pic_inf.h))
                  {
                     mouse_position_flag = 1;  
                     light_right_button(big_pic_inf, right_light_area_inf, fb_inf);               
                  }
                else
                  {
                    if ((m_x >= 0) && (m_x < big_pic_inf.w) && (m_y >= big_pic_inf.h) && (m_y < fb_inf.h))
                      {
                         mouse_position_flag = 2;
                         light_under_button(big_pic_inf, under_light_area_inf, fb_inf);
                      }
                  }
              }

	     fb_draw_cursor(fb_inf, m_x, m_y);

	     switch (mevent.button)
              {
	         case 1:
                    if (mouse_position_flag == 0) 
                      {
                        if (jpeg_is_bigger_flag == 0)
                          {
                            mevent_button_left(small_pic_inf, small_pic_inf, big_pic_inf, fb_inf);
                          }
                        else
                          {
                            mevent_button_left(bigger_pic_inf, small_pic_inf, big_pic_inf, fb_inf);
                          }
                      }
                    else 
                      {
                        if (mouse_position_flag == 1)
                          {
                           right_button_left(small_pic_inf, big_pic_inf, right_light_area_inf, fb_inf);
                          }
                        else
                          {
                            if (mouse_position_flag == 2)
                               {
                                 under_button_left(small_pic_inf, big_pic_inf, under_light_area_inf, fb_inf);
                               }
                          }
                      }

		      break;

		      case 2:
		          break;
                     
		      case 3:
//		          printf("middle\n");
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
int under_button_left(fb_info small_pic_inf, fb_info big_pic_inf, fb_info light_area_inf, fb_info fb_inf)
{
    int iloop;
    int jloop;
    picture_t *tmp;
    int max_some_pic_count;

    for (iloop = 1; iloop <= 2 * BUTTON_X_SUM - 1; iloop += 2)
    {
        if ((m_x >= iloop * big_pic_inf.w / (2 * BUTTON_X_SUM) - light_area_inf.w / 2) && (m_x < iloop * big_pic_inf.w / (2 * BUTTON_X_SUM) + light_area_inf.w / 2)
           && (m_y >= big_pic_inf.h + BUTTON_AREA_HEIGHT / 2 - light_area_inf.h / 2) && (m_y < big_pic_inf.h + BUTTON_AREA_HEIGHT / 2 + light_area_inf.h / 2))
        {
            switch (m_x * BUTTON_X_SUM / big_pic_inf.w) 
            {
                case 0:
                    if (under_button_one_pic_flag == 1)
                      {
                        if (under_button_one_pic_count > 0)
                          {
                            under_button_one_pic_count--;
                            for (jloop = 0, tmp = pic; jloop < under_button_one_pic_count; jloop++)
                              {
                                tmp = tmp->next;
                              }
                            display_jpeg_in_certain_size(tmp->name, 0, 0, big_pic_inf, fb_inf);
                          }
                      } 
                    else
                      {
                        if (under_button_some_pic_flag == 1)
                           {
                            if (under_button_some_pic_count > 0)
                               {
                                under_button_some_pic_count--;
                                display_jpegs_inner(small_pic_inf, big_pic_inf, fb_inf);
                               }
                           }
                      }
                    break;

                case 1:
                    if (under_button_one_pic_flag == 1)
                      {
                        if (under_button_one_pic_count < count - 1)
                          {
                            under_button_one_pic_count++;
                            for (jloop = 0, tmp = pic; jloop < under_button_one_pic_count; jloop++)
                              {
                                tmp = tmp->next;
                              }
                            display_jpeg_in_certain_size(tmp->name, 0, 0, big_pic_inf, fb_inf);
                          }
                      } 
                    else
                      {
                        if (under_button_some_pic_flag == 1)
                           {
                            if (count % (JPEG_X_NUM * JPEG_Y_NUM) == 0)
                               {
                                max_some_pic_count = count / (JPEG_X_NUM * JPEG_Y_NUM) - 1;
                               }
                            else
                               {
                                max_some_pic_count = count / (JPEG_X_NUM * JPEG_Y_NUM);
                               }

                            if (under_button_some_pic_count < max_some_pic_count)
                               {
                                under_button_some_pic_count++;
                                display_jpegs_inner(small_pic_inf, big_pic_inf, fb_inf);
                               }
                           }
                      }
                    break;

                case 2:
                    under_button_one_pic_flag = 1;
                    under_button_some_pic_flag = 0;
                    if (under_button_one_pic_start == 1)
                      {
                        under_button_one_pic_count = 0;
                        tmp = pic;
                        display_jpeg_in_certain_size(tmp->name, 0, 0, big_pic_inf, fb_inf);
                        under_button_one_pic_start = 0;
                        under_button_some_pic_start = 1;
                      }
                    show_start = 0;
                    break;

                case 3:
                    under_button_one_pic_flag = 0;
                    under_button_some_pic_flag = 1;
                    if (under_button_some_pic_start == 1)
                      {
                        under_button_some_pic_count = 0;
                        display_jpegs_inner(small_pic_inf, big_pic_inf, fb_inf);
                        under_button_some_pic_start = 0;
                        under_button_one_pic_start = 1;
                      }
                    show_start = 1;
                    break;

                case 4:
                    clock_flag = 0;
                    display_pictures(pic, fb_inf);
                    display_jpeg(HOMEPAGE, fb_inf);
                    clock_flag = 1;
                    button_left_pre_flag = -1;
                    button_left_now_flag = -1;
                    jpeg_is_big_flag = 0;
                    jpeg_big_button_left_times = 0;
                    jpeg_is_bigger_flag = 0;
                    mouse_response_time = 0;

                    under_button_one_pic_count = -1;
                    under_button_some_pic_count = -1;
                    under_button_one_pic_flag = -1;
                    under_button_some_pic_flag = -1;
                    under_button_one_pic_start = 1;
                    under_button_some_pic_start = 1;
                    show_start = 0;
                    break;

              case 5:
                    display_jpeg_part(HOMEPAGE, big_pic_inf, fb_inf);
                    clock_flag = 1;
                    button_left_pre_flag = -1;
                    button_left_now_flag = -1;
                    jpeg_is_big_flag = 0;
                    jpeg_big_button_left_times = 0;
                    jpeg_is_bigger_flag = 0;
                    mouse_response_time = 0;

                    under_button_one_pic_count = -1;
                    under_button_some_pic_count = -1;
                    under_button_one_pic_flag = -1;
                    under_button_some_pic_flag = -1;
                    under_button_one_pic_start = 1;
                    under_button_some_pic_start = 1;
                    show_start = 0;
                    break;

               default:
                    break;
                                   
            }
            break;
        }
    }
}
#endif

#if 1
int right_button_left(fb_info small_pic_inf, fb_info big_pic_inf, fb_info light_area_inf, fb_info fb_inf)
{
    int iloop;
    int jloop;
    picture_t *tmp;
    int max_some_pic_count;

    for (iloop = 1; iloop <= 2 * BUTTON_Y_SUM - 1; iloop += 2)
    {
        if ((m_y >= iloop * big_pic_inf.h / (2 * BUTTON_Y_SUM) - light_area_inf.h / 2) && (m_y < iloop * big_pic_inf.h / (2 * BUTTON_Y_SUM) + light_area_inf.h / 2)
           && (m_x >= big_pic_inf.w + BUTTON_AREA_WIDTH / 2 - light_area_inf.w / 2) && (m_y < big_pic_inf.w + BUTTON_AREA_WIDTH / 2 + light_area_inf.w / 2))
        {
            switch (m_y * BUTTON_Y_SUM / big_pic_inf.h) 
            {
                case 0:
                    display_jpeg_in_certain_size(COPYRIGHT, 0, 0, big_pic_inf, fb_inf);
                    show_start = 0;
                    break;

                case 1:
                    display_jpeg_in_certain_size(AUTHOR, 0, 0, big_pic_inf, fb_inf);
                    show_start = 0;
                    break;

                case 2:
                    display_jpeg_in_certain_size(JIYU, 0, 0, big_pic_inf, fb_inf);
                    show_start = 0;
                    break;

                case 3:
                    display_jpeg_in_certain_size(HELP, 0, 0, big_pic_inf, fb_inf);
                    show_start = 0;
                    break;

                default:
                     break;
                                   
            }
            break;
        }
    }
}
#endif

#if 1
int light_under_button(fb_info big_pic_inf, fb_info light_area_inf, fb_info fb_inf)
{
    int iloop;
    int jloop;
    static button_is_light_flag = 0;
    int button_in_light_area_flag;
    static p_iloop;

    if (button_is_light_flag == 0)
    {
        for (iloop = 1; iloop <= 2 * BUTTON_X_SUM - 1; iloop += 2)
        {
            if ((m_x >= iloop * big_pic_inf.w / (2 * BUTTON_X_SUM) - light_area_inf.w / 2) && (m_x < iloop * big_pic_inf.w / (2 * BUTTON_X_SUM) + light_area_inf.w / 2)
             && (m_y >= big_pic_inf.h + BUTTON_AREA_HEIGHT / 2 - light_area_inf.h / 2) && (m_y < big_pic_inf.h + BUTTON_AREA_HEIGHT / 2 + light_area_inf.h / 2))
            {
                light_area(iloop * big_pic_inf.w / (2 * BUTTON_X_SUM), fb_inf.h - BUTTON_AREA_HEIGHT / 2, light_area_inf, fb_inf);

                fb_save_cursor(fb_inf, m_x, m_y); 
                p_x = m_x;   
                p_y = m_y;

                button_is_light_flag = 1;
                p_iloop = iloop;
                break;
            }
        }
    }
    else
    {
        button_in_light_area_flag = 0;
        for (iloop = 1; iloop <= (2 * BUTTON_X_SUM) - 1; iloop += 2)
        {
            if ((m_x >= iloop * big_pic_inf.w / (2 * BUTTON_X_SUM) - light_area_inf.w / 2) && (m_x < iloop * big_pic_inf.w / (2 * BUTTON_X_SUM) + light_area_inf.w / 2)
             && (m_y >= big_pic_inf.h + BUTTON_AREA_HEIGHT / 2 - light_area_inf.h / 2) && (m_y < big_pic_inf.h + BUTTON_AREA_HEIGHT / 2 + light_area_inf.h / 2))
            {
                button_in_light_area_flag = 1;
                break;
            }
        }

        if (button_in_light_area_flag == 0)
        {
            restore_light_area(p_iloop * big_pic_inf.w / (2 * BUTTON_X_SUM), fb_inf.h - BUTTON_AREA_HEIGHT / 2, light_area_inf, fb_inf);

            fb_save_cursor(fb_inf, m_x, m_y); 
            p_x = m_x;   
            p_y = m_y;

            button_is_light_flag = 0;
        }
    }

    return 0;
}
#endif

#if 1
int light_right_button(fb_info big_pic_inf, fb_info light_area_inf, fb_info fb_inf)
{
    int iloop;
    int jloop;
    static button_is_light_flag = 0;
    int button_in_light_area_flag;
    static p_iloop;

    if (button_is_light_flag == 0)
    {
        for (iloop = 1; iloop <= 2 * BUTTON_Y_SUM - 1; iloop += 2)
        {
            if ((m_y >= iloop * big_pic_inf.h / (2 * BUTTON_Y_SUM) - light_area_inf.h / 2) && (m_y < iloop * big_pic_inf.h / (2 * BUTTON_Y_SUM) + light_area_inf.h / 2)
             && (m_x >= big_pic_inf.w + BUTTON_AREA_WIDTH / 2 - light_area_inf.w / 2) && (m_x < big_pic_inf.w + BUTTON_AREA_WIDTH / 2 + light_area_inf.w / 2))
            {
                light_area(fb_inf.w - BUTTON_AREA_HEIGHT / 2, iloop * big_pic_inf.h / (2 * BUTTON_Y_SUM), light_area_inf, fb_inf);

                fb_save_cursor(fb_inf, m_x, m_y); 
                p_x = m_x;   
                p_y = m_y;

                button_is_light_flag = 1;
                p_iloop = iloop;
                break;
            }
        }
    }
    else
    {
        button_in_light_area_flag = 0;
        for (iloop = 1; iloop <= (2 * BUTTON_Y_SUM) - 1; iloop += 2)
        {
            if ((m_y >= iloop * big_pic_inf.h / (2 * BUTTON_Y_SUM) - light_area_inf.h / 2) && (m_y < iloop * big_pic_inf.h / (2 * BUTTON_Y_SUM) + light_area_inf.h / 2)
             && (m_x >= big_pic_inf.w + BUTTON_AREA_WIDTH / 2 - light_area_inf.w / 2) && (m_x < big_pic_inf.w + BUTTON_AREA_WIDTH / 2 + light_area_inf.w / 2))
            {
                button_in_light_area_flag = 1;
                break;
            }
        }

        if (button_in_light_area_flag == 0)
        {
            restore_light_area(fb_inf.w - BUTTON_AREA_HEIGHT / 2, p_iloop * big_pic_inf.h / (2 * BUTTON_Y_SUM), light_area_inf, fb_inf);

            fb_save_cursor(fb_inf, m_x, m_y); 
            p_x = m_x;   
            p_y = m_y;

            button_is_light_flag = 0;
        }
    }

    return 0;
}
#endif

#if 1
int light_area(int x_center, int y_center, fb_info light_area_inf, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xloop;
    int yloop;
    int xres;
    int yres;
    int light_value = 50;

    u8_t *buf24 = decode_jpeg(HOMEPAGE, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for (xres = 0; xres <fb_inf.w; xres++)
    {
        for (yres = 0; yres < fb_inf.h; yres++)
        {
            if (*((u8_t *)&buf32[xres + yres * fb_inf.w] + 2) + light_value <= 255)
             {
                *((u8_t *)&buf32[xres + yres * fb_inf.w] + 2) = *((u8_t *)&buf32[xres + yres * fb_inf.w] + 2) + light_value; 
             }
            else
            {
                *((u8_t *)&buf32[xres + yres * fb_inf.w] + 2) = 255;
            }

            if (*((u8_t *)&buf32[xres + yres * fb_inf.w] + 1) + light_value <= 255)
             {
                *((u8_t *)&buf32[xres + yres * fb_inf.w] + 1) = *((u8_t *)&buf32[xres + yres * fb_inf.w] + 1) + light_value; 
             }
            else
            {
                *((u8_t *)&buf32[xres + yres * fb_inf.w] + 1) = 255;
            }

            if (*((u8_t *)&buf32[xres + yres * fb_inf.w] + 0) + light_value <= 255)
             {
                *((u8_t *)&buf32[xres + yres * fb_inf.w] + 0) = *((u8_t *)&buf32[xres + yres * fb_inf.w] + 0) + light_value; 
             }
            else
            {
                *((u8_t *)&buf32[xres + yres * fb_inf.w] + 0) = 255;
            }
        }
    }         

    for (yloop = 0; yloop < light_area_inf.h; yloop++)
    {
        for (xloop = 0; xloop < light_area_inf.w; xloop++)
        {
            xres = x_center - light_area_inf.w / 2 + xloop;
            yres = y_center - light_area_inf.h / 2 + yloop;

            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
             {
                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
             }
        }
    }
                                                             
    return 0;
}
#endif

#if 1
int restore_light_area(int x_center, int y_center, fb_info light_area_inf, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xloop;
    int yloop;
    int xres;
    int yres;

    u8_t *buf24 = decode_jpeg(HOMEPAGE, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);   

    for (yloop = 0; yloop < light_area_inf.h; yloop++)
    {
        for (xloop = 0; xloop < light_area_inf.w; xloop++)
        {
            xres = x_center - light_area_inf.w / 2 + xloop;
            yres = y_center - light_area_inf.h / 2 + yloop;

            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
             {
                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
             }
        }
    }
                                                             
    return 0; 
}
#endif

#if 1
/* jpeg bigger */
int jpeg_bigger(fb_info small_pic_inf, fb_info bigger_pic_inf, fb_info big_pic_inf, fb_info fb_inf)
{
    int num;
    int iloop;
    int jloop;
    int kloop;
    int flag_mouse_in_bigger;
    static int p_iloop;
    static int p_jloop;
    picture_t *tmp;

    if (jpeg_is_big_flag == 0)
    {
        if (jpeg_is_bigger_flag == 0)
         {
            for (jloop = 1; jloop < 2 * JPEG_Y_NUM; jloop += 2)
            {
                for (iloop = 1; iloop < 2 * JPEG_X_NUM; iloop += 2)
                 {
                   if ((m_x >= iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)) - small_pic_inf.w / 2) && m_x <= (iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)) + small_pic_inf.w / 2)
                     && (m_y >= jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)) - small_pic_inf.h / 2) && (m_y <= jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)) + small_pic_inf.h / 2))
                      {
                        num = iloop / 2 + JPEG_X_NUM * (jloop / 2) + JPEG_X_NUM * JPEG_Y_NUM * under_button_some_pic_count;
                        if (num < count)
                          {
                            for (kloop = 0, tmp = pic; kloop < num; kloop++)
                             {
                                tmp = tmp -> next;
                             }
                          display_bigger_jpeg_inner(tmp->name, iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)), jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)), bigger_pic_inf, fb_inf);
                         }

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

            if ((m_x >= p_iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)) - bigger_pic_inf.w / 2) && m_x <= (p_iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)) + bigger_pic_inf.w / 2)
               && (m_y >= p_jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)) - bigger_pic_inf.h / 2) && (m_y <= p_jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)) + bigger_pic_inf.h / 2))
            {
                flag_mouse_in_bigger = 1;
            }

            if (flag_mouse_in_bigger == 0)
            {
                display_jpeg_local(p_iloop, p_jloop, bigger_pic_inf, big_pic_inf, fb_inf); 

                num = p_iloop / 2 + JPEG_X_NUM * (p_jloop / 2) + JPEG_X_NUM * JPEG_Y_NUM * under_button_some_pic_count;
                if (num < count)
                  {
                    for (kloop = 0, tmp = pic; kloop < num; kloop++)
                      {
                        tmp = tmp -> next;
                      }
                    display_jpeg_inner(tmp->name, p_iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)), p_jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)), small_pic_inf, fb_inf);
                  }

                fb_save_cursor(fb_inf, m_x, m_y); 
                p_iloop = iloop;
                p_jloop = jloop;

                jpeg_is_bigger_flag = 0; 
             }
        }
    }

    return 0;
}
#endif

#if 1
/* display jpeg in local */
int display_jpeg_local(int p_iloop, int p_jloop, fb_info bigger_pic_inf, fb_info big_pic_inf, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int yloop;

    u8_t *buf24 = decode_jpeg(HOMEPAGE, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (yloop = 0; yloop < bigger_pic_inf.h; yloop++)
    {
        for (xloop = 0; xloop < bigger_pic_inf.w; xloop++)
        {
            xres = p_iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)) - bigger_pic_inf.w / 2 + xloop;
            yres = p_jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)) - bigger_pic_inf.h / 2 + yloop;

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
int mevent_button_left(fb_info mouse_area_inf, fb_info small_pic_inf, fb_info big_pic_inf, fb_info fb_inf)
{
    int iloop;
    int jloop;
    int kloop;
    int num;
    picture_t *tmp;

    mouse_response_time = 0;

    if (jpeg_is_big_flag == 1)
    {
        jpeg_big_button_left_times++;
        if (jpeg_big_button_left_times == 2)
         {
            display_jpegs_inner(small_pic_inf, big_pic_inf, fb_inf);
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
                if ((m_x >= iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)) - mouse_area_inf.w / 2) && m_x <= (iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)) + mouse_area_inf.w / 2)
                   && (m_y >= jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)) - mouse_area_inf.h / 2) && (m_y <= jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)) + mouse_area_inf.h / 2))
                  {
                    button_left_now_flag = iloop / 2 + JPEG_X_NUM * (jloop / 2);
                    if (button_left_pre_flag == button_left_now_flag)
                      {
                        num = button_left_now_flag + JPEG_X_NUM * JPEG_Y_NUM * under_button_some_pic_count;
                        if (num < count)
                          {
                            for (kloop = 0, tmp = pic; kloop < num; kloop++)
                             {
                                tmp = tmp -> next;
                             }
                        display_jpeg_in_certain_size(tmp->name, 0, 0, big_pic_inf, fb_inf);
                         }

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
int display_jpeg_in_certain_size(const char *jpegname, int x_start, int y_start, fb_info pic_inf, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int yloop;

    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, pic_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, pic_inf);

    for (yloop = 0; yloop < pic_inf.h; yloop++)
    {
        for (xloop = 0; xloop < pic_inf.w; xloop++)
        {
            xres = x_start + xloop;
            yres = y_start + yloop;

            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
            {
                fb_pixel(fb_inf, xres, yres, buf32[xloop + yloop * pic_inf.w]);
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
/* display jpegs inner */
int display_jpegs_inner(fb_info small_pic_inf, fb_info big_pic_inf, fb_info fb_inf)
{
    int num;
    int iloop;
    int jloop;
    int kloop;
    picture_t *tmp;

    display_jpeg_part(HOMEPAGE, big_pic_inf, fb_inf);

    for (jloop = 1; jloop < 2 * JPEG_Y_NUM; jloop += 2)
    {
        for (iloop = 1; iloop < 2 * JPEG_X_NUM; iloop += 2)
        {
            num = iloop / 2 + JPEG_X_NUM * (jloop / 2) + JPEG_X_NUM * JPEG_Y_NUM * under_button_some_pic_count;
            if (num < count)
             {
                for (kloop = 0, tmp = pic; kloop < num; kloop++)
                 {
                    tmp = tmp -> next;
                 }
                display_jpeg_inner(tmp->name, iloop * (big_pic_inf.w / (2 * JPEG_X_NUM)), jloop * (big_pic_inf.h / (2 * JPEG_Y_NUM)), small_pic_inf, fb_inf);
             }
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

    u8_t *buf24_big = decode_jpeg(HOMEPAGE, &big_jpeg_inf);
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


#if 1
/* display jpeg part */
int display_jpeg_part(const char *jpegname, fb_info pic_inf, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    
    for (yres = 0; yres < pic_inf.h; yres++)
    {
        for (xres = 0; xres < pic_inf.w; xres++)
        {
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 0
/* display jpeg */
int display_jpeg(const char *jpegname, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    
    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    
    for (yres = 0; yres < fb_inf.h; yres++)
    {
        for (xres = 0; xres < fb_inf.w; xres++)
        {
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif


