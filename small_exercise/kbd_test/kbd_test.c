/* key_test.c */

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

/* main */ 
int main (int argc, char *argv[])
{
    struct input_event ev[64];
    int fd;
    int  size = sizeof (struct input_event);
    char name[256] = "Unknown";
    char *device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";

    if ((getuid ()) != 0)
    {
        printf ("You are not root! This may not work...\n");
    }
 
    //Open Device
    if ((fd = open (device, O_RDONLY)) == -1)
    {
        printf ("%s is not a vaild device.\n", device);
    }
 
    //Print Device Name
    ioctl (fd, EVIOCGNAME (sizeof (name)), name);
    printf ("Reading From : %s (%s)\n", device, name);
 
    while (1)
    {
        if (read (fd, ev, size * 64) < size)
        {
            perror("read()"); 
            exit(1);   
        } 
 
        if (ev[0].value != ' ' && ev[1].value == 1 && ev[1].type == 1) // Only read the key press event
        { 
            printf ("Code1[%d]\n", (ev[1].code));;
        }
    }
 
  return 0;
}
