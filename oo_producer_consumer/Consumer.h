#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include"Thread.h"

namespace wd
{
class TaskQueue;

class Consumer:public Thread
{
public:
    Consumer(TaskQueue&taskQue);

private:
    void run();
private:
    TaskQueue &_taskQue;
};












}





#endif