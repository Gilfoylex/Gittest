#include "threadpool.h"

int main(int argc, char** argv)
{
	ThreadPool threadPool(10);
	MyTask objMytask;
	threadPool.addTask(std::bind(&MyTask::run, &objMytask, 3));

	while(1)
	{
		printf("there are still %d tasks need to process\n", threadPool.size());  
	    if (threadPool.size() == 0)
        {  
        	threadPool.stop();
        	printf("Now I will exit from main\n"); 
        	exit(0);   
        }  
        sleep(2);
	}
	return 0;
}
