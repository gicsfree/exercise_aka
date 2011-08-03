/* dict.h */

#ifndef _DICT_H_
#define _DICT_H_

typedef struct
{
    char *key_word;
    char **trans;
    int trans_num;
} dict_t;

#define HEADER_LEN 256

extern dict_t *init_dict_txt(const char *dict_txt, int *n);

extern dict_t *init_dict_dat(const char *dict_dat, int *n);

extern int create_index(const char *dict_dat, const char *dict_txt);

extern void merge_sort_dict(dict_t *dict, int start, int end);
extern int binary_search_word(dict_t *dict, int n, const char *key_word);
extern int printf_trans(dict_t *dict, int word_num);
extern int free_dict(dict_t *dict, int n);

#endif
