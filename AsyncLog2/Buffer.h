/*
 * @Description: 
 * @Author: haha_giraffe
 * @Date: 2019-06-17 15:00:14
 */
#pragma once
#include "Copyable.h"
#include <stdio.h> //FILE

//留个日志等级
enum LEVEL{
    TRACE = 1,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

//链表的节点Buffer
enum BUFFER_STATUS{
    FREE,
    FULL
};

class Buffer : private Noncopyable{
public:
    Buffer(int size);
    void append(const char* content , int size);
    bool Isempty();
    int avail_space();
    void clear();
    void persist(FILE*);
    Buffer* before_;
    Buffer* after_;
    BUFFER_STATUS status(){
        return status_;
    }
    void setstatusfull(){
        status_ = BUFFER_STATUS::FULL;
    }
private:
    BUFFER_STATUS status_;
    char* data_;
    int total_len_;
    int used_len_;
};