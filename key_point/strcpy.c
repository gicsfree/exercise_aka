#include <stdio.h>
#include <assert.h>

/* strcpy */
char *strcpy(char *strdest, const char *strsrc)
{
	assert((strdest != NULL) && (strsrc != NULL));

	char *address = strdest;

	while ((*strdest++ = *strsrc++) != '\0');

	return address;
}

/* main */
int main(int argc, const char *argv[])
{
	char s[10];
	char str[] = "hello";

	puts(strcpy(s, str));
//    puts(strcpy(NULL, str));

	return 0;
}
