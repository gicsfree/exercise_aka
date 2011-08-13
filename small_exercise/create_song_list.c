/* create_song_list.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define SONG_DIRECTORY "/home/akaedu/sdcard"
#define NAME_LEN 1024

struct song 
{
    char *songname;
    struct song *prev;
    struct song *next;
};
typedef struct song * link_t;

/* make node */
link_t make_node(const char *songname)
{
    link_t p;
    int len;

    p = (link_t)malloc(sizeof *p);
    if (p == NULL)
    {
        printf("memory out\n");
        exit(1);
    }

    len = strlen(songname);
    p->songname = (char *)malloc(len + 1);
    if (p->songname == NULL)
    {
        printf("memory out\n");
        exit(1);
    }
    memset(p->songname, 0, len + 1);
    strncpy(p->songname, songname, len);
    p->prev = p->next = NULL;

    return p;
}

/* free node */
void free_node(link_t p)
{
    if (p->songname != NULL)
    {
        free(p->songname);
        p->songname == NULL;
    }
    if (p != NULL)
    {
        free(p);
        p = NULL;
    }
}

/* insert node */
void insert_node(link_t p, link_t head)
{
    p->next = head->next;
    head->next->prev = p;
    head->next = p;
    p->prev = head;
}

/* traverse list */
void traverse_list(void (*visit)(link_t), link_t head)
{
    link_t p;

    for (p = head->next; p != head; p = p->next)
    {
        visit(p);
    }
}

/* sestory list */
void destroy_list(link_t head)
{
    link_t p = head->next;
    link_t q = head->next;

    head->next = head;
    head->prev = head;

    while (p != head) 
    {
        q = p;
        p = p->next;
        free_node(q);
    }
}

/* save song name */
link_t save_songname(const char *filename, link_t head)
{
    char *songname = NULL;
    link_t song;
    
    if ((songname = strrchr(filename, '.')) != NULL)
    {
        if (strcmp(songname, ".mp3") == 0)
        {
            song = make_node(filename);
            insert_node(song, head);
        }
    }
    
    return head;
}

/* get song list */
link_t get_song_list(const char *directory, link_t head)
{
    DIR * dirp = NULL;
    struct dirent * direntp = NULL;
    struct stat statbuf;

    char dir_str[NAME_LEN];
    char song_str[NAME_LEN];
    
    if (directory == NULL)
    {
        printf("the directory is null\n");
        return NULL;
    }
     
    chdir(directory);

    if ((dirp = opendir(directory)) != NULL)
    {  	
        while ((direntp = readdir(dirp)) != 0)
        {
            stat(direntp->d_name, &statbuf);
//            printf("%s\n", direntp->d_name);
//            continue;
            if (S_ISDIR(statbuf.st_mode))
            {
                if ((strcmp(direntp->d_name, ".") != 0) && (strcmp(direntp->d_name, "..") != 0))
                { 
                    strcpy(dir_str, directory);
                    strcat(dir_str, "/");
                    strcat(dir_str, direntp->d_name);
//                    printf("dir: %s\n", dir_str);
                    head = get_song_list(dir_str, head); 
                }
            }
           else if (S_ISREG(statbuf.st_mode))
            {
                strcpy(song_str, directory);
                strcat(song_str, "/");
                strcat(song_str, direntp->d_name); 
//                printf("reg: %s\n", pic_str);           
                head = save_songname(song_str, head);   
            }      
        }
    }
    else
    {
        printf("opendir %s error\n", directory);
        exit(1);
    }

    closedir(dirp);

    return head;
}

/* create song list */
link_t create_song_list(const char *directory)
{
    link_t head;

    struct song sentinel = {NULL, &sentinel, &sentinel};
    head = &sentinel;

    get_song_list(directory, head);

    return head;
}

/* printf song name */
void print_songname(link_t p)
{
    printf("%s\n", p->songname); 
}

/* main */
int main(void)
{
    link_t head;

    head = create_song_list(SONG_DIRECTORY);
    traverse_list(print_songname, head);
    destroy_list(head);

    return 0;
}
