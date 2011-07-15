/* display-pic-in-dir.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#include "frame.h"

#define BMP 0
#define JPEG 1

typedef struct picture
{
    char name[10];
    int type;
    struct picture *next;  
}picture_t;

picture_t *pic = NULL;

#if 1
/* save picture name */
static int save_pic_name(const char *filename, fb_info fb_inf)
{
    struct stat statbuf;
    picture_t *new_pic;
    picture_t *tmp;
    char *pic_name;
    
    if (stat(filename, &statbuf) != -1)
    {
        if ((pic_name = strrchr(filename, '.')) != NULL)
        {
            if (strcmp(pic_name, ".bmp") == 0)
            {
                new_pic = (picture_t *)malloc(sizeof(picture_t)); 
                strcpy(new_pic->name, filename);
                new_pic->type = BMP;
                new_pic->next = NULL;

                if (pic == NULL)
                 {
                    pic = new_pic;
                 }
               else
                {
                   for (tmp = pic; tmp->next != NULL; tmp = tmp->next)
                     {
                          ;
                     }
                  tmp->next = new_pic;
                }
              return 0;
            }

            if ((strcmp(pic_name, ".jpeg") == 0) || (strcmp(pic_name, ".jpg") == 0))
            {
                new_pic = (picture_t *)malloc(sizeof(picture_t)); 
                strcpy(new_pic->name, filename);
                new_pic->type = JPEG;
                new_pic->next = NULL;

                if (pic == NULL)
                 {
                    pic = new_pic;
                 }
               else
                {
                   for (tmp = pic; tmp->next != NULL; tmp = tmp->next)
                     {
                          ;
                     }
                  tmp->next = new_pic;
                }
              return 0;
            }
        }
    }
    
    if (S_ISDIR(statbuf.st_mode))
    {
        printf("%s\t(dir)\tmodified at %s", filename, ctime(&statbuf.st_mtime));
        return 0;
    }
    
    if (S_ISREG(statbuf.st_mode))
    {
        printf("%s\tsize:%ld bytes\n", filename, statbuf.st_size);
        return 0;
    }
    
    return 0;
}
#endif

#if 1
/* display pictures */
static int display_pictures(fb_info fb_inf)
{
    picture_t *tmp = pic;

    if (tmp == NULL)
    {
        return 0;
    }
    else
    {
        for ( ; tmp->next != NULL; tmp = tmp->next)
        {
            if (tmp->type == BMP)
            {
                display_bmp(tmp->name, fb_inf);
                sleep(1);
            }
            else
            {
                display_jpeg(tmp->name, fb_inf);
                sleep(1);
            }
        }
    }

    return 0;
}
#endif

#if 1
/* free picture struct */ 
static int free_pic(void)
{
    picture_t *tmp;

    if (pic == NULL)
    {
        return 0;
    }

    for ( ; pic->next != NULL; )
    {
        tmp = pic;
        pic = pic->next;
        free(tmp);
    }

    return 0;
}
#endif

#if 1
/* display pictures in directory */
int dispaly_pic_in_dir(const char *directory, fb_info fb_inf)
{
    DIR * dirp = NULL;
    struct dirent * direntp = NULL;
    
    if (directory == NULL)
    {
        printf("the directory is null\n");
        return -1;
    }
     
    if ((dirp = opendir(directory)) != NULL)
    {  	
        while ((direntp = readdir(dirp)) != NULL)
        {
            save_pic_name(direntp->d_name, fb_inf);           
        }
    }

    display_pictures(fb_inf);
    free_pic();

    closedir(dirp);

    return 0;
}
#endif




