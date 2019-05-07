/*
 * @Description:  c++线程池实现
 * @Author: haha_giraffe
 * @Date: 2019-04-02 10:37:00
 */
#ifndef THREAD_POLL_H
#define THREAD_POLL_H
#include "iostream"
#include <deque>
#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
/*大致思路，首先实现一个线程池类，里面有线程池管理者，线程个数等属性
然后实现任务类
*/
//task任务类，是一个抽象类，每一个job都是继承他
class Task
{
public:
    Task(void* arg=NULL,const std::string taskname="")
        :_arg(arg),taskname(taskname){ }
    virtual ~Task(){ }
    void setarg(void* arg){
        _arg=arg;
    }
    virtual int run()=0;//纯虚函数
protected:
    void* _arg;
    std::string taskname;
};

//线程池类
class ThreadPool
{
public:
    ThreadPool(int threadnum=10);
    ~ThreadPool();
public:
    int addTask(Task *task);
    void stop();
    int size();
    Task* take();
    int createThreads();//创建线程函数
    static void* threadfunc(void *threaddata);//线程执行函数

private:
    //拷贝构造和拷贝赋值运算符都定义为private为了不允许编译器默认生成
    //只能在类内使用
    ThreadPool(const ThreadPool&);
    ThreadPool& operator=(const ThreadPool&);
private:
    volatile bool state;//保存线程池状态
    int threadnumbers;
    pthread_t* threads;
    pthread_mutex_t mutex;//互斥量
    pthread_cond_t condition;//条件变量
    std::deque<Task*> taskQueue;//任务队列

};

#endif