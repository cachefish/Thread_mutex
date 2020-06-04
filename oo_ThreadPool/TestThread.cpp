#include "Threadpool.h"
#include "Task.h"

#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
: public wd::Task
{
	void process() 
	{
		::srand(::time(NULL));
		int number = ::rand() % 100;
		::sleep(1);
		cout << ">> subthread " << pthread_self() << ": number = " << number << endl;
	}
};
 
int main(void)
{
	cout << "mainThread: " << pthread_self() << endl;

	wd::Threadpool threadpool(4, 10);
	threadpool.start();

	unique_ptr<wd::Task> ptask(new MyTask());

	int cnt = 20;
	while(cnt--) {
		cout << ">> cnt = " << cnt << endl;
		threadpool.addTask(ptask.get());
	}

	threadpool.stop();
	return 0;
}
