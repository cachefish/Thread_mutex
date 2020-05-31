#include "Thread.h"

#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

void run() 
{
	int cnt = 10;
	::srand(::clock());
	while(cnt--) {
		int number = ::rand() % 100;
		::sleep(1);
		cout << ">> subthread " << pthread_self() << ": number = " << number << endl;
	}
}

struct Task 
{
	void process() {
		run();
	}
};
 
int main(void)
{
	cout << "mainThread: " << pthread_self() << endl;
	unique_ptr<wd::Thread> p(new wd::Thread(std::bind(&Task::process, Task())));
	p->start();
	cout << "mainThread: subthread  " << p->getThreadId() << endl;
	p->join();

	return 0;
}
