#include <stdio.h>

int main(int argc, const char *argv[])
{
    FILE *fp;
    int ret;

    fp = fopen("feof.c", "r");
    while (!(ret = feof(fp)))
    {
        putchar(getc(fp));
    }
    printf("%d\n", ret);
    fclose(fp);

    return 0;
}
