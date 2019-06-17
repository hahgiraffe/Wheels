#include "async_log.h"
#include "Buffer.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h> //mkdir,access
#include <unistd.h> //getpid()
#include <errno.h>
#include <sys/time.h> //
#include <stdarg.h> //va_list

#define MEM_USE_LIMIT (3u * 1024 * 1024 * 1024)//3GB
#define LOG_USE_LIMIT (1u * 1024 * 1024 * 1024)//1GB
#define LOG_LEN_LIMIT (4 * 1024)//4K
#define RELOG_THRESOLD 5
#define BUFF_WAIT_TIME 1

pthread_mutex_t AsyncLog::mutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t AsyncLog::condition_ = PTHREAD_COND_INITIALIZER;
pthread_once_t AsyncLog::once_ = PTHREAD_ONCE_INIT;
int AsyncLog::one_buffer_len_ = 30*1024*1024; //30mb
AsyncLog* AsyncLog::log_ = NULL;

AsyncLog::AsyncLog():
                buff_count_(3),
                current_buf_(NULL),
                pre_buf_(NULL),
                fp(NULL),
                pid(0),
                _env_ok(false),
                level_(LEVEL::INFO),
                lasterror(0)

{
    //创建双向链表
    Buffer *head = new Buffer(one_buffer_len_);
    if(!head){
        fprintf(stderr,"double linked list initialization error\n");
        exit(1);
    }
    Buffer* current;
    Buffer* pre = head;
    for(int i=1;i<buff_count_;i++){
        current = new Buffer(one_buffer_len_);
        if(!current){
            fprintf(stderr,"double linked list initialization error\n");
            exit(1);
        }
        current->before_ = pre;
        pre->after_ = current;
        pre = current;
    }
    pre->after_ = head;
    head->before_ = pre;
    current_buf_ = head;
    pre_buf_ = head;

    pid = getpid();
}
    
void AsyncLog::persist(){
    while (true)
    {
        pthread_mutex_lock(&mutex_);
        if(pre_buf_->status == BUFFER_STATUS::FREE){
            struct timespec tsp;
            struct timeval now;
            gettimeofday(&now, NULL);
            tsp.tv_sec = now.tv_sec;
            tsp.tv_nsec = now.tv_usec * 1000;//nanoseconds
            tsp.tv_sec += BUFF_WAIT_TIME;//wait for 1 seconds
            pthread_cond_timedwait(&condition_, &mutex_, &tsp);
        }

        if (pre_buf_->Isempty())
        {
            //如果还是空
            pthread_mutex_unlock(&mutex_);
            continue;
        }

        if(pre_buf_->status == BUFFER_STATUS::FREE)
        {
            assert(current_buf_ == pre_buf_);//to test
            current_buf_->status = BUFFER_STATUS::FULL;
            current_buf_ = current_buf_->after_;
        }
        pthread_mutex_unlock(&mutex_);

        if(!fp){
            fp =fopen(log_dir_,"w");
        }
        //write
        pre_buf_->persist(fp);
        fflush(fp);

        pthread_mutex_lock(&mutex_);
        pre_buf_->clear();
        pre_buf_ = pre_buf_->after_;
        pthread_mutex_unlock(&mutex_);
    }
    
}

void AsyncLog::try_append(const char *content , const char *format,...){ //不定长参数

    char log_line[LOG_LEN_LIMIT];
    timeval now;
    gettimeofday(&now,NULL);
    int prev_len = snprintf(log_line, LOG_LEN_LIMIT, "%s[%s , %s]", content, now.tv_sec, now.tv_usec);
    va_list arg_ptr;
    va_start(arg_ptr,format);
    int main_len = vsnprintf(log_line + prev_len, LOG_LEN_LIMIT - prev_len, format, arg_ptr);
    va_end(arg_ptr);
    
    int len = prev_len + main_len; //整个log总长度
    lasterror = 0;
    bool tell_back = false;

    pthread_mutex_lock(&mutex_);
    if(current_buf_->status() == BUFFER_STATUS::FREE && current_buf_->avail_space() >= len){
        current_buf_->append(content,len);
    }
    else{
        //两个可能，一是status == FULL 二是avail_space < len
        if(current_buf_->status() == BUFFER_STATUS::FULL){
            lasterror = 1;
        }
        else{
            //current_buf_->status() == BUFFER_STATUS::FREE && current_buf_ ->avail_space() < len
            current_buf_->setstatusfull();
            Buffer* nextbuf = current_buf_->after_;
            tell_back = true;
            if(nextbuf->status() == BUFFER_STATUS::FULL){
                //如果下一个也是为FULL，则判断是否超过使用限制
                if(one_buffer_len_ * (buff_count_+1) > MEM_USE_LIMIT){
                    fprintf(stderr, "no more log space can use\n");
                    current_buf_ = nextbuf;
                    lasterror = 1;
                }
                else{
                    //重新申请一个内存,在当前节点与下一个节点之间插入新的节点
                    Buffer* new_buffer = new Buffer(one_buffer_len_);
                    buff_count_ += 1;
                    new_buffer->before_ = current_buf_;
                    current_buf_->after_ = new_buffer;
                    new_buffer->after_ = nextbuf;
                    nextbuf->before_ = new_buffer;
                    current_buf_ = new_buffer;
                }
            }
            else{
                current_buf_ = nextbuf;
            }  
            if (!lasterror)
                current_buf_->append(log_line, len);
        }
    }
    pthread_mutex_unlock(&mutex_);
    if (tell_back)
    {
        pthread_cond_signal(&condition_);
    }

}

    
void AsyncLog::initpath(const char* log_dir, const char* prog_name, int level){
    pthread_mutex_lock(&mutex_);
    strncpy(log_dir_,log_dir,512);
    strncpy(program_name_,prog_name,512);
    mkdir(log_dir_,777); //创建一个目录及其权限
    if (access(log_dir_, F_OK | W_OK) == -1)
    {
        fprintf(stderr, "logdir: %s error: %s\n", log_dir_, strerror(errno));
    }
    else
    {
        _env_ok = true;
    }
    if (level < TRACE)
        level = TRACE;
    if (level > FATAL)
        level = FATAL;
    level_ = level;

    pthread_mutex_unlock(&mutex_);
}

