#include "MyThread.h"
#include <assert.h>
#include <stdio.h>

MyThread::MyThread(const Func& func):f_(func),
                                    pthreadID_(0),
                                    started_(false),
                                    joined_(false)
{
    
}

MyThread::~MyThread(){
    if(started_ && !joined_){
        pthread_detach(pthreadID_);
    }
}
void* runInthread(void* arg){

    MyThread& thread(*static_cast<MyThread*>(arg));
    (thread.f())();//执行函数
}

void MyThread::start(){
    assert(started_ == false);
    started_ = true;
    if(pthread_create(&pthreadID_,NULL,&runInthread,this)){
        started_ = false;
        printf("pthread_creat error\n");
    }
}
    
int MyThread::join(){
    assert(started_);
    assert(!joined_);
    joined_ = true;
    return pthread_join(pthreadID_, NULL);
}

bool MyThread::started(){
    return started_;
}

void MyThread::printtid() { printf("tid : %d",pthreadID_); }