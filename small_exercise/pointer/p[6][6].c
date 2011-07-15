#include <stdio.h>

/* printf a string */
int printf_str(char (*str)[6], int n)
{
    int iloop;

    for (iloop = 0; iloop < n; iloop++)
    {
        printf("str[%d]\t%s\n", iloop, str[iloop]);
    }

    return 0;
}

/* main */
int main(void)
{
    char str[6][6] = {"0.jpg", "1.jpg", "2.jpg", "3.jpg", "4.jpg", "5.jpg"};

    printf_str(str, 6);

    return 0;
}

