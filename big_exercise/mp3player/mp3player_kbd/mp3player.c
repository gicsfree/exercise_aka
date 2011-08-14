/* mp3player.c */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <linux/input.h>

#include "mp3player.h"

#define PERM S_IRUSR|S_IWUSR													

pid_t gradchild;
pid_t pid;
int shmid;
char *p_addr;
int first_key = 1;
int play_flag = 0;

/* play song*/
void play(link_t currentsong, link_t head)
{
    pid_t g_pid;
    char *c_addr;

    if (currentsong == head)
    {
        printf("cannot play the head\n");
        exit(1);
    }

    while (1)
    {
        g_pid = fork();
        if (g_pid == -1)
        {	
            perror("fork");
            exit(1);
        }
        else 
        {
            if (g_pid == 0)
            {
                printf("THIS SONG IS %s\n", currentsong->songname);
                execl("/usr/bin/mp3blaster", "mp3blaster", currentsong->songname, NULL);
                printf("\n\n\n");
            }
            else
            {
                c_addr = shmat(shmid, 0, 0);

                memcpy(c_addr, &g_pid, sizeof(pid_t));
                memcpy(c_addr + sizeof(pid_t) + 1, &currentsong, 4);

                if (g_pid == wait(NULL))
                {
                    currentsong = currentsong->next;
                    if (currentsong == head)
                     {
                        currentsong = currentsong->next;       
                     }
                    printf("===============================NEXT MP3=============================\n");
                }
            }
        }
    }
}

/* startplay */
void startplay(pid_t *childpid, link_t my_song, link_t head)
{
    pid_t c_pid;
    c_pid = fork();

    if (c_pid > 0)
    {
        *childpid = c_pid; 
        play_flag = 1;
    }
    else if(0 == c_pid) 
    {	
        play(my_song, head);
    }
}
/* pause song */
void my_pause(pid_t g_pid)
{
    printf("=======================PAUSE!PRESS K1 TO CONTINUE===================\n");
    kill(g_pid, SIGSTOP);
    play_flag = 0;
}

/* continue play song */
void conti_play(pid_t g_pid)
{
    printf("===============================CONTINUE=============================\n");
    kill(g_pid, SIGCONT);
    play_flag = 1;
}

/* stop song */
void my_stop(pid_t g_pid)
{
    printf("=======================STOP!PRESS K1 TO START PLAY===================\n");
    kill(g_pid, SIGKILL); 
    kill(pid, SIGKILL); 
}

/* play next song */
void next(pid_t g_pid, link_t head)
{
    link_t nextsong;

    printf("===============================NEXT MP3=============================\n");
    memcpy(&nextsong, p_addr + sizeof(pid_t) + 1, 4);
    nextsong = nextsong->next;
    if (nextsong == head)
    {
        nextsong = nextsong->next;
    }
    kill(g_pid, SIGKILL);
    kill(pid, SIGKILL);
    wait(NULL);
    startplay(&pid, nextsong, head);
}

/* play previous song */
void prev(pid_t g_pid, link_t head)
{
    link_t prevsong;

    printf("===============================PRIOR MP3=============================\n");
    memcpy(&prevsong, p_addr + sizeof(pid_t) + 1, 4);
    prevsong = prevsong->prev;
    if (prevsong == head)
    {
        prevsong = prevsong->prev;
    }
    kill(g_pid, SIGKILL);
    kill(pid, SIGKILL);
    wait(NULL);
    startplay(&pid, prevsong, head);
}

