#include "thread_pool.h"
#include <unistd.h>
#include <time.h>
//
class Mytask:public Task{
public:
    Mytask(){}
    virtual int run(){
        printf("thread[%lu]:%s\n",pthread_self(),(char*)this->_arg);
        sleep(1);  
        return 0;  
    }
};

int main(){
    //clock_t early,late;
    //early=clock();
    char myword[]="hello word";
    Mytask taskobj;
    taskobj.setarg((void*)myword);
    ThreadPool threadpool(10);
    for(int i=0;i<20;i++){
        threadpool.addTask(&taskobj);
    }

    while(1){
        printf("there are still %d tasks need to process\n",threadpool.size());
        if(threadpool.size()==0){
            threadpool.stop();
            printf("exit from main thread\n");
            //late=clock();
            //std::cout<<"time is "<<(double)(late-early)/CLOCKS_PER_SEC<<std::endl;
            exit(0);
        }
        sleep(2);
    }
    
    return 0;
}