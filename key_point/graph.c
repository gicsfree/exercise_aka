/* graph.c */

#include <stdio.h>

#define N 8

int main(int argc, const char *argv[])
{
	int i;
	int j;
	int k;

	for (i = 0; i < N; i++) {
		for (j = 0; j <= i; j++) {
			printf("*");
			for (k = 0; k < i; k++) {
				printf(".");
			}
		}
		printf("\n");
	}

	return 0;
}
