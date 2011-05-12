#include <stdio.h>

int main(int argc,char *argv[])
{
	int i, j = 0;
	for (i = 1; i <= 200; i++)
		if (i % 3 != 0) {
			j++;
			printf("%6d", i);
			if (j % 8 == 0)
				printf("\n");
		}
	return 0;
}
