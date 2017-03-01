#include "thread.h"

static pthread_key_t t_key;
static pthread_once_t t_key_once = PTHREAD_ONCE_INIT;

static void destructor(void *value)
{
    free(value);
}

static void once_init()
{
    int s;
    /*在phtread_once函数里创建特有数据的key，
    哪个线程先调用就哪个线程创建key*/
    s = pthread_key_create(&t_key, destructor);
    if (s != 0)
        cout<< "pthread_key_create error";
}

void GetValue(int &a)
{
    Data* value = (Data*)pthread_getspecific(t_key);
    value->GetValue(a);
}

void* Thread::run1()  
{  
    threadStatus = THREAD_STATUS_RUNNING;  
    tid = pthread_self();  
    run();  
    threadStatus = THREAD_STATUS_EXIT;  
    tid = 0;  
    pthread_exit(NULL);  
}  
  
Thread::Thread()  
{  
    tid = 0;  
    threadStatus = THREAD_STATUS_NEW;  
}  
  
bool Thread::start()  
{  
    int iRet = 0;
    pthread_create(&tid, NULL, thread_proxy_func, this) == 0;  
}  
  
pthread_t Thread::getThreadID()  
{  
    return tid;  
}  
  
int Thread::getState()  
{  
    return threadStatus;  
}  
  
void Thread::join()  
{  
    if (tid > 0)  
    {  
        pthread_join(tid, NULL);  
    }  
}

void * Thread::thread_proxy_func(void * args)  
{  
        Thread * pThread = static_cast<Thread *>(args);   
   
        pThread->run();   
          
        return NULL;   
}  
  
void Thread::join(unsigned long millisTime)  
{  
    if (tid == 0)  
    {  
        return;  
    }  
    if (millisTime == 0)  
    {  
        join();  
    }else  
    {  
        unsigned long k = 0;  
        while (threadStatus != THREAD_STATUS_EXIT && k <= millisTime)  
        {  
            usleep(100);  
            k++;  
        }  
    }  
}  



void MultiThread::run()
{
    int status;
    Data *value;
    status = pthread_once(&t_key_once, once_init);
    if(status != 0){
        cout<< "pthread_once error";
    }

    value = (Data*)malloc(sizeof(Data));
    if(value == NULL){
        cout<<"malloc error";
    }

    value->SetValue(this->a);

	//set setspecific
	status = pthread_setspecific(t_key, value);
	if(0 != status)
	{
		cout<<"setspecific error"<<endl;
	}

    void(*entrance_func)();
    //加载动态库
    void *pdlHandle = dlopen("./libtest.so", RTLD_LAZY);
    //错误处理
    if(pdlHandle == NULL ) {
        cout<<"Failed load library"<<endl;
        return;
    }

    char* pszErr = dlerror();

    if(pszErr != NULL)
    {
        cout<<pszErr<<endl;
        return;
    }

    //获取函数的地址
    entrance_func = (void(*)())dlsym(pdlHandle, "test");

    pszErr = dlerror();

    if(pszErr != NULL)
    {
        cout<<pszErr<<endl;
        dlclose(pdlHandle);
        return;
    }
    //实现函数调用
    (*entrance_func)();
    //程序结束时关闭动态库
    dlclose(pdlHandle);
}

MultiThread::MultiThread(int x)
{
    a = x;
}