/* main */
int main(void)
{
    int kbd_fd;
    int key_value;
    link_t head;
    struct input_event ev[64];
    int  size = sizeof (struct input_event);
    char *device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";

    if ((kbd_fd = open (device, O_RDONLY)) == -1)
    {
        printf ("%s is not a vaild device.\n", device);
    }
	
    head = create_song_list(SONG_DIRECTORY);
    if (is_empty_list(head) == 1)
    {
        printf("The song list is empty !\n");
        destroy_list(head);
        exit(1);
    }

    printf("===================================SONG LIST====================================\n");
    traverse_list(print_songname, head);
    printf("================================================================================\n");

	
    printf("===================================FUNTION======================================\n\n");
    printf("        K1:START/PAUSE     K2:STOP   K3:NEXT      K4:PRIOR\n\n");
    printf("================================================================================\n");

    if ((shmid = shmget(IPC_PRIVATE, 5, PERM)) == -1)
    {
        perror("shmget");
        exit(1);
    }
    p_addr = shmat(shmid, 0, 0);
    memset(p_addr, '\0', 1024);
		
    while (1) 
    {
        fd_set rds;
        int ret;

        FD_ZERO(&rds);
        FD_SET(kbd_fd, &rds);

        ret = select(kbd_fd + 1, &rds, NULL, NULL, NULL);
        if (ret < 0) 
        {
            perror("select");
            exit(1);
        }
        if (ret == 0) 
        {
            printf("Timeout.\n");
        }
        else if (FD_ISSET(kbd_fd, &rds))
        {
            if (read (kbd_fd, ev, size * 64) < size)
            {
                 perror("read()"); 
                exit(1);   
            }  
            if (ev[0].value != ' ' && ev[1].value == 1 && ev[1].type == 1) // Only read the key press event
            { 
                key_value = ev[1].code;
                printf ("Code1[%d]\n", (ev[1].code));
				
                if (first_key == 1)
                {
                    switch(key_value)
                    {	
                        case 105:
                            startplay(&pid, head->next, head);
                            first_key = 0;
                            break;

                        case 106:
                        case 103:
                        case 108:
                            printf("=======================PRESS K1 TO START PLAY===================\n");
                            break;

                        default:
                            printf("=======================PRESS K1 TO START PLAY===================\n");
                            break;

                    } //end switch
                }//end if(first_key)
                else if(first_key == 0)
                {
                    memcpy(&gradchild, p_addr, sizeof(pid_t));
                    switch(key_value)
                    {
                        case 105:
                            //printf("play_flag:%d\n",play_flag);
                            if(play_flag == 1)
                                {
                                my_pause(gradchild);
                                }
                            else
                                {
                                conti_play(gradchild);
                                }
                            break;

                        case 106:
                            my_stop(gradchild);
                            first_key = 1;
                            break;

                        case 103:
                            next(gradchild, head);
                            break;

                        case 108:
                            prev(gradchild, head);
                            break;

                        default:
                                break;

                    } //end switch
                }//end if(!first_key)
            }				
        }
    }

    destroy_list(head);
    close(kbd_fd);

    return 0;
}

#if 0
/* main */
int main(void)
{
    int iloop;
    int buttons_fd;
    int key_value;
    link_t head;
    char buttons[8] = {'0'};

    buttons_fd = open("/dev/buttons", 0);
    if (buttons_fd < 0) 
    {
        perror("open device buttons");
        exit(1);
    }
	
    head = create_song_list(SONG_DIRECTORY);
    if (is_empty_list(head) == 1)
    {
        printf("The song list is empty !\n");
        destroy_list(head);
        exit(1);
    }

    printf("===================================SONG LIST====================================\n");
    traverse_list(print_songname, head);
    printf("================================================================================\n");

	
    printf("===================================FUNTION======================================\n\n");
    printf("        K1:START/PAUSE     K2:STOP   K3:NEXT      K4:PRIOR\n\n");
    printf("================================================================================\n");

    if ((shmid = shmget(IPC_PRIVATE, 5, PERM)) == -1)
    {
        perror("shmget");
        exit(1);
    }
    p_addr = shmat(shmid, 0, 0);
    memset(p_addr, '\0', 1024);
		
    while (1) 
    {
        fd_set rds;
        int ret;

        FD_ZERO(&rds);
        FD_SET(buttons_fd, &rds);

        ret = select(buttons_fd + 1, &rds, NULL, NULL, NULL);
        if (ret < 0) 
        {
            perror("select");
            exit(1);
        }
        if (ret == 0) 
        {
            printf("Timeout.\n");
        }
        else if (FD_ISSET(buttons_fd, &rds))
        {
            ret = read(buttons_fd, buttons, sizeof buttons);
            if (ret != sizeof buttons) 
            {
                if (errno != EAGAIN)
                    perror("read buttons\n");
                    continue;
            } 
            else
            {
                key_value = -1;
                for (iloop = 0; iloop < 8; iloop++)
                {
                    if (buttons[iloop] == '1')
                    {
                    key_value = iloop;
                    break;
                    }
                }
                if (key_value ==  -1)
                {
                    continue;
                }
                printf("buttons_value: %d\n", key_value + 1);
				
                if (first_key == 1)
                {
                    switch(key_value)
                    {	
                        case 0:
                            startplay(&pid, head->next, head);
                            first_key = 0;
                            break;

                        case 1:
                        case 2:
                        case 3:
                            printf("=======================PRESS K1 TO START PLAY===================\n");
                            break;

                        default:
                            printf("=======================PRESS K1 TO START PLAY===================\n");
                            break;

                    } //end switch
                }//end if(first_key)
                else if(first_key == 0)
                {
                    memcpy(&gradchild, p_addr, sizeof(pid_t));
                    switch(key_value)
                    {
                        case 0:
                            //printf("play_flag:%d\n",play_flag);
                            if(play_flag == 1)
                                {
                                my_pause(gradchild);
                                }
                            else
                                {
                                conti_play(gradchild);
                                }
                            break;

                        case 1:
                            my_stop(gradchild);
                            first_key = 1;
                            break;

                        case 2:
                            next(gradchild, head);
                            break;

                        case 3:
                            prev(gradchild, head);
                            break;

                        default:
                                break;

                    } //end switch
                }//end if(!first_key)
            }				
        }
    }

    destroy_list(head);
    close(buttons_fd);

    return 0;
}
#endif

