/* display-bmp.c */

#include <stdlib.h>
#include <unistd.h>

#include "frame.h"

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


