/* main.c */

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>

#include "frame.h"

int clock_flag = 0;
int keyboard_display_pic_flag = 0;
pthread_t p_display_jpegs;

/* the thread display severial pictures at the same moment */
void *pro_thread_display_jpegs(void *fb_inf)
{
    display_jpeg_mouse(*(fb_info *)fb_inf);

    return NULL;
}

/* the thread receive frame by tcp */
void *pro_thread_tcp(void *para)
{
    tcp_receive_frame();

    return NULL;
}

/* the thread response keyboard */
void *pro_thread_keyboard(void *para)
{
    keyboard_response();

    return NULL;
}

/* the thread paly picture */
void *pro_thread_display_pic(void *fb_inf)
{
    while (keyboard_display_pic_flag == 0)
    {
        usleep(1);
    }
    pthread_cancel(p_display_jpegs);
    display_pic(*(fb_info *)fb_inf);

    return NULL;
}

/* the thread display clock */
void *pro_thread_clock(void *fb_inf)
{
    while (clock_flag == 0)
    {
        usleep(1);
    }
    display_clock(*(fb_info *)fb_inf);

    return NULL;
}

/* main */
int main(int argc, char *argv[]) 
{
    pthread_t p_clock; 
    pthread_t p_keyboard;
    pthread_t p_display_pic;
    pthread_t p_tcp_recv_frame;
//    pthread_t p_display_jpegs;

    fb_info fb_inf;

    if (init_fb(&fb_inf) < 0)
    {
        fprintf(stderr, "Error initial framebuffer\b")	;
        return -1;
    }
 
    pthread_create(&p_display_jpegs, NULL, pro_thread_display_jpegs, &fb_inf);   
    pthread_create(&p_clock, NULL, pro_thread_clock, &fb_inf);
    pthread_create(&p_keyboard, NULL, pro_thread_keyboard, NULL);
    pthread_create(&p_tcp_recv_frame, NULL, pro_thread_tcp, NULL);
again:
    pthread_create(&p_display_pic, NULL, pro_thread_display_pic, &fb_inf);

    while (1)
    {
        if (keyboard_display_pic_flag == 2)
        {
        pthread_cancel(p_display_pic);
        keyboard_display_pic_flag = 0;
        goto again;
        }
        usleep(1);
    }
        
    return 0;
}
