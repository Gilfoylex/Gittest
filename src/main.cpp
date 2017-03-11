#include "tcp_server.h"

int main(int argc, char** argv)
{
	ThreadPool threadPool(1);
	TcpServer myserver;
	int listenport = atoi(argv[1]);
	threadPool.addTask(std::bind(&TcpServer::run, &myserver, listenport));
//	MyTask objMytask;
//	threadPool.addTask(std::bind(&MyTask::run, &objMytask, "zenmehuishi"));

	while(1)
	{
		printf("there are still %d tasks need to process\n", threadPool.size());  
	    if (threadPool.size() == 0)
        {  
        	threadPool.stop();
        	printf("Now I will exit from main\n"); 
        	exit(0);   
        }  
        sleep(600);
	}
	return 0;
}
