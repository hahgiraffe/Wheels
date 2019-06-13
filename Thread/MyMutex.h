/*
 * @Description: 对于mutex进行包装
 * @Author: haha_giraffe
 * @Date: 2019-06-13 11:30:53
 */
#pragma once

#include <pthread.h>
#include "noncopyable.h"
//先看一下mutex的api
class MyMutexLock : private noncopyable{
public:
    MyMutexLock();
    ~MyMutexLock();
    void lock();
    void unlock();
    void assertlocked();
private:
    pthread_mutex_t mutex_;
    //bool status_;
    pthread_t tid;
};


class MyMutexLockGuard : noncopyable{
public:
    //这里是拷贝构造
    MyMutexLockGuard(MyMutexLock& lock) : lock_(lock){
        lock_.lock();
    }
    ~MyMutexLockGuard(){
        lock_.unlock();
    }
private:
    MyMutexLock& lock_; //因为MyMutexLock是没有拷贝构造，所以这里要定义为引用
};