#include <stdio.h>
#include <string.h>

#define SIZE_MAX 1024

void Gets(char[], int n);
void find_number(char str[]);

///////////////////////////////////////////////
/**********************************************
 * state0: conmon state;
 * state1: number state;
 *********************************************/
enum state { state0, state1 };

/* main */
int main(int argc, const char *argv[])
{
	char str[SIZE_MAX];

	printf("Please input str:");
	Gets(str, sizeof(str));
	while (strlen(str) > 0) {
		find_number(str);
		printf("\nPlease input str:");
		Gets(str, sizeof(str));
	}

	return 0;
}

/* gets a string */
void Gets(char str[], int n)
{
	char s[n];
	int i = 0;

	fgets(s, n, stdin);

	while ((s[i] != '\n') && (s[i] != '\0')) {
		*str++ = s[i];
		i++;
	}
	*str = '\0';
}

/* find number */
void find_number(char str[])
{
	int i = 0;
	int state = 0;

	while (str[i] != '\0') {
		switch (state) {
		case state0:	// common state
			if ((str[i] >= '0') && (str[i] <= '9')) {
				printf("%c", str[i]);
				state = state1;
			}
			i++;

			break;
		case state1:	// number state
			if ((str[i] >= '0') && (str[i] <= '9'))
				printf("%c", str[i]);
			else {
				printf("\n");
				state = state0;
			}
			i++;

			break;
		}
	}
}
