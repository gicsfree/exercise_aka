#include <stdio.h>
#include <string.h>

char *my_shell(char *s);

int main(int argc, char *argv[])
{
	char str[128];
	printf("mysh%% ");
	while (strlen(gets(str)) > 0) {
		printf("show the command:\n");
		my_shell(str);
		printf("mysh%% ");
	}

	return 0;
}

char *my_shell(char *s)
{
	char *p = s, *q = s, *r, *str = s;
	int flag = 0, flag1 = 0;
	while (*q) {
		if (*q == '<' || *q == '>') {
			flag = 1;
			break;
		} else
			*p++ = *q++;
	}
	if (flag == 1) {
		while (*q) {
			if (*q != ' ')
				*p++ = *q++;
			else
				q++;
		}
		*p = '\0';
	}

	while (*s) {
		if ((*s >= 'a' && *s <= 'z' || *s >= 'A' && *s <= 'Z')
		    && (*(s + 1) == ' ' || *(s + 1) == '<'
			|| *(s + 1) == '>' || *(s + 1) == '\0')) {
			r = s;
			int i, m = 0;
			for (; r > str; r--) {
				if (*r == ' ' || *r == '<' || *r == '>')
					break;
				m++;
			}
			if (r == str || flag1 == 0) {
				flag1 = 1;
				printf("command:");
				for (i = 0; i < m + 1; i++)
					printf("%c", *(r + i));
			} else if ((*r == ' ') && (*(r + 1) == '-' ||
						   (*(r + 1) >= 'a'
						    && *(r + 1) <= 'z')
						   || (*(r + 1) >= 'A'
						       && *(r + 1) <=
						       'Z'))) {
				printf(",argument:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));
			} else if (*r == '<') {
				printf("\n,in-file:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));
				printf(", out-file:NULL");
			} else if (*r == '>') {
				printf("\n,in-file:NULL, out-file:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));
			}

		}
		s++;
	}
	printf("\n");
	return str;
}
