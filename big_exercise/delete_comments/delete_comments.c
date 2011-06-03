#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void perr_exit(const char *s);
void delete_comments(FILE * fp_src, FILE * fp_dest);
////////////////////////////////////////////////////
/*****************************************************
* type0: get the comments's type
* type1: //
* type2: / *   
* type3: "" -> "/ * * /"
* type4: '  ->  '"'     // "
******************************************************/
enum type { type0, type1, type2, type3, type4 };

/* main */
int main(int argc, const char *argv[])
{
	if (argc != 3) {
		printf("Usage: ./main src.c dest.c\n");
		return -1;
	}

	FILE *fp_src;
	FILE *fp_dest;

	fp_src = fopen(argv[1], "r");
	if (fp_src == NULL)
		perr_exit("fopen file src.c");
	fp_dest = fopen(argv[2], "w");
	if (fp_dest == NULL)
		perr_exit("fopen file dest.c");

	delete_comments(fp_src, fp_dest);

	fclose(fp_src);
	fclose(fp_dest);

	return 0;
}

/* perr_exit */
void perr_exit(const char *s)
{
	perror(s);
	exit(1);
}

/* delete_comments */
void delete_comments(FILE * fp_src, FILE * fp_dest)
{
	char ch;
	char c;
	int type = 0;

	while ((ch = fgetc(fp_src)) != EOF) {
		switch (type) {
		case type0:	// get the comments's type 
			if (ch == '/') {
				c = fgetc(fp_src);
				if (c == '/')	// type: //
					type = type1;
				else if (c == '*')	// type: /* */
					type = type2;
			} else if (ch == '"') {	// type: "/* */"  "// "
				fputc(ch, fp_dest);
				type = type3;
			} else if (ch == '\047') {	// type: '"'  // "
				fputc(ch, fp_dest);
				type = type4;
			} else
				fputc(ch, fp_dest);

			break;
		case type1:	// type: //
			if (ch == '\n') {
				fputc(ch, fp_dest);
				type = type0;
			}

			break;
		case type2:	// type: /* */
			if (ch == '*') {
				while ((c = fgetc(fp_src)) == '*');	// type: /* *********/
				if (c == '/')
					type = type0;
			}

			break;
		case type3:	// type: "/* */"   "// "
			fputc(ch, fp_dest);
			if (ch == '"')
				type = type0;

			break;
		case type4:	// type: '"'   // "
			fputc(ch, fp_dest);
			if (ch == '\047')
				type = type0;

			break;
		}
	}
}
