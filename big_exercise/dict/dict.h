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

/* init dictionary from .txt */
extern dict_t *init_dict_txt(const char *dict_txt, int *n);

/* init dictionary from dict.dat */
extern dict_t *init_dict_dat(const char *dict_dat, int *n);

/* create index */
extern int create_index(const char *dict_dat, const char *dict_txt);

/* quick sort dictionary */
extern void quick_sort_dict(dict_t *dict, int first, int end);
/* merge sort dictionary */
extern void merge_sort_dict(dict_t *dict, int start, int end);
/* binary search the word in the dictionary */
extern int binary_search_word(dict_t *dict, int n, const char *key_word);
/* printf the keyword and the translations */
extern int printf_trans(dict_t *dict, int word_num);
/* free the dictionary */
extern int free_dict(dict_t *dict, int n);

#endif
