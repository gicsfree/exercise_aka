表示允许创建端口号相同但IP地址不同的多个socket描述符, 在server代码的socket()和bind()调用之间插入如下代码：

int opt = 1;
setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
