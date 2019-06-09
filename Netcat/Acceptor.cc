#include "Acceptor.h"
#include "Inetaddr.h"
#include "TcpStream.h"
#include <stdio.h>
#include <sys/socket.h>
Acceptor::Acceptor(const Inetaddr& addr) :listensocket(Socket::createTcp())
{
    listensocket.setreuseaddr(true);
    listensocket.bindordie(addr);
    listensocket.listenordie();
}

TcpStreamPtr Acceptor::accept(){
    int sockfd = ::accept(listensocket.fd(),NULL,NULL);
    if(sockfd >= 0){
        return TcpStreamPtr(new TcpStream(Socket(sockfd)));
    }
    else{
        printf("Acceptor::accept error\n");
        return TcpStreamPtr();
    }
}
    
Socket Acceptor::acceptSocketOrDie(){
    int sockfd = ::accept(listensocket.fd(), NULL, NULL);
    if (sockfd >= 0)
    {
        return Socket(sockfd);
    }
    else
    {
        perror("Acceptor::acceptSocketOrDie");
        abort();
    }
}