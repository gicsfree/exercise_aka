/* draw.c */
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "frame.h"

/* draw the blackground */
int fb_draw_blackground(fb_info fb_inf, u32_t color)
{
    int xres;
    int yres;

    for (yres = 0; yres < fb_inf.h; yres++)
    {
        for (xres = 0; xres < fb_inf.w; xres++)
        {
            fb_pixel(fb_inf, xres, yres, color);
        }
    }

    return 0;
}

/* draw a color row */
int fb_draw_row(fb_info fb_inf, int x_start, int y_start, int length, int width, u32_t color)
{
    int xloop;
    int yloop;
    int xres;
    int yres;

    if ((x_start < 0) || (x_start >= fb_inf.w) || (y_start < 0) || (y_start >= fb_inf.h))
    {
        printf("fb_draw_row cross the border\n");
        exit(1);
    }

    for (yloop = 0; yloop < width; yloop++)
    {       
        for (xloop = 0; xloop < length; xloop++)
        {
            xres = x_start + xloop;
            yres = y_start - width / 2 + yloop;
            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
            {
                fb_pixel(fb_inf, xres, yres, color);
            }
        }
    }
     
    return 0;
}

/* draw a color col */
int fb_draw_col(fb_info fb_inf, int x_start, int y_start, int length, int width, u32_t color)
{
    int xloop;
    int yloop;
    int xres;
    int yres;

    if ((x_start < 0) || (x_start >= fb_inf.w) || (y_start < 0) || (y_start >= fb_inf.h))
    {
        printf("fb_draw_row cross the border\n");
        exit(1);
    }

    for (xloop = 0; xloop < width; xloop++)
    {       
        for (yloop = 0; yloop < length; yloop++)
        {
            xres = x_start - width / 2 + xloop;
            yres = y_start + yloop;
            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
            {
                fb_pixel(fb_inf, xres, yres, color);
            }
        }
    }
     
    return 0;
}

/* draw a board */
int fb_draw_board(fb_info fb_inf, int x_start, int y_start)
{
    int iloop;
    int xres;
    int yres;

    if ((x_start < 0) || (x_start >= fb_inf.w) || (y_start < 0) || (y_start >= fb_inf.h))
    {
        printf("fb_draw_board cross the border\n");
        exit(1);
    }

    fb_draw_blackground(fb_inf, BLACKGROUND_COLOR);

    for (iloop = 0; iloop < CHESS_Y_NUM; iloop++)
    {
        xres = x_start + GRID_SIZE * iloop;
        if ((xres >= 0) && (xres < fb_inf.w))
        {
            fb_draw_col(fb_inf, xres, y_start, GRID_SIZE * (CHESS_X_NUM - 1), LINE_WIDTH, LINE_COLOR);
        } 
    }

    for (iloop = 0; iloop < CHESS_X_NUM; iloop++)
    {
        yres = y_start + GRID_SIZE * iloop;
        if ((yres >= 0) && (yres < fb_inf.h))
        {
            fb_draw_row(fb_inf, x_start, yres, GRID_SIZE * (CHESS_Y_NUM - 1), LINE_WIDTH, LINE_COLOR);
        } 
    }

    return 0;
}

/* draw a circle chess */
int fb_draw_chess(fb_info fb_inf, int x_center, int y_center, int r_len, u32_t color)
{
    int xres;
    int yres;

    if ((x_center < 0) || (x_center >= fb_inf.w) || (y_center < 0) || (y_center >= fb_inf.h))
    {
        printf("fb_draw_chess cross the border\n");
        exit(1);
    }

    for (xres = x_center - r_len; xres <= x_center + r_len; xres++)
    {
        for (yres = y_center - r_len; yres <= y_center + r_len; yres++)
        {
            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h) 
                && ((xres - x_center) * (xres - x_center) + (yres - y_center) * (yres - y_center) <= r_len * r_len))
            {
                fb_pixel(fb_inf, xres, yres, color);
            }
        }
    }

	return 0;
}





