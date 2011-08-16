先注册SIGCHLD信号，用wait处理僵尸进程

listenfd = socket(...);
bind(listenfd, ...);
listen(listenfd, ...); 
while (1) {
	connfd = accept(listenfd, ...);
	n = fork();
	if (n == -1) {
		perror("call to fork");
		exit(1);
	} else if (n == 0) {
		close(listenfd);
		while (1) {
			read(connfd, ...);
			...
			write(connfd, ...);
		}
		close(connfd);
		exit(0);
	} else
		close(connfd);
}
