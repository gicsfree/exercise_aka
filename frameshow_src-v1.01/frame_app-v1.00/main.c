/* main.c */

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "frame.h"

static int flag = 0;

/* the thread display clock */
void *pro_thread(void *fb_inf)
{
    while (flag == 0)
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
    fb_info new_inf;

    new_inf.w = 512;
    new_inf.h = 384;
//    new_inf.bpp = 0;
//    new_inf.fbmem = NULL;  

    if (init_fb(&fb_inf) < 0)
    {
        fprintf(stderr, "Error initial framebuffer\b")	;
        return -1;
    }

//    if (init_ft("mao.ttf", 30) < 0)
    if (init_ft("simkai.ttf", 30) < 0)
    {
        fprintf(stderr, "Error initial font\b")	;
    	 return -1;
    }
    
    pthread_create(&p_mon, NULL, pro_thread, &fb_inf);
 
    #ifdef FRAME_SUPPORT_JPEG
    display_jpeg("1.jpg", fb_inf);
    sleep(1);
    display_jpeg("2.jpg", fb_inf);
    sleep(1);

#if 1
    display_jpeg_blind_y("3.jpg", fb_inf);
    sleep(1);
    display_jpeg_blind_x("4.jpg", fb_inf);
    sleep(1);
    display_jpeg_cross("5.jpg", fb_inf);
    sleep(1);
    display_jpeg_blind_m("6.jpg", fb_inf);
    sleep(1);
    display_jpeg_diagonal_c("7.jpg", fb_inf);
    sleep(1);
    display_jpeg_circle("8.jpg", fb_inf);
    sleep(1);
//    display_jpeg_diagonal_o("9.jpg", fb_inf);
//    sleep(1);
    display_jpeg_circle_area("10.jpg", fb_inf);
    sleep(1);
    display_jpeg_square("11.jpg", fb_inf);
    sleep(1);
    display_jpeg_point("12.jpg", fb_inf);
    sleep(1);
#endif

    display_jpeg_down("13.jpg", fb_inf);
    sleep(1);

    display_jpeg_small("14.jpg", "9.jpg", 0, 0, new_inf, fb_inf);
    sleep(2);
    display_jpeg_small("15.jpg", "8.jpg", 0, 0, new_inf, fb_inf);
    sleep(2);
    display_jpeg_small("16.jpg", "4.jpg", fb_inf.w / 2, fb_inf.h / 2, new_inf, fb_inf);
    sleep(2);
    display_jpeg_small("17.jpg", "3.jpg", fb_inf.w / 2, fb_inf.h / 2, new_inf, fb_inf);
    sleep(2);

    #endif
     
    fb_draw_squarearea(fb_inf, 0, 0, fb_inf.w, fb_inf.h, 0xFF0000);
    fb_draw_star(fb_inf, 200, 220, 150, 0x00FFFF00);
    fb_draw_star(fb_inf, 380, 70, 40, 0x00FFFF00);	
    fb_draw_star(fb_inf, 440, 170, 40, 0x00FFFF00);
    fb_draw_star(fb_inf, 430, 270, 40, 0x00FFFF00);
    fb_draw_star(fb_inf, 380, 370, 40, 0x00FFFF00);
    
    #ifdef FRAME_SUPPORT_FONT    
    display_string ("北京 中关村", 10, fb_inf.h - 100, fb_inf,0x00FFFF00);
    sleep(1);
    #endif 

    #ifdef FRAME_SUPPORT_BMP
    display_bmp(fb_inf, "test.bmp");
    sleep(1);
    #endif

    flag = 1;   

    #ifdef FRAME_SUPPORT_MOUSE
    test_mouse(fb_inf);
    #endif 

    munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
        
    return 0;
}
