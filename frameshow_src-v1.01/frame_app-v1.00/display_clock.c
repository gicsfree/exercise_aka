/* display_clock.c */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <time.h>

#include "frame.h"

#define X 500
#define Y 0 
#define BMP_WIDTH  524
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
    char week_buf[10] = {0};

    fb_save_bmp(fb_inf, X, Y);

    while (1)
    {
        gettimeofday(&tm_get, NULL);
        ltm = localtime(&tm_get.tv_sec);

        switch (ltm->tm_wday)
        {
            case 0: 
                strcpy(week_buf, "Sunday");
                break;

            case 1: 
                strcpy(week_buf, "Monday");
                break;

            case 2: 
                strcpy(week_buf, "Tuesday");
                break;

            case 3: 
                strcpy(week_buf, "Wednesday");
                break;

            case 4: 
                strcpy(week_buf, "Thursday");
                break;

            case 5: 
                strcpy(week_buf, "Wriday");
                break;

            case 6: 
                strcpy(week_buf, "Saturday");
                break;

            default: 
                break;
        }

        sprintf(time_buf, "%d-%d-%d %d:%d:%d", ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday,
                ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

        fb_restore_bmp(fb_inf, X, Y);
        display_string (time_buf, 500, 30, fb_inf, 0x00FFFF00);
        display_string (week_buf, 500, 60, fb_inf, 0x00FFFF00);

        sleep(1);
    }
}


