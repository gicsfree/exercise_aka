all:c_cli.cgi login.cgi

c_cli.cgi:c_cli.c
	gcc c_cli.c -o $@ -lcgi

login.cgi:login.c
	gcc login.c -o $@ -lcgi -lsqlite3

clean:
	-rm -rf c_cli.cgi login.cgi 
.PHONY:clean
