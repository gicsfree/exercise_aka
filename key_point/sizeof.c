#include <stdio.h>

int main(int argc, const char *argv[])
{
    printf("type\tsizeof\n");
    printf("char\t%d\n", sizeof(char));
    printf("short\t%d\n", sizeof(short));
    printf("int\t%d\n", sizeof(int));
    printf("long\t%d\n", sizeof(long));
    printf("double\t%d\n", sizeof(double));
    printf("long long\t%d\n", sizeof(long long));

    return 0;
}
