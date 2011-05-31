#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"

#define LEN 128

void encryption()
{
	char s[LEN];
	printf("input a string:");
	empty_cache();
	Gets(s, sizeof(s));

	char *p = s, *q = s;

	while (*p) {
		*p = *p ^ 'x';	/* 加密，即和一个字母取异或 */
		p++;
	}
	printf("encrypted is :%s\n", s);
	while (*q) {
		*q = *q ^ 'x';	/* 解密，即和同一个字母取异或 */
		q++;
	}
	printf("decrypted is :%s\n", s);

}
