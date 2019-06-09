#ifndef NETCAT_INETADDR_H
#define NETCAT_INETADDR_H
#include "IsCopyable.h"
#include <netinet/in.h>
#include <string>
class Inetaddr{
public:
    explicit Inetaddr(const struct sockaddr_in saddr):sockaddr(saddr){ }
    explicit Inetaddr(int port);
    const struct sockaddr_in& getsocketaddress() const {
        return sockaddr;
    }

    void setSockAddrInet(const struct sockaddr_in& saddr) { sockaddr = saddr; }

    void setPort(uint16_t port) { sockaddr.sin_port = htons(port); }

    uint32_t ipNetEndian() const { return sockaddr.sin_addr.s_addr; }
    uint16_t portNetEndian() const { return sockaddr.sin_port; }

    uint32_t ipHostEndian() const { return ntohl(sockaddr.sin_addr.s_addr); }
    uint16_t portHostEndian() const { return ntohs(sockaddr.sin_port); }
    
    std::string toIp() const;
    std::string toIpPort() const;

    static bool resolve(std::string hostname, Inetaddr*);
    //static std::vector<Inetaddr> resolveAll(StringArg hostname, uint16_t port = 0);
private:
    struct sockaddr_in sockaddr;
};

#endif