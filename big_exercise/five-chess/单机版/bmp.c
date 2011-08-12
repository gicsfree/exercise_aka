#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "frame.h"

#ifdef FRAME_SUPPORT_BMP

/* bmp decode */
u8_t *decode_24bmp (const char *bmpname, fb_info *bmp_inf)
{
    int fd;
    u8_t rd_rgb[3];
    int iloop;
    int jloop;
    int bmpwidth;
    int bmpheight;
  
    if ((fd = open(bmpname, O_RDONLY)) < 0)
    {
        fprintf(stderr, "Open %s failed:%s\n", bmpname, strerror(errno));
        exit(1);
    }

    if (lseek(fd, 18, SEEK_SET) < 0)
    {
        perror("lseek bmp 18");
        exit(1);
    }
    if (read(fd, &bmpwidth, 4) < 0)
    {
        perror("read bmp width");
        exit(1);
    }
    if (read(fd, &bmpheight, 4) < 0)
    {
        perror("read bmp height");
        exit(1);
    } 

    bmp_inf->w = bmpwidth;
    bmp_inf->h = bmpheight;
    u8_t *rgbbuf = (u8_t *)malloc(3 * (bmp_inf->w * bmp_inf->h));   

    if (lseek(fd, 54, SEEK_SET) < 0)
    {
        perror("lseek bmp 54");
        exit(1);
    }
    for (jloop = bmp_inf->h - 1; jloop >= 0; jloop--)
    {
       for (iloop = 0; iloop < bmp_inf->w; iloop++)
        {
           if (read(fd, rd_rgb, 3) < 0)
            {
               perror("read rgb");
               exit(1);
            } 
           rgbbuf[iloop * 3 + jloop * bmp_inf->w * 3 + 0] = rd_rgb[2];
           rgbbuf[iloop * 3 + jloop * bmp_inf->w * 3 + 1] = rd_rgb[1];
           rgbbuf[iloop * 3 + jloop * bmp_inf->w * 3 + 2] = rd_rgb[0];
        }        
    }

    if (close(fd) < 0)
    {
        perror("close bmp");
        exit(1);   
    }

    return rgbbuf;
}
#endif
