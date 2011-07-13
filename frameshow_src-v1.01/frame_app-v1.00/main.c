/* main.c */

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "frame.h"

static int clock_flag = 0;

/* the thread display clock */
void *pro_thread_clock(void *fb_inf)
{
    while (clock_flag == 0)
    {
        sleep(1);
    }
    display_clock(*(fb_info *)fb_inf);

    return NULL;
}

/* main */
int main(int argc, char *argv[]) 
{
    pthread_t p_mon; 
    fb_info fb_inf; 
    fb_info small_inf;

    if (init_fb(&fb_inf) < 0)
    {
        fprintf(stderr, "Error initial framebuffer\b")	;
        return -1;
    }
    
    pthread_create(&p_mon, NULL, pro_thread_clock, &fb_inf);

    small_inf.w = fb_inf.w / 2;
    small_inf.h = fb_inf.h / 2;
 
    #ifdef FRAME_SUPPORT_JPEG

    display_jpeg_mouse(fb_inf);

#if 1
    display_jpeg("1.jpg", fb_inf);
    sleep(1);
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

    display_jpeg_circle_num("23.jpg", fb_inf, 9, 10);
    sleep(1);
    display_jpeg_down("13.jpg", fb_inf);
    sleep(1);

    display_jpeg_inset("15.jpg", "8.jpg", fb_inf.w / 4, fb_inf.h / 4, 1, small_inf, fb_inf);
    sleep(2);
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

    clock_flag = 1;   

    #ifdef FRAME_SUPPORT_MOUSE
    test_mouse(fb_inf);
    #endif 

    munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
        
    return 0;
}
