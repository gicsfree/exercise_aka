#ifndef _WRAP_H_
#define _WRAP_H_

extern void perr_exit(const char *s);
extern int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
extern void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
extern void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
extern void Listen(int fd, int backlog);
extern int Socket(int family, int type, int protocol);
extern ssize_t Send(int fd, const void *buf, size_t len, int flags);
extern ssize_t Recv(int fd, const void *buf, size_t len, int flags);
extern ssize_t Sendto(int fd, void *buf, size_t len, int flags, struct sockaddr *dest_addr, socklen_t addrlen);
extern ssize_t Recvfrom(int fd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
extern void Close(int fd);

#endif
