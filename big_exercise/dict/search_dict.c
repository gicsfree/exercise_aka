/* search_dict.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

/* bubble the dictionary */
int bubble_dict(dict_t *dict, int n)
{
    int iloop;
    int jloop;
    char *tmp_key_word;
    char **tmp_trans;
    int tmp_trans_num;
    int exchange_flag = 0;

    for (iloop = 1; iloop < n; iloop++)
    {
        exchange_flag = 0;

        for (jloop = n - 1; jloop >= iloop; jloop--)
        {
            if (strcmp(dict[jloop].key_word, dict[jloop - 1].key_word) < 0)
            {
                tmp_key_word = dict[jloop].key_word;
                dict[jloop].key_word = dict[jloop - 1].key_word;
                dict[jloop - 1].key_word = tmp_key_word;

                tmp_trans = dict[jloop].trans;
                dict[jloop].trans = dict[jloop - 1].trans;
                dict[jloop - 1].trans = tmp_trans;

                tmp_trans_num = dict[jloop].trans_num;
                dict[jloop].trans_num = dict[jloop - 1].trans_num;
                dict[jloop - 1].trans_num = tmp_trans_num;
         
                exchange_flag = 1;
            }
        }

        if (exchange_flag == 0)
        {
            break;
        }
    }

    return 0;
}

/* binary search the word in the dictionary */
int binary_search_word(dict_t *dict, int n, const char *key_word)
{
    int mid;
    int start = 0;
    int end = n - 1;

    while (start <= end)
    {
        mid = (start + end) / 2;
        if (strcmp(dict[mid].key_word, key_word) < 0)
        {
            start = mid + 1;
        }
        else
        {
            if (strcmp(dict[mid].key_word, key_word) > 0)
            {
                end = mid - 1;
            }
            else
            {
                return mid;
            }
        }
    }    
    
    return -1;
}

/* search word in the dictionary */
int search_word(dict_t *dict, int n, const char *key_word)
{
    int iloop;

    for (iloop = 0; iloop < n; iloop++)
    {
        if (strcmp(dict[iloop].key_word, key_word) == 0)
        {
            return iloop;
        }
    }

    return -1;
}

/* printf the keyword and the translations */
int printf_trans(dict_t *dict, int word_num)
{
    int iloop;

    printf("key_word:\t%s\n", dict[word_num].key_word);

    for (iloop = 0; iloop < dict[word_num].trans_num; iloop++)
    {
        printf("Trans%d:\t%s\n", iloop + 1, dict[word_num].trans[iloop]);
    }

    return 0;
}

/* free the dictionary */
int free_dict(dict_t *dict, int n)
{
    int iloop;
    int jloop;

    for (iloop = 0; iloop < n; iloop++)
    {
        free(dict[iloop].key_word);
        if (dict[iloop].trans_num > 0)
        {
            for (jloop = 0; jloop < dict[iloop].trans_num; jloop++)
             {
                free(dict[iloop].trans[jloop]);
             }
            free(dict[iloop].trans);
        }
    }

    free(dict);

    return 0;
}
