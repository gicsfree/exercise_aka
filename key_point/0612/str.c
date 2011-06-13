#include <stdio.h>

int main(int argc, const char *argv[])
{
	char str1[] = "abc";
	char str2[] = "abc";
	const char str3[] = "abc";
	const char str4[] = "abc";
	const char *str5 = "abc";
	const char *str6 = "abc";

	printf("%d\n", str1 == str2);
	printf("%d\n", str3 == str4);
	printf("%d\n", str5 == str6);

	return 0;
}
