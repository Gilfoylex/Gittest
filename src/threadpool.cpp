#include "threadpool.h"

static pthread_key_t	t_key;
static pthread_once_t	t_key_once = PTHREAD_ONCE_INIT; 

//线程特有数据的析构函数
static void destory_key(void * value)
{
	//free(value);
	delete (MesData*)value;
}

//线程数据的一次性初始化
static void once_init()
{
	int s;
	s = pthread_key_create(&t_key, destory_key);
	if(s != 0)
		cout<<"pthread_key_create error"<<endl;
}

//超时函数，实现功能号调用超时，暂未实现
void exec_over_time(int)
{
	//Data * value = (Data*)pthread_getspecific(t_key);
	int a = 0;
	//value->GetValue(a);
	cout <<"this value exec over time:"<<a<<endl;
}

//功能木块获取入参的函数
void GetValue(string &a, string paramname)
{
	MesData * value = (MesData*)pthread_getspecific(t_key);
	value->GetValue(a, paramname);
}

void GetValue(int &a, string paramname)
{
	MesData * value = (MesData*)pthread_getspecific(t_key);
	value->GetValue(a, paramname);
}

void GetValue(double &a, string paramname)
{
	MesData * value = (MesData*)pthread_getspecific(t_key);
	value->GetValue(a, paramname);
}

void MakeResult(string ret)
{
	MesData * value = (MesData*)pthread_getspecific(t_key);
	value->CleanMapParams();
	string writeret;
	writeret = value->GetParams() + ret;
	cout<< "writeret===="<<writeret<<endl;
    const char* buffer = writeret.c_str();
	cout << value->GetParams()<<endl;
	cout <<"acccept_fd"<<endl;
	write(value->GetClientFd(), buffer, 100);
}


//具体的任务，根据消息里的对应信息调用对应的共享库（.so文件）
int MyTask::run(string message, int accept_fd)
{
	cout <<message<<endl;
	cout<<"kaishizhixing !"<<endl;
	int suc;
	MesData *value = new MesData();
	suc = pthread_once(&t_key_once,  once_init);
	if(0 != suc)
	{
		cout<<"pthread_once error"<<endl;
	}
	//value = (MesData*)malloc(sizeof(MesData));
	cout<<"fuzhizhiqian"<<endl;
	if(NULL == value)
	{
		cout<<"malloc error"<<endl;
	}
	value->SetParams(message);
	cout<<message<<endl;
	value->SetClientFd(accept_fd);
	suc = pthread_setspecific(t_key, value);
	if(0 != suc)
	{
		cout<<"set pthread_setspecialfic error"<<endl;
	}
	
	//定义一个接受模块入口函数的函数	
	void (*exec_func)();
	void *pdlHandle = dlopen("./libtest.so", RTLD_LAZY);
	if(NULL == pdlHandle)
	{
		cout<<"failed load library"<<endl;
		return -1;
	}
		
	char* pszErr = dlerror();
	if(NULL != pszErr)
	{
		cout<<pszErr<<endl;
		return -1;
	}
	
	//获取函数
	exec_func = (void(*)())dlsym(pdlHandle, "test");

	pszErr = dlerror();
	if(NULL != pszErr)
	{
		cout<<pszErr<<endl;
		dlclose(pdlHandle);
		return -1;
	}
	
	//信号处理实现控制超时（未实现）	
	//signal(SIGALRM, exec_over_time);
	//alarm(5);
	(*exec_func)();
	dlclose(pdlHandle);
	//alarm(0);
	return 0;
}

ThreadPool::ThreadPool(int threadNum)
{
	_isRunning = true;
	_threadNum = threadNum;
	createThreads();
}

ThreadPool::~ThreadPool()
{
	stop();
}

int ThreadPool::createThreads()
{
	pthread_mutex_init(&_mutex, NULL);
	pthread_cond_init(&_condition, NULL);
	_threads = (pthread_t*)malloc(sizeof(pthread_t)*_threadNum);
	for(int i = 0; i < _threadNum; i++)
	{
		pthread_create(&_threads[i], NULL, threadFunc, this);
	}

	return 0;
}

size_t ThreadPool::addTask(const Task& task)
{
	pthread_mutex_lock(&_mutex);
	_taskQueue.push_back(task);
	int size = _taskQueue.size();
	pthread_mutex_unlock(&_mutex);
	pthread_cond_signal(&_condition);
	return size;
}

int ThreadPool::size()
{
	pthread_mutex_lock(&_mutex);
	int size = _taskQueue.size();
	pthread_mutex_unlock(&_mutex);
	return size;
}

void * ThreadPool::threadFunc(void *arg)
{
	pthread_t tid = pthread_self();
	ThreadPool* pool = static_cast<ThreadPool*>(arg);
	while(pool->_isRunning)
	{
		ThreadPool::Task task = pool->take();
		if(!task)
		{
			printf("thread %lu will exit\n", tid);
			break;
		}
		assert(task);
		task();
	}
	return 0;
}

ThreadPool::Task ThreadPool::take()
{
	Task task = NULL;
	pthread_mutex_lock(&_mutex);
	while(_taskQueue.empty() && _isRunning)
	{
		pthread_cond_wait(&_condition, &_mutex);
	}
	if(!_isRunning)
	{
		pthread_mutex_unlock(&_mutex);
		return task;
	}
	assert(!_taskQueue.empty());
	task = _taskQueue.front();
	_taskQueue.pop_front();
	pthread_mutex_unlock(&_mutex);
	return task;
}

void ThreadPool::stop()
{
	if(!_isRunning)
	{
		return;
	}
	_isRunning = false;
	pthread_cond_broadcast(&_condition);

	for(int i =0; i < _threadNum; i++)
	{
		pthread_join(_threads[i], NULL);
	}
	free(_threads);
	_threads = NULL;

	pthread_mutex_destroy(&_mutex);
	pthread_cond_destroy(&_condition);
}




