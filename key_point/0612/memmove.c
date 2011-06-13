/* memmove.c */

#include <stdio.h>
#include <assert.h>

/* memmove */
void *memmove(void *dest, const void *src, size_t n)
{
	assert(dest != NULL);
	assert(src != NULL);
	assert(n >= 0);

	if (dest == src)
		return dest;

	char *d = (char *) dest;
	const char *s = (const char *) src;

	if ((dest < src) || (dest >= src + n)) {
		while (n--) {
			*d++ = *s++;
		}
	} else {
		d += n - 1;
		s += n - 1;
		while (n--) {
			*d-- = *s--;
		}
	}

	return dest;
}

/* main */
int main(int argc, const char *argv[])
{
	char str[10] = "hello";
	char s[6];

	memmove(s, str, 6);
	printf("%s\n", s);

	memmove(str + 2, str + 3, 2);
	printf("%s\n", str);

	memmove(str + 3, str + 2, 2);
	printf("%s\n", str);

	return 0;
}
