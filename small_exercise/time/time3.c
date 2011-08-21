/* gettimeofday */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* function */
void function(void)
{
    unsigned int i, j;
    double y;

    for (i = 0; i < 1000; i++)
        for (i = 0; i < 1000; i++)
            y++;
}

/* main */
int main(void)
{
    struct timeval tpstart, tpend;
    float timeuse;

    gettimeofday(&tpstart, NULL);
    function();
    gettimeofday(&tpend, NULL);

    timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
    timeuse /= 1000000;
    printf("Used Time: %f\n", timeuse);

    return 0;
}
