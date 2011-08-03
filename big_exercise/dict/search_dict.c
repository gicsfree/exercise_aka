/* search_dict.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

/* merge dictionary */
static void merge_dict(dict_t *dict, int start, int mid, int end)
{
    int i;
    int j;
    int k;
    int n1 = mid - start + 1;
    int n2 = end - mid;
    dict_t left[n1];
    dict_t right[n2];

    for (i = 0; i< n1; i++)
    {
        left[i].key_word = dict[start + i].key_word;
        left[i].trans = dict[start + i].trans;
        left[i].trans_num = dict[start + i].trans_num;
    }

    for (j = 0; j< n2; j++)
    {
        right[j].key_word = dict[mid + 1 + j].key_word;
        right[j].trans = dict[mid + 1 + j].trans;
        right[j].trans_num = dict[mid + 1 + j].trans_num;
    }

    i = 0;
    j = 0;
    k = start;
 
    while ((i < n1) && (j < n2))
    {
        if (strcmp(left[i].key_word, right[j].key_word) <= 0)
        {
            dict[k].key_word = left[i].key_word;
            dict[k].trans = left[i].trans;
            dict[k++].trans_num = left[i++].trans_num;
        }
        else
        {
            dict[k].key_word = right[j].key_word;
            dict[k].trans = right[j].trans;
            dict[k++].trans_num = right[j++].trans_num;
        }
    } 

    while (i < n1)
    {
        dict[k].key_word = left[i].key_word;
        dict[k].trans = left[i].trans;
        dict[k++].trans_num = left[i++].trans_num;
    }

    while (j < n2)
    {
        dict[k].key_word = right[j].key_word;
        dict[k].trans = right[j].trans;
        dict[k++].trans_num = right[j++].trans_num;
    }
}

/* merge sort dictionary */
void merge_sort_dict(dict_t *dict, int start, int end)
{
    int mid;

    if (start < end)
    {
        mid = (start + end) / 2;
        merge_sort_dict(dict, start, mid);
        merge_sort_dict(dict, mid + 1, end);
        merge_dict(dict, start, mid, end);
    }

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
