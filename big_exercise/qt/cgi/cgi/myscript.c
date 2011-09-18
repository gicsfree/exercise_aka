#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char buf[1024];
    char *res;
    int n;

    //http协议
    printf("Content-Type:text/plain\r\n\r\n");

    printf("hello world!\n");

    //POST方法
    if ((n = read(0, buf, 1024)) > 0)
    {
        buf[n] = 0;
        printf("POST method. n=%d, buf=%s\n", n, buf);
    }

    //GET方法
    res = getenv("QUERY_STRING");
    if (res != NULL)
    {
        if ((strlen(res)) > 0)
        {
            printf("GET methord=%s", res);
        }
    }
    else
    {
        printf("Warning!!! res is NULL\n");
    }

    return 0;
}
