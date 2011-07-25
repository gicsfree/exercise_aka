#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#include "frame.h"


/* display jpg block*/
int display_jpeg_block(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
  
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    
    for(yres = 256; yres < 512; ++yres)
    {
        for (xres = 340; xres < 684; ++xres)
        {
	 fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
    	}
      
    }
      sleep(1);
   for(yres = 255; yres >= 0; --yres)
    {
        for (xres = 340; xres < 684; ++xres)
        {
	 fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
    	}
      
    }
    sleep(1);
   for(xres = 339; xres >= 0; --xres)
    {
        for (yres = 256; yres < 512; ++yres)
        {
	 fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
    	}
      
    }
    sleep(1);
   for(yres = 512; yres < fb_inf.h; ++yres)
    {
        for (xres = 340; xres < 684; ++xres)
        {
	 fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
    	}
     
    }
     sleep(1);
   for(xres = 684; xres < fb_inf.w; ++xres)
    {
        for (yres = 256; yres < 512; ++yres)
        {
	 fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
    	}
      
    }
    sleep(1);
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
