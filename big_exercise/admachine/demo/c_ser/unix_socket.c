#include<stdio.h>		/*                           cli_conn */
#include<stddef.h>		/* serv_listen, serv_accept, cli_conn */
#include<sys/stat.h>	/*              serv_accept, cli_conn */
#include<sys/socket.h>	/* serv_listen, serv_accept, cli_conn */
#include<sys/un.h>		/* serv_listen, serv_accept, cli_conn */
#include<errno.h>		/* serv_listen, serv_accept, cli_conn */
#include<unistd.h>      /* unlink(), read(), write(), close() */
#include<fcntl.h>		/* open() */

#define QLEN 10
#define CLI_PATH   "/var/tmp/"		/* +5 for pid = 14 chars */

/*
 * Create a server endpoint of a connection.
 * Returns fd if all OK, <0 on error.
 */
int serv_listen(const char *name)
{
	int fd, len, err, rval;
	struct sockaddr_un un;

	/* create a UNIX domain stream socket */
	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		return (-1);
	unlink(name);	/* in case it already exists */

	/* fill in socket address structure */
	memset(&un, 0, sizeof(un));
	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, name);
	len = offsetof(struct sockaddr_un, sun_path) + strlen(name);

	/* bind the name to the descriptor */
	if(bind(fd, (struct sockaddr *)&un, len) < 0)
	{
		rval = -2;				/* 绑定出错  */
		goto errout;
	}
	if(listen(fd, QLEN) < 0)	/* tell kernel we're a server */
	{
		rval = -3;				/* 监听出错 */
		goto errout;
	}
	return fd;

errout:
	err = errno;
	close(fd);
	errno = err;
	return rval;
}

int serv_accept(int listenfd, uid_t *uidptr)
{
	int clifd, len, err, rval;
	/* time_t staletime; */
	struct sockaddr_un un;
	struct stat statbuf;

	len = sizeof(un);
	if((clifd = accept(listenfd, (struct sockaddr *)&un, (socklen_t *)&len)) < 0)
		return -1;		/* often errno = EINTR, if signal caught */

	/* obtain the client's uid from its calling address */
	len -= offsetof(struct sockaddr_un, sun_path); /* len of pathname */
	un.sun_path[len] = 0;	/*null terminate */

	if(stat(un.sun_path, &statbuf) < 0)
	{
		rval = -2;
		goto errout;
	}

	if(S_ISSOCK(statbuf.st_mode) == 0)	/* 检查对端套接字文件是否真的是一个套接字文件类型 */
	{
		rval = -3;			/* not a socket file */
		goto errout;
	}

	if(uidptr != NULL)
		*uidptr = statbuf.st_uid;	/* return uid of caller */
	unlink(un.sun_path);			/* we're done with pathname now */
	return(clifd);

errout:
	err = errno;
	close(clifd);
	errno = err;
	return(rval);
}

/*
 * Create a client endpoint and connect to a server.
 * Returns fd if all OK, <0 on error.
 */
int cli_conn(const char *name)
{
	int fd, len, err, rval;
	struct sockaddr_un un;

	/* create a UNIX domain stream socket */
	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		return -1;

	/* fill socket address structure with our address */
	memset(&un, 0, sizeof(un));
	un.sun_family = AF_UNIX;
	sprintf(un.sun_path, "%s%05d", CLI_PATH, getpid());
	len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

	unlink(un.sun_path);	/* in case it already exists */
	if(bind(fd, (struct sockaddr *)&un, len) < 0)
	{
		rval = -2;
		goto errout;
	}

	/* fill socket address structure with server's address */
	memset(&un, 0, sizeof(un));
	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, name);
	len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
	if(connect(fd, (struct sockaddr *)&un, len) < 0)
	{
		rval = -4;
		goto errout;
	}
	return(fd);

errout:
	err = errno;
	close(fd);
	errno = err;
	return(rval);
}

