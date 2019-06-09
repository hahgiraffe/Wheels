#include "Inetaddr.h"
#include "Socket.h"
#include <assert.h>
#include <string.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
Socket::Socket(int sockfd):socketfd(sockfd)
{

}

Socket::~Socket()
{ 
    //关闭socket
    if(socketfd>0){
        int ret = ::close(socketfd);
        assert(ret == 0);
    }
}

void Socket::bindordie(const Inetaddr& address){
    const struct sockaddr_in& saddr = address.getsocketaddress();
    int ret = ::bind(socketfd,(struct sockaddr*)(&saddr),sizeof(saddr));
    assert(ret == 0);
}

void Socket::listenordie(){
    int ret = ::listen(socketfd,5);
    assert(ret == 0);
}
    
int Socket::connect(const Inetaddr& address){
    const struct sockaddr_in& saddr = address.getsocketaddress();
    return ::connect(socketfd,(sockaddr*)&saddr,sizeof(saddr));
}
    
void Socket::shutdownwrite(){
    //关闭写端，处于timewait
    if(::shutdown(socketfd,SHUT_WR) < 0){
        printf("Socket::shutdownwrite error\n");
    }
}
    
void Socket::setreuseaddr(bool on){
    //端口重用，服务器被杀死后可以立刻重启
    int option = on ? 1 : 0;
    if(::setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option)) < 0){
        printf("Socket::setreuseaddr error\n");
    }
}
    
void Socket::settcpnodelay(bool on){
    //设置Nagle禁用
    int option = on ? 1 : 0;
    if(::setsockopt(socketfd,IPPROTO_TCP,TCP_NODELAY,&option,(socklen_t)sizeof(option)) < 0){
        printf("Socket::setreuseaddr error\n");
    }

}
    
Inetaddr Socket::getlocaladdr(){
    struct sockaddr_in localaddr;
    bzero(&localaddr,sizeof(localaddr));
    if(::getsockname(socketfd,(sockaddr*)&localaddr,(socklen_t*)sizeof(&localaddr)) < 0){
        printf("Socket::getsockname error\n");
    }
    return Inetaddr(localaddr);
}
    
Inetaddr Socket::getpeeraddr(){
    struct sockaddr_in peeraddr;
    bzero(&peeraddr,sizeof(peeraddr));
    socklen_t socklen = static_cast<socklen_t>(sizeof(peeraddr));
    if(::getpeername(socketfd,(sockaddr*)&peeraddr,&socklen) < 0){
        printf("Socket::getpeeraddr error\n");
    }
    return Inetaddr(peeraddr);
}

Socket Socket::createTcp(){
    int sockfd = ::socket(AF_INET,SOCK_STREAM | SOCK_CLOEXEC ,IPPROTO_TCP);
    assert(sockfd >= 0);
    return Socket(sockfd);
}

int Socket::read(void* buf, int len)
{
  // FIXME: EINTR
  return ::read(socketfd, buf, len);
}

int Socket::write(const void* buf, int len)
{
  // FIXME: EINTR
  return ::write(socketfd, buf, len);
}
