#include <stdio.h>

#define LEN 10

void Gets(char str[], int n)
{
	char s[n];
	int i = 0;

	fgets(s, n, stdin);

	while ((s[i] != '\n') && (s[i] != '\0')) {
		*str++ = s[i];
		i++;
	}
	*str = '\0';
}

#if 0

int main(void)
{
	char str[LEN];

	printf("Please input a string:");
	Gets(str, sizeof(str));
	puts(str);

	return 0;
}

#endif
