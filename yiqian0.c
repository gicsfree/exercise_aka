#include <stdio.h>

int main(void)
{
	int i, sum = 0;
	for (i = 5; i <= 1000; i += 5) {
		sum++;
		if (0 == i % 25) {
			sum++;
			if (0 == i % 125)
				sum++;
		}
	}
	printf("0 is %d\n", sum);
	return 0;
}
