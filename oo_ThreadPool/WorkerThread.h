
#ifndef __WORKERTHREAD_H__ 
#define __WORKERTHREAD_H__ 

#include "Thread.h"
#include "Threadpool.h"

namespace wd
{

class WorkerThread
: public Thread
{
public:
	WorkerThread(Threadpool & threadpool)
	: _threadpool(threadpool)
	{}
private:
	void run()
	{
		_threadpool.threadFunc();
	}
	
private:
	Threadpool & _threadpool;
};

}//end of namespace wd


#endif
 