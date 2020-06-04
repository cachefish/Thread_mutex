#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include"TaskQueue.h"
#include"Thread.h"
#include<memory>
#include<vector>
using std::vector;
using std::unique_ptr;

namespace wd
{

class Thread;
class WorkThread;

class Threadpool
{
    friend WorkThread;
public:
    Threadpool(size_t,size_t);
    ~Threadpool();

    void start();
    void stop();
    void addTask(Task*);
private:
    Task*getTask();
    void threadFunc();

private:
    size_t _threadNumber;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskque;
    bool _isExit;
};

}
#endif