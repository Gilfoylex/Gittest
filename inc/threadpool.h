#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <deque>
#include <pthread.h>
#include <functional>	//for std::function, std::bind
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <signal.h>
#include <dlfcn.h>	//动态加载共享库
#include "data.h"


class MyTask
{
public:
	int run(int data); //不同的任务可以键不同的类，通过std::function<void()>将任务抽象为可执行函数
};

class ThreadPool
{
public:
	typedef std::function<void()> Task;	//任务对象，具体参见任务实现在源文件	
	ThreadPool(int threadNum = 10);
	~ThreadPool();

	size_t addTask(const Task& task);
	void stop();
	int size();
	Task take();

private:
	int createThreads();
	static void* threadFunc(void * threadData);


	//禁用默认的两个函数	
	ThreadPool& operator = (const ThreadPool&);
	ThreadPool(const ThreadPool&);

	volatile bool		_isRunning;
	int					_threadNum;
	pthread_t*			_threads;

	std::deque<Task>	_taskQueue;
	pthread_mutex_t		_mutex;
	pthread_cond_t		_condition;
};



#endif
