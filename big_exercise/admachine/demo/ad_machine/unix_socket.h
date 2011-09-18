#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

#include<stdio.h>		/*                           cli_conn */
#include<stddef.h>		/* serv_listen, serv_accept, cli_conn */
#include<sys/stat.h>	/*              serv_accept, cli_conn */
#include<sys/socket.h>	/* serv_listen, serv_accept, cli_conn */
#include<sys/un.h>		/* serv_listen, serv_accept, cli_conn */
#include<errno.h>		/* serv_listen, serv_accept, cli_conn */

#define QLEN 10
#define CLI_PATH   "/var/tmp/"		/* +5 for pid = 14 chars */

#endif

/*
 * Create a server endpoint of a connection.
 * Returns fd if all OK, <0 on error.
 */
int serv_listen(const char *name);

int serv_accept(int listenfd, uid_t *uidptr);

/*
 * Create a client endpoint and connect to a server.
 * Returns fd if all OK, <0 on error.
 */
int cli_conn(const char *name);

