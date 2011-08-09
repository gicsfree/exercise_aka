/* main.c */

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "frame.h"

/* main */
int main(int argc, char *argv[]) 
{
    fb_info fb_inf;
    
    if (init_fb(&fb_inf) < 0)
    {
    	  fprintf(stderr, "Error initial framebuffer\b")	;
    	  return -1;
    }

    if (init_ft("mao.ttf", 150) < 0)
    {
        fprintf(stderr, "Error initial font\b");
    	 exit(1);
    }

    mouse_work(fb_inf, X_START, Y_START);
    
    munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
    
    return 0;
}
