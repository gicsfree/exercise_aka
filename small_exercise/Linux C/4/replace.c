
#include <stdio.h>

char * replace(char *str)
{
	char *p; 

	if(str == NULL)
		return NULL;

	p = str;
	while(*p != '\0'){
		if(*p == ' ')
			*p = '_';
		p++;
	}

	return str;
}

int main(void)
{
	char p[] = "hello world and China\n"; 

	printf("the string : %s", replace(p));

	return 0;
}
