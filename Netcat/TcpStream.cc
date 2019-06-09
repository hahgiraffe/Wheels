#include "TcpStream.h"
#include <errno.h>
#include "Inetaddr.h"

TcpStream::TcpStream(Socket&& sock)
  : socket(std::move(sock))
{
}



int TcpStream::receiveAll(void* buf, int len)
{
  // FIXME: EINTR
  return ::recv(socket.fd(), buf, len, MSG_WAITALL);
}
int TcpStream::sendAll(const void* buf, int len)
{
  int written = 0;
  while (written < len)
  {
    int nw = socket.write(static_cast<const char*>(buf) + written, len - written);
    if (nw > 0)
    {
      written += nw;
    }
    else if (nw == 0)
    {
      break;
    }
    else if (errno != EINTR)  // nw < 0
    {
      break;
    }
  }
  return written;
}

int TcpStream::sendSome(const void* buf, int len)
{
  // FIXME: EINTR
  return socket.write(buf, len);
}

void TcpStream::setTcpNoDelay(bool on)
{
  socket.settcpnodelay(on);
}

void TcpStream::shutdownWrite()
{
  socket.shutdownwrite();
}
int TcpStream::receiveSome(void* buf, int len){
    return socket.read(buf, len);
}

TcpStreamPtr TcpStream::connect(const Inetaddr& serverAddr)
{
  return connectInternal(serverAddr, nullptr);
}

TcpStreamPtr TcpStream::connect(const Inetaddr& serverAddr, const Inetaddr& localAddr)
{
  return connectInternal(serverAddr, &localAddr);
}

TcpStreamPtr TcpStream::connectInternal(const Inetaddr& serverAddr, const Inetaddr* localAddr)
{
  TcpStreamPtr stream;
  Socket sock(Socket::createTcp());
  if (localAddr)
  {
    sock.bindordie(*localAddr);
  }
  if (sock.connect(serverAddr) == 0)
  {
    // 还需要检测自连接
    stream.reset(new TcpStream(std::move(sock)));
  }
  return stream;
}