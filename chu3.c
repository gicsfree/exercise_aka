#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i, j = 0;
	for (i = 1; i <= 200; i++)
		if (i % 3 != 0)
			if (j != 7) {
				printf("%6d", i);
				j++;
			} else {
				printf("%6d\n", i);
				j = 0;
			}
	return 0;
}
