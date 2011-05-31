#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"

#define LEN 128

void exchange()
{
	char string[LEN];
	printf("input a string:");
	empty_cache();
	Gets(string, sizeof(string));

	char *p = string;
	while (*p)
		if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
			*p = (*p) ^ (0x01 << 5);	/* 大小写字母只有第5位不同 */
			p++;
		} else
			p++;
	printf("exchanged is:%s\n", string);

}
