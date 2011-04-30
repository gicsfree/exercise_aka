#include <stdio.h>
char *strcpy(char *dest, const char *src);
int main(int argc, const char *argv[])
{
	char a[7], b[6] = "hello";
	strcpy(a, b);

	printf("%s\n", a);
	return 0;
}

char *strcpy(char *dest, const char *src)
{
	while (*src) {
		*dest++ = *src++;
	}
	*dest = '\0';
	return dest;
}
