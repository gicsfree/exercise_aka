#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* atoi */
#if 1
int atoi(const char str[])
{
	assert(str != NULL);

	int n = 0;
	int flag = 0;

	if (*str == '-') {
		flag = 1;
		str++;
	}

	while (*str != '\0') {
		if ((*str >= '0') && (*str <= '9')) {
			n = n * 10 + *str - '0';
			str++;
		} else {
			if (n > 0)
				return (flag ? -n : n);
			else
				return -1;
		}
	}

	return (flag ? -n : n);
}
#endif

/* main */
int main(int argc, const char *argv[])
{
	if (argc != 2) {
		printf("Usage: ./main string\n");
		return -1;
	}

//    int ret = atoi(NULL);
	int ret = atoi(argv[1]);
	printf("string %s converts to integer is: %d\n", argv[1],
	       (ret != -1) ? ret : 0);

	return 0;
}
