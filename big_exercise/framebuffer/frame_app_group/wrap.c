#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>

void perr_exit(const char *s)
{
	perror(s);
	exit(1);
}

int Accept(int fd, struct sockaddr *sa, socklen_t * salenptr)
{
	int n;

      again:
	if ((n = accept(fd, sa, salenptr)) < 0) {
		if ((errno == ECONNABORTED) || (errno == EINTR))
			goto again;
		else
			perr_exit("accept error");
	}
	return n;
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
		perr_exit("bind error");
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0)
		perr_exit("connect error");
}

void Listen(int fd, int backlog)
{
	if (listen(fd, backlog) < 0)
		perr_exit("listen error");
}

int Socket(int family, int type, int protocol)
{
	int n;

	if ((n = socket(family, type, protocol)) < 0)
		perr_exit("socket error");
	return n;
}

ssize_t Send(int fd, void *buf, size_t len, int flags)
{
    ssize_t n;

    again:
        if ((n = send(fd, buf, len, flags))== -1){
            if (errno == EINTR)
                goto again;
            else
                return -1;
        }
        
    return n;
}

ssize_t Recv(int fd, void *buf, size_t len, int flags)
{
    ssize_t n;

    again:
        if ((n = recv(fd, buf, len, flags))== -1){
            if (errno == EINTR)
                goto again;
            else
                return -1;
        }
        
    return n;
}

ssize_t Sendto(int fd, void *buf, size_t len, int flags, struct sockaddr *dest_addr, socklen_t addrlen)
{
    ssize_t n;

    again:
        if ((n = sendto(fd, buf, len, flags, dest_addr, addrlen))== -1){
            if (errno == EINTR)
                goto again;
            else
                return -1;
        }
        
    return n;
}

ssize_t Recvfrom(int fd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
    ssize_t n;

    again:
        if ((n = recvfrom(fd, buf, len, flags, src_addr, addrlen))== -1){
            if (errno == EINTR)
                goto again;
            else
                return -1;
        }
        
    return n;
}

void Close(int fd)
{
	if (close(fd) == -1)
		perr_exit("close error");
}