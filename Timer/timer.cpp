/*
 * @Author: haha_giraffe
 * @Date: 2019-10-09 16:34:25
 * @Description: file content
 */
#include "timer.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <iostream>
#include <algorithm>
#define MAXEVENTNUM 100

namespace haffe{

Timer::Timer(std::function<void()> cb, int addtime, int calltimes)
    :m_cb(cb)
    ,m_calltimes(calltimes)
{
    m_timerfd = timerfd_create(CLOCK_REALTIME,0);
    if(m_timerfd == -1){
        std::cout<<"create timerfd error"<<std::endl;
    }
    timespec now;
    if(clock_gettime(CLOCK_REALTIME, &now) == -1)       // 得到现在的时间
        std::cout<<"clock_gettime";
    itimerspec newtimer;
    newtimer.it_value.tv_sec = now.tv_sec + 1;          //第一次开始事件的时间（过一秒后开始）
    newtimer.it_value.tv_nsec = now.tv_nsec;
    newtimer.it_interval.tv_sec = addtime;              //时间间隔，单位是秒
    newtimer.it_interval.tv_nsec = 0;
    if(timerfd_settime(m_timerfd,TFD_TIMER_ABSTIME,&newtimer,NULL) == -1 ){
        std::cout<<"set timerfd error"<<std::endl;
    }
    std::cout<<"start timer"<<std::endl;
}

Timer::~Timer(){
    if(m_timerfd){
        close(m_timerfd);
    }
}

void Timer::runcb() const{
    //std::cout<<"runcb"<<std::endl;
    if(m_cb){
        m_cb();
    }
    else{
        std::cout<<"start timer"<<std::endl;
    }
}

void Timer::reset(std::function<void ()> cb){
    if(m_cb){
        m_cb.swap(cb);
    }
}

TimerManager::TimerManager()
{
    m_epollfd = epoll_create(1024);
    if(m_epollfd == -1){
        std::cout<<"create epollfd error"<<std::endl;
    }
    int event;
    fcntl(m_epollfd,F_GETFL,&event);
    event |= O_NONBLOCK;
    fcntl(m_epollfd,F_SETFL,event);
}

TimerManager::~TimerManager(){
    if(m_epollfd){
        close(m_epollfd);
    }
}


void TimerManager::start(){
    struct epoll_event events[MAXEVENTNUM];
    std::cout<<"wait ..."<<std::endl;
    while(true){
        int num = epoll_wait(m_epollfd,events,MAXEVENTNUM,500);
        for(int i=0;i<num;++i){
            epoll_event tmpevent = events[i];
            //int listenfd = tmpevent.data.fd;
            Timer::ptr* time = (Timer::ptr*)tmpevent.data.ptr;
            int listenfd = (*time)->getfd();
            (*time)->runcb();
            int& timenum = (*time)->m_calltimes;
            timenum--;
            if(!timenum){
                std::cout<<"delevent";
                delEvent(*time);
                auto itr = std::find(m_vec.begin(),m_vec.end(),*time);
                m_vec.erase(itr);
            }
            if(m_vec.empty()){
                return;
            }
            uint64_t exp = 0;
            read(listenfd, &exp, sizeof(uint64_t)); 

        }
    }
}

/*这里有一个需要注意的地方，就是epoll.data中的fd和ptr不要同时使用 */
void TimerManager::addEvent(Timer::ptr timer){
    struct epoll_event event;
    //event.data.fd = timer->getfd();
    event.events = EPOLLIN | EPOLLET;
    event.data.ptr = &timer;
    if(!epoll_ctl(m_epollfd,EPOLL_CTL_ADD,timer->getfd(),&event)){
        std::cout<<"epoll_ctl ADD success"<<std::endl;
    }
    m_vec.push_back(timer);
}

void TimerManager::delEvent(Timer::ptr timer){
    struct epoll_event event;
    event.events = EPOLLOUT | EPOLLET;
    event.data.ptr = &timer;
    if(!epoll_ctl(m_epollfd,EPOLL_CTL_DEL,timer->getfd(),NULL)){
        std::cout<<"epoll_ctl mod success"<<std::endl;
    }
}

}