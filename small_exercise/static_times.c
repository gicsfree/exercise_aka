#include <stdio.h>

int times();

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < 4; i++)
		printf("%d\n", times());
	return 0;
}

int times()
{
	static int j = 0;
	return ++j;
}
