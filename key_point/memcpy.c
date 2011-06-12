/* memcpy.c */

#include <stdio.h>
#include <assert.h>

/* memcpy */
void *memcpy(void *dest, const void *src, int n)
{
	assert(dest != NULL);
	assert(src != NULL);
	assert(n >= 0);

	if ((unsigned int) dest == (unsigned int) src)
		return dest;

	char *d = (char *) dest;
	const char *s = (const char *) src;
	while (n--) {
		*d++ = *s++;
	}

	return dest;
}

/* main */
int main(int argc, const char *argv[])
{
	char str[] = "hello";
	char s[6];

	memcpy(s, str, sizeof(s));
	printf("%s\n", s);

	printf("%s\n", (char *) memcpy(s, str, sizeof(s)));

	return 0;
}
