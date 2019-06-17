/*
 * @Description:  
 * @Author: haha_giraffe
 * @Date: 2019-06-15 16:42:08
 */

#pragma once
#include "Copyable.h"
#include <pthread.h>
#include <stdio.h>
class Buffer;

//单例模式(多线程安全)
class AsyncLog : Noncopyable{
public:
    inline int getlevel(){
        return level_;
    }
    void persist();
    void try_append(const char *content , const char *format,...);
    void initpath(const char* log_dir, const char* prog_name, int level);

    static void init(){
        while(!log_){
            log_ = new AsyncLog();
        }
    }
    static AsyncLog* instance(){
        pthread_once(&once_,&init);
        return log_; //返回指向唯一实例的指针
    }
private:
    AsyncLog();
    int buff_count_;
    Buffer* current_buf_;
    Buffer* last_buf_;
    Buffer* pre_buf_;
    FILE* fp;
    pid_t pid;
    char program_name_[512];
    char log_dir_[512];
    int level_;
    bool _env_ok;
    
    static pthread_mutex_t mutex_;
    static pthread_cond_t condition_;
    static int one_buffer_len_;

    static AsyncLog* log_;
    static pthread_once_t once_;

};
