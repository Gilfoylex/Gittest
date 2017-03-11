#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "threadpool.h"

#define MAXSIZE 1024

class NetCon{
	public:
		int run(int accept_fd);
};

class TcpServer{
	public:
		int run(int listenport);
};

#endif
