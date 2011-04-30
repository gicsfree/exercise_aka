#include <stdio.h>
#include<stdlib.h>
int main(int argc, const char *argv[])
{
	int i, a[10] = { 0 };
	for (i = 0; i < 1000; i++)
		a[rand() % 10]++;
	for (i = 0; i < 10; i++)
		printf("%d has %d\n", i, a[i]);
	return 0;
}
