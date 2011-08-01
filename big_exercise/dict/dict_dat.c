/* dict_dat.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

/* init dictionary from dict.dat */
dict_t *init_dict_dat(const char *dict_dat, int *n)
{
    int iloop;
    int jloop;
    int len;
    int trans_num;
    dict_t *dict = NULL; 
    FILE *fp_dict; 

    fp_dict = fopen(dict_dat, "rb"); 
    if (fp_dict == NULL)
    {
        printf("cannot open %s, is it exist ?\n", dict_dat);
        exit(1);
    }    

    fseek(fp_dict, HEADER_LEN, SEEK_SET);
    fread(n, sizeof(int), 1, fp_dict);

    dict = (dict_t *)malloc(sizeof(dict_t) * (*n));
    if (dict == NULL)
    {
        printf("memory out\n");
        exit(1);
    }

//    printf("%d\n", *n);

    for (iloop = 0; iloop < *n; iloop++)
    {
        fread(&len, sizeof(int), 1, fp_dict);
        dict[iloop].key_word = (char *)malloc(len + 1);
        memset(dict[iloop].key_word, 0, len + 1);
        if (dict[iloop].key_word == NULL)
        {
            printf("memory out\n");
            exit(1);            
        }
        fread(dict[iloop].key_word, len, 1, fp_dict);
//        printf("%s\n", dict[iloop].key_word);

        fread(&trans_num, sizeof(int), 1, fp_dict);
        dict[iloop].trans_num = trans_num;
//        printf("%d\n", dict[iloop].trans_num);

        if (trans_num > 0)
        {
            dict[iloop].trans = (char **)malloc(sizeof(char *) * trans_num);
            if (dict[iloop].trans == NULL)
            {
                printf("memory out\n");
                exit(1);            
            }

            for (jloop = 0; jloop < trans_num; jloop++)
            {
                fread(&len, sizeof(int), 1, fp_dict);
                dict[iloop].trans[jloop] = (char *)malloc(len + 1);
                memset(dict[iloop].trans[jloop], 0, len + 1);
                if (dict[iloop].trans[jloop] == NULL)
                 {
                    printf("memory out\n");
                    exit(1);            
                 }
                fread(dict[iloop].trans[jloop], len, 1, fp_dict);
//                printf("%s\n", dict[iloop].trans[jloop]);
            }
        }                
    } 

    fclose(fp_dict);

    return dict;
}
