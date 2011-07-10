/* disp-jpeg.c */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "frame.h"

#ifdef FRAME_SUPPORT_JPEG
////////////////////////////////////////////////////////////////
/* display jpeg */
int display_jpeg(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    
    for(xres = 0; xres < fb_inf.h; ++xres)
    {
        for (yres = 0; yres < fb_inf.w; ++yres)
        {
            fb_pixel(fb_inf, yres, xres, buf32[yres + (xres * fb_inf.w)]);
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}

#if 1
/* display jpeg blind y */
int display_jpeg_blind_y(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int yloop;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(yloop = 0; yloop < fb_inf.h / 5; yloop++)
    {
        for (yres = yloop; yres < fb_inf.h; yres += fb_inf.h / 5)
        {
            for(xres = 0; xres < fb_inf.w; xres++)
            {
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
            }            
        }
        usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display jpeg blind x */
int display_jpeg_blind_x(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(xloop = 0; xloop < fb_inf.w / 5; xloop++)
    {
        for (xres = xloop; xres < fb_inf.w; xres += fb_inf.w / 5)
        {
            for(yres = 0; yres < fb_inf.h; yres++)
            {
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
            }            
        }
        usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display jpeg blind middle */
int display_jpeg_blind_m(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (xloop = 0; xloop < fb_inf.w / 2; xloop++)
    {
        for(yres = 0; yres < fb_inf.h; yres++)
        {
            fb_pixel(fb_inf, fb_inf.w / 2 - xloop, yres, buf32[fb_inf.w / 2 - xloop + (yres * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 + xloop, yres, buf32[fb_inf.w / 2 + xloop + (yres * fb_inf.w)]);
        }  
        usleep(1);          
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display jpeg cross */
int display_jpeg_cross(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int xres_temp;
    int yres_temp;
    int t_sum = 0;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (xres = 0; xres < fb_inf.w; xres++)
    {
        for(yres = 0; yres < fb_inf.h; yres++)
        {
            if ((yres / (fb_inf.h /5)) % 2 == 0)
            {
                fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
            }
            else
            {
                xres_temp = fb_inf.w - 1 - xres;
                yres_temp = yres;
                fb_pixel(fb_inf, xres_temp, yres_temp, buf32[xres_temp + (yres_temp * fb_inf.w)]);
            }
        }  

        t_sum++;
        if (t_sum % 3 == 0)
        {
            usleep(1);
        }          
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 0
/* display jpeg circle */
int display_jpeg_circle(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int r_len;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(r_len = 0; r_len < sqrt(fb_inf.w * fb_inf.w + fb_inf.h * fb_inf.h) / 2 + 1; r_len++)
    {
        for (xres = fb_inf.w / 2 - r_len; xres <= fb_inf.w / 2 + r_len; xres++)
        {
            for(yres = fb_inf.h / 2 - r_len; yres <= fb_inf.h / 2 + r_len; yres++)
            {
                if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h)
                      && (((xres - fb_inf.w / 2) * (xres - fb_inf.w / 2) + (yres - fb_inf.h / 2) * (yres - fb_inf.h / 2)) <= r_len * r_len)
                      && (((xres - fb_inf.w / 2) * (xres - fb_inf.w / 2) + (yres - fb_inf.h / 2) * (yres - fb_inf.h / 2)) >= (r_len - 1) * (r_len - 1))) 
                    fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
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
/* display jpeg circle */
int display_jpeg_circle(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int r_len;
    int x_loop;
    int y_loop;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(r_len = 0; r_len < sqrt(fb_inf.w * fb_inf.w + fb_inf.h * fb_inf.h) / 2 + 1; r_len++)
    {
        for (x_loop = 0; x_loop < fb_inf.w / 2; x_loop++)
        {
            for (y_loop = 0; y_loop < fb_inf.h / 2; y_loop++)
            {
                if (((x_loop * x_loop + y_loop * y_loop) <= r_len * r_len)
                   && ((x_loop * x_loop + y_loop * y_loop) >= (r_len - 1) * (r_len - 1)))
                { 
                    fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
                }
            }            
        }
       usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display jpeg diagonal close */
int display_jpeg_diagonal_c(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int xres1;
    int xres2;
    int yres1;
    int yres2;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
//    for (xloop = fb_inf.w - 1; xloop >= 0; xloop--)
    for (xloop = 0; xloop < fb_inf.w; xloop++)
    {
        for (xres = 0; xres < xloop; xres++)
        {
            xres1 = xres;
            yres1 = ((float )fb_inf.h / fb_inf.w) * (xloop - xres1);
            xres2 = fb_inf.w - 1 - xres1;
            yres2 = fb_inf.h - 1 - yres1;
            fb_pixel(fb_inf, xres1, yres1, buf32[xres1 + (yres1 * fb_inf.w)]);
            fb_pixel(fb_inf, xres2, yres2, buf32[xres2 + (yres2 * fb_inf.w)]);          
        }
        usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display jpeg diagonal open */
int display_jpeg_diagonal_o(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int xres1;
    int xres2;
    int yres1;
    int yres2;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (xloop = fb_inf.w - 1; xloop >= 0; xloop--)
//    for (xloop = 0; xloop < fb_inf.w; xloop++)
    {
        for (xres = 0; xres < xloop; xres++)
        {
            xres1 = xres;
            yres1 = ((float )fb_inf.h / fb_inf.w) * (xloop - xres1);
            xres2 = fb_inf.w - 1 - xres1;
            yres2 = fb_inf.h - 1 - yres1;
            fb_pixel(fb_inf, xres1, yres1, buf32[xres1 + (yres1 * fb_inf.w)]);
            fb_pixel(fb_inf, xres2, yres2, buf32[xres2 + (yres2 * fb_inf.w)]);          
        }
        usleep(1);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display jpeg square */
int display_jpeg_square(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int r_len;
    int x_loop;
    int y_loop;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(r_len = 0; r_len < fb_inf.w / 2; r_len++)
    {
        for (x_loop = 0; x_loop < fb_inf.w / 2; x_loop++)
        {
            for (y_loop = 0; y_loop < fb_inf.h / 2; y_loop++)
            {
                if ((x_loop * y_loop <= (float)(fb_inf.h) / fb_inf.w * r_len * r_len)
                   && (x_loop * y_loop >= ((float)(fb_inf.h) / fb_inf.w * r_len - 1)* (r_len - 1)))
                { 
                    fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
                }
            }            
        }
       usleep(100);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display jpeg point */
int display_jpeg_point(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int t_sum;
    int iloop;
    int jloop;
    int x_flag = 4;
    int y_flag = 4;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for (iloop = 0; iloop < x_flag; iloop++)
    {
        for (jloop = 0; jloop < y_flag; jloop++)
        {
            for (xres = 0; xres < fb_inf.h; ++xres)
             {
                for (yres = 0; yres < fb_inf.w; ++yres)
                  {
                    if (((xres % x_flag) == iloop) && ((yres % y_flag) == jloop))
                        {
                        fb_pixel(fb_inf, yres, xres, buf32[yres + (xres * fb_inf.w)]);
                        }
                   }
             }
            usleep(200000);
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 0
/* display jpeg square */
int display_jpeg_square(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int r_len;
    int x_loop;
    int y_loop;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(r_len = 0; r_len < fb_inf.w / 2; r_len++)
    {
        for (x_loop = 0; x_loop < fb_inf.w / 2; x_loop++)
        {
            for (y_loop = 0; y_loop < fb_inf.h / 2; y_loop++)
            {
            
           
                if ((x_loop * y_loop <= (float)(fb_inf.h) / fb_inf.w * r_len * r_len)
                   && (x_loop * y_loop >= ((float)(fb_inf.h) / fb_inf.w * r_len - 1)* (r_len - 1)))
                { 
                    fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
                    fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
                }
            }            
        }
       usleep(100);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
int display_jpeg_small(char *filename, int x, int y, fb_info new_inf, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, new_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, new_inf);
    
    
    for(xres = x; xres < new_inf.h; ++xres)
    {
        for (yres = y; yres < new_inf.w; ++yres)
        {
            if (yres % 2 == 0)
            fb_pixel(fb_inf, yres, xres, buf32[yres + (xres * new_inf.w)]);
        }
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#endif    /* FRAME_SUPPORT_JPEG */
