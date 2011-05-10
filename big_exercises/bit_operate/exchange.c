#include <stdio.h>
#include <string.h>
#include "common.h"

void exchange()
{
	char string[128];
	printf("input a string:");
	empty_cache();
	while (0 == strlen(gets(string)))
		printf("input a string:");
	char *p = string;
	while (*p)
		if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
			*p = (*p) ^ (0x01 << 5);
			p++;
		} else
			p++;
	printf("exchanged is:%s\n", string);

}
