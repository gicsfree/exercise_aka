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
	int bpp;			     /* bits per pixel */
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
extern int init_ft(const char *file, int size);

/* display string */
extern int display_string(const char * buf, int x, int y, fb_info fb_inf, u32_t color);

#endif    /* FRAME_SUPPORT_FONT */

#ifdef FRAME_SUPPORT_MOUSE
////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	int x;
	int y;
	int button;
}mouse_event_t;

#define C_WIDTH  10
#define C_HEIGHT 17
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

#endif  /* FRAME_SUPPORT_JPEG */

#ifdef FRAME_SUPPORT_BMP
////////////////////////////////////////////////////////////////////////////
/* bmp decode */
u8_t *decode_24bmp (const char *bmpname, fb_info *bmp_inf);

#endif  /* FRAME_SUPPORT_BMP */

//////////////////////////////////////////////////////////////////////////
extern int tcp_recv_chessitem(void);

typedef struct chess 
{
    int x;
    int y;
} chess_t;

#define X_START 15
#define Y_START 15
#define LINE_WIDTH 4
#define LINE_COLOR 0x00FFFF00
#define GRID_SIZE 30
#define CHESS_SIZE 13
#define CHESS_X_NUM 25
#define CHESS_Y_NUM 33
#define BLACKGROUND_COLOR 0x00FF0000
#define BLACK_CHESS_COLOR 0x00000000
#define WHITE_CHESS_COLOR 0x00FFFFFF

#define GAME_CHESS_NUM 5
#define WIN_SUM (CHESS_X_NUM * (CHESS_Y_NUM - GAME_CHESS_NUM + 1) + CHESS_Y_NUM * (CHESS_X_NUM - GAME_CHESS_NUM + 1) + (CHESS_X_NUM - GAME_CHESS_NUM + 1) * (CHESS_Y_NUM - GAME_CHESS_NUM + 1) * 2)

#endif /* _FRAME_H_ */
