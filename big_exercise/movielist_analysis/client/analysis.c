#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOVIELIST "movielist.txt"
#define LINE_LEN 1024

static int analysis_by_Name(char Name[]);
static int analysis_by_Director(char Director[]);
static int analysis_by_Year(char Year[]);
static void Puts(char *str);
static int select_nr(void);
static void pfunc(void);
static void empty_cache(void);
void Gets(char str[], int n);

/************************************************************
* analysis the movielist.txt
* return -1 : the movielist is not exist ! 
*************************************************************/
int analysis(void)
{
    char Name[LINE_LEN];
    char Director[LINE_LEN];
    char Year[LINE_LEN];
    
    while (1)
    {
        switch (select_nr())
        {
            case 1:
                printf("input the movie'name:");
                empty_cache();
                Gets(Name, LINE_LEN);
                if (-1 == analysis_by_Name(Name))
					return -1;
                break;

            case 2:
                printf("input the movie'Director:");
                empty_cache();
                Gets(Director, LINE_LEN);
                if (-1 == analysis_by_Director(Director))
					return -1;
                break;

            case 3:
                printf("input the movie'Year:");
                empty_cache();
                Gets(Year, LINE_LEN);
                if (-1 == analysis_by_Year(Year))
					return -1;
                break;

            case 4:
                return 0;
        }
    }

}

/************************************************************
* analysis the movielist.txt by Name
* return -1 : the movielist is not exist ! 
*************************************************************/
static int analysis_by_Name(char Name[])
{
    char aLine[LINE_LEN];
    int flag = 0;

    FILE *fp = fopen(MOVIELIST, "r");
    if (fp == NULL)
    {
        printf("cannot open %s\n", MOVIELIST);
        return -1;
    }

    while (fgets(aLine, LINE_LEN, fp) != NULL)
    {
        if (strstr(aLine, Name) != NULL)
        {
            Puts(aLine);
            Puts(fgets(aLine, LINE_LEN, fp));
            Puts(fgets(aLine, LINE_LEN, fp));
            printf("\n");
            flag++;
        }
    }

	fclose(fp);
    if (0 == flag)
        printf("no such Name !\n");
	
	return 0;
}

/************************************************************
* analysis the movielist.txt by Director
* return -1 : the movielist is not exist ! 
*************************************************************/
static int analysis_by_Director(char Director[])
{
    char Name[LINE_LEN];
    char aLine[LINE_LEN];
    int flag = 0;

    FILE *fp = fopen(MOVIELIST, "r");
    if (fp == NULL)
    {
        printf("cannot open %s\n", MOVIELIST);
        return -1;
    }

    while (fgets(aLine, LINE_LEN, fp) != NULL)
    {
        if (strstr(aLine, Director) == NULL)
            strncpy(Name, aLine, LINE_LEN);
        else
        {
            Puts(Name);
            Puts(aLine);
            Puts(fgets(aLine, LINE_LEN, fp));
            printf("\n");
            flag++;
        }
    }

	fclose(fp);
    if (0 == flag)
        printf("no such Director !\n");

	return 0;
}

/************************************************************
* analysis the movielist.txt by Year
* return -1 : the movielist is not exist ! 
*************************************************************/
static int analysis_by_Year(char Year[])
{
    char Name[LINE_LEN];
    char Director[LINE_LEN];
    char aLine[LINE_LEN];
    int flag = 0;

    FILE *fp = fopen(MOVIELIST, "r");
    if (fp == NULL)
    {
        printf("cannot open %s\n", MOVIELIST);
        return -1;
    }

    while (fgets(aLine, LINE_LEN, fp) != NULL)
    {
        if (strstr(aLine, Year) == NULL)
        {
            if (strstr(aLine, "Name") != NULL)
                strncpy(Name, aLine, LINE_LEN);
            else 
                if (strstr(aLine, "Director") != NULL)
                strncpy(Director, aLine, LINE_LEN);
        }
        else
        {
            Puts(Name);
            Puts(Director);
            Puts(aLine);
            printf("\n");
            flag++;
        }
    }

	fclose(fp);
    if (0 == flag)
        printf("no such Year !\n");

	return 0;
}

/* Puts */
static void Puts(char *str)
{
    printf("%s",str);
}

/* select_nr */
static int select_nr(void)
{
    int nr = 0;

    while (nr < 1 || nr > 4) {
        pfunc();
        if (0 == scanf("%d", &nr)) 
            empty_cache();
    }

    return nr;
}

/* fpunc */
static void pfunc(void)
{
    printf("1.analysis by Name\n");
    printf("2.analysis by Director\n");
    printf("3.analysis by Year\n");
    printf("4.exit analysis\n");
    printf("Please Select[1-4]:");
}

/* empty_cache */
static void empty_cache(void)
{
    char ch;

    while ((ch = getchar()) != '\n');
}

/* Gets */
void Gets(char str[], int n)
{
    char s[n];
    int i =0 ;

    fgets(s, n, stdin);

    while ((s[i] != '\n') && (s[i] != '\0'))
    {
        *str++ = s[i];
        i++;
    }

    *str = '\0';
}
