/* display-bmp.c */

#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "frame.h"

#ifdef FRAME_SUPPORT_BMP

#if 1

/* display bmp */
int display_bmp(const char *bmpname, fb_info fb_inf)
{
    fb_info bmp_inf;
    int xres;
    int yres;
    
    u8_t *buf24 = decode_24bmp(bmpname, &bmp_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, bmp_inf);
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

#if 1
/* display bmp blind */
int display_bmp_blind(const char *bmpname, fb_info fb_inf)
{
    fb_info bmp_inf;
    int xres;
    int yres;
    int xloop;
    
    u8_t *buf24 = decode_24bmp(bmpname, &bmp_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, bmp_inf);
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
/* display bmp some circle */
int display_bmp_circle_num(const char *bmpname, fb_info fb_inf, int x_num, int y_num)
{
    fb_info bmp_inf;
    int xres;
    int yres;
    int xres_center;
    int yres_center;
    int x_loop;
    int y_loop;
    int r_len;
    
    u8_t *buf24 = decode_24bmp(bmpname, &bmp_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, bmp_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
//    for(r_len = 0; r_len <= sqrt((fb_inf.w / x_num) * (fb_inf.w / x_num) + (fb_inf.h / y_num) * (fb_inf.h / y_num)) / 2 + 10; r_len++)
    for(r_len = sqrt((fb_inf.w / x_num) * (fb_inf.w / x_num) + (fb_inf.h / y_num) * (fb_inf.h / y_num)) / 2 + 10; r_len >= 0; r_len--)
    {
        for (x_loop = 0; x_loop <= r_len; x_loop++)
        {
            for (y_loop = 0; y_loop <= r_len; y_loop++)
            {
                if (((x_loop * x_loop + y_loop * y_loop) <= r_len * r_len)
                   && ((x_loop * x_loop + y_loop * y_loop) >= (r_len - 1) * (r_len - 1)))
                { 
                    for (xres_center = fb_inf.w / (x_num * 2); xres_center < fb_inf.w; xres_center += fb_inf.w / x_num )
                      {
                        for (yres_center = fb_inf.h / (y_num * 2); yres_center < fb_inf.h; yres_center += fb_inf.h / y_num ) 
                           {       
                            xres = xres_center + x_loop;
                            yres = yres_center + y_loop;
                            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                               {
                                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                               }

                            xres = xres_center + x_loop;
                            yres = yres_center - y_loop;
                            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                               {
                                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                               }

                            xres = xres_center - x_loop;
                            yres = yres_center + y_loop;
                            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                               {
                                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                               }

                            xres = xres_center - x_loop;
                            yres = yres_center - y_loop;
                            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
                               {
                                fb_pixel(fb_inf, xres, yres, buf32[xres + yres * fb_inf.w]);
                               }
                         } 
                    }
                }
            }            
        }
       usleep(500 * x_num * y_num);
    }
    
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#if 1
/* display bmp square */
int display_bmp_square(const char *bmpname, fb_info fb_inf)
{
    fb_info bmp_inf;
    int x_len;
    int y_len;
    int x_loop;
    int y_loop;
    
    u8_t *buf24 = decode_24bmp(bmpname, &bmp_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, bmp_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for (x_len = 0; x_len < fb_inf.w / 2 ; x_len++)
//    for (x_len = fb_inf.w / 2 - 1; x_len >= 0; x_len--)
    {
        y_len = (float)fb_inf.h / fb_inf.w *x_len;
        for (x_loop = 0; x_loop <= x_len; x_loop++)
        {
            fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 + y_len, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 + y_len) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 + x_loop, fb_inf.h / 2 - y_len, buf32[fb_inf.w / 2 + x_loop + ((fb_inf.h / 2 - y_len) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 + y_len, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 + y_len) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 - x_loop, fb_inf.h / 2 - y_len, buf32[fb_inf.w / 2 - x_loop + ((fb_inf.h / 2 - y_len) * fb_inf.w)]);
        }
        for (y_loop = 0; y_loop <= y_len; y_loop++)
        {
            fb_pixel(fb_inf, fb_inf.w / 2 + x_len, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 + x_len + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 + x_len, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 + x_len + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 - x_len, fb_inf.h / 2 + y_loop, buf32[fb_inf.w / 2 - x_len + ((fb_inf.h / 2 + y_loop) * fb_inf.w)]);
            fb_pixel(fb_inf, fb_inf.w / 2 - x_len, fb_inf.h / 2 - y_loop, buf32[fb_inf.w / 2 - x_len + ((fb_inf.h / 2 - y_loop) * fb_inf.w)]);
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
/* display bmp diagonal open */
int display_bmp_diagonal(const char *bmpname, fb_info fb_inf)
{
    fb_info bmp_inf;
    int xres;
    int xloop;
    int xres1;
    int xres2;
    int yres1;
    int yres2;
    float h_div_w = (float)fb_inf.h / fb_inf.w;
    
    u8_t *buf24 = decode_24bmp(bmpname, &bmp_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, bmp_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for (xloop = fb_inf.w - 1; xloop >= 0; xloop--)
//    for (xloop = 0; xloop < fb_inf.w; xloop++)
    {
        for (xres = 0; xres < xloop; xres++)
        {
            xres1 = xres;
            yres1 = h_div_w * (xloop - xres1);
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

#endif
