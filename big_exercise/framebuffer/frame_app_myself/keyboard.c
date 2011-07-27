#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

extern int keyboard_display_pic_flag;
 
void handler (int sig)
{
    printf ("\nexiting...(%d)\n", sig);
    exit (0);
}
 
void perror_exit (char *error)
{
    perror (error);
    handler (9);
}

/* response when keyboard work */ 
int keyboard_response(void)
{
    struct input_event ev[64];
    int fd, rd, value, size = sizeof (struct input_event);
    char name[256] = "Unknown";
    char *device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
 
    if ((getuid ()) != 0)
    {
        printf ("You are not root! This may not work...\n");
    }
 
    /* Open Device */
    if ((fd = open (device, O_RDONLY)) == -1)
    {
        printf ("%s is not a vaild device.\n", device);
    }
 
    /*Print Device Name */
    ioctl (fd, EVIOCGNAME (sizeof (name)), name);
    printf ("Reading From : %s (%s)\n", device, name);
 
    while (1)
    {
        if ((rd = read (fd, ev, size * 64)) < size)
        {
            perror_exit ("read()");     
        }
 
        value = ev[0].value;
 
        if (value != ' ' && ev[1].value == 1 && ev[1].type == 1) // Only read the key press event
        {
//            printf("Code1[%d]\n", (ev[1].code));
    
            if (ev[1].code == 31)
            {
                keyboard_display_pic_flag = 1;
            }

            if (ev[1].code == 18)
            {
                keyboard_display_pic_flag = 2;
            }
        }
    }
 
    return 0;
}
