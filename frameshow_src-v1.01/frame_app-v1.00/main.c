/* main.c */

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "frame.h"

static int flag = 0;
// static int flag_mouse = 1;
// int flag_mouse = 1;

/* the thread display clock */
void *pro_thread_clock(void *fb_inf)
{
    while (flag == 0)
    {
        sleep(1);
    }
    display_clock(*(fb_info *)fb_inf);

    return NULL;
}

#if 0
/* the thread display jpeg when mouse work */
void *pro_thread_mouse(void *fb0_inf)
{
    int mfd = -1;
    u8_t buf[8];
    mouse_event_t mevent;
    fb_info fb_inf;

    fb_inf.w = ((fb_info *)fb0_inf)->w;
    fb_inf.h = ((fb_info *)fb0_inf)->h;
    fb_inf.bpp = ((fb_info *)fb0_inf)->bpp;
    fb_inf.fbmem = ((fb_info *)fb0_inf)->fbmem;

//    flag_mouse = 0;

    int m_x = fb_inf.w / 2;
    int m_y = fb_inf.h / 2;
    int p_x;
    int p_y;
        
    mouse_open(NULL, &mfd);

    fb_save_cursor(fb_inf, m_x, m_y);
    p_x = m_x;   
    p_y = m_y;  
    fb_draw_cursor(fb_inf, m_x, m_y);
        
    for(;;)
     {
        if (read(mfd, buf, 8) != -1)
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

	     switch (mevent.button)
              {
	         case 1:
		      printf("left\n");
		      break;

		  case 2:
		      printf("right\n");
		      break;
                     
		  case 3:
		      printf("middle\n");
		      break;

		  default:
		      break;
	     }
	 }	
        usleep(300);
     }

    return NULL;
}
#endif

/* main */
int main(int argc, char *argv[]) 
{
    pthread_t p_mon; 
    pthread_t p_m;
    fb_info fb_inf; 
    fb_info small_inf;

    if (init_fb(&fb_inf) < 0)
    {
        fprintf(stderr, "Error initial framebuffer\b")	;
        return -1;
    }
    
    pthread_create(&p_mon, NULL, pro_thread_clock, &fb_inf);
//    pthread_create(&p_m, NULL, pro_thread_mouse, &fb_inf);

    small_inf.w = fb_inf.w / 2;
    small_inf.h = fb_inf.h / 2;
 
    #ifdef FRAME_SUPPORT_JPEG
//    display_jpeg("1.jpg", fb_inf);
//    sleep(1);


    display_jpeg_mouse(fb_inf);

#if 0
    while (0)
    {
        if (flag_mouse == 1)
        {
            display_jpegs(fb_inf);
            flag_mouse = 0;
        }
        usleep(50);
    }
#endif

#if 0
    display_jpeg_blind_y("3.jpg", fb_inf);
    sleep(1);
    display_jpeg_blind_x("4.jpg", fb_inf);
    sleep(1);
    display_jpeg_cross("5.jpg", fb_inf);
    sleep(1);
    display_jpeg_door("6.jpg", fb_inf);
    sleep(1);
    display_jpeg_diagonal_c("7.jpg", fb_inf);
    sleep(1);
    display_jpeg_circle("8.jpg", fb_inf);
    sleep(1);
    display_jpeg_square("10.jpg", fb_inf);
    sleep(1);
    display_jpeg_circle_area("11.jpg", fb_inf);
    sleep(1);
    display_jpeg_point("12.jpg", fb_inf);
    sleep(1);
    display_jpeg_mosaic("1.jpg", fb_inf, 10);
    sleep(3);

#endif

//    display_jpeg_right("14.jpg", fb_inf);
//    sleep(1);

    display_jpeg_circle_num("23.jpg", fb_inf, 9, 10);
    sleep(1);
    display_jpeg_down("13.jpg", fb_inf);
    sleep(1);

    display_jpeg_inset("15.jpg", "8.jpg", fb_inf.w / 4, fb_inf.h / 4, 1, small_inf, fb_inf);
    sleep(10);
    #endif
     
    fb_draw_squarearea(fb_inf, 0, 0, fb_inf.w, fb_inf.h, 0xFF0000);
    fb_draw_star(fb_inf, 200, 220, 150, 0x00FFFF00);
    fb_draw_star(fb_inf, 380, 70, 40, 0x00FFFF00);	
    fb_draw_star(fb_inf, 440, 170, 40, 0x00FFFF00);
    fb_draw_star(fb_inf, 430, 270, 40, 0x00FFFF00);
    fb_draw_star(fb_inf, 380, 370, 40, 0x00FFFF00);
    
    #ifdef FRAME_SUPPORT_FONT  
    if (init_ft("mao.ttf", 65) < 0)
    {
        fprintf(stderr, "Error initial font\b");
    	 return -1;
    }  
    display_string_ch ("北京 中关村", 50, fb_inf.h - 200, fb_inf,0x00FFFF00);
    sleep(2);
    #endif 

    #ifdef FRAME_SUPPORT_BMP
    display_bmp_square("3.bmp", fb_inf);
    sleep(1);
    display_bmp_circle_num("1.bmp", fb_inf, 6, 5);
    sleep(1);
    display_bmp_diagonal("4.bmp", fb_inf);
    sleep(1);
    display_bmp_blind("2.bmp", fb_inf);
    sleep(1);
    display_jpeg_inset("2.jpg", "8.jpg", fb_inf.w / 4, fb_inf.h / 4, 0.7, small_inf, fb_inf);
    sleep(1);
    #endif

    flag = 1;   

    #ifdef FRAME_SUPPORT_MOUSE
    test_mouse(fb_inf);
    #endif 

    munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
        
    return 0;
}
