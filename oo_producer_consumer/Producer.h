#include"Thread.h"

#include<iostream>
using std::cout;
using std::endl;

namespace wd{

class TaskQueue;

class  Producer:public Thread
{
public:
    Producer(TaskQueue&taskQue);
private:
    void run();
private:
    TaskQueue&_taskQue;

};


}