/* display_clock.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <time.h>

#include "frame.h"

#define COLURE 0x00FF0000
#define X 700
#define Y 0 
#define BMP_WIDTH  320
#define BMP_HEIGHT 70

static unsigned long save_bmp[BMP_WIDTH * BMP_HEIGHT];

/* save clock bmp area */
int fb_save_bmp(fb_info fb_inf, int x, int y)
{
    int iloop;
    int jloop;
    u32_t color;
    
    for (jloop = 0; jloop < BMP_HEIGHT; jloop++)
    {
        for (iloop = 0; iloop < BMP_WIDTH; iloop++)
        {
            color = *(u32_t*)(fb_inf.fbmem + ((y + jloop) * fb_inf.w + x + iloop) * fb_inf.bpp/8);
            save_bmp[iloop + jloop * BMP_WIDTH] = color;
        }
    }
    
	  return 0;
}

/* restore clock bmp area */
int fb_restore_bmp(fb_info fb_inf, int x, int y)
{
    int iloop;
    int jloop;
    u32_t color;
    
    for (jloop = 0; jloop < BMP_HEIGHT; jloop++)
    {
        for (iloop = 0; iloop < BMP_WIDTH; iloop++)
        {
            color = save_bmp[iloop + jloop * BMP_WIDTH];
            fb_pixel(fb_inf, x+iloop, y+jloop, color);
        }
    }
    
    return 0;
}

/* display clock */
void display_clock(fb_info fb_inf)
{
    struct timeval tm_get;
    struct tm *ltm;

    char time_buf[50] = {0};
//    char week_buf[10] = {0};

    #ifdef FRAME_SUPPORT_FONT
    if (init_ft("simkai.ttf", 30) < 0)
    {
        fprintf(stderr, "Error initial font\b");
    	 exit(1);
    }
    #endif

    fb_save_bmp(fb_inf, X, Y);

    while (1)
    {
        gettimeofday(&tm_get, NULL);
        ltm = localtime(&tm_get.tv_sec);

        fb_restore_bmp(fb_inf, X, Y);

        sprintf(time_buf, "%d-%d-%d %d:%d:%d", ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday,
                ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

        display_string (time_buf, X + 20, Y + 30, fb_inf, COLURE);

//        display_string_ch (week_buf, 720, 60, fb_inf, COLURE);

        switch (ltm->tm_wday)
        {
            case 0:
//                strcpy(week_buf, "Sunday");
                display_string_ch ("星期日", X + 20, Y + 60, fb_inf, COLURE);
                break;

            case 1: 
                display_string_ch ("星期一", X + 20, Y + 60, fb_inf, COLURE);
                break;

            case 2: 
                display_string_ch ("星期二", X + 20, Y + 60, fb_inf, COLURE);
                break;

            case 3: 
                display_string_ch ("星期三", X + 20, Y + 60, fb_inf, COLURE);
                break;

            case 4: 
                display_string_ch ("星期四", X + 20, Y + 60, fb_inf, COLURE);
                break;

            case 5: 
                display_string_ch ("星期五", X + 20, Y + 60, fb_inf, COLURE);
                break;

            case 6: 
                display_string_ch ("星期六", X + 20, Y + 60, fb_inf, COLURE);
                break;

            default: 
                break;
        }
        sleep(1);
    }
}


