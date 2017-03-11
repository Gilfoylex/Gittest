#ifndef TCP_SERVER_H
#define TCP_SERVER_H

//#include <unistd.h>
#include <stdio.h>
//#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
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
