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
int wav_music_flag = -1;

/* the thread display severial pictures at the same moment */
void *pro_thread_display_jpegs(void *fb_inf)
{
    while (keyboard_display_pic_flag != 1)
    {
        usleep(1);
    }
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

/* thread play music */
void * pro_thread_music(void *pPara)
{
   
    while(1)
    {
        if(wav_music_flag == 1)
        wav_music_play();
        sleep(5);
     
    }  
    
   return NULL;
}

/* main */
int main(int argc, char *argv[]) 
{
    pthread_t p_clock; 
    pthread_t p_keyboard;
    pthread_t p_display_pic;
    pthread_t p_tcp_recv_frame;
    pthread_t p_display_jpegs;
    pthread_t wavplay;

    fb_info fb_inf;

    if (init_fb(&fb_inf) < 0)
    {
        fprintf(stderr, "Error initial framebuffer\b")	;
        return -1;
    }
   
    pthread_create(&p_clock, NULL, pro_thread_clock, &fb_inf);
    pthread_create(&p_keyboard, NULL, pro_thread_keyboard, NULL);
    pthread_create(&p_tcp_recv_frame, NULL, pro_thread_tcp, NULL);
    pthread_create(&wavplay, NULL, pro_thread_music, NULL);
again:
    pthread_create(&p_display_jpegs, NULL, pro_thread_display_jpegs, &fb_inf);

    while (1)
    {
        if (keyboard_display_pic_flag == 2)
        {
            pthread_cancel(p_display_jpegs);
            keyboard_display_pic_flag = 0;
            goto again;
        }

        usleep(1);
    }
        
    return 0;
}
