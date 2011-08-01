/* creat_index.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

/* create index */
int create_index(const char *dict_dat, const char *dict_txt)
{
    int n;
    int iloop;
    int jloop;
    int len;
    dict_t *dict = NULL;
    FILE *fp_dict;

    char dict_version[HEADER_LEN] = {0};

    dict = init_dict_txt(dict_txt, &n);

    fp_dict = fopen(dict_dat, "wb");
    if (fp_dict == NULL)
    {
        printf("cannot open %s\n", dict_dat);
        exit(1);
    }

    fwrite(dict_version, HEADER_LEN, 1, fp_dict);
    fwrite(&n, sizeof(int), 1, fp_dict);

    for (iloop = 0; iloop < n; iloop++)
    {
        len = strlen(dict[iloop].key_word);
        fwrite(&len, sizeof(int), 1, fp_dict);
//        printf("%s\n", dict[iloop].key_word);
        fwrite(dict[iloop].key_word, len, 1, fp_dict);

//        printf("%d\n", dict[iloop].trans_num);
        fwrite(&dict[iloop].trans_num, sizeof(int), 1, fp_dict);

        if (dict[iloop].trans_num > 0)
        {
            for (jloop = 0; jloop < dict[iloop].trans_num; jloop++)
            {
                len = strlen(dict[iloop].trans[jloop]);
                fwrite(&len, sizeof(int), 1, fp_dict);

//                printf("%s\n", dict[iloop].trans[jloop]);
                fwrite(dict[iloop].trans[jloop], len, 1, fp_dict);
            }    
        } 
    }

    free_dict(dict, n);
    fclose(fp_dict);

    return 0;
}
