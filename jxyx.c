#include <stdio.h>
#include<stdlib.h>

void get_email(char *str);
int name(char s1);
int domain(char s2);

int main(int argc, char *argv[])
{
	FILE *fp;
	char string[1024];
	if (2 != argc) {
		printf("intput:./file1 file2\n");
		return 0;
	}
	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("can't open file\n");
		exit(0);
	}
	while (fgets(string, 1024, fp) != NULL)
		get_email(string);
	fclose(fp);

	return 0;
}

void get_email(char *str)
{
	int i=0,j,k;
	while (str[i]) {
		if (str[i] == '@') {
			j = i - 1;
			k = i + 1;
			int m = 0, n = 0, l;
			while (name(str[j]) == 1) {
				m++;
				j--;
			}
			while (domain(str[k]) == 1) {
				n++;
				k++;
			}
			if ((m >= 1 && m <= 32) && (n >= 1 && n <= 64)) {
				for (l = 0; l < m + n + 1; l++)
					printf("%c", str[++j]);
				printf("\n");
			}
		}
		i++;
	}

}

int name(char s1)
{
	if (s1 >= 'a' && s1 <= 'z' || s1 >= 'A' && s1 < 'Z' || s1 == '.'
	    || s1 == '_' || s1 >= '0' && s1 <= '9')
		return 1;
	return 0;
}

int domain(char s2)
{
	if (s2 >= 'a' && s2 <= 'z' || s2 >= 'A' && s2 <= 'Z' || s2 == '.'
	    || s2 == '-' || s2 >= '0' && s2 <= '9')
		return 1;
	return 0;
}
