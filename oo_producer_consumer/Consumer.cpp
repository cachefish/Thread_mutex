#include"Consumer.h"
#include"TaskQueue.h"

#include<unistd.h>
#include<iostream>
using namespace wd;
using std::cout;
using std::endl;
Consumer::Consumer(TaskQueue&taskQue):_taskQue(taskQue)
{}


void Consumer::run()
{
    int cnt = 10;
    while(cnt--)
    {
        int number = _taskQue.pop();
        ::sleep(2);
        cout<<"consumer thread"<<pthread_self()<<"consumer number "<<number<<endl;;
    }
}