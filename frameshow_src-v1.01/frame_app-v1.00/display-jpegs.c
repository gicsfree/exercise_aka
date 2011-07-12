/* display-jpegs.c */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "frame.h"

#ifdef FRAME_SUPPORT_JPEG
////////////////////////////////////////////////////////////////

#if 1
int display_jpegs(fb_info fb_inf)
{
    int height;
    int width;
    fb_info size_inf;

    size_inf.w = fb_inf.w / 4;
    size_inf.h = fb_inf.h / 3;

    display_jpeg("1.jpg", fb_inf);

    display_jpeg_inner("8.jpg", fb_inf.w / 6, fb_inf.h / 4, size_inf, fb_inf);
    display_jpeg_inner("9.jpg", fb_inf.w / 2, fb_inf.h / 4, size_inf, fb_inf);
    display_jpeg_inner("10.jpg", fb_inf.w * 5 / 6, fb_inf.h / 4, size_inf, fb_inf);

    display_jpeg_inner("11.jpg",  fb_inf.w / 6, fb_inf.h * 3 / 4, size_inf, fb_inf);
    display_jpeg_inner("12.jpg",  fb_inf.w / 2, fb_inf.h * 3 / 4, size_inf, fb_inf);
    display_jpeg_inner("13.jpg",  fb_inf.w * 5 / 6, fb_inf.h * 3 / 4, size_inf, fb_inf);

//    display_jpeg_mouse(fb_inf);

    return 0;
}
#endif

#if 1
/* display jpeg inner */
int display_jpeg_inner(const char *jpegname, int x, int y, fb_info size_inf, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int xres;
    int yres;
    int xloop;
    int yloop;

    u8_t *buf24 = decode_jpeg(jpegname, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, size_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, size_inf);
    
    for (yloop = 0; yloop < size_inf.h; yloop++)
    {
        for (xloop = 0; xloop < size_inf.w; xloop++)
        {
            xres = x - size_inf.w / 2 + xloop;
            yres = y - size_inf.h / 2 + yloop;

            if ((xres >= 0) && (xres < fb_inf.w) && (yres >= 0) && (yres < fb_inf.h))
             {
                fb_pixel(fb_inf, xres, yres, buf32[xloop + yloop * size_inf.w]);
             }
        }
    }
        
    free(buf24);
    free(scale_buf);
    free(buf32);
    
    return 0;
}
#endif

#ifdef FRAME_SUPPORT_MOUSE
#if 0
/* display jpeg when mouse work */
int display_jpeg_mouse(fb_info fb_inf)
{
    int mfd = -1;
    u8_t buf[8];
    mouse_event_t mevent;

    int m_x = fb_inf.w / 2;
    int m_y = fb_inf.h / 2;
    int p_x;
    int p_y;
        
    mouse_open(NULL, &mfd);

    fb_save_cursor(fb_inf, m_x, m_y);
    p_x = m_x;   
    p_y = m_y;  
    fb_draw_cursor(fb_inf, m_x, m_y);
        
    for(;;)
     {
        if (read(mfd, buf, 8) != -1)
         {
	     mouse_parse(buf, &mevent);

	     m_x += mevent.x;
	     m_y += mevent.y;
                           
            if((m_x >= 0) && (m_x < fb_inf.w - C_WIDTH) && (m_y >= 0) && (m_y < fb_inf.h - C_HEIGHT))
              {
                fb_restore_cursor(fb_inf, p_x, p_y);
                fb_save_cursor(fb_inf, m_x, m_y); 
                p_x = m_x;   
                p_y = m_y;
	         fb_draw_cursor(fb_inf, m_x, m_y);
              }
            else
             {
	         m_x -= mevent.x;
	         m_y -= mevent.y;
             }

	     switch (mevent.button)
              {
	         case 1:
		      printf("left\n");
		      break;

		  case 2:
		      printf("right\n");
		      break;
                     
		  case 3:
		      printf("middle\n");
		      break;

		  default:
		      break;
	     }
	 }	
        usleep(300);
     }
     
    return 0;
}
#endif
#endif    /* FRAME_SUPPORT_MOUSE */

#endif
