/* main.c */

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "frame.h"

/* the thread send and receive chessitem */
void *pro_thread_tcp(void *addr)
{
    tcp_send_chessitem((const char *)addr);

    return NULL;
}

/* main */
int main(int argc, char *argv[]) 
{
    fb_info fb_inf;
    pthread_t p_tcp;

    if (argc != 2)
    {
        printf("Usage: ./appname 192.168.1.***\n");
        exit(1);
    }
    
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

    pthread_create(&p_tcp, NULL, pro_thread_tcp, argv[1]);
    mouse_work(fb_inf, X_START, Y_START);
    
    munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
    
    return 0;
}

