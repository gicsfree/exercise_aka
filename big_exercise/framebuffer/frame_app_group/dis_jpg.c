#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "frame.h"


////////////////////////////////////////////////////////////////////////////

/***************************   扫一圈   **************************/

////////////////////////////////////////////////////////////////////////////

int display_jpeg_scan(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int x = fb_inf.w/2;
    int y = fb_inf.h/2;
    int xres;
    int yres;
    int scan;
    

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
     

    for(scan = x; scan > 0; scan--)
    {
        for(yres = 0; yres < y; yres++)
        {
            xres = yres * ((float)(scan - 512)/(0 - 384)) + scan;
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);

        }
	usleep(10);
    }

    for(scan = 0; scan <= fb_inf.h; scan++)
    {
        for(xres = 0; xres < x; xres++)
        {
            yres = xres * ((float)(scan - 384)/(0 - 512)) + scan;
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
        }
       usleep(10);
    }
    
    for(scan = fb_inf.w; scan >= 0; scan--)
    {
        for(yres = y; yres < fb_inf.h; yres++)
        {
            xres = yres * ((float)(scan - 512)/(0 -384)) + scan;
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
        }
       usleep(10);
    }

    
    for(scan = 0; scan <= fb_inf.h; scan++)
    {
        for(xres = x; xres < fb_inf.w; xres++)
        {
            yres = xres * ((float)(scan - 384)/(0 - 512)) + scan;
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);
        }
       usleep(10);
    }
    
    for(scan = fb_inf.w; scan >= 0; scan--)
    {
        for(yres = 0; yres < y; yres++)
        {
            xres = yres * ((float)(scan - 512)/(0 - 384)) + scan;
            fb_pixel(fb_inf, xres, yres, buf32[xres + (yres * fb_inf.w)]);

        }
	usleep(10);
    }
    

    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}


//////////////////////////////////////////////////////////////////////////////////

/*******************************  风车  ****************************/

//////////////////////////////////////////////////////////////////////////////////


int display_jpeg_scan_m(char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int x = fb_inf.w/2;
    int y = fb_inf.h/2;
    int xres1, xres2, xres3, xres4;
    int yres1, yres2, yres3, yres4;
    int scan1, scan2, scan3, scan4;
    

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
     

    scan2 = y;
    for(scan1 = x; scan1 >= 0; scan1--)
    {
        for(yres1 = 0; yres1 < fb_inf.h; yres1++)
        {
             
            xres1 = yres1 * ((float)(scan1 - 512)/(0 - 384)) + scan1;
            fb_pixel(fb_inf, xres1, yres1, buf32[xres1 + (yres1 * fb_inf.w)]);
        }

	if(scan2 <= fb_inf.h)
	{
	    for(xres2 = 0; xres2 < fb_inf.w; xres2++)
            {
	        yres2 = xres2 * ((float)(scan2 - 384)/(0 - 512)) +scan2;
	        fb_pixel(fb_inf, xres2, yres2, buf32[xres2 + (yres2 * fb_inf.w)]);
	    }
	}
	scan2++;
        usleep(10);
    }

    scan4 = y;
    for(scan3 = x; scan3 <=  fb_inf.w; scan3++)
    {
        for(yres3 = 0; yres3 < fb_inf.h; yres3++)
        {
            xres3 = yres3 * ((float)(scan3 - 512)/(0 - 384)) + scan3;
            fb_pixel(fb_inf, xres3, yres3, buf32[xres3 + (yres3 * fb_inf.w)]);
        }

	if(scan4 >= 0)
	{
	    for(xres4 = 0; xres4 < fb_inf.w; xres4++)
	    {
	         yres4 = xres4 * ((float)(scan4 - 384)/(0 - 512)) + scan4;
		  fb_pixel(fb_inf, xres4, yres4, buf32[xres4 + (yres4 * fb_inf.w)]);
	    }
	}
	scan4--;
	usleep(10);
    }

    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
*                                      翻转                                   *
*****************************************************************************/       

int display_jpeg_zoom(char * filename1, fb_info fb_inf)
{
    fb_info jpeg_inf;
    fb_info zoom_inf;
    int xres;
    int yres;
    int x = 235;
    int x_x = 747;

    if (init_fb(&zoom_inf) < 0)
    {
        fprintf(stderr, "Error initial framebuffer\b")	;
    	 return -1;
    }

    u8_t *buf24 = decode_jpeg(filename1, &jpeg_inf);

    for(zoom_inf.w = 40; zoom_inf.w <= 512; zoom_inf.w = zoom_inf.w + 2)
    {
	u8_t *scale_buf = scale24(buf24, zoom_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, zoom_inf);

	for(yres = 0; yres < zoom_inf.h; yres++)
	{
	    for(xres = 1; xres < zoom_inf.w; xres++)
	    {
		fb_pixel(fb_inf, x + xres, yres, buf32[xres + yres * zoom_inf.w]);
		fb_pixel(fb_inf, x_x + xres, yres, buf32[xres + yres * zoom_inf.w]);		
	    }	   
	}
		
       free(scale_buf);
       free(buf32);
	x = x - 1;
	x_x = x_x - 1;
    }
    
    free(buf24);
    return 0;
}
