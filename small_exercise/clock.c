#include <stdio.h>
#include<unistd.h>
int clock_update();
struct Clock {
	int hour;
	int min;
	int sec;
} clock;

int main(int argc, char *argv[])
{
	clock.hour = 0;
	clock.min = 0;
	clock.sec = 0;
	while (1) {
		update_clock();
		sleep(1);
		printf("%d%d:%d%d:%d%d\r", clock.hour / 10,
		       clock.hour % 10, clock.min / 10, clock.min % 10,
		       clock.sec / 10, clock.sec % 10);
		fflush(stdout);
	}

	return 0;
}

int update_clock()
{
	clock.sec++;
	if (clock.sec == 60) {
		clock.sec = 0;
		clock.min++;
	}
	if (clock.min == 60) {
		clock.min = 0;
		clock.hour++;
	}
	if (clock.hour == 24)
		clock.hour = 0;
	return 0;

}
