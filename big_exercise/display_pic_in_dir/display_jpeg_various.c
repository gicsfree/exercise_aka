/* display_jpeg.c */

#include <unistd.h>

#include "frame.h"

/* display jpeg various */
int display_jpeg_various(const char *jpegname, fb_info fb_inf)
{
    static int num = 0;

    switch (num++ % 100)
    {
        case 1:
            display_jpeg_blind_y(jpegname, fb_inf);
            sleep(1);
            break;

        case 2:
            display_jpeg_blind_x(jpegname, fb_inf);
            sleep(1);
            break;

        case 3:
            display_jpeg_cross(jpegname, fb_inf);
            sleep(1);
            break;

        case 4:
            display_jpeg_door(jpegname, fb_inf);
            sleep(1);
            break;

        case 5:
            display_jpeg_circle(jpegname, fb_inf);
            sleep(1);
            break;

        case 6:
            display_jpeg_diagonal_c(jpegname, fb_inf);
            sleep(1);
            break;

        case 7:
            display_jpeg_circle_area(jpegname, fb_inf);
            sleep(1);
            break;

        case 8:
            display_jpeg_point(jpegname, fb_inf);
            sleep(1);
            break;

        case 9:
            display_jpeg_square(jpegname, fb_inf);
            sleep(1);
            break;

        case 10:
            display_jpeg_circle_num(jpegname, fb_inf, 4, 3);
            sleep(1);
            break;

        case 11:
            display_jpeg_down(jpegname, fb_inf);
            sleep(1);
            break;

        case 12:
            display_jpeg_mosaic(jpegname, fb_inf, 30);
            sleep(1);
            break;

        default:
            display_jpeg(jpegname, fb_inf);
            sleep(1);
            break;
    }

    return 0; 
}
