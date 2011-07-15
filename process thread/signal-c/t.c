#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, const char *argv[])
{
    while (1){
        kill(atoi(argv[1]), atoi(argv[2]));
        sleep(3);
    }

    return 0;
}
