/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

#define DICT_TXT "dict.txt"
#define DICT_DAT "dict.dat"
#define USR_DICT "usr_dict.txt"
#define LEN 20

/* empty the cache */
static void empty_cache(void)
{
    int ch;

    while ((ch = getchar()) != '\n')
    {
        ;
    }
}

/* printf the function */
static void printf_func(void)
{
    printf("1.search from %s\n", DICT_TXT);
    printf("2.search from %s\n", DICT_DAT);
    printf("3.search from %s\n", USR_DICT);
    printf("4.create index\n");
    printf("5.Exit\n");
    printf("Please Select[1-5]:");
}

/* get the function number */
static int get_func_num(void)
{
    int num = 0;
    int ret;

    while ((num < 1) || (num > 5)) 
    {
        printf_func();
        ret = scanf("%d", &num);
        if (ret != 1)
        {
            empty_cache();
        }
    }

    return num;
}

/* get a string from stdin */
static char *Gets(char str[], int n)
{
    char s[n];
    char *p = str;
    int iloop = 0;

    fgets(s, n, stdin);

    while ((s[iloop] != '\n') && (s[iloop] != '\0')) 
    {
        *p++ = s[iloop];
        iloop++;
    }
    *p = '\0';

    return str;
}

/* main.c */
int main(void)
{
    int n;
    int word_num;
    char key_word[LEN] = {0};
    dict_t *dict = NULL;

    switch (get_func_num()) 
    {
        case 1:
            dict = init_dict_txt(DICT_TXT, &n);
            printf("init dictionary from %s successfully !\n", DICT_TXT);
            break;

        case 2:
            dict = init_dict_dat(DICT_DAT, &n);
            printf("init dictionary from %s successfully !\n", DICT_DAT);
            break;

        case 3:
            dict = init_dict_txt(USR_DICT, &n);
            printf("init dictionary from %s successfully !\n", USR_DICT);
            break;

        case 4:
            create_index(DICT_DAT, DICT_TXT);
            printf("create %s successfully !\n", DICT_DAT);
            return 0;

        case 5:
            return 0;

    }

//    create_index(DICT_DAT, DICT_TXT);
//    dict = init_dict_txt(DICT_TXT, &n);
//    dict = init_dict_dat(DICT_DAT, &n);

//    n = 10;
//    bubble_dict(dict, n);

#if 1
    empty_cache();
    printf("exit with enter\n");
    printf("input your keyword:");
    while (strlen(Gets(key_word, sizeof(key_word))) != 0)
    {
//        word_num = binary_search_word(dict, n, key_word);
        word_num = search_word(dict, n, key_word);
        if (word_num != -1)
        {
            printf_trans(dict, word_num);
        }
        else
        {
            printf("No such word in the dictionary!\n");
        }
       printf("input your keyword:");
    }

    free_dict(dict, n);
#endif

#if 0
    int iloop;
    int jloop;
    
    for (iloop = 0; iloop < n; iloop++)
    {
        printf("%s\n", dict[iloop].key_word);  
        for (jloop = 0; jloop < dict[iloop].trans_num; jloop++)
        {
            printf("%s\n", dict[iloop].trans[jloop]); 
        }   
    }

    free_dict(dict, n);
#endif

    return 0;
}
