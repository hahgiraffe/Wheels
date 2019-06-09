#ifndef NETCAT_TCPSTREAM_H
#define NETCAT_TCPSTREAM_H
#include "Socket.h"
#include "IsCopyable.h"
#include <memory>
class InetAddr;
class TcpStream;
typedef std::unique_ptr<TcpStream> TcpStreamPtr;

class TcpStream :private Noncopyable{
public:
    explicit TcpStream(Socket&& sock);
    TcpStream(TcpStream&&) = default;
    ~TcpStream() = default;
    static TcpStreamPtr connect(const Inetaddr& serverAddr);
    static TcpStreamPtr connect(const Inetaddr& serverAddr, const Inetaddr& localAddr);

    int receiveAll(void* buf, int len);  // read len bytes, unless error happens
    int receiveSome(void* buf, int len); // read len or less bytes

    int sendAll(const void* buf, int len);  // send len bytes, unless error happens
    int sendSome(const void* buf, int len); // send len or less bytes

    void setTcpNoDelay(bool on);
    void shutdownWrite();
private:
    static TcpStreamPtr connectInternal(const Inetaddr& serverAddr, const Inetaddr* localAddr);
    Socket socket;
};
#endif