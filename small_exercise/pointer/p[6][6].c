#include <stdio.h>

#define STR

/* printf a string */
#ifdef STR
int printf_str(char (*str)[6], int n)
{
    int iloop;

    for (iloop = 0; iloop < n; iloop++)
    {
        printf("str[%d]\t%s\n", iloop, str[iloop]);
    }

    return 0;
}
#else
int printf_str(char *str[], int n)
{
    int iloop;

    for (iloop = 0; iloop < n; iloop++)
    {
        printf("str[%d]\t%s\n", iloop, str[iloop]);
    }

    return 0;
}
#endif



/* main */
#ifdef STR
int main(void)
{
    char str[6][6] = {"0.jpg", "1.jpg", "2.jpg", "3.jpg", "4.jpg", "5.jpg"};

    printf_str(str, 6);

    return 0;
}
#else
int main(void)
{
    char *str[6] = {"0.jpg", "1.jpg", "2.jpg", "3.jpg", "4.jpg", "5.jpg"};

    printf_str(str, 6);

    return 0;
}
#endif


