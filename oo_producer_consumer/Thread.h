#pragma once

#include<pthread.h>
namespace wd
{
    class Thread
    {
        public:
                Thread():_pthid(0),_isRunning(false)
                {}

                virtual  ~Thread();
                void  start();
                void join();

                pthread_t getThreadId(){return _pthid;}
        private:
           virtual void run()=0;

         static  void *threadFunc(void*arg);
        private:
            pthread_t _pthid;
            bool _isRunning;

    };
}





