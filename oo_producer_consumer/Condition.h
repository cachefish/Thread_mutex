#ifndef _CONDITION_H__
#define _CONDITION_H__
#include"Noncopyable.h"
#include"MutexLock.h"
#include<pthread.h>

namespace wd
{
    
class Condition:Noncopyable
{
public:
    Condition(MutexLock&mutex);
     ~Condition();

     void wait();
     void notify();
     void notifyall();

private:
    pthread_cond_t _cond;
    MutexLock&_mutex;
};













} // namespace wd
#endif