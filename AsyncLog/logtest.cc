#include "Logging.h"
#include "AsyncLog.h"
using namespace haha_giraffe;

AsyncLogger *logptr=NULL;

void asyncoutput(const char *msg,int len){
    logptr->Append(msg,len);//前台进程传递日志
}

int main(int argc,char *argv[]){
    LOG_DEBUG<<"hello";
    char name[256];
    strcpy(name,argv[0]);
    AsyncLogger asynclog("asynclog",500*1000*1000);    
    asynclog.Start();//这里先让后台线程运行
    logptr=&asynclog;
    Logger::SetOutput(asyncoutput);
    for(int i=0;i<10;i++){
        LOG_INFO<<"ASYNC LOG";
        struct timespec ts = { 0, 500*1000*1000 };
        nanosleep(&ts, NULL);
    }
    
}