/* mp3player.h */

#ifndef _MP3PLAYER_H_
#define _MP3PLAYER_H_

#define SONG_DIRECTORY "/sdcard"

struct song 
{
    char *songname;
    struct song *prev;
    struct song *next;
};
typedef struct song * link_t;

/* create song list */
extern link_t create_song_list(const char *directory);
/* is empty list */
extern int is_empty_list(link_t head);
/* printf song name */
extern void print_songname(link_t p);
/* traverse list */
extern void traverse_list(void (*visit)(link_t), link_t head);
/* sestory list */
extern void destroy_list(link_t head);

#endif
