#include "tcp_server.h"

int TcpServer::run(int listenport)
{
	int socket_fd;
	int accept_fd;
	sockaddr_in remote_addr;
	sockaddr_in myserver;
	socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socket_fd < 0)
	{
		throw "socket() failed";
	}
	memset(&myserver, 0, sizeof(myserver));
	myserver.sin_family = AF_INET;
	myserver.sin_addr.s_addr = htonl(INADDR_ANY);
	myserver.sin_port = htons(listenport);
	if(bind(socket_fd, (sockaddr*)&myserver, sizeof(myserver)) < 0)
	{
		throw "bind() failed";
	}
	if(listen(socket_fd, 10) < 0)
	{
		throw "listen() failed";
	}
	ThreadPool ClientCon(5);
	NetCon objnetcon;
	while(1)
	{
		socklen_t sin_size = sizeof(struct sockaddr_in);
		if((accept_fd = accept(socket_fd, (struct sockaddr*)&remote_addr, &sin_size)) == -1)
		{
			throw "accpet error!";
			continue;
		}
		printf("Received a connection from %s, accept = %d\n", (char*)inet_ntoa(remote_addr.sin_addr), accept_fd);
		ClientCon.addTask(std::bind(&NetCon::run, &objnetcon, accept_fd));
	}
	close(accept_fd);
	close(socket_fd);
	return 0;
}

int NetCon::run(int accept_fd)
{
	char buffer[MAXSIZE];
	memset(buffer, 0, MAXSIZE);
	ThreadPool execpool(3);
	MyTask objMytask;
	while(1)
	{
		if(read(accept_fd, buffer, MAXSIZE)<=0)
		{
			//throw "read error";
			cout<<"dunkai"<<endl;
			break;
		}
		else
		{
			string strMes(buffer);
			cout<<strMes<<endl;
			execpool.addTask(std::bind(&MyTask::run, &objMytask, strMes, accept_fd));
		}
	}
	close(accept_fd);
}
