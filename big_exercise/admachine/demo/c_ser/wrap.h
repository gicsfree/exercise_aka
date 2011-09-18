#ifndef __WRAP_H__
#define __WRAP_H__
extern void perr_exit(const char *s);
extern int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
extern void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
extern ssize_t Read(int fd, void *ptr, size_t nbytes);
extern ssize_t Write(int fd, const void *ptr, size_t nbytes);
extern void Close(int fd);
extern ssize_t Readn(int fd, void *vptr, size_t n);
extern ssize_t Writen(int fd, const void *vptr, size_t n);
//extern static ssize_t my_read(int fd, char *ptr);
extern ssize_t Readline(int fd, void *vptr, size_t maxlen);
#endif
