#include"Thread.h"
namespace wd
{
    Thread::Thread(ThreadCallback&&cb):_pthid(0),_cb(std::move(cb))
    {
    }

    void Thread::start()
    {
        pthread_create(&_pthid,NULL,threadFunc,this);
        _isRunning = true;
    }

    void*Thread::threadFunc(void*arg)
    {
        Thread*pthread = static_cast<Thread*> (arg);
        if(pthread){
            pthread->_cb();
        }
        return NULL;
    }

    void Thread::join()
    {
        if(_isRunning){
                pthread_join(_pthid,NULL);
                _isRunning = true;
        }
    }

    Thread::~Thread()
    {
        if(_isRunning){
            pthread_detach(_pthid);
            _isRunning = false;
        }
    }

}