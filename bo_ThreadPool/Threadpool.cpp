#include "Threadpool.h"
#include "Thread.h"
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
		unique_ptr<Thread> up(new Thread(
			std::bind(&Threadpool::threadFunc, this)
		));
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
		_taskque.wakeup();
		for(auto & ptr : _threads) {
			ptr->join();
		}
	}
}


//充当的是生成者角色
void Threadpool::addTask(Task && task) 
{
	_taskque.push(std::move(task));
}

//充当的是消费者角色
Threadpool::Task Threadpool::getTask()
{
	return _taskque.pop();
}

//线程池交给子线程的任务
void Threadpool::threadFunc()
{
	while(!_isExit) {
		Task task = getTask();
		if(task) 
			task();// 任务执行的时间不确定
	}
}
