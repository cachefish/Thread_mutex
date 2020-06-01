#include "Threadpool.h"
#include "Task.h"
#include "WorkerThread.h"

#include <unistd.h>

using namespace wd;

Threadpool::Threadpool(size_t threadNumber, size_t queSize)
: _threadNumber(threadNumber)
, _queSize(queSize)
, _taskque(_queSize)
, _isExit(false)
{
	_threads.reserve(threadNumber);
}

Threadpool::~Threadpool()
{
	if(!_isExit) 
		stop();
}


void Threadpool::start() 
{
	for(size_t idx = 0; idx != _threadNumber; ++idx) {
		unique_ptr<Thread> up(new WorkerThread(*this));
		_threads.push_back(std::move(up));
	}

	for(auto & ptr : _threads)
	{
		ptr->start();
	}
}

void Threadpool::stop() 
{
	if(!_isExit) {
		while(!_taskque.empty()) {
			::sleep(1);	
		}

		_isExit = true;	

		for(auto & ptr : _threads) {
			ptr->join();
		}
	}
}


//充当的是生成者角色
void Threadpool::addTask(Task * ptask) 
{
	_taskque.push(ptask);
}

//充当的是消费者角色
Task * Threadpool::getTask()
{
	return _taskque.pop();
}

//线程池交给子线程的任务
void Threadpool::threadFunc()
{
	while(!_isExit) {
		Task * ptask = getTask();
		if(ptask) 
			ptask->process();
	}
}
