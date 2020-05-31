#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include"MutexLock.h"
#include"Condition.h"
#include<queue>

using std::queue;

namespace wd
{
    typedef int ElemType;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);

    bool empty()const;
    bool full() const;

    void push(const ElemType&Elem);
    void pop();


private:
    size_t                               _queSize;
    queue<ElemType>     _que;
    MutexLock                     _mutex;
    Condition                       _notfull;
    Condition                       _notempty;

};









}
#endif