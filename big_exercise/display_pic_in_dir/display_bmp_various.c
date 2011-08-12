/* display_bmp_various.c */

#include <unistd.h>

#include "frame.h"

/* display bmp various */ 
int display_bmp_various(const char *bmpname, fb_info fb_inf)
{
    static int num = 0;

    switch(num++ % 4)
    {
        case 0:
            display_bmp(bmpname, fb_inf);
            sleep(1);
            break;

        default:
            display_bmp(bmpname, fb_inf);
            sleep(1);
            break;
    }

    return 0; 
}
