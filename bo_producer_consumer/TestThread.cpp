#include "Thread.h"
#include "TaskQueue.h"

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

struct Producer
{
	void produce(wd::TaskQueue & taskQue) {
		int cnt = 20;
		::srand(::clock());
		while(cnt--) {
			int number = ::rand() % 100;
			taskQue.push(number);
			::sleep(1);
			cout << ">> producerthread " << pthread_self() << ": produce number = " << number << endl;
		}
	}
};

struct Consumer
{
	void consume(wd::TaskQueue & taskQue)
	{
		int cnt = 20;
		while(cnt--)
		{
			int number = taskQue.pop();
			::sleep(2);
			cout << ">>> consumeThread " << pthread_self() << ": consume a number " << number << endl;
		}
	}
};
 
int main(void)
{
	wd::TaskQueue taskqueue(10);
	cout << "mainThread: " << pthread_self() << endl;
	unique_ptr<wd::Thread> pProducer(
		new wd::Thread(
			//bind绑定参数时，采用的是值传递--> 复制
			std::bind(&Producer::produce, Producer(), std::ref(taskqueue))
	));

	unique_ptr<wd::Thread> pConsumer(
		new wd::Thread(
			std::bind(&Consumer::consume, Consumer(), std::ref(taskqueue))	
		)		
	);

	pProducer->start();
	pConsumer->start();
	pProducer->join();
	pConsumer->join();

	return 0;
}
