/*
 * @Description: 对thread进行封装
 * @Author: haha_giraffe
 * @Date: 2019-06-13 17:11:00
 */
#pragma once
#include <pthread.h>
#include <functional>
#include "noncopyable.h"

class MyThread : private noncopyable{
public:
    typedef std::function<void ()> Func;
    MyThread(const Func&);
    ~MyThread();
    void start();
    int join();
    bool started();
    void printtid();
    Func f(){ return f_;}
    //void* runInthread(void*);
private:
    Func f_;
    pthread_t pthreadID_;
    bool started_;
    bool joined_;
};
