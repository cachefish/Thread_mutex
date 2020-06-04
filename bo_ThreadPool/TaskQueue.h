#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"

#include <queue>
#include <functional>
using std::queue;

namespace wd
{

typedef std::function<void()> ElemType;

class TaskQueue
{
public:
	TaskQueue(size_t queSize);

	bool empty() const;
	bool full() const;
	void push(const ElemType & elem);
	ElemType pop();

	void wakeup() {
		_flag = false;
		_notEmpty.notifyall();
	}
	
private:
	size_t          _queSize;
	queue<ElemType> _que;
	MutexLock       _mutex;
	Condition       _notFull;
	Condition       _notEmpty;
	bool			_flag;
};

}//end of namespace wd


#endif
