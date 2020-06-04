#include"TaskQueue.h"

using namespace wd;


TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize)
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
,_flag(true)
{

}

bool TaskQueue::empty()const
{
    return _que.size()==0;
}

bool TaskQueue::full() const
{
    return _que.size()==_queSize;
}

void TaskQueue::push(const ElemType&Elem)
{   
    MutexLockGuand autoLock(_mutex);
    while(full()){    //使用while是为了防止条件变量被异常唤醒
        _notFull.wait();
    }
    _que.push(Elem);

    _notEmpty.notify();
}
ElemType TaskQueue::pop()
{
    MutexLockGuand autoLock(_mutex);
    while(_flag&&empty()){
        _notEmpty.wait();
    }
    if(_flag){
            ElemType temp = _que.front();
    _que.pop();
    _notFull.notify();
    return temp;
    }else{
        return NULL;
    }

}