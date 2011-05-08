#include <stdio.h>

void exchange()
{
    char string[128];
    printf("inout a string:");
    scanf("%s",string);
	char *p = string;
	while (*p)
		if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
			*p = (*p) ^ (0x01 << 5);
			p++;
		} else
			p++;
    printf("%s\n",string);            
 
}
