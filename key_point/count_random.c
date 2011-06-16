#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000
#define UPPER_BOUND 10

void count_random(int n, int upper_bound)
{
    if ((n < 1) || (upper_bound < 1) || (upper_bound > n)){
        printf("wrong input !\n");
        exit(1);
    }

    int i;
    int b[upper_bound];

    for (i = 0; i < upper_bound; i++)
        b[i] = 0;

    srand((int)time(NULL));
    for (i = 0; i < n; i++)
        b[rand() % upper_bound]++;

    printf("value\thow many\n");
    for (i = 0; i < upper_bound; i++)
        printf("%d\t%d\n", i, b[i]);
}

int main(void)
{
    count_random(N, UPPER_BOUND); 

    return 0;
}
