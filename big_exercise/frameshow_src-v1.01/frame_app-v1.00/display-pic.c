/* display-pic.c */

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "frame.h"

extern int clock_flag;

/* display picture */
int display_pic(fb_info fb_inf) 
{
    fb_info small_inf;

    small_inf.w = fb_inf.w / 2;
    small_inf.h = fb_inf.h / 2;

    dispaly_pic_in_dir("../frame_app-v1.00", fb_inf);
     
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

    clock_flag = 1;   

    #ifdef FRAME_SUPPORT_MOUSE
    test_mouse(fb_inf);
    #endif 

    munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
        
    return 0;
}
