/* search_dict.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

/* quick sort dictionary */
void quick_sort_dict(dict_t *dict, int first, int end)
{
    int iloop = first;
    int jloop = end;
    dict_t temp = dict[first];

    while (iloop < jloop)
    {
        while((iloop < jloop) && (strcmp(dict[jloop].key_word, temp.key_word) >= 0))
        {
            jloop--;
        }
        dict[iloop] = dict[jloop];

        while((iloop < jloop) && (strcmp(dict[iloop].key_word, temp.key_word) <= 0))
        {
            iloop++;	
        }	
        dict[jloop] = dict[iloop];
    }
    dict[iloop] = temp;

    if (first < iloop - 1) 
    {
        quick_sort_dict(dict, first, iloop - 1);
    }
    if (end > iloop + 1) 
    {		
        quick_sort_dict(dict, iloop + 1, end);
    }
}

/* merge dictionary */
static void merge_dict(dict_t *dict, int start, int mid, int end)
{
    int iloop;
    int jloop;
    int kloop;
    int n1 = mid - start + 1;
    int n2 = end - mid;
    dict_t left[n1];
    dict_t right[n2];

    for (iloop = 0; iloop< n1; iloop++)
    {
        left[iloop] = dict[start + iloop];
    }

    for (jloop = 0; jloop< n2; jloop++)
    {
        right[jloop] = dict[mid + 1 + jloop];
    }

    iloop = 0;
    jloop = 0;
    kloop = start;
 
    while ((iloop < n1) && (jloop < n2))
    {
        if (strcmp(left[iloop].key_word, right[jloop].key_word) <= 0)
        {
            dict[kloop++] = left[iloop++];
        }
        else
        {
            dict[kloop++] = right[jloop++];
        }
    } 

    while (iloop < n1)
    {
        dict[kloop++] = left[iloop++];
    }

    while (jloop < n2)
    {
        dict[kloop++] = right[jloop++];
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
