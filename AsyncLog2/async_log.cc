#include "async_log.h"
#include "Buffer.h"
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
                level_(LEVEL::INFO)

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

}

void AsyncLog::try_append(const char *content , const char *format,...){ //不定长参数

    char log_line[LOG_LEN_LIMIT];
    va_list arg_ptr;
    va_start(arg_ptr,format);
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

