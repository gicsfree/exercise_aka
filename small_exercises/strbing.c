#include <stdio.h>
char *strbing(const char *s1,const char *s2,char *s3);
int main(int argc,char *argv[])
{
	char a[6] = "hello", b[6]="hello",c[12];
	printf("%s\n", strbing(a,b,c));
	return 0;
}

char *strbing(const char *s1,const char *s2,char *s3)
{   char *p=s3;
	while (*s1 && *s2) {
		*s3++ = *s1 < *s2 ? *s1++ : *s2++;
	}
	while (*s1)
		*s3++ = *s1++;
	while (*s2)
		*s3++ = *s2++;
        *s3='\0';
    return p;	
}
