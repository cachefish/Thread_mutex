#include "TaskQueue.h"
#include "Producer.h"
#include "Consumer.h"

#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

int main(void)
{
    cout<<"mainThread"<<pthread_self()<<endl;
    wd::TaskQueue queue(4);

    unique_ptr<wd::Thread> pProduecer(new wd::Producer(queue));
    unique_ptr<wd::Thread> pConsumer(new wd::Consumer(queue));
    pProduecer->start();
    pConsumer->start();
    
    pProduecer->join();
    pConsumer->join();

    return 0;
}