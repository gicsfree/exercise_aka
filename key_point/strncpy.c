#include <stdio.h>
#include <assert.h>

/* strncpy */
char *strncpy(char *dest, const char *src, int n)
{
	assert((dest != NULL) && (src != NULL));

	int i;

	for (i = 0; (i < n) && (src[i] != '\0'); i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';

	return dest;
}

/* main */
int main(int argc, const char *argv[])
{
	char str[] = "hello";
	char s[5];

	strncpy(s, str, sizeof(s));
	s[4] = '\0';
	printf("%s\n", s);

	return 0;
}
