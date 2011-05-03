#include <stdio.h>
int strcmp(const char *s1, const char *s2);
int main(int argc, char *argv[])
{
	char a[6] = "hello", b[6] = "Hello";
	int n;
	n = strcmp(a, b);
	switch (n) {
	case 1:
		printf("a>b\n");
		break;
	case 0:
		printf("a=b\n");
		break;
	case -1:
		printf("a<b\n");
		break;
	}

	return 0;
}

int srtcmp(const char *s1, const char *s2)
{
	int flag = 1, n;
	while (*s1 && *s2)
		if (*s1++ == *s2++)
			continue;
		else {
			flag = 0;
			break;
		}
	if (0 == flag) {
		s1--;
		s2--;
	}
	if (*s1 - *s2 > 0)
		n = 1;
	else if (*s1 - *s2 == 0)
		n = 0;
	else
		n = -1;
	return n;

}
