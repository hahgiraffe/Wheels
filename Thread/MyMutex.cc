#include "MyMutex.h"
#include <assert.h>
#include <pthread.h>
MyMutexLock::MyMutexLock():tid(0){
    pthread_mutex_init(&mutex_,NULL);
}
MyMutexLock::~MyMutexLock(){
    assert(tid == 0);
    pthread_mutex_destroy(&mutex_);
}

void MyMutexLock::lock(){
    //assert(status_ == false);
    pthread_mutex_lock(&mutex_);
    tid = pthread_self();
}
   
void MyMutexLock::unlock(){
    //assert(status_ == true);
    tid = 0;
    pthread_mutex_unlock(&mutex_);
}
    
void MyMutexLock::assertlocked(){
    assert(tid == pthread_self());
}