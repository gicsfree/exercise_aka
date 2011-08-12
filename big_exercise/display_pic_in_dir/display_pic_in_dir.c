/* get_pic_in_dir.c */

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

#define DIRECTORY "/home/akaedu/test/new/picture"
#define BMP 0
#define JPEG 1

/* save picture name */
picture_t *save_pic_name(const char *filename, picture_t *pic)
{
    picture_t *new_pic;
    picture_t *tmp;
    char *pic_name;
    
    if ((pic_name = strrchr(filename, '.')) != NULL)
    {
        if (strcmp(pic_name, ".bmp") == 0)
        {
//            printf("%s\n", filename);
            new_pic = (picture_t *)malloc(sizeof(picture_t)); 
            if (new_pic == NULL)
            {
                printf("memory out\n");
                exit(1);
            }
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
            return pic;
        }

        if ((strcmp(pic_name, ".jpeg") == 0) || (strcmp(pic_name, ".jpg") == 0))
        {
//            printf("%s\n", filename);
            new_pic = (picture_t *)malloc(sizeof(picture_t)); 
            if (new_pic == NULL)
            {
                printf("memory out\n");
                exit(1);
            }
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
            return pic;
        }
    }
    
    return pic;
}

/* display pictures in directory */
picture_t *get_pictures(const char *directory, picture_t *pic)
{
    DIR * dirp = NULL;
    struct dirent * direntp = NULL;
    struct stat statbuf;

    char dir_str[NAME_LEN];
    char pic_str[NAME_LEN];
    
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
                    pic = get_pictures(dir_str, pic); 
                }
            }
           else if (S_ISREG(statbuf.st_mode))
            {
                strcpy(pic_str, directory);
                strcat(pic_str, "/");
                strcat(pic_str, direntp->d_name); 
//                printf("reg: %s\n", pic_str);           
                pic = save_pic_name(pic_str, pic);   
            }      
        }
    }

    closedir(dirp);

    return pic;
}

/* count pictures */ 
int count_pic(picture_t *pic)
{
    picture_t *tmp;
    int count = 0;

    if (pic == NULL)
    {
        return 0;
    }

    for (tmp = pic; tmp != NULL; tmp = tmp->next)
    {
        count++;
    }

    return count;
}

/* free picture struct */ 
int free_pic(picture_t *pic)
{
    picture_t *tmp;

    if (pic == NULL)
    {
        return 0;
    }

    for ( ; pic != NULL; )
    {
        tmp = pic;
        pic = pic->next;
        free(tmp);
    }

    return 0;
}

/* display pictures */
int display_pictures(picture_t *pic, fb_info fb_inf)
{
    picture_t *tmp = pic;

    if (tmp == NULL)
    {
        return 0;
    }
    else
    {
        for ( ; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->type == BMP)
            {
                display_bmp_various(tmp->name, fb_inf);
            }
            else
            {
                display_jpeg_various(tmp->name, fb_inf);
            }
        }
    }

    return 0;
}

/* display pictures in directory */
int dispaly_pic_in_dir(const char *directory, fb_info fb_inf)
{
    picture_t *pic = NULL;

    pic = get_pictures(DIRECTORY, pic);
    display_pictures(pic, fb_inf);
    free_pic(pic);

    return 0;
}




