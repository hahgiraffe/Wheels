/*
 * @Description:  测试MyThread
 * @Author: haha_giraffe
 * @Date: 2019-06-13 18:39:50
 */

#include "MyMutex.h"
#include "MyThread.h"
#include <iostream>
static int a = 3;
MyMutexLock lock;
void func(){
    {
        MyMutexLockGuard guard(lock);
        for(int i=0;i<50;i++){
            a++;
            std::cout<<"other thread a : "<<a<<" , tid : "<<pthread_self()<<std::endl;
        }
    }
}

int main(){
    MyThread thread(func);
    thread.start();
    {
        MyMutexLockGuard guard(lock);
        for(int i=0;i<50;i++){
            a++;
            std::cout<<"main thread a : "<<a<<" , tid : "<<pthread_self()<<std::endl;
        }
    }
    thread.join();
}
