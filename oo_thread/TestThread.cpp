#include"Thread.h"
#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<memory>
#include<unistd.h>
using std::cout;
using std::endl;
using std::unique_ptr;

class MyThread:public wd::Thread
{
private:
    void run()
    {
        int cnt =10;
        while(cnt--)
        {
            int number = ::rand()%100;
            ::sleep(1);
            cout<<">>number="<<number<<endl;
        }
    }
};

int main()
{
    unique_ptr<wd::Thread> p(new MyThread());
    cout<<"mainThread:subthread"<<p->getThreadId()<<endl;
    p->start();
    p->join();

    return 0;

}