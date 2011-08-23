#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define N 2

int *p;

void func(int me)
{
    int n = 0;

    while (1)
    {
        switch (me)
        {
            case 0:
                *p = n;
                printf("save a value %d\n", n);
                n++;
                sleep(1);
                break;

            case 1:
                printf("the value is %d\n", *p);
                sleep(1);
                break;
        }
    }
}

int main(void)
{
    int i;
    int fd;

    fd = open("/dev/zero", O_RDWR);
//    p = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    p = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    for (i = 0; i < N-1; i++)
        if (!fork())
            break;

    func(i);

    return 0;
}
