#include <stdio.h>
#include "josephus.h"

int main(int argc, char *argv[])
{
	int i, m, n;
	if (3 != argc) {
		printf("input(m<n): ./file m(1-100) n(1-100)\n");
		return 0;
	}
	for (i = 1; i <= 2; i++)
		if (atoi(argv[i]) < 1 || atoi(argv[i]) > 100) {
			printf("input(m<n): ./file m(1-100) n(1-100)\n");
			return 0;
		}
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	if (m > n) {
		printf("input(m<n): ./file m(1-100) n(1-100)\n");
		return 0;
	}
	josephus(m, n);
	return 0;
}
