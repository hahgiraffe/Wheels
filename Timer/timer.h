/*
 * @Author: haha_giraffe
 * @Date: 2019-10-09 16:34:20
 * @Description: epoll定时器(epoll + timerfd)
 */
#ifndef HAHA_GIRAFFE_TIMER_H
#define HAHA_GIRAFFE_TIMER_H
#include <sys/timerfd.h>
#include <memory>
#include <vector>
#include <functional>

namespace haffe{

class Timer{
    friend class TimerManager;
public:
    typedef std::shared_ptr<Timer> ptr;
    //addtime时间间隔，calltime是次数
    Timer(std::function<void()> cb ,int addtime = 1, int calltimes = 5);
    ~Timer();
    const int getfd() const { return m_timerfd; }
    int getcalltime() const { return m_calltimes; }
    void setcb(std::function<void()> cb){ m_cb = cb; }
    void runcb() const;
    void reset(std::function<void ()> cb);
private:
    int m_timerfd;
    std::function<void ()> m_cb;
    int m_calltimes;
};

class TimerManager{
public:
    typedef std::shared_ptr<TimerManager> ptr;
    TimerManager();
    ~TimerManager();
    void start();  //定时次数
    void addEvent(Timer::ptr timer);
    void delEvent(Timer::ptr timer);
private:
    int m_epollfd;
    std::vector<std::shared_ptr<Timer> > m_vec;

};

}
#endif