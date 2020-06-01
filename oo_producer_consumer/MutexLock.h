#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__
#include<pthread.h>

namespace wd
{


class MutexLock
{
public:
    MutexLock();
    ~MutexLock();

    void lock();
    void unlock();

    pthread_mutex_t*getMutexLockPtr(){return &_mutex;}

private:
    pthread_mutex_t  _mutex;
    bool _islocking;
};

class MutexLockGuand
{
public:
    MutexLockGuand(MutexLock&mutex):_mutex(mutex)
    {
        _mutex.lock();
    }
    ~MutexLockGuand()
    {
        _mutex.unlock();
    }
private:
    MutexLock&_mutex;

};


} // namespace
#endif