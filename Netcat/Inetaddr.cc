#include "Inetaddr.h"
#include "string.h"
#include <assert.h>
#include <netdb.h>
#include <arpa/inet.h>
Inetaddr::Inetaddr(int port){
    ::bzero(&sockaddr,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

std::string Inetaddr::toIp() const{
    char buf[32] = "";
    ::inet_ntop(AF_INET, &sockaddr.sin_addr, buf, sizeof(buf));
    return buf;
}
    
std::string Inetaddr::toIpPort() const{
    char buf[32] = ""; // "255.255.255.255:65535" 4*4+5+1 = 22
    ::inet_ntop(AF_INET, &sockaddr.sin_addr, buf, sizeof buf);
    int end = ::strlen(buf);
    uint16_t port = portHostEndian();
    snprintf(buf + end, sizeof buf - end, ":%u", port);
    return buf;
}

static const int kResolveBufSize = 4096;

bool Inetaddr::resolve(std::string hostname, Inetaddr* out)
{
  assert(out);
  char buf[kResolveBufSize];
  struct hostent hent;
  struct hostent* he = NULL;
  int herrno = 0;
  bzero(&hent, sizeof(hent));

  int ret = gethostbyname_r(hostname.c_str(), &hent, buf, sizeof buf, &he, &herrno);
  if (ret == 0 && he != NULL)
  {
    assert(he->h_addrtype == AF_INET && he->h_length == sizeof(uint32_t));
    out->sockaddr.sin_addr = *reinterpret_cast<struct in_addr*>(he->h_addr);
    return true;
  }
  else if (ret == ERANGE)
  {
    //return resolveSlow(hostname.c_str(), out);
  }
  else
  {
    if (ret)
      perror("InetAddress::resolve");
    return false;
  }
}