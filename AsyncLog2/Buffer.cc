#include "Buffer.h"
#include <stdlib.h> //exit
#include <string.h>
Buffer::Buffer(int size):
                    before_(NULL),
                    after_(NULL),
                    status_(BUFFER_STATUS::FREE),
                    data_(NULL),
                    total_len_(size),
                    used_len_(0)
{
    data_ = new char[total_len_];
    if(!data_){
        fprintf(stderr,"data initialization error\n");
        exit(1);
    }
}

void Buffer::append(const char* content , int size){
    if(size > avail_space()){
        //提供的大于剩余的空间
        return;
    }
    memcpy(data_ + used_len_,content,size);
    used_len_ += size;
}
    
bool Buffer::Isempty(){
    return used_len_ == 0;
}

int Buffer::avail_space(){
    return total_len_ - used_len_;
}
    
void Buffer::clear(){
    used_len_ = 0;
    status_ = BUFFER_STATUS::FREE;
}
    
void Buffer::persist(FILE* f){
    size_t len = fwrite(data_,used_len_,1,f);
    if(len != used_len_){
        fprintf(stderr,"data write to logfile error\n");
        exit(1);
    }
}