#if 0
/* main */
int main(void)
{
    int buttons_fd;
    int key_value;
    link_t head;

    buttons_fd = open("/dev/key", 0);
    if (buttons_fd < 0) 
    {
        perror("open device buttons");
        exit(1);
    }
	
    head = create_song_list(SONG_DIRECTORY);
    if (is_empty_list(head) == 1)
    {
        printf("The song list is empty !\n");
        destroy_list(head);
        exit(1);
    }

    printf("===================================SONG LIST====================================\n");
    traverse_list(print_songname, head);
    printf("================================================================================\n");

	
    printf("===================================FUNTION======================================\n\n");
    printf("        K1:START/PAUSE     K2:STOP   K3:NEXT      K4:PRIOR\n\n");
    printf("================================================================================\n");

    if ((shmid = shmget(IPC_PRIVATE, 5, PERM)) == -1)
    {
        perror("shmget");
        exit(1);
    }
    p_addr = shmat(shmid, 0, 0);
    memset(p_addr, '\0', 1024);
		
    while (1) 
    {
        fd_set rds;
        int ret;

        FD_ZERO(&rds);
        FD_SET(buttons_fd, &rds);

        ret = select(buttons_fd + 1, &rds, NULL, NULL, NULL);
        if (ret < 0) 
        {
            perror("select");
            exit(1);
        }
        if (ret == 0) 
        {
            printf("Timeout.\n");
        }
        else if (FD_ISSET(buttons_fd, &rds))
        {
            ret = read(buttons_fd, &key_value, sizeof key_value);
            if (ret != sizeof key_value) 
            {
                if (errno != EAGAIN)
                    perror("read buttons\n");
                    continue;
            } 
            else
            {
                printf("buttons_value: %d\n", key_value + 1);
				
                if (first_key == 1)
                {
                    switch(key_value)
                    {	
                        case 0:
                            startplay(&pid, head->next, head);
                            first_key = 0;
                            break;

                        case 1:
                        case 2:
                        case 3:
                            printf("=======================PRESS K1 TO START PLAY===================\n");
                            break;

                        default:
                            printf("=======================PRESS K1 TO START PLAY===================\n");
                            break;

                    } //end switch
                }//end if(first_key)
                else if(first_key == 0)
                {
                    memcpy(&gradchild, p_addr, sizeof(pid_t));
                    switch(key_value)
                    {
                        case 0:
                            //printf("play_flag:%d\n",play_flag);
                            if(play_flag == 1)
                                {
                                my_pause(gradchild);
                                }
                            else
                                {
                                conti_play(gradchild);
                                }
                            break;

                        case 1:
                            my_stop(gradchild);
                            first_key = 1;
                            break;

                        case 2:
                            next(gradchild, head);
                            break;

                        case 3:
                            prev(gradchild, head);
                            break;

                        default:
                                break;

                    } //end switch
                }//end if(!first_key)
            }				
        }
    }

    destroy_list(head);
    close(buttons_fd);

    return 0;
}
#endif

