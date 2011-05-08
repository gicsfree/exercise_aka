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
	int flag = 0, flag1 = 0,flag2=0,flag3=0;
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
		if ((*s!=' ')
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
			} else if ((*r == ' ') && (*(r + 1) !='<') &&
						  ( *(r + 1) != '>')){
				printf(",argument:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));
			} else if (*r == '<') {
				printf("\n,in-file:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));
                    flag2=1;
		
			} else if (*r == '>') {
				printf("\n, out-file:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));
                    flag3=1;
			}


		}
		s++;
	}
    if(flag2==0)
    		printf(",in-file:NULL");
            if(flag3==0)
printf(",out-file:NULL\n");
	printf("\n");
	return str;
}
