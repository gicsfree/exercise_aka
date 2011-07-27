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

//picture_t *pic = NULL;

#if 1
/* save picture name */
picture_t *save_pic_name(const char *filename, picture_t *pic)
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
//                printf("%s\n", filename);
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
              return pic;
            }

            if ((strcmp(pic_name, ".jpeg") == 0) || (strcmp(pic_name, ".jpg") == 0))
            {
//                printf("%s\n", filename);
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
              return pic;
            }
        }
    }

#if 0
    
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
#endif
    
    return pic;
}
#endif

#if 1

/* display jpegd various */
int display_jpeg_various(const char *jpegname, fb_info fb_inf)
{
    static int num = 0;

    switch(num++ % 29)
    {
        case 0:
            display_jpeg_blind_y(jpegname, fb_inf);
            sleep(1);
            break;

        case 1:
            display_jpeg_blind_x(jpegname, fb_inf);
            sleep(1);
            break;

        case 2:
            display_jpeg_cross(jpegname, fb_inf);
            sleep(1);
            break;

        case 3:
            display_jpeg_door(jpegname, fb_inf);
            sleep(1);
            break;

        case 4:
            display_jpeg_diagonal_c(jpegname, fb_inf);
            sleep(1);
            break;

        case 5:
            display_jpeg_circle(jpegname, fb_inf);
            sleep(1);
            break;

        case 6:
            display_jpeg_square(jpegname, fb_inf);
            sleep(1);
            break;

        case 7:
            display_jpeg_circle_area(jpegname, fb_inf);
            sleep(1);
            break;

        case 8:
            display_jpeg_point(jpegname, fb_inf);
            sleep(1);
            break;

        case 9:
            display_jpeg_mosaic(jpegname, fb_inf, 20);
            sleep(1);
            break;

        case 10:
            display_jpeg_circle_num(jpegname, fb_inf, 5, 6);
            sleep(1);
            break;

        case 11:
            display_jpeg_down(jpegname, fb_inf);
            sleep(1);
            break;

        case 12:
            opend_dcant(jpegname, fb_inf);
            sleep(1);
            break;

        case 13:
            close_open(jpegname, fb_inf);
            sleep(1);
            break;

        case 14:
            opend_cant1(jpegname, fb_inf);
            sleep(1);
            break;

        case 15:
            four_corner(jpegname, fb_inf);
            sleep(1);
            break;

        case 16:
            display_jpeg_zoom(jpegname, fb_inf);
            sleep(1);
            break;

        case 17:
            display_jpeg_scan_m(jpegname, fb_inf);
            sleep(1);
            break;

        case 18:
            display_jpeg_scan(jpegname, fb_inf);
            sleep(1);
            break;

        case 19:
            display_shutters5(jpegname, fb_inf);
            sleep(1);
            break;

        case 20:
            display_shutters6(jpegname, fb_inf);
            sleep(1);
            break;

        case 21:
           display_shutters7(jpegname, fb_inf);
            sleep(1);
            break;

        case 22:
            display_shutters10(jpegname, fb_inf);
            sleep(1);
            break;

        case 23:
            display_shutters11(jpegname, fb_inf);
            sleep(1);
            break;

        case 24:
            display_shutters12(jpegname, fb_inf);
            sleep(1);
            break;

        case 25:
            display_shutters13(jpegname, fb_inf);
            sleep(1);
            break;

        case 26:
            display_shutters14(jpegname, fb_inf);
            sleep(1);
            break;

        case 27:
            display_shutters15(jpegname, fb_inf);
            sleep(1);
            break;

        case 28:
            display_jpeg_block(jpegname, fb_inf);
            sleep(1);
            break;

        default:
            break;
    }

    return 0; 
}

/* display bmp various */ 
int display_bmp_various(const char *bmpname, fb_info fb_inf)
{
    static int num = 0;

    switch(num++ % 4)
    {
        case 0:
            display_bmp_square(bmpname, fb_inf);
            sleep(1);
            break;

        case 1:
            display_bmp_circle_num(bmpname, fb_inf, 6, 5);
            sleep(1);
            break;

        case 2:
            display_bmp_diagonal(bmpname, fb_inf);
            sleep(1);
            break;

        case 3:
            display_bmp_blind(bmpname, fb_inf);
            sleep(1);
            break;

        default:
            break;
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

#endif

#if 0
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
        for ( ; tmp != NULL; tmp = tmp->next)
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
#endif

#if 1
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
#endif

#if 1
/* display pictures in directory */
picture_t *get_pictures(const char *directory, picture_t *pic)
{
    DIR * dirp = NULL;
    struct dirent * direntp = NULL;
    struct stat statbuf;

    char dir_str[100];
    char pic_str[100];
    
    if (directory == NULL)
    {
        printf("the directory is null\n");
        return NULL;
    }
     
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
//                    printf("%s\n", dir_str);
                    pic = get_pictures(dir_str, pic); 
                }
            }
           else
            {
                strcpy(pic_str, directory);
                strcat(pic_str, "/");
                strcat(pic_str, direntp->d_name); 
//                printf("%s\n", pic_str);           
                pic = save_pic_name(pic_str, pic);   
            }      
        }
    }

    closedir(dirp);

    return pic;
}
#endif

#if 1
/* display pictures in directory */
int dispaly_pic_in_dir(const char *directory, fb_info fb_inf)
{
    picture_t *pic = NULL;

    pic = get_pictures(directory, pic);
    display_pictures(pic, fb_inf);
    free_pic(pic);

    return 0;
}
#endif




