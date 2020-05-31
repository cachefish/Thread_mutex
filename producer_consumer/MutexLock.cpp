#include"MutexLock.h"

using namespace wd;


MutexLock::MutexLock():_islocking(false)
{
    pthread_mutex_init(&_mutex,NULL);
}


MutexLock::~MutexLock()
{
    pthread_mutex_destroy(&_mutex);
}