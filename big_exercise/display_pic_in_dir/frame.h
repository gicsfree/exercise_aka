/* frame.h */
#ifndef _FRAME_H_
#define _FRAME_H_

#define FRAME_SUPPORT_JPEG
#define FRAME_SUPPORT_FONT
#define FRAME_SUPPORT_MOUSE
#define FRAME_SUPPORT_BMP

////////////////////////////////////////////////////////////////////////////
typedef unsigned char  u8_t;
typedef unsigned short u16_t;
typedef unsigned int   u32_t;

typedef struct 
{
	int w;				     /* width */
	int h;				     /* high */
	int bpp;				   /* bits per pixel */
	u8_t *fbmem;
}fb_info;

////////////////////////////////////////////////////////////////////////////
/* initial framebuffer */
extern int init_fb(fb_info *fb_inf);

/* drawing pixel */
extern int fb_pixel(fb_info fb_inf, int x, int y, u32_t color);

#ifdef FRAME_SUPPORT_FONT
////////////////////////////////////////////////////////////////////////////
/* init font library */
extern int init_ft (const char *file, int size);

/* display string */
extern int display_string (const char * buf, int x, int y, fb_info fb_inf, u32_t color);

#endif    /* FRAME_SUPPORT_FONT */

#ifdef FRAME_SUPPORT_MOUSE
////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	int x;
	int y;
	int button;
}mouse_event_t;

////////////////////////////////////////////////////////////////////////////
/* open mouse */
extern int mouse_open(char *device_name, int *fd);
/* parse mouse */
extern int mouse_parse(const u8_t *buf, mouse_event_t* mevent);

/* restore cursor */
extern int fb_restore_cursor(fb_info fb_inf, int x, int y);
/* save cursor */
extern int fb_save_cursor (fb_info fb_inf,int x,int y);
/* draw cursor */
extern int fb_draw_cursor(fb_info fb_inf, int x, int y);

#endif  /* FRAME_SUPPORT_MOUSE */


#ifdef FRAME_SUPPORT_JPEG
////////////////////////////////////////////////////////////////////////////
/* decode jpeg */
extern unsigned char *decode_jpeg (const char *filename, fb_info *jpeg_inf);
/* rgb888 to argb8888 */
extern u32_t * rgb24to32(u8_t *buf24, fb_info jpeg_inf);
/* scale24 */
u8_t * scale24(u8_t *buf24, fb_info new_inf, fb_info jpeg_inf);

/* display jpeg various */
extern int display_jpeg_various(const char *jpegname, fb_info fb_inf);

/* display jpeg */
extern int display_jpeg(const char *jpegname, fb_info fb_inf);
/* display jpeg blind y */
extern int display_jpeg_blind_y(const char *jpegname, fb_info fb_inf);
/* display jpeg blind x */
extern int display_jpeg_blind_x(const char *jpegname, fb_info fb_inf);
/* display jpeg cross */
extern int display_jpeg_cross(const char *jpegname, fb_info fb_inf);
/* display jpeg door */
extern int display_jpeg_door(const char *jpegname, fb_info fb_inf);
/* display jpeg circle */
extern int display_jpeg_circle(const char *jpegname, fb_info fb_inf);
/* display jpeg diagonal close */
extern int display_jpeg_diagonal_c(const char *jpegname, fb_info fb_inf);
/* display jpeg circle area */
extern int display_jpeg_circle_area(const char *jpegname, fb_info fb_inf);
/* display jpeg point */
extern int display_jpeg_point(const char *jpegname, fb_info fb_inf);
/* display jpeg square */
extern int display_jpeg_square(const char *jpegname, fb_info fb_inf);
/* display jpeg some circle */
extern int display_jpeg_circle_num(const char *jpegname, fb_info fb_inf, int x_num, int y_num);
/* display jpeg down */
extern int display_jpeg_down(const char *jpegname, fb_info fb_inf);
/* display jpeg mosaic*/
extern int display_jpeg_mosaic(const const char *jpegname, fb_info fb_inf, int size);

#endif  /* FRAME_SUPPORT_JPEG */

#ifdef FRAME_SUPPORT_BMP
////////////////////////////////////////////////////////////////////////////
/* bmp decode */
u8_t *decode_24bmp (const char *bmpname, fb_info *bmp_inf);

/* display bmp various */ 
extern int display_bmp_various(const char *bmpname, fb_info fb_inf);
/* display bmp */
extern int display_bmp(const char *bmpname, fb_info fb_inf);

#endif  /* FRAME_SUPPORT_BMP */

////////////////////////////////////////////////////////////////////////////
#define NAME_LEN 100

typedef struct picture
{
    char name[NAME_LEN];
    int type;
    struct picture *next;  
} picture_t;

/* display pictures in directory */
extern int dispaly_pic_in_dir(const char *directory, fb_info fb_inf);

#endif /* _FRAME_H_ */
