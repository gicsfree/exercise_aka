/* loopmove.c */

#include <stdio.h>
#include <string.h>
#include <assert.h>

// #define STR "abcdefghi" // here have a bug, constant cannot be changed !
#define N 2
#define MEM

/* loopmove */
#ifdef MEM
void loopmove(char *str, int steps)
{
	assert(str != NULL);
	assert(steps >= 0);

	int n;
	int len = strlen(str);
	char temp[len];

	steps = steps % len;
	n = len - steps;

	memset(temp, 0, len);
	memcpy(temp, str + n, steps);
	memcpy(temp + steps, str, n);
	memcpy(str, temp, len);
}

#else
void loopmove(char *str, int steps)
{
	assert(str != NULL);
	assert(steps >= 0);

	int i;
	int j;
	char temp;
	int len = strlen(str);

	steps = steps % len;
	for (i = 0; i < steps; i++) {
		temp = str[len - 1];
		for (j = len - 1; j > 0; j--) {
			str[j] = str[j - 1];
		}
		str[0] = temp;
	}
}
#endif

/* main */
int main(int argc, const char *argv[])
{
	char s[10] = "abcdefghi";

	printf("%s loopmove %d is: ", s, N);
//    loopmove(NULL, N);
	loopmove(s, N);
	printf("%s\n", s);

	return 0;
}
