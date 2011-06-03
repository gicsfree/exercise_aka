#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void perr_exit(const char *s);
int delete_comments(FILE *fp_src, FILE *fp_dest);
////////////////////////////////////////////////////
/*****************************************************
* state0: get the state
* state1: //
* state2: / *   
* state3: "" -> "/ * * /"
* state4: '  ->  '"'  // "
******************************************************/
enum state {state0, state1, state2, state3, state4};

/* main */
int main(int argc, const char *argv[])
{
    if (argc != 3){
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
int delete_comments(FILE *fp_src, FILE *fp_dest)
{
    char ch;
    char c;
    int state = 0;

    while ((ch = fgetc(fp_src)) != EOF){
        switch (state){
        case state0:                       // get the state
            if (ch == '/'){
                c = fgetc(fp_src);
                if (c == '/')              // state: //
                    state = state1;
                else if (c == '*')         // state: / *
                    state = state2;
            }else if (ch == '"'){          // state: "// / *"
                fputc(ch, fp_dest);
                state = state3;
            }else if (ch == '\047'){       // state: '"'  // "
                fputc(ch, fp_dest);
                state = state4;
            }
            else
                fputc(ch, fp_dest); 
            
            break;
        case state1:                       // state: //
            if (ch == '\n'){
                fputc(ch, fp_dest);
                state = state0;
            }

            break;
        case state2:                       // state: / *
            if (ch == '*'){
                c = fgetc(fp_src);
                if (c == '/')
                    state = state0;
            }
                
            break;
        case state3:                       // state: "// / * "
            fputc(ch, fp_dest);
            if (ch == '"')
                state = state0;
            break;
        
        case state4:                       // state: '"'  // "
            fputc(ch, fp_dest);
            if (ch == '\047')
                state = state0;

            break;
        }
    }

    return 0;
}

