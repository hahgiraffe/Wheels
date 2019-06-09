#ifndef NETCAT_SOCKET_H
#define NETCAT_SOCKET_H
#include "IsCopyable.h"
#include <utility> //std::swap

class Inetaddr;
class Socket : private Noncopyable{
public:
    explicit Socket(int sockfd);
    ~Socket();

    //移动拷贝构造
    Socket(Socket&& soc): Socket(soc.socketfd)
    {
        soc.socketfd = -1;
    }
    //移动拷贝赋值运算符
    Socket& operator = (Socket&& soc){
        swap(soc);
        return *this;
    }

    void swap(Socket& soc){
        std::swap(socketfd,soc.socketfd);
    }

    int fd() const {return socketfd;}

    //socket api
    void bindordie(const Inetaddr& address);
    void listenordie();
    int connect(const Inetaddr& address);
    void shutdownwrite();
    void setreuseaddr(bool on);
    void settcpnodelay(bool on);
    Inetaddr getlocaladdr();
    Inetaddr getpeeraddr();

    int read(void* buf, int len);
    int write(const void* buf, int len);

    //工厂方法
    static Socket createTcp();
private:
    int socketfd;
};

#endif