#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>
#include "cgi.h"

int rscallback(void *p, int argc, char **argv, char **argvv)
{
    int i;
    *(int *)p = 0;
    /*for(i=0; i<argc; i++) {
        printf("%s=%s ", argvv[i], argv[i]?argv[i]:"NULL");
    }
    putchar('\n');*/
    return 0;
}

int main(void)
{
    cgi_init();
    cgi_process_form();

    sqlite3 *db;
    char *err = 0;
    int ret = 0;
    int empty = 1;
    char *sql = NULL;
    sql = sqlite3_mprintf("select * from user where username=%Q and password=%Q;", cgi_param("UserName"), cgi_param("PassWord"));

    ret = sqlite3_open("./user.db", &db);
    if(ret != SQLITE_OK) {
                fputs(sqlite3_errmsg(db), stderr);
                fputs("\n", stderr);
                exit(1);
    }

    ret = sqlite3_exec(db, sql, rscallback, &empty, &err);        
    if(ret != SQLITE_OK) {
        fputs(err,stderr);
        fputs("\n", stderr);
        sqlite3_close(db);
        exit(1);
    }
    sqlite3_close(db);
    if(empty){
        cgi_redirect("../errpage.html");
    }
    else if(!empty){
        cgi_redirect("../menu.html");
    }

    sqlite3_close(db);
    return 0;
}

