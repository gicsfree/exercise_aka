#include <stdio.h>
#include <stdlib.h>
#include "joseph.h"

int main(int argc, char *argv[])
{
    /* n是玩游戏的人数，m是报的数 */
	int m, n;

	if (3 != argc) {
		printf("input(m<n):./file m n\n");
		return 0;
	}
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	if (m > n || m < 1 || m > 100 || n < 1 || n > 100) {
		printf("input(m<n):./file m n\n");
		return 0;
	}
	joseph(m, n);
	return 0;
}
