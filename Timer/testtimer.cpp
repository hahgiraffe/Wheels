/*
 * @Author: haha_giraffe
 * @Date: 2019-10-09 17:34:44
 * @Description: 只能实现一个定时器的定时
 */
#include "timer.h"
#include <iostream>

void run(){
    std::cout<<"helloworld"<<std::endl;
}
void run2(){
    std::cout<<"helloworld222"<<std::endl;
}

int main(int argc,char* argv[]){
    haffe::TimerManager::ptr manager(new haffe::TimerManager());
//    haffe::Timer::ptr mytime(new haffe::Timer(run,1,2));
    haffe::Timer::ptr mytime2(new haffe::Timer(run2,2,2));
//    manager->addEvent(mytime);
    manager->addEvent(mytime2);
    manager->start();
    return 0;
}