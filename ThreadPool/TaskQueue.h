#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"

#include <queue>
using std::queue;

namespace wd
{

class Task;

typedef Task * ElemType;

class TaskQueue
{
public:
	TaskQueue(size_t queSize);

	bool empty() const;
	bool full() const;
	void push(const ElemType & elem);
	ElemType pop();
	
private:
	size_t          _queSize;
	queue<ElemType> _que;
	MutexLock       _mutex;
	Condition       _notFull;
	Condition       _notEmpty;
};

}//end of namespace wd


#endif
