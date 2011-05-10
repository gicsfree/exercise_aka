#include <stdio.h>
#include <string.h>
#include "common.h"

void encryption()
{
	char s[128];
	printf("input a string:");
	empty_cache();
	while (0 == strlen(gets(s)))
		printf("input a string:");
	char *p = s, *q = s;

	while (*p) {
		*p = *p ^ 'x';
		p++;
	}
	printf("encrypted is :%s\n", s);
	while (*q) {
		*q = *q ^ 'x';
		q++;
	}
	printf("decrypted is :%s\n", s);

}
