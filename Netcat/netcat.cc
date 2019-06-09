#include "TcpStream.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Inetaddr.h"
#include <thread>
#include <string.h>
#include <unistd.h>
using namespace std;

int write_n(int fd, const void* buf, int length)
{
  int written = 0;
  while (written < length)
  {
    int nw = ::write(fd, static_cast<const char*>(buf) + written, length - written);
    if (nw > 0)
    {
      written += nw;
    }
    else if (nw == 0)
    {
      break;  // EOF
    }
    else if (errno != EINTR)
    {
      perror("write");
      break;
    }
  }
  return written;
}

void run(TcpStreamPtr tcpstreamptr){
    //两个线程，每个线程都有一个循环
    std::thread thr(
        //这个线程用于将从fd接收到的数据放到stdout
        [&tcpstreamptr](){
            char buf[8192];
            int nr = 0;
            while ( (nr = tcpstreamptr->receiveSome(buf, sizeof(buf))) > 0)
            {       
                int nw = write_n(STDOUT_FILENO, buf, nr);
                if (nw < nr)
                {
                    break;
                }
            }
            ::exit(0); 
        }
    );
    //主线程用于读取stdin的数据并发送到fd
    char buf[8192];
    int nr = 0;
    while ( (nr = ::read(STDIN_FILENO, buf, sizeof(buf))) > 0)
    {
        int nw = tcpstreamptr->sendAll(buf, nr);
        if (nw < nr)
        {
            break;
        }
    }
    tcpstreamptr->shutdownWrite();
    thr.join();

}


int main(int argc,char *argv[]){
    if(argc < 3){
        printf("Usage:\n  %s hostname port\n  %s -l port\n", argv[0], argv[0]);
        return 0;
    }
    int port = atoi(argv[2]);//argv[2]是端口
    if(strcmp(argv[1],"-l") == 0){
        //只有一个port,服务器端
        std::unique_ptr<Acceptor> AcceptorPtr(new Acceptor(Inetaddr(port)));
        TcpStreamPtr streamptr(AcceptorPtr->accept());
        if(streamptr){
            AcceptorPtr.reset();//重置指针
            run(std::move(streamptr));
        }
        else{
            printf("main:streamptr error\n");
        }
    }
    else{
        //argv[1]是地址，客户端
        const char* hostname = argv[1];
        Inetaddr addr(port);
        if (Inetaddr::resolve(static_cast<std::string>(hostname), &addr))
        {
            TcpStreamPtr stream(TcpStream::connect(addr));
            if (stream)
            {
                run(std::move(stream));
            }
            else
            {
                printf("Unable to connect %s\n", addr.toIpPort().c_str());
                perror("");
            }
        }
        else
        {
            printf("Unable to resolve %s\n", hostname);
        }

    }

}