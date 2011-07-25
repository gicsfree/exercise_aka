/* test mouse */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "frame.h"

#ifdef FRAME_SUPPORT_MOUSE

/* mouse test */
int test_mouse(fb_info fb_inf)
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
	     //printf("dx:%d\tdy:%d\n", mevent.x, mevent.y);
	     //printf("mx:%d\tmy:%d\n", m_x, m_y);

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
//		      printf("left\n");
		      break;

		  case 2:
//		      printf("right\n");
		      break;
                     
		  case 3:
//		      printf("middle\n");
		      break;

		  default:
		      break;
	     }
	 }	
        usleep(300);
     }
     
    return 0;
}

#endif    /* FRAME_SUPPORT_MOUSE */
