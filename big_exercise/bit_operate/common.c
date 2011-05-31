#include <stdio.h>

/* empty_cache */
void empty_cache(void)
{
	char ch;
	while ((ch = getchar()) != '\n');
}

/* Gets */
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
