#include <stdio.h>
char *strcat(char *s1, const char *s2);
int main(int argc, const char *argv[])
{
	char a[6] = "hello", b[6] = "hello";
	strcat(a, b);
	printf("%s\n", a);

	return 0;
}

char *strcat(char *s1, const char *s2)
{
	while (*s1++);
	s1--;
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
	return s1;
}
