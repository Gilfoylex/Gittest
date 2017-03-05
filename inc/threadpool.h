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
#include <dlfcn.h>
#include "data.h"


class MyTask
{
	public:
		int run(int data);
};

class ThreadPool
{
public:
	typedef std::function<void()> Task;
	
	ThreadPool(int threadNum = 10);
	~ThreadPool();

	size_t addTask(const Task& task);
	void stop();
	int size();
	Task take();

private:
	int createThreads();
	static void* threadFunc(void * threadData);


	//ban operator =
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
