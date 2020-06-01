#include"Producer.h"
#include"TaskQueue.h"
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
using std::cout;
using std::endl;

using namespace wd;

Producer::Producer(TaskQueue&taskQue):_taskQue(taskQue)
{

}

void Producer::run()
{
        //生产数据
        ::srand(::clock());
        int cnt = 10;
        while(cnt--){
                int number =  ::rand()%100;
                ::sleep(1);
                _taskQue.push(number);
                cout<<"producer thread"<<pthread_self()<<"producer number:"<<number<<endl;

        }
}