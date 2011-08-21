/* time.c */

#include <stdio.h>
#include <time.h>

/* main */
int main(void)
{
    struct tm *ptr;
    time_t t;

    t = time(NULL);
    ptr = gmtime(&t);
    printf("%s\n", asctime(ptr));
    ptr = localtime(&t);
    printf("%s\n", asctime(ptr));
    printf("%s\n", ctime(&t));

    return 0;
}
