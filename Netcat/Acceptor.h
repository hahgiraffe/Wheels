#ifndef NETCAT_ACCEPTOR_H
#define NETCAT_ACCEPTOR_H
#include "IsCopyable.h"
#include "Socket.h"
#include <memory>

class Inetaddr;
class TcpStream;
typedef std::unique_ptr<TcpStream> TcpStreamPtr;

//Socket类的又一层封装
class Acceptor : private Noncopyable{
public:
    explicit Acceptor(const Inetaddr& addr);
    ~Acceptor() = default;
    Acceptor(Acceptor&&) = default;
    Acceptor& operator=(Acceptor&&) = default;

    TcpStreamPtr accept();
    Socket acceptSocketOrDie();
private:
    Socket listensocket;
};


#endif