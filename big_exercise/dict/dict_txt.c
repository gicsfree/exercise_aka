/* dict_txt.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

#define LINE_BUF_SIZE 4096
#define TRANS_SIZE 200

/* turn a linebuf to a string */
static int to_str(char *line_buf)
{
    char *p = NULL;

    if ((p = strchr(line_buf, '\n')) != NULL)
    {
        *p = '\0';
    } 

    return 0;
}

/* get the keyword from the linebuf */
static char *get_key_word(const char *line_buf)
{
    int len;
    char *key_word = NULL;

    len = strlen(line_buf);
    key_word = (char *)malloc(len);
    if (key_word == NULL)
    {
        printf("memory out\n");
        exit(1);
    }
    memset(key_word, 0, len);
    strncpy(key_word, line_buf + 1, len - 1);

    return key_word;
}

/* turn a linebuf to a standard transline */
static int to_trans_line(char *line_buf)
{
    int iloop;
    int jloop = 0;

    to_str(line_buf);

    for (iloop = 0; line_buf[iloop] != '\0'; iloop++)
    {
        if (line_buf[iloop] == '@')
        {
            if ((line_buf[jloop - 1] == ':') || (line_buf[jloop - 1] == '@'))
            {
                continue;
            }
        }
        line_buf[jloop++] = line_buf[iloop];
    }

    if (line_buf[jloop - 1] == '@')
    {
        line_buf[jloop - 1] = '\0';
        return 0;
    }

    line_buf[jloop] = '\0';

    return 0;
}

/* get the number of translation */
static int get_trans_num(const char *line_buf)
{
    int n = 1;
    const char *p = line_buf;

    if (strlen(line_buf) == 6)
    {
        return 0;
    }

    while ((p = strchr(p + 1, '@')) != NULL)
    {
        n++;
    }

    return n;    
}

/* get the translation */
static int get_trans(char *line_buf, int trans_num, char **trans)
{
    int iloop;
    int len;
    char *token;

    token = strtok(line_buf, ":");

    for (iloop = 0; iloop < trans_num; iloop++)
    {
        if ((token = strtok(NULL, "@")) != NULL)
        {
            len = strlen(token);
            trans[iloop] = (char *)malloc(len + 1);
            if (trans[iloop] == NULL)
            {
                printf("memory out\n");
                exit(1);
            }
            memset(trans[iloop], 0, len + 1);
            strncpy(trans[iloop], token, len);
        }
    }

    return 0;
}

/* load dictionary */
static int load_dict(FILE *fp_dict, dict_t *dict, int n)
{
    int iloop;
//    int jloop;
    char line_buf[LINE_BUF_SIZE] = {0};

    for (iloop = 0; iloop < n; iloop++)
    {
        memset(line_buf, 0, sizeof(line_buf));
        fgets(line_buf, sizeof(line_buf), fp_dict);
        to_str(line_buf);
        dict[iloop].key_word = get_key_word(line_buf); 

//        printf("%s\n", dict[iloop].key_word);
 
        memset(line_buf, 0, sizeof(line_buf));
        fgets(line_buf, sizeof(line_buf), fp_dict);
        to_trans_line(line_buf);
        dict[iloop].trans_num = get_trans_num(line_buf);

//        printf("%d\n", dict[iloop].trans_num);

        if (dict[iloop].trans_num != 0)
        {
            dict[iloop].trans = (char **)malloc(dict[iloop].trans_num * sizeof(char *)); 
            if (dict[iloop].trans == NULL)
            {
                printf("memory out\n");
                exit(1);
            }
            get_trans(line_buf, dict[iloop].trans_num, dict[iloop].trans); 
#if 0
            for (jloop = 0; jloop < dict[iloop].trans_num; jloop++)
            {
                printf("%s\n", dict[iloop].trans[jloop]); 
            }     
#endif   
        } 
    }

    return 0;
}

/* init dictionary from .txt */
dict_t *init_dict_txt(const char *dict_txt, int *n)
{
    int n_line = 0;
    char line_buf[LINE_BUF_SIZE] = {0};
    dict_t *dict;

    FILE *fp_dict = fopen(dict_txt, "r");
    if (fp_dict == NULL)
    {
        printf("cannot open %s, is it exist ?\n", dict_txt);
        exit(1);
    }

    while (fgets(line_buf, sizeof(line_buf), fp_dict) != NULL)
    {
        n_line++;
    }
    n_line /= 2;

    dict = (dict_t *)malloc(sizeof(dict_t) * n_line);
    if (dict == NULL)
    {
        printf("memory out!\n");
        exit(1);
    }

    fseek(fp_dict, 0, SEEK_SET);
    load_dict(fp_dict, dict, n_line);
    fclose(fp_dict);

    *n = n_line;

    return dict;
}

